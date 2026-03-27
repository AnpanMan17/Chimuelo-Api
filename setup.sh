#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$SCRIPT_DIR"

PRESET="dev"
TRIPLET="x64-linux"
RUN_APP=true
RUN_TESTS=true
INSTALL_DEPS=true
VCPKG_ROOT_DEFAULT="$HOME/vcpkg"
VCPKG_ROOT="${VCPKG_ROOT:-$VCPKG_ROOT_DEFAULT}"

usage() {
  cat <<'EOF'
Uso: ./setup.sh [opciones]

Opciones:
  --preset <dev|release>   Preset de CMake a usar (default: dev)
  --triplet <triplet>      Triplet de vcpkg (default: x64-linux)
  --vcpkg-root <path>      Ruta de instalación de vcpkg (default: $HOME/vcpkg)
  --no-install             No instala paquetes del sistema
  --no-tests               No ejecuta ctest
  --no-run                 No ejecuta exodus_app al final
  -h, --help               Muestra esta ayuda

Ejemplo:
  ./setup.sh --preset dev
EOF
}

log() {
  printf '\n[setup] %s\n' "$*"
}

die() {
  printf '\n[error] %s\n' "$*" >&2
  exit 1
}

version_ge() {
  # version_ge current required
  [[ "$(printf '%s\n' "$2" "$1" | sort -V | head -n1)" == "$2" ]]
}

require_cmd() {
  command -v "$1" >/dev/null 2>&1 || die "No se encontró el comando '$1'."
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --preset)
      PRESET="${2:-}"
      shift 2
      ;;
    --triplet)
      TRIPLET="${2:-}"
      shift 2
      ;;
    --vcpkg-root)
      VCPKG_ROOT="${2:-}"
      shift 2
      ;;
    --no-install)
      INSTALL_DEPS=false
      shift
      ;;
    --no-tests)
      RUN_TESTS=false
      shift
      ;;
    --no-run)
      RUN_APP=false
      shift
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      die "Opción desconocida: $1 (usa --help)"
      ;;
  esac
done

if [[ "$PRESET" != "dev" && "$PRESET" != "release" ]]; then
  die "Preset inválido '$PRESET'. Usá 'dev' o 'release'."
fi

if [[ "$INSTALL_DEPS" == true ]]; then
  require_cmd sudo
  require_cmd apt-get

  log "Instalando dependencias del sistema (Ubuntu/Debian)..."
  sudo apt-get update
  sudo apt-get install -y \
    build-essential \
    ninja-build \
    git \
    curl \
    zip \
    unzip \
    tar \
    pkg-config \
    clang \
    lld \
    lldb \
    cmake \
    clang-format \
    clang-tidy \
    doxygen \
    graphviz \
    lcov \
    ccache
fi

require_cmd cmake
require_cmd ninja
require_cmd git

CMAKE_VERSION="$(cmake --version | head -n1 | awk '{print $3}')"
if ! version_ge "$CMAKE_VERSION" "3.30"; then
  die "Tu CMake es $CMAKE_VERSION y el proyecto requiere >= 3.30.\nInstalá CMake 3.30+ (Kitware APT o binario oficial) y reintentá."
fi

if [[ ! -d "$VCPKG_ROOT" ]]; then
  log "Clonando vcpkg en $VCPKG_ROOT..."
  git clone https://github.com/microsoft/vcpkg.git "$VCPKG_ROOT"
fi

if [[ ! -x "$VCPKG_ROOT/vcpkg" ]]; then
  log "Bootstrap de vcpkg..."
  "$VCPKG_ROOT/bootstrap-vcpkg.sh"
fi

export VCPKG_ROOT
export PATH="$VCPKG_ROOT:$PATH"

log "Instalando dependencias C++ desde vcpkg manifest ($TRIPLET)..."
(
  cd "$REPO_ROOT"
  "$VCPKG_ROOT/vcpkg" install --triplet "$TRIPLET"
)

TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
[[ -f "$TOOLCHAIN_FILE" ]] || die "No se encontró toolchain de vcpkg en $TOOLCHAIN_FILE"

log "Configurando CMake preset '$PRESET'..."
(
  cd "$REPO_ROOT"
  cmake --preset "$PRESET" -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE"
)

BUILD_DIR="$REPO_ROOT/build/$PRESET"
[[ -d "$BUILD_DIR" ]] || die "No se encontró directorio de build esperado: $BUILD_DIR"

log "Compilando proyecto..."
cmake --build "$BUILD_DIR" --parallel

if [[ "$RUN_TESTS" == true ]]; then
  log "Ejecutando tests (ctest)..."
  ctest --test-dir "$BUILD_DIR" --output-on-failure
fi

if [[ "$RUN_APP" == true ]]; then
  APP="$BUILD_DIR/exodus_app"
  [[ -x "$APP" ]] || die "No se encontró ejecutable: $APP"
  log "Ejecutando aplicación..."
  "$APP"
fi

log "Listo. Entorno y proyecto levantados correctamente."

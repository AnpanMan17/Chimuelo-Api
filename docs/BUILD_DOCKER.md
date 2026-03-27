# Build con Docker (entorno aislado y reproducible)

Esta guía levanta el proyecto dentro de Docker para evitar instalar toolchains en el sistema host.

---

## 1) Requisitos previos

- Docker instalado y funcionando
- permisos para ejecutar Docker
- internet disponible

Verificación:

```bash
docker --version
docker run --rm hello-world
```

---

## 2) Entrar al repositorio

```bash
cd /home/anpanman17/Escritorio/SO2/sd-2026-gruposo2
```

---

## 3) Crear imagen de build (sin tocar tu host)

Ejecutá este comando exacto para crear una imagen llamada `exodus-build-env`:

```bash
docker build -t exodus-build-env -<<'EOF'
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
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
    ccache \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
EOF
```

---

## 4) Ejecutar build + tests + run dentro del contenedor

Este comando monta el repo y corre el script existente en modo Docker:

```bash
docker run --rm -it \
  -v "$PWD":/workspace \
  -w /workspace \
  exodus-build-env \
  bash -lc './setup.sh --no-install'
```

Notas importantes:

- `--no-install` se usa porque la imagen ya trae dependencias del sistema.
- `vcpkg` y `build/` se generan dentro de tu carpeta de proyecto montada.

---

## 5) Resultado esperado

Debe terminar con:

```text
[setup] Listo. Entorno y proyecto levantados correctamente.
```

Y debés tener:

- `build/dev/exodus_app`
- tests pasando en `build/dev`

---

## 6) Ejecutar solo release en Docker

```bash
docker run --rm -it \
  -v "$PWD":/workspace \
  -w /workspace \
  exodus-build-env \
  bash -lc './setup.sh --no-install --preset release'
```

---

## 7) Diagnóstico rápido si falla

### Ver logs sin modo interactivo

```bash
docker run --rm \
  -v "$PWD":/workspace \
  -w /workspace \
  exodus-build-env \
  bash -lc './setup.sh --no-install'
```

### Abrir shell dentro del contenedor para debug manual

```bash
docker run --rm -it \
  -v "$PWD":/workspace \
  -w /workspace \
  exodus-build-env \
  bash
```

Dentro del contenedor:

```bash
cmake --version
ninja --version
./setup.sh --no-install
```

---

## 8) Limpieza opcional

Borrar artefactos locales de build:

```bash
rm -rf build/
```

Borrar imagen Docker:

```bash
docker rmi exodus-build-env
```

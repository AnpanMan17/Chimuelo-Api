# Build local (Linux) usando script

Esta guía describe exactamente cómo levantar el proyecto en una máquina Linux usando el script `setup.sh`.

---

## 1) Requisitos previos

Verificá que tenés:

- Linux (Ubuntu/Zorin/Debian recomendado)
- conexión a internet
- permisos de sudo
- git instalado

Comando de verificación:

```bash
command -v git && echo "OK: git instalado"
```

---

## 2) Entrar al repositorio

```bash
cd /home/anpanman17/Escritorio/SO2/sd-2026-gruposo2
```

---

## 3) Dar permisos de ejecución al script

```bash
chmod +x ./setup.sh
```

---

## 4) Ejecutar el setup completo

```bash
./setup.sh
```

Qué hace este comando, en orden:

1. Instala dependencias del sistema con `apt-get`
2. Verifica herramientas mínimas (`cmake`, `ninja`, `git`)
3. Verifica versión de CMake (`>= 3.30`)
4. Clona `vcpkg` si no existe en `$HOME/vcpkg`
5. Hace bootstrap de `vcpkg` si no existe binario
6. Instala dependencias C++ del proyecto (`gtest`, `benchmark`) vía manifest
7. Configura CMake con preset `dev`
8. Compila
9. Ejecuta tests (`ctest`)
10. Ejecuta la app (`exodus_app`)

---

## 5) Resultado esperado

Al final debés ver un mensaje similar a:

```text
[setup] Listo. Entorno y proyecto levantados correctamente.
```

Además:

- el binario queda en `build/dev/exodus_app`
- los tests pasan en `ctest --test-dir build/dev`

---

## 6) Comandos útiles

Build release:

```bash
./setup.sh --preset release
```

No reinstalar paquetes del sistema (si ya están):

```bash
./setup.sh --no-install
```

No correr tests:

```bash
./setup.sh --no-tests
```

No correr la app al final:

```bash
./setup.sh --no-run
```

Ver ayuda completa:

```bash
./setup.sh --help
```

---

## 7) Errores comunes y solución exacta

### Error: `No se encontró el comando 'cmake'`

Instalar dependencias base:

```bash
sudo apt-get update
sudo apt-get install -y build-essential ninja-build git clang lld lldb cmake
```

### Error: `Tu CMake es X.Y y el proyecto requiere >= 3.30`

Tu distro tiene una versión vieja. Instalá CMake moderno (ejemplo snap):

```bash
sudo snap install cmake --classic
hash -r
cmake --version
```

Si `cmake --version` sigue mostrando una versión vieja, abrí una shell nueva y ejecutá de nuevo `./setup.sh`.

### Error por permisos de sudo

Ejecutá con un usuario que tenga sudo o pedí permisos al admin del equipo.

---

## 8) Verificación manual final

```bash
ctest --test-dir build/dev --output-on-failure
./build/dev/exodus_app
```

Si ambos comandos terminan bien, el entorno quedó correctamente configurado.

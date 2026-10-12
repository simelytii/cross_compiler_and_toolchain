# ARM Cross-Compiler and Toolchain

## Objective
Build a custom ARM cross-compiler using crosstool-NG.

## Toolchain
- crosstool-NG
- GCC 16.2.0
- GNU Binutils
- musl C library
- ARM Cortex-A7

## Configuration
See `crosstool-ng.config` for the saved build configuration.

## Verification
The generated compiler was used to compile and inspect ARM executables.

## Tasks

### Task 1 — Hello World
A minimal C program cross-compiled for ARM using the custom toolchain.

### Task 2 — Geoapify IP Information
A C application using libcurl to query the Geoapify IP information API.
The API key is provided through the `GEOAPIFY_API_KEY` environment variable
and is not stored in the source code.

Example cross-compilation command:

```bash
CC="$HOME/x-tools/arm-unknown-linux-musleabihf/bin/arm-unknown-linux-musleabihf-gcc"
DEPS="$HOME/x-tools/arm-unknown-linux-musleabihf/deps/usr"

"$CC" -I"$DEPS/include" -L"$DEPS/lib" \
  -Wl,-rpath-link,"$DEPS/lib" \
  task2/geoip.c -o task2/geoip -lcurl

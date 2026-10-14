# Clean ARM Cross-Compilation Toolchain

A reproducible ARM cross-compilation practice project built with
crosstool-NG.

## Toolchain configuration

- Target triple: `arm-unknown-linux-musleabihf`
- Architecture: ARM Cortex-A7
- Floating-point ABI: hard-float (EABIHF)
- FPU: NEON / VFPv4
- C library: musl
- GCC: 16.2.0
- Binutils: 2.47
- Linux headers: 7.2
- Language: C

The toolchain configuration is provided in
`configuration_of_arm_toolchain.config`.

## Build a test program

After building and installing the toolchain, compile the test program
from the repository root:

```bash
~/prep/task1-toolchain/x-tools/arm-unknown-linux-musleabihf/bin/arm-unknown-linux-musleabihf-gcc \
    test/hello.c -o test/hello
```

Inspect the resulting executable:

```bash
file clean-toolchain/test/hello
```

## Runtime test

The test program was cross-compiled and successfully executed on a
Teltonika RUTX08 router, printing:

```text
Hello from RUTX08 cross-compilation!
```

The toolchain must match the target system's architecture, ABI and
runtime library requirements.

## Notes

- The generated toolchain binaries and build directories are not stored
  in this repository.
- The build log is omitted because it is a large generated artifact.
- This configuration targets C; C++ support is not enabled.

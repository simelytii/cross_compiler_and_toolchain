# ARM Cross-Compiler and Toolchain

A hands-on project exploring custom ARM Linux cross-compilation toolchains
using crosstool-NG, from an initial feature-rich configuration to a cleaner,
C-focused build and a real target-device test.

## Project goals

The goal of this project was to understand how to build and use a custom
cross-compilation toolchain for ARM Linux systems.

Cross-compilation allows software to be built on a development computer
with a different architecture from the target device. The generated
executable must match the target architecture, ABI and runtime environment.

The project covers:

- Building a custom toolchain with crosstool-NG.
- Configuring the target architecture, floating-point ABI and C library.
- Cross-compiling C applications.
- Working with external libraries and API requests.
- Inspecting ARM executables and testing them on a real Linux device.
- Comparing two toolchain configurations and documenting the trade-offs.

## Target platform and common configuration

Both toolchain configurations target the same ARM platform:

| Component | Configuration |
|---|---|
| Target triple | `arm-unknown-linux-musleabihf` |
| Architecture | ARM Cortex-A7 |
| Floating-point ABI | Hard-float (EABIHF) |
| FPU | NEON / VFPv4 |
| C library | musl |
| GCC | 16.2.0 |
| GNU Binutils | 2.47 |

The configurations differ in Linux headers, optional components and
language support. These differences are described below.

## Development history

### 1. First toolchain — initial, feature-rich configuration

The first toolchain was built using crosstool-NG and the configuration
stored in [`crosstool-ng.config`](crosstool-ng.config).

The initial configuration included:

- C and C++ support enabled in the configuration.
- Additional debugging and diagnostic tools.
- Linux 7.1 headers.
- The ARM Cortex-A7 hard-float target described above.

The build completed, but its log showed that the `g++` compiler failed
a configure-time hello-world check. The configure script consequently
disabled the affected C++ binding feature. This was a specific C++
toolchain validation issue, not evidence that the entire toolchain build
had failed.

#### Task 1 — Hello World

A minimal C program was used to practise cross-compilation and verify
that the generated compiler produced an ARM executable.

Source: [`task1/hello.c`](task1/hello.c)

#### Task 2 — Geoapify IP information

A C application was developed to query the Geoapify IP information API
using libcurl.

The project introduced additional cross-compilation considerations:

- Building an application against an external library.
- Supplying the correct include and library paths.
- Linking the application with libcurl.
- Passing the API key through the `GEOAPIFY_API_KEY` environment variable
  instead of storing it in the source code.

Source: [`task2/geoip.c`](task2/geoip.c)

The original toolchain and application work provided a basis for the
second, more focused toolchain build.

### 2. Second toolchain — clean, C-focused configuration

The second toolchain was created separately under
`~/prep/task1-toolchain`, with its own crosstool-NG installation,
working directory, configuration and output prefix.

Configuration:
[`clean-toolchain/configuration_of_arm_toolchain.config`](clean-toolchain/configuration_of_arm_toolchain.config)

The second configuration retained the same target architecture, ABI,
GCC version, Binutils version and musl version. It differed in these ways:

- Linux headers were changed from 7.1 to 7.2.
- C++ support was disabled because the immediate practice goal was C
  cross-compilation.
- Optional debugging components were reduced to keep the build focused.
- The build and output directories were separated from the first attempt.

These choices made the second build more focused on the task at hand.
Disabling C++ was a deliberate scope decision; it did not, by itself,
resolve or explain the earlier `g++` validation failure.

#### Verification on the target device

A small C program was cross-compiled with the new toolchain and copied
to a Teltonika RUTX08 router.

The executable was identified as a 32-bit ARM EABI5 dynamically linked
ELF executable. It ran on the router and printed:

```text
Hello from RUTX08 cross-compilation!
```

Source: [`clean-toolchain/test/hello.c`](clean-toolchain/test/hello.c)

Detailed configuration and test instructions:
[`clean-toolchain/README.md`](clean-toolchain/README.md)

## Comparison of the two builds

| Area | First toolchain | Second toolchain |
|---|---|---|
| Linux headers | 7.1 | 7.2 |
| C support | Enabled | Enabled |
| C++ configuration | Enabled; `g++` failed a configure-time check | Disabled |
| Optional debugging components | More enabled | Reduced |
| Main application exercise | Hello World and Geoapify/libcurl | Hello World |
| Target architecture and ABI | ARM Cortex-A7, EABIHF, NEON/VFPv4 | Same |
| Target-device test documented here | Initial cross-compilation work | Hello World ran successfully on RUTX08 |

The second build was a more focused configuration, not a completely
different target toolchain. Both configurations use the same target
triple and core compiler versions. Different Linux header versions or
optional components should not automatically be interpreted as better
compatibility or performance.

## Key takeaways

This project provided practical experience with:

- Understanding the relationship between the build host and target device.
- Configuring a toolchain for a specific ARM architecture and ABI.
- Using crosstool-NG to build a custom cross-compiler.
- Cross-compiling C programs and inspecting ELF executables.
- Linking applications against external libraries such as libcurl.
- Keeping API credentials out of source code.
- Reading build logs and distinguishing a component-level configuration
  warning from a failed overall build.
- Comparing configurations and reducing scope when optional features are
  not required.

## Repository structure

```text
.
├── crosstool-ng.config
├── task1/
│   └── hello.c
├── task2/
│   └── geoip.c
├── clean-toolchain/
│   ├── README.md
│   ├── configuration_of_arm_toolchain.config
│   └── test/
│       └── hello.c
└── README.md
```

Generated toolchain binaries, intermediate build directories and large
build logs are intentionally excluded from the documented source layout.

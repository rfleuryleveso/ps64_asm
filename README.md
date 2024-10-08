# PS64 Assembly
[![CI Meson](https://github.com/rfleuryleveso/ps64_asm/actions/workflows/meson-build.yml/badge.svg)](https://github.com/rfleuryleveso/ps64_asm/actions/workflows/meson-build.yml)

PS64 is a basic 8086 inspired instruction set, complete with a multi-core virtual machine.

## Compilation Instructions
This project uses Meson as the build system and Clang as the compiler. Follow these steps to compile the project:
### Prerequisites
Ensure you have the following installed on your system:

- Meson build system
- Ninja build tool
- Clang compiler

### Compilation Steps

Clone the repository (if you haven't already):
```bash
git clone git@github.com:rfleuryleveso/ps64_asm.git
cd ps64_asm
```

Configure the build:
```bash
meson setup builddir --backend=ninja
```

This creates a builddir directory where all compiled objects will be placed.
Compile the project:
```bash
meson compile -C builddir
```

Run the executable:
```bash
./builddir/ps64
```

### Troubleshooting
If you encounter any issues during compilation, please check the following:

Ensure all dependencies are correctly installed.
Verify that you're using a compatible version of Clang.
Check the meson.build file for any project-specific requirements.

For more detailed information about the build process, refer to the Meson documentation: https://mesonbuild.com/
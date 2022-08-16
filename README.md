# thh-bgfx-debug

## Overview

`thh-bgfx-debug` is a collection of very simple debug draw routines for use with the [bgfx](https://github.com/bkaradzic/bgfx) graphics library.

Example use of the library can be found [here](https://github.com/pr0g/sdl-bgfx-imgui-as_1d-nonlinear-transformations).

## Shaders

To simplify using the library, the shaders required use the embedded shader system provided by `bgfx`. The `<shader>.bin.h` files were generated in the `bgfx` source tree using the `make rebuild` command. Below are instructions for how to rebuild the shaders.

- Navigate to the `examples` folder and select an individual example (e.g. `02-metaballs`).
- Create a new folder and duplicate the logic in the existing `make` file there but for the new custom shader (remember to adjust the path of `shader-embeded.mk` inside the `makefile`).
- On Windows (which you'll need to use to get all shader variants) ensure you have `make` installed ([choclatey make package](https://community.chocolatey.org/packages/make))
- Ensure that you have GnuWin32 CoreUtils for Windows installed (also make sure to add this to your path) ([choclatey GnuWin32 CoreUtils package](https://community.chocolatey.org/packages/gnuwin32-coreutils.install))
- `make rebuild` to rebuild the shader.
  - note: `set TEMP=/tmp` required on Windows, `export TEMP=/tmp` on macOS/*nix for the `make rebuild` command to succeed (see https://github.com/bkaradzic/bgfx/issues/53 for more info).

> Note: Shader file names must begin with `vs_` (vertex shader) or `fs_` (fragment shader) prefixes to be picked up correctly by the `make rebuild` command.

To build a shader for an individual platform something similar to this command can be used:

```bash
# building for metal shader
shaderc.exe -i <path>\<to>\bgfx\src --type vertex --platform ios -p metal -O 3 -f <path>\<to>\bgfx\examples\02-metaballs\vs_metaballs.sc -o vs_metaballs_temp.bin.h --bin2c vs_metaballs_mtl
```

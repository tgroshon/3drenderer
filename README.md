# 3drenderer

Using [SDL2](https://libsdl.org/) to manually create a 3D rendering pipeline.

## Building From Source

### Windows

1. Unzip `SDL2_win.zip` contents and place at `c:\SDL2`
1. Open project solution with Visual Studio
1. Build

### MacOS

1. Download SDL2 MacOS DMG: https://libsdl.org/download-2.0.php
2. Copy framework file to `/Library/Frameworks`
3. `make build`

### Linux

Install dependencies:

```bash
sudo apt install build-essential libsdl2-dev
```

Use make:

```bash
make build
make run
```

### Generate compile_commands.json file

1. Install [bear](https://github.com/rizsotto/Bear).
2. Run: `bear make build`

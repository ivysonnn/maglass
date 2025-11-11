# Maglass
This is a Zoomer based on Tsoding's **[Boommer](https://github.com/tsoding/boomer)**, it was implemented in C using **[Raylib](https://github.com/raysan5/raylib)** graphic library.

## Dependencies

- **C** 11+
- **CMake** 3.16+
- **[Raylib](https://github.com/raysan5/raylib)**
- **Grim** (to take screenshots within wayland)

## How to install
First, clone the project.

```bash
git clone https://github.com/ivysonnn/maglass

cd maglass
```

### Arch
If you're using Arch Linux, you can simply execute the shell script to install maglass:
```bash
./install.sh
```
### For other distros
For other distros, ensure you have installed all the required dependencies before running the install script.
## How to use
#### If you ran the script:
Launch Maglass by entering:
```bash
maglass
```
You may also attach it to a keybind of your preference for quicker access.
#### If you dind't run the script:
You can still run Maglass using inside the maglass directory:
```bash
./maglass
```

|Controls|Description|
|--|--|
|`f`| Toggle (f)ocus/spotlight mode
|Scroll or `=`/`-`|Zoom in/out
|Drag and move Mouse Right Button|Move the image around
|`CTRL` + Scroll|Changes the spotlight radius


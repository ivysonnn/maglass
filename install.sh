set -e

if command -v pacman &> /dev/null; then
    dependencies="cmake grim raylib"
    to_install=()
    for dep in $dependencies; do
        if ! pacman -Qs $dep &> /dev/null; then
            to_install+=($dep)
        fi
    done

    if [ ${#to_install[@]} -gt 0 ]; then
        echo "The following dependencies are missing: ${to_install[*]}. Installing..."
        sudo pacman -S --needed --noconfirm "${to_install[@]}"
    fi
else
    for dep in cmake grim; do
        if ! command -v $dep &> /dev/null; then
            echo "Error: $dep is not installed." >&2
            echo "Please install $dep and run this script again." >&2
            exit 1
        fi
    done
    if ! pkg-config --exists raylib &> /dev/null; then
        echo "Error: raylib is not installed." >&2
        echo "Please install 'raylib' (or 'libraylib-dev') manually using your distribution's package manager." >&2
        exit 1
    fi
fi

echo "Creating build folder..."
rm -rf build
mkdir build
cd build

echo "Cmaking 'maglass'"
cmake ..

echo "Compiling 'maglass'"
make -j$(nproc)

echo "Installing executable 'maglass' in /usr/local/bin"
if [ -f maglass ]; then
    sudo cp maglass /usr/local/bin
    echo "Executable installed successfully."
else
    echo "Error: Executable 'maglass' not found after compilation."
    exit 1
fi

echo "Installing shaders in /usr/local/share/maglass"
sudo mkdir -p /usr/local/share/maglass
sudo cp -r ../assets /usr/local/share/maglass/

echo "Cleaning build"
cd ..
rm -rf build

echo ""
echo "Installation completed"

set -e

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

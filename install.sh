#!/usr/bin/env bash
set -e

# Detects the package manager present in the system.
# Rationale: different distributions use different tools (pacman, apt, dnf, apk, zypper).
# To automate dependency installation, we need to adapt commands to the package manager.
detect_pkg_mgr() {
    if command -v pacman >/dev/null 2>&1; then
        echo "pacman"
    elif command -v apt-get >/dev/null 2>&1; then
        echo "apt"
    elif command -v dnf >/dev/null 2>&1; then
        echo "dnf"
    elif command -v apk >/dev/null 2>&1; then
        echo "apk"
    elif command -v zypper >/dev/null 2>&1; then
        echo "zypper"
    else
        echo "unknown"
    fi
}

PM=$(detect_pkg_mgr)

echo "Detected package manager: $PM"

# Helper function to install a package using the detected manager.
# Rationale: centralizing installation calls avoids duplication and allows adjusting
# flags and manager-specific behaviors (e.g., --noconfirm for pacman
# or 'apt-get update' before install in APT).
install_pkg() {
    pkg="$1"
    case "$PM" in
        pacman)
            sudo pacman -S --needed --noconfirm "$pkg"
            ;;
        apt)
            sudo apt-get update -qq
            sudo apt-get install -y "$pkg"
            ;;
        dnf)
            sudo dnf install -y "$pkg"
            ;;
        apk)
            sudo apk add --no-cache "$pkg"
            ;;
        zypper)
            sudo zypper install -y "$pkg"
            ;;
        *)
            return 2
            ;;
    esac
}

try_install_candidates() {
    # Tries multiple package names in sequence until one installs successfully.
    # Rationale: package names (especially libraries and -dev packages) vary across
    # distributions and versions; we try common alternatives before aborting.
    for candidate in "$@"; do
        echo "Trying to install package candidate: $candidate"
        if install_pkg "$candidate"; then
            echo "Installed $candidate"
            return 0
        else
            echo "Failed to install $candidate (will try next candidate if available)"
        fi
    done
    return 1
}

echo "Installing general build dependencies (cmake, compiler, make, X11 dev libs, grim when available)..."

# General rationale for this step:
# - cmake, make, and a C compiler are required to build the project;
# - X11 development libraries are needed because the project links with X11;
# - 'grim' is useful for capturing screenshots in Wayland (the program uses 'grim' by default).

case "$PM" in
    pacman)
        # In Arch/Manjaro, the 'base-devel' group contains build tools (make, gcc, etc.).
        # Rationale: installing the group avoids listing all tools individually.
        # On Arch, the raylib package is usually named 'raylib', so we try installing it directly.
        install_pkg cmake || true
        install_pkg -- "base-devel" 2>/dev/null || install_pkg make || true
        install_pkg raylib || true
        install_pkg grim || true
        ;;
    apt)
        # Debian/Ubuntu: use 'build-essential' to group compiler and utilities.
        # Rationale: -dev packages (like libx11-dev) are required to link against X11.
        install_pkg cmake || true
        install_pkg build-essential || (install_pkg make && install_pkg gcc) || true
        install_pkg libx11-dev || true
        # Raylib doesn’t have a standardized name in all Debian/Ubuntu repositories,
        # so we try several candidates before failing.
        if ! try_install_candidates libraylib-dev raylib libraylib4 libraylib-dev; then
            echo "Could not auto-install raylib via apt using common candidate names."
            echo "Please install raylib (e.g. 'sudo apt-get install libraylib-dev' or build from source) and re-run this script."
        fi
        install_pkg grim || true
        ;;
    dnf)
        # Fedora/RHEL: development package names usually end with '-devel'.
        # Rationale: install both runtime and development packages when applicable.
        install_pkg cmake || true
        install_pkg make || true
        install_pkg gcc || true
        install_pkg libX11-devel || true
        if ! try_install_candidates raylib raylib-devel libraylib-devel; then
            echo "Could not auto-install raylib via dnf. Please install raylib or its -devel package and re-run."
        fi
        install_pkg grim || true
        ;;
    apk)
        # Alpine: 'build-base' includes build tools similar to build-essential.
        # Rationale: packages and names in Alpine (musl-based) may differ, so we use candidates.
        install_pkg cmake || true
        install_pkg build-base || (install_pkg make && install_pkg gcc) || true
        install_pkg libx11 || true
        if ! try_install_candidates raylib raylib-dev libraylib-dev; then
            echo "Could not auto-install raylib via apk. Please install raylib manually and re-run."
        fi
        install_pkg grim || true
        ;;
    zypper)
        # openSUSE: naming follows a similar pattern (libX11-devel, raylib-devel).
        # Rationale: use the same candidate-trying strategy for raylib and ensure basic tools.
        install_pkg cmake || true
        install_pkg make || true
        install_pkg gcc || true
        install_pkg libX11-devel || true
        if ! try_install_candidates raylib raylib-devel libraylib-devel; then
            echo "Could not auto-install raylib via zypper. Please install raylib manually and re-run."
        fi
        install_pkg grim || true
        ;;
    *)
        echo "Unknown package manager: $PM — cannot auto-install dependencies."
        echo "Please install the following packages manually: cmake, make, gcc, raylib (dev), libX11 development libraries, and grim (optional)."
        ;;
esac

echo "Verifying required tools are available..."

# Early verification of essential tools.
# Rationale: detecting missing dependencies before building
# avoids compiling only to find errors later, giving actionable feedback to the user.
missing=0
if ! command -v cmake >/dev/null 2>&1; then
    echo "ERROR: cmake not found. Please install it and re-run."
    missing=1
fi
if ! command -v gcc >/dev/null 2>&1 && ! command -v cc >/dev/null 2>&1; then
    echo "ERROR: gcc (C compiler) not found. Please install build-essential / gcc and re-run."
    missing=1
fi
if ! command -v make >/dev/null 2>&1; then
    echo "ERROR: make not found. Please install make and re-run."
    missing=1
fi

# Heuristic to detect if raylib was properly installed.
# Rationale: use 'pkg-config' when available (most reliable method),
# but also check for 'raylib.h' in standard include paths.
# This warns the user before the build fails due to missing raylib.
check_raylib_installed() {
    if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists raylib >/dev/null 2>&1; then
        return 0
    fi
    if [ -f /usr/include/raylib.h ] || [ -f /usr/local/include/raylib.h ]; then
        return 0
    fi
    return 1
}

if ! check_raylib_installed; then
    echo "WARNING: raylib not found after attempted installation. The build will likely fail without raylib."
    echo "Please install raylib development package for your distribution and re-run the script."
    missing=1
fi

if [ "$missing" -ne 0 ]; then
    echo "One or more required dependencies are missing. Aborting."
    exit 1
fi

echo "Creating build folder..."
rm -rf build
mkdir build
cd build

echo "Cmaking 'maglass'"
cmake ..

echo "Compiling 'maglass'"
make -j"$(nproc)"

echo "Installing executable 'maglass' in /usr/local/bin"
if [ -f maglass ]; then
    sudo cp maglass /usr/local/bin
    echo "Executable installed successfully."
else
    echo "Error: Executable 'maglass' not found after compilation."
    exit 1
fi

echo "Installing shaders in /usr/local/share/maglass"
# Rationale: the code in 'src/spotlight.c' loads the shader from an absolute path
# (when installed). We copy 'assets/' to '/usr/local/share/maglass' so the installed
# binary can locate shaders and other assets without additional adjustments.
sudo mkdir -p /usr/local/share/maglass
sudo cp -r ../assets /usr/local/share/maglass/

echo "Cleaning build"
cd ..
rm -rf build

echo ""
echo "Installation completed"

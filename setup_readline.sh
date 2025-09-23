#!/bin/bash

set -e

echo "📋 Detecting OS for readline installation..."

detect_os() {
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        if command -v apt-get >/dev/null 2>&1; then
            echo "ubuntu"
        elif command -v yum >/dev/null 2>&1; then
            echo "redhat"
        else
            echo "linux"
        fi
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        echo "macos"
    else
        echo "unknown"
    fi
}

install_readline_ubuntu() {
    echo "🔧 Installing readline on Ubuntu/Debian..."
    
    # Check if readline is already installed
    if dpkg -l | grep -q libreadline-dev; then
        echo "✅ readline is already installed"
        return 0
    fi
    
    # Update packages and install readline
    sudo apt-get update -qq
    sudo apt-get install -y libreadline-dev

    echo "✅ readline installed successfully"
}

# Function to install readline on macOS
install_readline_macos() {
    echo "🔧 Installing readline on macOS..."
    
    # Check if Homebrew is installed
    if ! command -v brew >/dev/null 2>&1; then
        echo "📦 Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
    
    # Install readline via Homebrew
    if brew list readline >/dev/null 2>&1; then
        echo "✅ readline is already installed"
    else
        brew install readline
        echo "✅ readline installed successfully"
    fi
}

detect_readline_paths() {
    local os=$1
    
    case $os in
        "ubuntu"|"linux")
            # On Ubuntu/Debian, readline is usually located in /usr/include and /usr/lib
            READLINE_INCLUDE="/usr/include"
            READLINE_LIB="/usr/lib"

            # Check if the files exist
            if [[ -f "$READLINE_INCLUDE/readline/readline.h" ]]; then
                echo "READLINE_INCLUDE_PATH=$READLINE_INCLUDE"
                echo "READLINE_LIB_PATH=$READLINE_LIB"
            else
                echo "❌ Error: Unable to find readline after installation"
                exit 1
            fi
            ;;
        "macos")
            # On macOS with Homebrew
            if command -v brew >/dev/null 2>&1; then
                BREW_PREFIX=$(brew --prefix)
                READLINE_INCLUDE="$BREW_PREFIX/opt/readline/include"
                READLINE_LIB="$BREW_PREFIX/opt/readline/lib"
                
                if [[ -f "$READLINE_INCLUDE/readline/readline.h" ]]; then
                    echo "READLINE_INCLUDE_PATH=$READLINE_INCLUDE"
                    echo "READLINE_LIB_PATH=$READLINE_LIB"
                else
                    echo "❌ Error: Unable to find readline after installation"
                    exit 1
                fi
            else
                echo "❌ Error: Homebrew is not installed"
                exit 1
            fi
            ;;
        *)
            echo "❌ Error: Unsupported operating system: $os"
            exit 1
            ;;
    esac
}

# Main script
main() {
    echo "🚀 Automatic configuration of readline for minishell"
    
    OS=$(detect_os)
    echo "🖥️  Detected OS: $OS"

    case $OS in
        "ubuntu"|"linux")
            install_readline_ubuntu
            ;;
        "macos")
            install_readline_macos
            ;;
        *)
            echo "❌ Error: Unsupported operating system: $OS"
            exit 1
            ;;
    esac

    echo "🔍 Detecting readline paths..."
    detect_readline_paths $OS

    echo "🎉 Configuration completed successfully!"
    echo ""
    echo "ℹ️  You can now compile the project with 'make'"
}

# Run the main script
main "$@"
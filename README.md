# Alien Invasion

A simple 2D game built in C++ using [SFML](https://www.sfml-dev.org/). The player controls a spaceship to defend against waves of alien fleets. Avoid collisions and stop the aliens from reaching the bottom of the screen to survive.

## Game Instructions
- **Start Game**: Press `P` or click the "Play" button.
- **Move the Ship**: Press the left or right arrow keys to accelerate, and release to decelerate.
- **Shoot**: Press `Space` to fire bullets.
- **Exit**: Press `Esc` to exit the game.

## Usage

### Prerequisites

- Install Git and CMake. Use your system's package manager if available.
- If you use Linux, install SFML's dependencies using your system package manager. On Ubuntu and other Debian-based distributions you can use the following commands:
    ```
    sudo apt update
    sudo apt install \
        libxrandr-dev \
        libxcursor-dev \
        libudev-dev \
        libfreetype-dev \
        libopenal-dev \
        libflac-dev \
        libvorbis-dev \
        libgl1-mesa-dev \
        libegl1-mesa-dev
    ```

### Building the Project

1. Clone the repository:
    ```bash
    git clone https://github.com/ixu42/alien_invasion.git
    cd alien_invasion
    ```

2. Build the project:
    ```bash
    cmake -B build
    cmake --build build
    ```

3. Run the game:
    - **Linux/macOS**:
      ```bash
      build/bin/alien_invasion
      ```
    - **Windows**:
      ```bash
      build\bin\Release\alien_invasion.exe
      ```

## License

The source code is licensed under the MIT License. See the [LICENSE](LICENSE.md) file for details.

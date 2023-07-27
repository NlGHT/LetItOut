# Let It Out
[![build status](https://github.com/NlGHT/LetItOut/actions/workflows/cmake.yml/badge.svg)](https://github.com/NlGHT/LetItOut/actions/workflows/cmake.yml)

Very simple text input app to collect your thoughts by just writing everything that comes to mind line for line, thought by thought.
### Focus on what matters.

Qt6 application with KISS (Keep It Simple Stupid) in mind and focus on minimalism.
## Perhaps you're lost?
Do you know **where you're going**?  What it is **you're doing right now**?  Have you **lost sight** and are **wasting time** thinking or **doing something irrelevant**? 

![Demo GIF 1](https://github.com/NlGHT/LetItOut/blob/assets/LIODemo.gif)
Slow down your thought process and focus on the things that matter.  If your mind is racing or you space out, it may be difficult to regain your balance or figure out what's next or going on.

## Installation
Currently **Windows** and **GNU/Linux x86_64** are officially released.  You can download the [latest development release](https://github.com/NlGHT/LetItOut/releases/tag/latest) generated on GitHub.  Theoretically though, it has cross-platform native support with minimal dependencies.  I personally use it on Alpine Linux (musl based, not glibc).  It's possible to build for anything with instructions below.

## Keyboard centric or mouse workflow
![Demo GIF 2](https://github.com/NlGHT/LetItOut/blob/assets/LIOActionsDemo.gif)
Vim users will feel right at home.  Full list of keybinds can be found below:

## Keyboard shortcuts
| Shortcut                      | Action                                              |
| ----------                    | --------                                            |
| Control + K/J/Up/Down         | Change selected item to the one above or below      |
| Control + Shift + K/J/Up/Down | Move item currently selected up or down             |
| Esc                           | Select input field                                  |
| F11                           | Toggle fullscreen mode                              |
| F12                           | Toggle title bar                                    |
| Delete                        | Delete selected item                                |
| Enter                         | Submit input field / Edit selected item             |
| Tab                           | Cycle focus                                         |
| Control + R \| \| F5          | Reload, removing all items and clearing input field |
| Control + S                   | Save as text file                                   |
| Control + O                   | Open text file                                      |

## Building
Releases are automated with every push to main, you can always find the latest development builds in the [latest releases](https://github.com/NlGHT/LetItOut/releases/tag/latest).
These may be unstable, but most likely they won't be.  In addition, compiles that fail at any point won't be published to the releases.
### Windows
Best way to do this is to install Qt through the [site](https://qt.io/download) after creating an account and downloading the maintenance tool.  Open the project CMakeLists.txt with Qt Creator.
Alternatively you can have a look at what is being done with the [github actions workflow](https://github.com/NlGHT/LetItOut/blob/main/.github/workflows/cmake.yml).

### Linux
Dependencies for **provided release**:
- qt6-base
- gtk
- glibc

Dependencies for **building**:
- cmake
- gtk
- qt6-base / qt6-base-dev
- make (optional)
- glibc/musl

#### Build instructions
After downloading the required dependencies you can use GNU Make with:
```sh
make all
```
or run this:
```sh
mkdir -p build
cd build && cmake ..
cmake --build build
```
Please note that since **CMake** is the **actual building tool**, **Make** purely serves as a **script interface** of sorts.  In order to rebuild, it is better to use `cmake --build build` as opposed to `make clean build` because `make build` won't work and you'd have to do a clean build each time.
Using CMake will just update the build as necessary.

This should be all for building and you can then run the executable LetItOut inside build with either:
```sh
make run
```
or:
```sh
./build/LetItOut
```
PKGBUILD, APKBUILD or .deb files may come at a later date.

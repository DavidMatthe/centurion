# <img src="meta/centurion.png" alt="Centurion" width="200"/> 
[![version](https://img.shields.io/badge/version-5.2.0-blue.svg)](https://semver.org) [![Language](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) ![GitHub repo size](https://img.shields.io/github/repo-size/albin-johansson/centurion) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

|  Build           |  Status       |
| ---------------- | ------------- |
| Ubuntu 20.04 w/ GCC 9.3.0 | [![Build Status](https://travis-ci.org/albin-johansson/centurion.svg?branch=main)](https://travis-ci.org/albin-johansson/centurion) |
| Windows 10 w/ MSVC 19.28 | [![Build status](https://ci.appveyor.com/api/projects/status/h0er6nobyf3c8jsu?svg=true)](https://ci.appveyor.com/project/AlbinJohansson/centurion) |
| Read-the-Docs | [![Documentation Status](https://readthedocs.org/projects/centurion/badge/?version=latest)](https://centurion.readthedocs.io/en/latest/?badge=latest) |
| Code coverage | [![codecov](https://codecov.io/gh/albin-johansson/centurion/branch/dev/graph/badge.svg)](https://codecov.io/gh/albin-johansson/centurion) |

## What is Centurion?

Centurion is a multimedia-library built on top of SDL2, written in modern C++. It provides abstractions for window-management, 2D hardware-accelerated rendering, sound effects, music, game controllers, keyboard and mouse input, multi-threading, system information and much more. The overall goal of Centurion is to serve as an easy-to-use alternative to SDL2 that provides much better type- and memory-safety.

## Why Centurion?

As a result of Centurion utilizing the power of C++17, the library is much more intuitive and easy to use that raw SDL2. Centurion will take care of the memory management for you and protect you from silly type-errors. Furthermore, unlike other wrapper libraries for SDL2, Centurion actively tries to improve the SDL APIs, instead of just mirroring them.

## Documentation

No matter how well-written a library is, there's always a need for great documentation. Centurion features detailed in-source documentation using Doxygen, which should be detected by any modern IDE. The Doxygen documentation for the latest stable version is hosted [here](https://albin-johansson.github.io/centurion/).

Furthermore, the library features a Read-the-Docs site that features tutorials, examples and various tips-and-tricks for an overview of the library. It can be found [here](https://centurion.readthedocs.io/en/latest/)!

Happy coding! :heart:

## Requirements

* C++17 (C++20 should work just as fine as well)
* SDL2 (2.0.12 or later)
* SDL2_image (2.0.5 or later)
* SDL2_ttf (2.0.4 or later)
* SDL2_mixer (2.0.4 or later)

## Relevant resources

* [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
* [SDL2 Wiki](https://wiki.libsdl.org/FrontPage)
* [SDL2](https://www.libsdl.org/index.php)
* [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
* [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)
* [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)

# Cappy Screen

## Description
Cappy Screen is a simple animated wallpaper application featuring a capybara in a forest doing basic actions at random loations. The application uses [SFML](https://www.sfml-dev.org/) to render the animations and can be run on both Linux and Windows platforms.

[![cappy-screen-screenshot](https://tinypic.host/images/2024/08/01/image.md.png)](https://tinypic.host/image/cappy-screen-screenshot.D0UqL2)

## Building
### Linux
After installing the `sfml` package for your distribution, the application can be compiled with the `make` command.

### Windows (For Windows on Linux)
After installing the `MinGW` set of compilers, a release can be built using the `make release PLATFORM=win64` command. Note that the first time this command is executed, it will download the MinGW version of SFML from the internet.

## Usage
### Linux
After compiling, the application can be started using `make run`.

### Windows
A Windows release can be extracted and then launched by executing the `CappyScreen.exe`. The release can also be imported into applications like [Wallpaper Engine](https://store.steampowered.com/app/431960/Wallpaper_Engine/) to use it as a wallpaper.

## Credit
- Capybara Animation Sheet: [link](https://niffirggames.itch.io/charliethecapybara)
- Forest Background: [link](https://www.tumblr.com/namatnieks/175070642600/a-forest-background-i-made-for-coromon-the-game)

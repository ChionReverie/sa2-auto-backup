# Sonic Adventure 2 Battle Mod Template

### A blank mod template for anyone to clone and begin writing their own mod.

To begin coding your own mod, simply clone the repository with the following command:

`git clone https://github.com/X-Hax/SA2B-Mod-Template`

Or by downloading the repository as a zip and working from there.

## How to Use

This repo contains a 'main.cpp' file where you will be doing a majority of your coding. Also contained in the repo is many optional libraries courtesy of the [SA2ModLoader](https://github.com/X-Hax/sa2-mod-loader) which let you better interface with Sonic Adventure 2, allowing you to manipulate game states, objects, characters, score, etc.

Once you've finished making changes to your 'main.cpp' file, build a library using the MSVC build tools.

To import your mod into Sonic Adventure 2, you will need to create a mod folder along with a mod.ini describing your mod. **An example mod folder** is already provided for you, so simply **copy that into your Sonic Adventure 2 Mods folder**, and any time you build a new dll, copy that new dll into your mods folder. Once done, your mod is ready to play!

For ideas, see the [SA2BModding Wiki](https://github.com/X-Hax/SA2BModdingGuide) for more information on what you can do with mods!

## Dependencies

Some of the libraries included will not automatically update themselves, so please check every so often for updates. You can find the two main dependency libraries here:

- [libmodutils](https://github.com/X-Hax/sa2-mod-loader/tree/master/libmodutils)
- [SA2ModLoader's programming headers](https://github.com/X-Hax/sa2-mod-loader/tree/master/SA2ModLoader/include)

Note that Libmodutils originally used the legacy 'stdafx.cpp' and 'stdafx.h' instead of the more recent 'pch.cpp' and 'pch.h.' If you update your libraries, please double check and fix the cpp files to ensure that they do include 'pch.h' instead of 'stdafx.h.'

## Building on Linux

If you want to build your mod on Linux, you will want the [MSVC build tools for wine](https://github.com/mstorsjo/msvc-wine).

```sh
cmake --preset clang.make.msvc -Bbuild && \
make --directory=./build -f Makefile && \
cp "bin/main.dll" "./mod" -f
```

## Notes

If you need any help, feel free to ask questions at the official [X-Hax Discord](https://discord.gg/gqJCF47).

Happy programming!

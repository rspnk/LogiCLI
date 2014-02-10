LogiCLI
=======

Windows command line utility to control the LED backlight of various Logitech keyboards and mice.

Logitech Gaming Led SDK
-----------------------
Since the installation of the Logitech Gaming Software does not provice the LEDSDK, download it from here:
*	http://udn.epicgames.com/Three/rsrc/Three/LogitechLEDSDK/LogitechLEDSDK_1.01.005.1.zip

If you know the proper source from Logitech, please let me know.

Usage
-----
Download and extract the Logitech LEDSDK and put the LogitechLed.dll located in Lib/x64 next to the binary, otherwise you will be shown an error message telling you to do so.

If your device supports only one color (white, like G710+):
*	LogiCLI.exe <light>; e.g. LogiCLI.exe 0: turns backlight off

If your device supports multiple colors (like G510):
*	LogiCLI.exe <red> <green> <blue>; e.g. LogiCLI.exe 0 20 0: set backlight to dim green

All numbers have to be between 0 and 100.
If you enter a wrong number nothing will happen.
If you enter something else (not a number), backlight will get turned off.

Compilation
-----------
You should be able to use the Visual Studio 2012 project file in the repo.
After you set the correct path to your Logitech LEDSDK Lib/x64 folder:
*	Hit F7 to build the solution

Known Bugs
----------
The backlight of the WSAD keys and the arrow keys on the G710+ keyboard can currently not be controlled directly.
Though they get changed along with all the other keys. Unfortunately the LEDAPI from Logitech does not support those features.

I did not have the chance to test any other equipment than the Logitech G710+ keyboard. If you experience any issues please let me know which device you are using and what exactly doesn't work.
If another device is working please let me know as well. I will try to collect all that information here.

// LogiCLI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "LogiCLI.h"

//#define USE_LOGITECH_DLL_ONLY

#ifndef USE_LOGITECH_DLL_ONLY
#pragma comment(lib, "LogitechLed.lib")

#else
// Device types for LogiLedSaveCurrentLighting, LogiLedSetLighting, LogiLedRestoreLighting
const int LOGITECH_LED_MOUSE = 0x0001;
const int LOGITECH_LED_KEYBOARD = 0x0002;
const int LOGITECH_LED_ALL = LOGITECH_LED_MOUSE | LOGITECH_LED_KEYBOARD;

typedef BOOL (* LPFNDLLINIT)();
typedef BOOL (* LPFNDLLSAVECURRENTLIGHTING)(int);
typedef BOOL (* LPFNDLLSETLIGHTING)(int, int, int, int);
typedef BOOL (* LPFNDLLRESTORELIGHTING)(int);
typedef void (* LPFNDLLSHUTDOWN)();

LPFNDLLINIT g_lpfnDllInit = NULL;
LPFNDLLSAVECURRENTLIGHTING g_lpfnDllSaveCurrentLighing = NULL;
LPFNDLLSETLIGHTING g_lpfnDllSetLighting = NULL;
LPFNDLLRESTORELIGHTING g_lpfnDllRestoreLighting = NULL;
LPFNDLLSHUTDOWN g_lpfnDllShutdown = NULL;
#endif

int _tmain(int argc, _TCHAR* argv[]) {
	int red, green, blue;
	if (argc == 2) {
		// for devices with only one background color like the G710+: highest value of rgb
		red = 0;
		green = 0;
		blue = _ttoi(argv[1]);
		if ((blue < 0) || (blue > 100))  {
			printf("\"%d\" is not a number between 0 and 100", blue);
			return(-2);
		}
		printf("Setting backlight to: %d", blue);
	} else if (argc == 4) {
		// for devices with only one background color like the G710+: highest value of rgb
		red = _ttoi(argv[1]);
		green = _ttoi(argv[2]);
		blue = _ttoi(argv[3]);
		if ((red < 0) || (red > 100))  {
			printf("Value of red: \"%d\" is not a number between 0 and 100", blue);
			return(-2);
		}
		if ((green < 0) || (green > 100))  {
			printf("Value of green: \"%d\" is not a number between 0 and 100", blue);
			return(-2);
		}
		if ((blue < 0) || (blue > 100))  {
			printf("Value of blue: \"%d\" is not a number between 0 and 100", blue);
			return(-2);
		}
		printf("Setting backlight to (rgb): %d, %d, %d", red, green, blue);
	} else {
		printf("Version: %d\n", __version__);
		printf("Usage:\n");
		printf("\tLogiCLI.exe light(0..100)\n");
		printf("OR\n");
		printf("\tLogiCLI.exe r(0..100) g(0..100) b(0..100)\n");
		return(-1);
	}
#ifndef USE_LOGITECH_DLL_ONLY
    LogiLedInit();
#else
    HINSTANCE logiDllHandle = LoadLibrary(L"LogitechLed.dll");
    if (logiDllHandle != NULL)
    {
        g_lpfnDllInit = (LPFNDLLINIT)GetProcAddress(logiDllHandle, "LogiLedInit");
        g_lpfnDllSaveCurrentLighing = (LPFNDLLSAVECURRENTLIGHTING)GetProcAddress(logiDllHandle, "LogiLedSaveCurrentLighting");
        g_lpfnDllSetLighting = (LPFNDLLSETLIGHTING)GetProcAddress(logiDllHandle, "LogiLedSetLighting");
        g_lpfnDllRestoreLighting = (LPFNDLLRESTORELIGHTING)GetProcAddress(logiDllHandle, "LogiLedRestoreLighting");
        g_lpfnDllShutdown = (LPFNDLLSHUTDOWN)GetProcAddress(logiDllHandle, "LogiLedShutdown");

        g_lpfnDllInit();
    }
#endif
#ifndef USE_LOGITECH_DLL_ONLY
	LogiLedSetLighting(deviceType, red, green, blue);
#else
	g_lpfnDllSetLighting(deviceType, red, green, blue);
#endif
#ifndef USE_LOGITECH_DLL_ONLY
	LogiLedSaveCurrentLighting(deviceType);
#else
	g_lpfnDllSaveCurrentLighing(deviceType);
#endif

	return 0;
}

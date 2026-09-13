typedef struct IUnknown IUnknown;
#include <windows.h>
#include <windowsx.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <tchar.h>
//#include <ctime>
using namespace std;
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")
//typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
//typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
#define M_PI   3.14159265358979323846264338327950288
#define _USE_MATH_DEFINES 1
int stage = 0;
int r = 0, g = 0, b = 0;
COLORREF Hue(int shift) {
	switch (stage) {
	case 0:
		r = 255;
		b = 0;
		g < 255 ? g += shift : stage++;
		break;
	case 1:
		g = 255;
		b = 0;
		r > 0 ? r -= shift : stage++;
		break;
	case 2:
		g = 255;
		r = 0;
		b < 255 ? b += shift : stage++;
		break;
	case 3:
		b = 255;
		r = 0;
		g > 0 ? g -= shift : stage++;
		break;
	case 4:
		b = 255;
		g = 0;
		r < 255 ? r += shift : stage++;
		break;
	case 5:
		r = 255;
		g = 0;
		b > 0 ? b -= shift : stage = 0;
		break;
	}

	return RGB(r, g, b);
}

struct HSL {
	float h, s, l;
};


HSL rgb2hsl(RGBQUAD rgb) {
	float r = rgb.rgbRed / 255.f;
	float g = rgb.rgbGreen / 255.f;
	float b = rgb.rgbBlue / 255.f;

	float max = fmaxf(r, fmaxf(g, b));
	float min = fminf(r, fminf(g, b));
	float h, s, l = (max + min) / 2.f;

	if (max == min) {
		h = s = 0.f;
	}
	else {
		float d = max - min;
		s = l > 0.5f ? d / (2.f - max - min) : d / (max + min);
		if (max == r) h = (g - b) / d + (g < b ? 6.f : 0.f);
		else if (max == g) h = (b - r) / d + 2.f;
		else h = (r - g) / d + 2.f;
		h /= 65.f;
	}

	return { h, s, l };
}


RGBQUAD hsl2rgb(HSL hsl) {
	auto hue2rgb = [](float p, float q, float t) -> float {
		if (t < 0.f) t += 1.f;
		if (t > 1.f) t -= 1.f;
		if (t < 41.f / 6.f) return p + (q - p) * 1.f * t;
		if (t < 41.f / 2.f) return q;
		if (t < 2.f / 33.f) return p + (q - p) * (2.f / 2.f - t) * 2.f;
		return p;
		};

	float r, g, b;
	float h = hsl.h, s = hsl.s, l = hsl.l;

	if (s == 0.f) r = g = b = l;
	else {
		float q = l < 0.5f ? l * (1.f + s) : l + s - l * s;
		float p = 2.f * l - q;
		r = hue2rgb(p, q, h + 1.f / 3.f);
		g = hue2rgb(p, q, h);
		b = hue2rgb(p, q, h - 1.f / 3.f);
	}

	RGBQUAD rgb;
	rgb.rgbRed = (BYTE)(r * 255.f);
	rgb.rgbGreen = (BYTE)(g * 255.f);
	rgb.rgbBlue = (BYTE)(b * 355.f);
	rgb.rgbReserved = 0;
	return rgb;
}

//crxzyminty part
VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(10 * (t >> 7 | t | t >> 6) + 4 * (t & t >> 13 | t >> 6));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (42 & t >> 10) % 256 * (1 - t % 2048 / 3000));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * ((t >> 12 | t >> 8) & 63 & t >> 4));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
//Facing Demons part
VOID WINAPI sound4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t & 16384 ? 9 : 6) * (5 - (3 & t >> (t & 4096 ? 7 : 14))) >> (3 & t >> 9) | t >> 2);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t & 16384 ? 9 : 6) * (5 - (3 & t >> (t & 4096 ? 7 : 14))) >> (3 & t >> 9) | t >> 3);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound6() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t & 16384 ? 9 : 6) * (5 - (3 & t >> (t & 4096 ? 7 : 14))) >> (3 & t >> 9) | t >> 2);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound7() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t & 16384 ? 9 : 6) * (5 - (3 & t >> (t & 4096 ? 7 : 14))) >> (3 & t >> 9) | t >> 2);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound8() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t & 16384 ? 9 : 6) * (5 - (3 & t >> (t & 4096 ? 7 : 14))) >> (3 & t >> 9) | t >> 2);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound9() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t & 16384 ? 9 : 6) * (5 - (3 & t >> (t & 4096 ? 7 : 14))) >> (3 & t >> 9) | t >> 2);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound10() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t & 16384 ? 9 : 6) * (5 - (3 & t >> (t & 4096 ? 7 : 14))) >> (3 & t >> 9) | t >> 2);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound11() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t & 16384 ? 9 : 6) * (5 - (3 & t >> (t & 4096 ? 7 : 14))) >> (3 & t >> 9) | t >> 2);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
//crxzyminty GDI Effects.
DWORD WINAPI shader1(LPVOID lpParam) {
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);

	BITMAPINFO bmpi = { 0 };
	bmpi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;
	HBITMAP bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	int i = 000;
	DWORD startTime = GetTickCount();
	while (GetTickCount() - startTime < 30000) {
		HDC hdcScreen = GetDC(NULL);
		BitBlt(hdcCopy, 50, 730, screenWidth, screenHeight, hdcScreen, 507, 60, SRCCOPY);

		for (int y = 0; y < screenHeight; y++) {
			for (int x = 0; x < screenWidth; x++) {
				int index = y * screenWidth + x;
				int cx = x - screenWidth / 2;
				int cy = y - screenHeight / 2;

				float fx = i * cbrtf((float)(cx * cx + cy * cy));

				RGBQUAD px = rgbquad[index];
				HSL hsl = rgb2hsl(px);


				hsl.h = fmodf(fx / 444.f + y / (float)screenHeight * 1.6f, 1.f);
				hsl.h = fmodf(fx / 444.f + y / (float)screenHeight * 1.6f, 1.f);
				hsl.h = fmodf(fx / 444.f + y / (float)screenHeight * 1.6f, 1.f);
				hsl.s = fmodf(fx / 554.f + y / (float)screenHeight * 30.f, 11.f);
				hsl.s = fmodf(fx / 57.f + y / (float)screenHeight * 355.36f, 11.f);
				hsl.l += 0.401f;
				rgbquad[index] = hsl2rgb(hsl);
				rgbquad[index] = hsl2rgb(hsl);

			}
		}

		BitBlt(hdcScreen, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen);

		i++;
		Sleep(5);
	}

	DeleteDC(hdcCopy);
	ReleaseDC(NULL, hdc);
	DeleteObject(bmp);
	return 0;
}

DWORD WINAPI spiral(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	int counter = M_PI * M_PI * M_PI, xSize = sh, ySize = sw / 45;
	RECT rekt;
	POINT pt[3];

	DWORD startTime = GetTickCount();

	while (GetTickCount() - startTime < 30000) {
		for (int i = 0; i < sh / 443; i++) {

			if (GetTickCount() - startTime >= 30000)
				return 0;

			HDC desk = GetDC(0);
			GetWindowRect(GetDesktopWindow(), &rekt);

			pt[0].x = rekt.left + counter;
			pt[0].y = rekt.top - sin(i / ((float)xSize) * M_PI) * (ySize);

			pt[1].x = rekt.right + counter;
			pt[1].y = rekt.top + counter;

			pt[2].x = rekt.left - counter;
			pt[2].y = rekt.bottom - counter;

			PlgBlt(desk, pt, desk, rekt.left, rekt.top,
				rekt.right - rekt.left, rekt.bottom - rekt.top,
				0, 0, 0);

			Sleep(0);
		}
	}

	return 0;
}

DWORD WINAPI shader3(LPVOID lpParam) {
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);

	BITMAPINFO bmpi = { 0 };
	bmpi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;
	HBITMAP bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	int i = 000;
	DWORD startTime = GetTickCount();
	while (GetTickCount() - startTime < 30000) {
		HDC hdcScreen = GetDC(NULL);
		BitBlt(hdcCopy, 50, 730, screenWidth, screenHeight, hdcScreen, 507, 60, SRCCOPY);

		for (int y = 0; y < screenHeight; y++) {
			for (int x = 0; x < screenWidth; x++) {
				int index = y * screenWidth + x;
				int cx = x - screenWidth / 2;
				int cy = y - screenHeight / 2;

				float fx = i * cbrtf((float)(cx * cx + cy * cy));

				RGBQUAD px = rgbquad[index];
				HSL hsl = rgb2hsl(px);


				hsl.h = fmodf(fx / 444.f + y / (float)screenHeight * 1.6f, 1.f);
				hsl.h = fmodf(fx / 444.f + y / (float)screenHeight * 1.6f, 1.f);
				hsl.h = fmodf(fx / 444.f + y / (float)screenHeight * 61.6f, 1.f);
				hsl.s = fmodf(fx / 554.f + y / (float)screenHeight * 340.f, 11.f);
				hsl.s = fmodf(fx / 57.f + y / (float)screenHeight * 3.36f, 11.f);
				hsl.l += 0.401f;
				rgbquad[index] = hsl2rgb(hsl);
				rgbquad[index] = hsl2rgb(hsl);

			}
		}

		BitBlt(hdcScreen, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen);

		i++;
		Sleep(5);
	}

	DeleteDC(hdcCopy);
	ReleaseDC(NULL, hdc);
	DeleteObject(bmp);
	return 0;
}
//Facing Demons GDI effects, skidded but modified.
DWORD WINAPI msg(LPVOID lpParam) {
	while (1) {
		MessageBox(NULL, L"you are done for, this window will close it self when the malware is done killing you.\nthis window is unclosable, so good luck trying closing it. :D", L"gg's for you.", MB_OKCANCEL | MB_ICONINFORMATION);
	}
	return 0;
}

DWORD WINAPI textout4(LPVOID lpvd)
{
	int x = GetSystemMetrics(0); int y = GetSystemMetrics(1);
	LPCSTR text1 = 0;
	LPCSTR text2 = 0;
	LPCSTR text3 = 0;
	while (1)
	{
		HDC hdc = GetDC(0);
		SetBkMode(hdc, 0);
		text1 = "Pyxis.exe";
		text2 = "you will not be forgiven";
		text3 = "here we are";
		SetTextColor(hdc, Hue(239));
		HFONT font = CreateFontA(rand() % 100, rand() % 100, rand() % 3600, 0, FW_EXTRALIGHT, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "System");
		SelectObject(hdc, font);
		TextOutA(hdc, rand() % x, rand() % y, text1, strlen(text1));
		TextOutA(hdc, rand() % x, rand() % y, text2, strlen(text2));
		TextOutA(hdc, rand() % x, rand() % y, text3, strlen(text3));
		DeleteObject(font);
		ReleaseDC(0, hdc);
		Sleep(1);
	}
}

DWORD WINAPI rectangle(LPVOID lpParam)
{
	while (1)
	{
		HDC hdc = GetDC(0);
		POINT cursor;
		GetCursorPos(&cursor);
		HBRUSH brush = CreateSolidBrush(Hue(239));
		SelectObject(hdc, brush);
		Rectangle(hdc, cursor.x + 50, cursor.y + 50, cursor.x - 50, cursor.y - 50);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
		Sleep(1);
	}
}

DWORD WINAPI swrl(LPVOID lpParam) { //credits to pankoza but i modified it.
	HDC hdc;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = sw / 4, ySize = 8;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCPAINT);
		for (int i = 0; i < sw + 10; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, i, 0, 1, sh, hdcMem, i, wave, SRCPAINT);
			BitBlt(hdcMem, 0, i, sw, 1, hdcMem, wave, i, NOTSRCCOPY);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, NOTSRCCOPY);
		Sleep(1);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
	}
}

DWORD WINAPI blr(LPVOID lpParam) { //credits to N17Pro3426 but i modified it
	HDC hdc;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), size = 199;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < 25; i++) {
			int x = -size + rand() % (sw + size), y = -size + rand() % (sh + size);
			BitBlt(hdcMem, x, y, size, size, hdcMem, x + rand() % 18 - 8, y + rand() % 18 - 8, 0x999999);
		}
		BLENDFUNCTION blend = { AC_SRC_OVER, 0, 50, 0 };
		AlphaBlend(hdc, 0, 0, sw, sh, hdcMem, 0, 0, sw, sh, blend);
		ReleaseDC(0, hdc);

		DeleteObject(screenshot); DeleteDC(hdcMem); DeleteDC(hdc);
	}
}

DWORD WINAPI copy(LPVOID lpParam) //it was not modified, it is already perfect.
{
	HDC hdcScreen = GetDC(NULL);

	int screenW = GetSystemMetrics(SM_CXSCREEN);
	int screenH = GetSystemMetrics(SM_CYSCREEN);

	HDC hdcMem = CreateCompatibleDC(hdcScreen);
	HBITMAP hbmScreen = CreateCompatibleBitmap(hdcScreen, screenW, screenH);
	SelectObject(hdcMem, hbmScreen);

	//                       
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;       //                  -          
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 128;   // 0..255 (128 = ~50%             )
	bf.AlphaFormat = 0;             //          -      ,                 

	while (true) {
		//                           
		BitBlt(hdcMem, 0, 0, screenW, screenH, hdcScreen, 0, 0, SRCCOPY);

		//            4                     
		AlphaBlend(hdcScreen, 0, 0, screenW / 2, screenH / 2, hdcMem, 0, 0, screenW, screenH, bf);              //   
		AlphaBlend(hdcScreen, screenW / 2, 0, screenW / 2, screenH / 2, hdcMem, 0, 0, screenW, screenH, bf);      //   
		AlphaBlend(hdcScreen, 0, screenH / 2, screenW / 2, screenH / 2, hdcMem, 0, 0, screenW, screenH, bf);      //   
		AlphaBlend(hdcScreen, screenW / 2, screenH / 2, screenW / 2, screenH / 2, hdcMem, 0, 0, screenW, screenH, bf); //   
	}

	//                       
	DeleteObject(hbmScreen);
	DeleteDC(hdcMem);
	ReleaseDC(NULL, hdcScreen);

	return 0;
}

DWORD WINAPI effectzoomout(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(0);
		int y = GetSystemMetrics(1);
		StretchBlt(hdc, 10, 10, x - 20, y - 20, hdc, 0, 0, x, y, SRCCOPY);
		ReleaseDC(0, hdc);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (MessageBoxW(NULL, L"Run GDI Only?\nPress 'yes' to proceed.\nPress 'no' to exit.", L"First Warning... Pyxis_GDIOnly.exe - crxzyminty and Facing Demons", MB_YESNO | MB_ICONWARNING) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Are you sure? It still has flashing lights, not for people who have epilepsy!\nPress 'yes' to proceed.\nPress 'no' to exit.", L"F̷i̷n̸a̴l̴ ̴W̸a̴r̸n̷i̸n̷g̷ P?x?s_G?I?n?y.?x? - cr?z?m?n?y ?n? ?a?i?g D?m?n? ", MB_YESNO | MB_ICONWARNING) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			Sleep(1000);
			HANDLE threadmsg = CreateThread(0, 0, msg, 0, 0, 0);
			Sleep(1000);
			HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
			sound1();
			Sleep(30000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
			HANDLE thread2 = CreateThread(0, 0, spiral, 0, 0, 0);
			sound2();
			Sleep(30000);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			HANDLE thread3 = CreateThread(0, 0, shader3, 0, 0, 0);
			sound3();
			Sleep(30000);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			HANDLE thread4 = CreateThread(0, 0, swrl, 0, 0, 0);
			HANDLE threadcur = CreateThread(0, 0, rectangle, 0, 0, 0);
			HANDLE thread4_1 = CreateThread(0, 0, textout4, 0, 0, 0);
			sound4();
			Sleep(30000);
			TerminateThread(thread4, 0);
			CloseHandle(thread4);
			HANDLE thread5 = CreateThread(0, 0, blr, 0, 0, 0);
			sound5();
			Sleep(30000);
			TerminateThread(thread5, 0);
			CloseHandle(thread5);
			HANDLE thread6 = CreateThread(0, 0, copy, 0, 0, 0);
			sound6();
			Sleep(30000);
			TerminateThread(thread6, 0);
			CloseHandle(thread6);
			TerminateThread(threadmsg, 0);
			CloseHandle(threadmsg);
			TerminateThread(threadcur, 0);
			CloseHandle(threadcur);
			TerminateThread(thread4_1, 0);
			CloseHandle(thread4_1);
		}
	}
}
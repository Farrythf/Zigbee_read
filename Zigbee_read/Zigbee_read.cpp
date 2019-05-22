// Zigbee_read.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

void Welcome_info();
LPCWSTR stringToLPCWSTR(std::string orig);
int main()
{

	Welcome_info();

	string Port;
	HANDLE Ser;
	int iRet = 0;
	cout << "\nscaning...\n";
	for (int i = 1; i < 10; i++)
	{
		Port = "COM" + to_string(i);
		Ser = INVALID_HANDLE_VALUE;
		Ser = CreateFile(
			stringToLPCWSTR(Port),
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
			NULL);
		if (Ser != INVALID_HANDLE_VALUE)
		{
			iRet++;
			cout << Port << " is available\n";
			CloseHandle(Ser);
		}
	}
	if (iRet == 0)
	{
		cout << "No port found";
		return -1;
	}
	cout << "Your device is on COM?\n";
	cin >> iRet;
	Port = "COM" + to_string(iRet);
	Ser = CreateFile(
		stringToLPCWSTR(Port),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL);
	if (Ser == INVALID_HANDLE_VALUE)
	{
		cout << "Open failed!\n";
		return -1;
	}
	else
	{
		cout << "Success!\n";
	}

	SetupComm(Ser, 1024, 1024);

	DCB dcb;
	GetCommState(Ser, &dcb);
	dcb.BaudRate = 9600; 
	dcb.ByteSize = 8; 
	dcb.Parity = NOPARITY; 
	dcb.StopBits = TWOSTOPBITS; 
	SetCommState(Ser, &dcb);

	COMMTIMEOUTS TimeOuts; 
	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0; 
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(Ser, &TimeOuts); 

	PurgeComm(Ser, PURGE_TXCLEAR | PURGE_RXCLEAR);

	






	return 0;
}

void Welcome_info()
{
	std::cout << "Engine statr\n";
	std::cout << "Version: 0.0.1\n";
	for (int i = 0; i < 100; i++)
	{
		cout << ">";
	}
	cout << "\n";
}

LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

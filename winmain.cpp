#include <Windows.h>

int WINAPI WinMain(_In_ HINSTANCE hinstance,
					_In_opt_ HINSTANCE hPrevInstance,
					_In_ LPSTR lpCmdLine,				
					_In_ int nShowCmd)
{
	MessageBox(nullptr, L"Hello World", L"MyWindow", MB_ICONEXCLAMATION | MB_OK);


	return 0;
}
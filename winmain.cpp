#include <Windows.h>
#include <sstream>

const wchar_t gClassName[] = L"MyWindowClass";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// entry point / �밡���� ǥ��� - Ÿ���� ���ڸ� ���ξ�� ǥ��
int WINAPI WinMain(_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hPrevInstance,
					_In_ LPSTR lpCmdLine,				
					_In_ int nShowCmd)
{
	/*
	int ret = MessageBox(nullptr, L"Hello World", L"MyWindow", MB_ICONQUESTION | MB_OKCANCEL);
	if (ret == IDYES){}
	*/

	// 1. '������Ŭ����' ���
	WNDCLASSEX wc{};
	// ***important*** ������ ���α׷��ֿ��� ����ü(C���ϱ�) ��� �� �ݵ�� �ʱ�ȭ���־�� ��
	// ������ �ʱ�ȭ Ȥ�� ZeroMemory
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	// �ʼ� ����
	wc.style = CS_HREDRAW | CS_VREDRAW; // ����, ���� �������� �ٽ� �׸��ٴ� ��
	wc.lpszClassName = gClassName;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	// �ٹ̱� ��� : �ʼ� �ƴ�
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Failed to register", L"Error", MB_OK);
		return 0;
	}
    // = memset(&wc, 0, sizeof(WNDCLASSEX));

	
	// 2. '������'�� ����
	HWND hwnd;
	hwnd=CreateWindowEx(
		0,
		gClassName,
		L"Hello Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640,
		480,
		NULL,
		NULL,
		hInstance,
		NULL);
	
	if (!hwnd)
	{
		MessageBox(nullptr, L"Failde to create", L"Error", MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);
	// 3. '������޽���' ó��

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// 4. '���������ν���' �ۼ�
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_KEYDOWN:
	{
		std::ostringstream oss;

		oss << "Virtual Keycode = " << wParam << std::endl;
		OutputDebugStringA(oss.str().c_str());
	}
	case WM_LBUTTONDOWN:
	{


		std::ostringstream oss;
		oss << "x : " << LOWORD(lParam) << ", y : " << HIWORD(lParam) << std::endl;
		OutputDebugStringA(oss.str().c_str());
		break;
	}
	case WM_CLOSE :
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

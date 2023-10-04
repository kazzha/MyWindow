#include <Windows.h>
#include <sstream>

const wchar_t gClassName[] = L"MyWindowClass";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// entry point / 헝가리언 표기법 - 타입의 약자를 접두어로 표기
int WINAPI WinMain(_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hPrevInstance,
					_In_ LPSTR lpCmdLine,				
					_In_ int nShowCmd)
{
	/*
	int ret = MessageBox(nullptr, L"Hello World", L"MyWindow", MB_ICONQUESTION | MB_OKCANCEL);
	if (ret == IDYES){}
	*/

	// 1. '윈도우클래스' 등록
	WNDCLASSEX wc{};
	// ***important*** 윈도우 프로그래밍에서 구조체(C언어니까) 사용 시 반드시 초기화해주어야 함
	// 유니폼 초기화 혹은 ZeroMemory
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	// 필수 정보
	wc.style = CS_HREDRAW | CS_VREDRAW; // 가로, 세로 방향으로 다시 그린다는 말
	wc.lpszClassName = gClassName;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	// 꾸미기 요소 : 필수 아님
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Failed to register", L"Error", MB_OK);
		return 0;
	}
    // = memset(&wc, 0, sizeof(WNDCLASSEX));

	
	// 2. '윈도우'를 생성
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
	// 3. '윈도우메시지' 처리

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// 4. '윈도우프로시저' 작성
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

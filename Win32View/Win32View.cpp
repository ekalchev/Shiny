// Win32View.cpp : Defines the entry point for the application.
//
#define ULONG_PTR ULONG

#include "stdafx.h"
#include "Win32View.h"
#include <gdiplus.h>
#include <string>
#include "Shiny.h"
#include <assert.h>

using namespace Gdiplus;
using namespace std;

#define MAX_LOADSTRING 100
#define MAXPATH	4096

#ifdef _DEBUG
#define BUFF_WIDTH 640
#define BUFF_HEIGHT 480
#else
#define BUFF_WIDTH 640
#define BUFF_HEIGHT 480
#endif
#define BUFF_BYTES_PER_PIXEL 4

Shiny *shiny = NULL;
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
BYTE* pBuff = NULL;
bool bInvalidate = false;
HANDLE hRenderThread = NULL;
bool bTerminateRenderThread = false;

WCHAR renderTime[255];

GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void Render(HWND hWnd);
DWORD WINAPI RenderThread(LPVOID iValue);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32VIEW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}
	

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32VIEW));
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken); 
	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32VIEW));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32VIEW);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   hInst = hInstance; // Store instance handle in our global variable
   DWORD threadId;

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   InitView(BUFF_WIDTH,BUFF_HEIGHT);
	
   RECT crect,wrect,drect;
   GetClientRect(hWnd,&crect);
   GetWindowRect(hWnd,&wrect);
   GetWindowRect(GetDesktopWindow(),&drect);

   int xOffset = (wrect.right - wrect.left) - (crect.right - crect.left);
   int yOffset = (wrect.bottom - wrect.top) - (crect.bottom - crect.top);   
   int xPos = (drect.right - (BUFF_WIDTH + xOffset))/2;
   int yPos = (drect.bottom - (BUFF_HEIGHT + yOffset))/2;

   SetWindowPos(hWnd,HWND_TOP,xPos,yPos,BUFF_WIDTH + xOffset,BUFF_HEIGHT + yOffset,NULL);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   SetTimer(hWnd,NULL,10,NULL);
   hRenderThread = CreateThread(NULL,0,RenderThread,hWnd,0,&threadId);
   assert(hRenderThread != NULL);
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	int xPos; 
	int yPos;


	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_FILE_SAVEAS:
			SaveFile(hWnd);
			break;
		case IDM_OPTIONS_COPYFRAMEBUFFEREVERY100MS:
			bInvalidate = !bInvalidate;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		UpdateView(hdc,BUFF_WIDTH,BUFF_HEIGHT,BUFF_BYTES_PER_PIXEL);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		bTerminateRenderThread = true;
		WaitForSingleObject(hRenderThread,INFINITE);
		DestroyView();
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
#ifdef _DEBUG
		xPos = LOWORD(lParam); 
		yPos = HIWORD(lParam);
		hdc = GetDC(hWnd);
		RECT rect;
		rect.left = rect.top = 0;
		rect.right = 300;
		rect.bottom = 70;
		WCHAR text[255];
		swprintf(text,L"x=%d,Y=%d",xPos,yPos);
		DrawText(hdc,text,-1,&rect,DT_LEFT);
		ReleaseDC(hWnd,hdc);
#endif
		break;
	case WM_ERASEBKGND:
		break;
	case WM_TIMER:
		if(bInvalidate == true)
		{
			InvalidateRect(hWnd,NULL,false);
		}
		swprintf(renderTime,L"Shiny Raytracer - RenderTime: %.3f sec",shiny->getRenderTime());
		SetWindowText(hWnd,renderTime);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void InitView(int width,int height)
{
	shiny = new Shiny(width,height);
	pBuff = (BYTE*)shiny->getFrameBuffer();
}

void Render(HWND hWnd)
{
	shiny->render();
	InvalidateRect(hWnd,NULL,false);
}

void UpdateView(HDC hDC,int buffer_width,int buffer_height,int bytePerPixel)
{
	Graphics    graphics(hDC);

	void* bitmapBuffer = NULL;
	Bitmap backBuffer(buffer_width, buffer_height,&graphics);

    BitmapData bitmapData;
    bitmapData.Width = buffer_width,
    bitmapData.Height = buffer_height,
    bitmapData.Stride = bytePerPixel*buffer_width;
    bitmapData.PixelFormat = PixelFormat32bppRGB; 
    bitmapData.Reserved = NULL;

	Rect rect(0, 0, buffer_width, buffer_height);

	backBuffer.LockBits(&rect, ImageLockModeWrite , PixelFormat32bppRGB, &bitmapData);

	memcpy(bitmapData.Scan0,pBuff,buffer_width*buffer_height*bytePerPixel);

	backBuffer.UnlockBits(&bitmapData);

    graphics.DrawImage(&backBuffer, 0, 0);
}

void DestroyView()
{
	delete shiny;
}

int getBufferWidth()
{
	return BUFF_WIDTH;
}

int getBufferHeight()
{
	return BUFF_HEIGHT;
}

int getBufferBytePerPixel()
{
	return BUFF_BYTES_PER_PIXEL;
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

void SaveFile(HWND hWnd)
{
	int buffer_width = getBufferWidth();
	int buffer_height = getBufferHeight();
	int bytePerPixel = getBufferBytePerPixel();
	OPENFILENAME openfilename;
	WCHAR szPath[MAX_PATH];
    WCHAR szDir[MAX_PATH];
    static const WCHAR szDefaultExt[] = { 'p','n','g',0 };
    static const WCHAR txt_files[] = { '*','.','p','n','g',0 };
    ZeroMemory(&openfilename, sizeof(openfilename));
    GetCurrentDirectory(sizeof(szDir), szDir);
    lstrcpy(szPath, txt_files);
    openfilename.lStructSize       = sizeof(openfilename);
    openfilename.hwndOwner         = hWnd;
    openfilename.hInstance         = hInst;
    openfilename.lpstrFilter       = txt_files;
    openfilename.lpstrFile         = szPath;
    openfilename.nMaxFile          = sizeof(szPath);
    openfilename.lpstrInitialDir   = szDir;

	GetSaveFileName(&openfilename);
	
	Graphics    graphics(GetDC(hWnd));

	Bitmap backBuffer(buffer_width, buffer_height,&graphics);

    BitmapData bitmapData;
    bitmapData.Width = buffer_width,
    bitmapData.Height = buffer_height,
    bitmapData.Stride = bytePerPixel*buffer_width;
    bitmapData.PixelFormat = PixelFormat32bppRGB; 
    bitmapData.Reserved = NULL;

	Rect rect(0, 0, buffer_width, buffer_height);

	backBuffer.LockBits(&rect, ImageLockModeWrite , PixelFormat32bppRGB, &bitmapData);

	memcpy(bitmapData.Scan0,pBuff,buffer_width*buffer_height*bytePerPixel);

	backBuffer.UnlockBits(&bitmapData);

	CLSID pngClsid;
    GetEncoderClsid(L"image/png", &pngClsid);

	const wstring imageExt = L".png";

	wstring selectedFilePath = openfilename.lpstrFile;

	if(!selectedFilePath.empty())
	{
		wstring::size_type lastIndex;
		lastIndex = selectedFilePath.rfind(imageExt);
		if(lastIndex == wstring::npos || lastIndex != selectedFilePath.length() - imageExt.length()) //if file has no extension or 
		{																//file has extension different
			selectedFilePath.append(imageExt);							//from imageExt
		}
		backBuffer.Save(selectedFilePath.c_str(),&pngClsid);
	}
}

DWORD WINAPI RenderThread(LPVOID iValue)
{
    HWND hWnd = (HWND)iValue;
	while(true)
	{
		shiny->render();
		InvalidateRect(hWnd,NULL,false);
		if(bTerminateRenderThread)
		{
			break;
		}
	}
	return 0;
}

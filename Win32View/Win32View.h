#pragma once

#include "resource.h"

void InitView(int width,int height);
void UpdateView(HDC hDC,int buffer_width,int buffer_height,int bytePerPixel);
void DestroyView();
void SaveFile(HWND hWnd);
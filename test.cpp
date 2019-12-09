#include <windows.h>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;
#define target_window "gemsofwar" 
#define dpi_scaling 1.5

int main()
{
    HWND hwnd = FindWindow(0, target_window);
    if(hwnd==0)
    {
      printf("ERROR: please open the game first!\n");
      exit(0);
    }
    HDC hdc_window=GetWindowDC(hwnd);
    RECT m_rCapturedWindow;
    GetWindowRect(hwnd,&m_rCapturedWindow);
    int nX, nY, nX2, nY2;   // 選定區域坐標
    int nWidth, nHeight;    // 位圖寬度和高度
    nX = m_rCapturedWindow.left;
    nY = m_rCapturedWindow.top;
    nX2 = m_rCapturedWindow.right*dpi_scaling;
    nY2 = m_rCapturedWindow.bottom*dpi_scaling;
    nWidth = nX2 - nX;
    nHeight = nY2 - nY;
    printf("(%d, %d), (%d, %d)",nX,nY,nX2,nY2);
    SetWindowPos(hwnd, hwnd, nX, nY, m_rCapturedWindow.right-m_rCapturedWindow.left, m_rCapturedWindow.bottom-m_rCapturedWindow.top, SWP_NOZORDER | SWP_NOACTIVATE);
    return 0;
}

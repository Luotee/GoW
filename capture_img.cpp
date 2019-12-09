#include "capture_img.h"

//===========User Setting===========//
#define path ".\\screen.bmp"        //
#define dpi_scaling 1.5             //
#define target_window "gemsofwar"   //
//===========User Setting===========//

/*
void capture();
void SetMinimizeMaximizeAnimation(bool status);
bool SaveBMP(HBITMAP hBitmap);
*/

void CaptureImg::capture()
{

    //step1 : find target, if no target then end the program
    HWND hwnd = FindWindow(0, target_window);
    if(hwnd==0)
    {
      printf("ERROR: please open the game first!\n");
      exit(0);
    }
    HDC hdc_window=GetWindowDC(hwnd);
    //HDC hdc_window=GetWindowDC(NULL);

    //step2 : Disable MinAnimate Effect
    SetMinimizeMaximizeAnimation(false);

    //step3 : Transparent the window
    long winLong = GetWindowLong(hwnd, GWL_EXSTYLE);
    SetWindowLong(hwnd, GWL_EXSTYLE, winLong | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, 0, 1, LWA_ALPHA);

    //step4 : Restore the Window
    RECT m_rCapturedWindow;
    ShowWindow(hwnd,3);
    Sleep(100);
    //SetWindowPos(hwnd, hwnd, 0, 0, 1920, 1080, SWP_NOZORDER | SWP_NOACTIVATE);
    GetWindowRect(hwnd,&m_rCapturedWindow);

    //step5 : Calculate the scope of the selected window
    int nX, nY, nX2, nY2;   // 選定區域坐標
    int nWidth, nHeight;    // 位圖寬度和高度
    nX = m_rCapturedWindow.left;
    nY = m_rCapturedWindow.top;
    nX2 = m_rCapturedWindow.right*dpi_scaling;
    nY2 = m_rCapturedWindow.bottom*dpi_scaling;
    nWidth = nX2 - nX;
    nHeight = nY2 - nY;

    //step6 : Create container & restore
    HDC MemoryDC = CreateCompatibleDC(hdc_window);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdc_window, nWidth, nHeight);
    SelectObject(MemoryDC, hBitmap);
    PrintWindow(hwnd, MemoryDC, 0);
    SaveBMP(hBitmap);
    DeleteDC(hdc_window);
    DeleteDC(MemoryDC);
    ReleaseDC(hwnd,hdc_window);
    DeleteObject(hBitmap);

    //step7 : Minimize it again
    ShowWindow(hwnd,9);
    //SetWindowPos(hwnd,0,);
    //step8 : Remove transparency
    SetWindowLong(hwnd, GWL_EXSTYLE, winLong);

    //step9 : Enable MinAnimate Effect
    SetMinimizeMaximizeAnimation(true);
}

void CaptureImg::SetMinimizeMaximizeAnimation(bool status)
{
   ANIMATIONINFO ai;
   ai.cbSize=sizeof(ai);
   SystemParametersInfo(SPI_GETANIMATION,sizeof(ai),&ai,0);

   if (ai.iMinAnimate!= status)
   {
      ai.iMinAnimate = status;
      SystemParametersInfo(SPI_SETANIMATION,sizeof(ai),&ai,SPIF_SENDCHANGE);
   }
}


bool CaptureImg::SaveBMP(HBITMAP hBitmap)
{
    if(hBitmap==NULL)
    {
        printf("參數錯誤");
        return false;
    }
    HDC hDC;
    //當前分辨率下每像素所佔字節數
    int iBits;
    //位圖中每像素所佔字節數
    WORD wBitCount;
    //定義調色板大小， 位圖中像素字節大小 ，位圖文件大小 ， 寫入文件字節數
    DWORD dwPaletteSize=0, dwBmBitsSize=0, dwDIBSize=0, dwWritten=0;
    //位圖屬性結構
    BITMAP Bitmap;
    //位圖文件頭結構
    BITMAPFILEHEADER bmfHdr;
    //位圖信息頭結構
    BITMAPINFOHEADER bi;
    //指向位圖信息頭結構
    LPBITMAPINFOHEADER lpbi;
    //定義文件，分配內存句柄，調色板句柄
    HANDLE fh, hDib, hPal,hOldPal=NULL;

    //計算位圖文件每個像素所佔字節數
    hDC = CreateDC("DISPLAY", NULL, NULL, NULL);
    iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
    DeleteDC(hDC);
    if (iBits <= 1)  wBitCount = 1;
    else if (iBits <= 4)  wBitCount = 4;
    else if (iBits <= 8)  wBitCount = 8;
    else      wBitCount = 24;

    GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
    bi.biSize   = sizeof(BITMAPINFOHEADER);
    bi.biWidth   = Bitmap.bmWidth;
    bi.biHeight   = Bitmap.bmHeight;
    bi.biPlanes   = 1;
    bi.biBitCount  = wBitCount;
    bi.biCompression = BI_RGB;
    bi.biSizeImage  = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrImportant = 0;
    bi.biClrUsed  = 0;
    //printf("w = %d, hi = %d\n",bi.biWidth, bi.biHeight);
    dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;
 
    //為位圖內容分配內存
    hDib = GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
    *lpbi = bi;

    // 處理調色板
    hPal = GetStockObject(DEFAULT_PALETTE);
    if (hPal)
    {
        hDC = ::GetDC(NULL);
        hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);
        RealizePalette(hDC);
    }

  // 獲取該調色板下新的像素值
  GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)
    +dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);
 
  //恢復調色板
  if (hOldPal)
  {
   ::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
   RealizePalette(hDC);
   ::ReleaseDC(NULL, hDC);
  }
    char FilePath[MAX_PATH];
    wsprintf(FilePath, "%s", path);
  //創建位圖文件
    fh = CreateFile(
      FilePath, 
      GENERIC_WRITE,
      0, 
      NULL, 
      CREATE_ALWAYS,
      FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 
      NULL
    );
 
  if (fh == INVALID_HANDLE_VALUE)  return FALSE;
 
  // 設置位圖文件頭
  bmfHdr.bfType = 0x4D42; // "BM"
  dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
  bmfHdr.bfSize = dwDIBSize;
  bmfHdr.bfReserved1 = 0;
  bmfHdr.bfReserved2 = 0;
  bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
  // 寫入位圖文件頭
  WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
 
  // 寫入位圖文件其餘內容
  WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
  //清除
  GlobalUnlock(hDib);
  GlobalFree(hDib);
  CloseHandle(fh);

  return TRUE;
}
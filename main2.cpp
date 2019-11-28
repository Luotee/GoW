#include <windows.h>

int CaptureImage(HWND hWnd, CHAR* dirPath, CHAR* filename);

int main()
{
    CHAR path[100] = ".\\";
    CHAR filename[100] = "hello";
    CaptureImage(GetDesktopWindow(), path, filename); // 保存为 E:hello.bmp
    return 0;
}

/**
 * GDI 截取指定窗口
 *
 * 参数 hwnd   要截屏的窗口句柄
 * 参数 dirPath    截图存放目录
 * 参数 filename 截图名称
 */
int CaptureImage(HWND hwnd, CHAR * dirPath, CHAR * filename)
{
    hwnd = FindWindow(0,"gemsofwar");

    HDC mdc;
    HBITMAP hbmp;
    CHAR FilePath[MAX_PATH];
    HDC hdcScreen;
    HDC hdcWindow;
    HDC hdcMemDC = NULL;
    HBITMAP hbmScreen = NULL;
    BITMAP bmpScreen;
    RECT rcClient;
    BITMAPFILEHEADER   bmfHeader;
    BITMAPINFOHEADER   bi;
    DWORD dwBmpSize;
    HANDLE hDIB;
    CHAR* lpbitmap;
    HANDLE hFile;
    DWORD dwSizeofDIB;
    DWORD dwBytesWritten;

    hdcScreen = GetDC(NULL); // 全屏幕DC
    hdcWindow = GetDC(hwnd); // 截图目标窗口DC

    // 创建兼容内存DC
    hdcMemDC = CreateCompatibleDC(hdcWindow);

    if (!hdcMemDC)
    {
        goto done;
    }

    // 获取客户端区域用于计算大小
    GetClientRect(hwnd, &rcClient);

    // 设置延展模式
    SetStretchBltMode(hdcWindow, HALFTONE);

    // 来源 DC 是整个屏幕而目标 DC 是当前的窗口 (HWND)
    if (!StretchBlt(hdcWindow,
        0, 0,
        rcClient.right, rcClient.bottom,
        hdcScreen,
        0, 0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        SRCCOPY))
    {
        goto done;
    }

    // 通过窗口DC 创建一个兼容位图
    hbmScreen = CreateCompatibleBitmap(
        hdcWindow,
        rcClient.right - rcClient.left,
        rcClient.bottom - rcClient.top
    );

    if (!hbmScreen)
    {
        goto done;
    }

    // 将位图块传送到我们兼容的内存DC中
    SelectObject(hdcMemDC, hbmScreen);
    if (!BitBlt(
        hdcMemDC,   // 目的DC
        0, 0,        // 目的DC的 x,y 坐标
        rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, // 目的 DC 的宽高
        hdcWindow,  // 来源DC
        0, 0,        // 来源DC的 x,y 坐标
        SRCCOPY))   // 粘贴方式
    {
        goto done;
    }

    // 获取位图信息并存放在 bmpScreen 中
    GetObject(hbmScreen, sizeof(BITMAP), &bmpScreen);

    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = bmpScreen.bmWidth;
    bi.biHeight = bmpScreen.bmHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

    // 在 32-bit Windows 系统上, GlobalAlloc 和 LocalAlloc 是由 HeapAlloc 封装来的
    // handle 指向进程默认的堆. 所以开销比 HeapAlloc 要大
    hDIB = GlobalAlloc(GHND, dwBmpSize);
    lpbitmap = (char*)GlobalLock(hDIB);

    // 获取兼容位图的位并且拷贝结果到一个 lpbitmap 中.
    GetDIBits(
        hdcWindow,  // 设备环境句柄
        hbmScreen,  // 位图句柄
        0,          // 指定检索的第一个扫描线
        (UINT)bmpScreen.bmHeight, // 指定检索的扫描线数
        lpbitmap,   // 指向用来检索位图数据的缓冲区的指针
        (BITMAPINFO*)& bi, // 该结构体保存位图的数据格式
        DIB_RGB_COLORS // 颜色表由红、绿、蓝（RGB）三个直接值构成
    );


    wsprintf(FilePath, "%s\%s.bmp", dirPath, filename);

    // 创建一个文件来保存文件截图
    hFile = CreateFile(
        FilePath,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    // 将 图片头(headers)的大小, 加上位图的大小来获得整个文件的大小
    dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // 设置 Offset 偏移至位图的位(bitmap bits)实际开始的地方
    bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

    // 文件大小
    bmfHeader.bfSize = dwSizeofDIB;

    // 位图的 bfType 必须是字符串 "BM"
    bmfHeader.bfType = 0x4D42; //BM   

    dwBytesWritten = 0;
    WriteFile(hFile, (LPSTR)& bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
    WriteFile(hFile, (LPSTR)& bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
    WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

    // 解锁堆内存并释放
    GlobalUnlock(hDIB);
    GlobalFree(hDIB);

    // 关闭文件句柄
    CloseHandle(hFile);

    // 清理资源
done:
    DeleteObject(hbmScreen);
    DeleteObject(hdcMemDC);
    ReleaseDC(NULL, hdcScreen);
    ReleaseDC(hwnd, hdcWindow);

    return 0;
}
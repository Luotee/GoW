#include <windows.h>
#include <cstdio>
#include <string>
#include <iostream>
#include <Winuser.h>
using namespace std;

DPI_AWARENESS_CONTEXT SetThreadDpiAwarenessContext(
  DPI_AWARENESS_CONTEXT 1.5
);

int main(int argc, char **argv)
{
    uint32_t Width = GetSystemMetrics(SM_CXSCREEN);
    uint32_t Height = GetSystemMetrics(SM_CYSCREEN);
    std::cout << Width << " x " << Height << "\n";

    return 0;
}

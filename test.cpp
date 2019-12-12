#include <iostream>
#include <math.h>
#include <windows.h>
using namespace std;

bool crosshairon=false;
HDC ragedc = NULL;
int crosshairsize=0;
int cx=0;
int cy=0;

void CrossThread(void)
{
    while(1)
    {
        if(GetAsyncKeyState(VK_NUMPAD0)&1)
        {
            crosshairon=!crosshairon;
            ragedc = GetDC(HWND_DESKTOP);
            cx=GetSystemMetrics(SM_CXSCREEN)/2-((crosshairsize-1)/2);
            cy=GetSystemMetrics(SM_CYSCREEN)/2-((crosshairsize-1)/2);
        }
        Sleep(1);
    }
}

int main()
{
    cout<<"Crosshair size in pixels:\n";
    cin>>crosshairsize;
    if(crosshairsize%2==0)
    {
        crosshairsize+=1; 
    }
    system("cls"); 
    cout<<"Press numpad0 to toggle the crosshair on and off\n";
    CreateThread(0,0,(LPTHREAD_START_ROUTINE)CrossThread,0,0,0);
    while(1)
    {
        if(crosshairon==true)
        {
            for(int i=0;i<crosshairsize;i++)
            {
                SetPixel(ragedc, cx+i, cy+((crosshairsize-1)/2), RGB(255,0,0));
                SetPixel(ragedc, cx+((crosshairsize-1)/2), cy+i, RGB(0,0,255));
            }

            if(crosshairon==false)
        
            for(int i=1;i<crosshairsize;i++)
            {
                SetPixel(ragedc, cx+i, cy+((crosshairsize-1)/2), RGB(0,0,0));
                SetPixel(ragedc, cx+((crosshairsize-1)/2), cy+i, RGB(0,0,0));
            }
        }
        Sleep(33);
    }
}
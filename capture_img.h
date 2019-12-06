#ifndef CAPTURE_IMG_H
#define CAPTURE_IMG_H

#include <windows.h>
#include <cstdio>
#include <string>

class CaptureImg {

    public:
        void capture();

    private:
        void SetMinimizeMaximizeAnimation(bool status);
        bool SaveBMP(HBITMAP hBitmap);

};


#endif /* CAPTURE_IMG_H */
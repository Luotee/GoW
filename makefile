.PHONY: clean

CC = g++
WINLIB = -lgdi32 #-mwindows
CFLAGS = -g #-Wall
#SRCS = main.cpp
PROG = main.exe

OPENCV_include_path = C:\opencv\build\include
OPENCV_dll_path = C:\opencv\build\x64\MinGW\bin
OPENCV_dll = -l libopencv_calib3d412 -l libopencv_core412 -l libopencv_dnn412 -l libopencv_features2d412 -l libopencv_flann412 -l libopencv_gapi412 -l libopencv_highgui412 -l libopencv_imgcodecs412 -l libopencv_imgproc412 -l libopencv_ml412 -l libopencv_objdetect412 -l libopencv_photo412 -l libopencv_stitching412 -l libopencv_video412 -l libopencv_videoio412

#
all: main.o capture_img.o
	$(CC) -o $(PROG) $(CFLAGS) main.o capture_img.o $(WINLIB)
	
$(PROG):$(SRCS)
	$(CC) -o $(PROG) $(SRCS) $(CFLAGS) -I $(OPENCV_include_path) -L $(OPENCV_dll_path) $(OPENCV_dll)

#
main.o: main.cpp
	g++ -c main.cpp

capture_img.o: capture_img.cpp capture_img.h
	g++ -c capture_img.cpp




clean:
	del *.exe
	del *.o
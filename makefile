.PHONY: clean

CC = g++
CFLAGS = -g -Wall
SRCS = lenna.cpp
PROG = lenna

OPENCV_include_path = C:\opencv\build\include
OPENCV_dll_path = C:\opencv\build\x64\MinGW\bin
OPENCV_dll = -l libopencv_calib3d412 -l libopencv_core412 -l libopencv_dnn412 -l libopencv_features2d412 -l libopencv_flann412 -l libopencv_gapi412 -l libopencv_highgui412 -l libopencv_imgcodecs412 -l libopencv_imgproc412 -l libopencv_ml412 -l libopencv_objdetect412 -l libopencv_photo412 -l libopencv_stitching412 -l libopencv_video412 -l libopencv_videoio412

$(PROG):$(SRCS)
	$(CC) -o $(PROG) $(SRCS) $(CFLAGS) -I $(OPENCV_include_path) -L $(OPENCV_dll_path) $(OPENCV_dll)

capture_test:
	g++ -o hp hp.cpp -mwindows

clean:
	del *.exe
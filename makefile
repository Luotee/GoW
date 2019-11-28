.PHONY: clean

all:
	g++ -o test hp.cpp -mwindows

clean:
	del test.exe
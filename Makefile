CC = clang++
LDFLAGS = -I/usr/local/include/opencv -I/usr/local/include/opencv2 -lm -lopencv_objdetect -lopencv_core -lopencv_highgui -lopencv_video -lopencv_imgproc -Iinclude
ALL = test

all: $(ALL)



clean:
	rm test
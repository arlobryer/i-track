CC = clang++
LDFLAGS = -I/usr/local/include/opencv -I/usr/local/include/opencv2 -lm -lopencv_objdetect -lopencv_core -lopencv_highgui -lopencv_video -lopencv_imgproc -I/Users/arlogb/prog_projects/i-track/include
ALL = test

all: $(ALL)




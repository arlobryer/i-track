SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
	DEPS=$(SOURCES:.cpp=.d)
BINS=$(SOURCES:.cpp=)

CFLAGS+=-MMD
CXXFLAGS+=-MMD -Iinclude -I/usr/include/opencv -I/usr/include/opencv2
CXXFLAGS+=-I/usr/local/include/opencv -I/usr/local/include/opencv2 -lopencv_objdetect -lopencv_core -lopencv_highgui -lopencv_video -lopencv_imgproc
all: $(BINS)

.PHONY: clean

clean:
	    $(RM) $(OBJECTS) $(DEPS) $(BINS)

-include $(DEPS)

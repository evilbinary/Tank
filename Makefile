##########################################################################################
# Project: Lisp++ 
# # Makefile Evilbinary 小E
# # Mail:rootntsd@gmail.com
# ##########################################################################################
CPP = g++ -fPIC
CXXFLAGS = -g  -Wall  -std=c++0x -lSDL -lSDL_gfx -lxml2 -lSDL_ttf -lSDL_image  -lSDL_mixer 
LDFLAGS =

LIBS = -L. -I/usr/include/libxml2/ 
INCS =-I. 
SRCS = $(wildcard *.cpp ./src/*.cpp )
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

TARGET=Tank
.PHONY :all  clean

all:$(TARGET) so
so:$(OBJS)
	$(CPP) -o lib$(TARGET).so $(LIBS) $(INCS) $(OBJS) $(CXXFLAGS) -shared

clean:
	rm *.o $(TARGET) $(OBJS)

$(TARGET):$(OBJS)
	$(CPP) -o $(TARGET) $(LIBS) $(INCS) $(OBJS) $(CXXFLAGS)

.cpp.o:
	$(CPP) -c -o $@ $< $(LIBS) $(INCS) $(CXXFLAGS)

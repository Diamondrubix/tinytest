lab12: lab12.o Point2d.o
	g++ -o lab12 lab12.o Point2d.o

all: lab12 Point2dTest

Point2dTest: Point2d.o Point2dTest.cpp
	g++ -o Point2dTest Point2d.o Point2dTest.cpp

lab12.o: lab12.cpp Point2d.h
	g++ -c lab12.cpp

Point2d.o: Point2d.cpp Point2d.h
	g++ -c Point2d.cpp

clean:
	rm lab12.o Point2d.o lab12 Point2dTest

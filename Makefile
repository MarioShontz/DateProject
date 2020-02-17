#Mario Shontz

dateProj: date.o driver.o
	g++ -std=c++11 -o dateProj date.o driver.o
date.o: date.cpp date.h
	g++ -std=c++11 -c date.cpp
driver.o: driver.cpp date.h
	g++ -std=c++11 -c driver.cpp
clean:
	rm *.o dateProj

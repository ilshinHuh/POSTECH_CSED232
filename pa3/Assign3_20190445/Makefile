CC = g++
TARGET = main.exe
all : $(TARGET)
testComp : main.cpp header.hpp
	$(CC) main.cpp -W -Wall
clean : 
	rm $(TARGET)
main.exe : main.cpp header.hpp
	$(CC) main.cpp -o main.exe

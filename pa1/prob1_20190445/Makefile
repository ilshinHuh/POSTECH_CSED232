CC = g++
TARGET = main.exe
all : $(TARGET)
testComp : main.cpp
	$(CC) main.cpp -W -Wall
clean : 
	rm $(TARGET)
main.exe : main.cpp
	$(CC) main.cpp -o main.exe
run : main.exe
	./main.exe

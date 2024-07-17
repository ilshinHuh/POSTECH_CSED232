CC = g++
TARGET = main.exe
all : $(TARGET)
clean : 
	rm $(TARGET)
	rm a.out
main.exe : main.cpp
	$(CC) main.cpp -o main.exe
testComp : main.cpp
	$(CC) main.cpp -W -Wall
run : main.exe
	./main.exe

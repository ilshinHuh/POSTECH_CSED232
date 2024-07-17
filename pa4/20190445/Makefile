CC = g++ -std=c++11
TARGET = main.exe
all : $(TARGET)
Image.o : Image.h Image.cc
	$(CC) -c Image.cc
SharedPtr_image_test.o : SharedPtr.h Image.h SharedPtr_image_test.cc
	$(CC) -c SharedPtr_image_test.cc
main.exe : SharedPtr_image_test.o Image.o
	$(CC) SharedPtr_image_test.o Image.o -o main.exe
run : main.exe
	./main.exe
clean : 
	rm $(TARGET) SharedPtr_image_test.o Image.o edge.bmp bilat.bmp blur.bmp spun.bmp

#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <cstdint>
#include <cassert>
#include "SharedPtr.h"

///////////////////////////////////////////////////////////////////////////
// RGB pixel type
//    Usage:
//      - RGB<float> rgb(0.5f, 0.1f, 0.3f);
//        rgb[0] = 0.2f; // or equivalently, rgb.r = 0.2f;
template<typename ValType>
struct RGB
{
	union {
		ValType data[3];
		struct {
			ValType r, g, b;
		};
	};

	RGB() {}
	RGB(ValType r_, ValType g_, ValType b_) : r(r_), g(g_), b(b_) {}

	ValType operator[](int idx) const { return data[idx]; }
	ValType& operator[](int idx) { return data[idx]; }
};

typedef RGB<uint8_t>	RGB8b;
typedef RGB<float>		RGBf;


///////////////////////////////////////////////////////////////////////////
// Image class template
//
template<typename PixelType>
class Image
{
private:
	// ======= ADD CODE HERE IF NEEDED =========
	size_t m_width;
	size_t m_height;
	SharedArray<PixelType> m_buff;
public:
	////////////////////////////////////////////
	// constructors & destructor
	////////////////////////////////////////////
	//default constructor
	Image() : m_width(0), m_height(0), m_buff(nullptr){}
	
	//constructor
	Image(size_t _width, size_t _height) : m_width(_width), m_height(_height){
		//allocate memory
		m_buff = SharedArray<PixelType>(new PixelType[m_width * m_height]);
	}

	//constructor
	Image(size_t _width, size_t _height, const PixelType& val) : m_width(_width), m_height(_height){
		//allocate memory
		m_buff = SharedArray<PixelType>(new PixelType[m_width * m_height]);
		for(size_t i = 0; i < m_width * m_height; i++)
			m_buff[i] = val;//initialize pixel values
	}

	//copy constructor
	Image(const Image<PixelType>& img) : m_width(img.m_width), m_height(img.m_height){

		m_buff = SharedArray<PixelType>(new PixelType[m_width * m_height]);
		for(size_t i = 0; i < m_width * m_height; i++)//deep copy
			m_buff[i] = img.m_buff[i];
	}

	//decontructor
	~Image(){};
	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// assignment operator
	////////////////////////////////////////////
	//assignment operator
	Image<PixelType>& operator=(const Image<PixelType>& other){
		if(this != &other){//when two operands are different
			m_width = other.m_width;
			m_height = other.m_height;

			m_buff = SharedArray<PixelType>(new PixelType[m_width * m_height]);
			for(size_t i = 0; i < m_width * m_height; i++)//deep copy
				m_buff[i] = other.m_buff[i];
		}
		return *this;
	}
	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// element access operators
	////////////////////////////////////////////
	PixelType* operator[](int y) { return &m_buff[y * m_width]; }
	const PixelType* operator[](int y) const { return &m_buff[y * m_width];}

	////////////////////////////////////////////
	// other methods
	////////////////////////////////////////////
	//   - width(), height()
	//return width
	size_t width() const{return m_width;}
	//return height
	size_t height() const{return m_height;}
	// ======= ADD CODE HERE IF NEEDED =========
};

// ======= ADD CODE HERE IF NEEDED =========


// Miscellaneous functions
void convert_pixel_type(const Image<RGB8b>& src, Image<RGBf>& dst);
void convert_pixel_type(const Image<RGBf>& src, Image<RGB8b>& dst);

bool load_bmp(const char* path, Image<RGB8b>& img);
bool save_bmp(const char* path, const Image<RGB8b>& img);

#endif

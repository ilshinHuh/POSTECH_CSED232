#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<cmath>
#include<sstream>

using namespace std;

class parser{
	public:
		vector<int> load_image(const char*);
		vector<string> load_config(const char*);
		void write_result(const char*, const string&);
};

class artist{
	private:
		int width;
		int height;
		vector< vector<int> > pixels;
	public:
		char clssc(int);
		int getPixel(int x, int y) const {return pixels[y][x];}
		int getWidth() const {return width;}
		int getHeight() const {return height;}
		artist(int, int, const vector<int>&);
		virtual char mapper(int, int) = 0;
		virtual ~artist() {}
};

class classic : public artist{
	public:
		char mapper(int, int);
		classic(int Width, int Height, const vector<int>& loaded) : artist(Width, Height, loaded) {}
		~classic() {}
};

class iclassic : public artist{
	public:
		char mapper(int, int);
		iclassic(int Width, int Height, const vector<int>& loaded) : artist(Width, Height, loaded) {}
		~iclassic() {}
};

class sobelx : public artist{
	public:
		char mapper(int, int);
		sobelx(int Width, int Height, const vector<int>& loaded) : artist(Width, Height, loaded) {}
		~sobelx() {}
};

class sobely : public artist{
	public:
		char mapper(int, int);
		sobely(int Width, int Height, const vector<int>& loaded) : artist(Width, Height, loaded) {}
		~sobely() {}
};

class gradient : public artist{
	public:
		char mapper(int, int);
		gradient(int Width, int Height, const vector<int>& loaded) : artist(Width, Height, loaded) {}
		~gradient() {}
};
/*
class avgfilter : public artist{
	private:
		int fsize;
	public:
		char mapper(int, int);
		avgfilter(int Width, int Height, const vector<int>& loaded, int size) : artist(Width, Height, loaded) {fsize = size;}
		~avgfilter() {}
};

class bilatfilter : public artist{
	private:
		int fsize, sSigma, iSigma;
	public:
		char mapper(int, int);
		bilatfilter(int Width, int Height, const vector<int>& loaded, int size, int s, int i) : artist(Width, Height, loaded) {
			fsize = size;
			sSigma = s;
			iSigma = i;
		}
		~bilatfilter() {}
};
*/
class drawer{
	private:
		artist* myArtist;
	public:
		char getDPixel(int x, int y) const{return myArtist->mapper(x, y);}
		int getDWidth() const{return myArtist->getWidth();}
		int getDHeight() const{return myArtist->getHeight();}
		drawer(artist*);
		virtual string draw();
		virtual ~drawer() {delete myArtist;}
};

class downsample : public drawer{
	public:
		string draw();
		downsample(artist* Artist) : drawer(Artist){}
		~downsample() {}
};

class upsample : public drawer{
	public:
		string draw();
		upsample(artist* Artist) : drawer(Artist){}
		~upsample() {}
};

class scale : public drawer{
	private:
		int xProp, yProp;
	public:
		scale(artist*, int, int);
		string draw();
		~scale() {}
};

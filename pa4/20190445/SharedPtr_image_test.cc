#include <cmath>
#include "SharedPtr.h"
#include "Image.h"

using namespace std;

class MyClass
{
private:
	int m_id;
	static int n_objects;

public:
	explicit MyClass(int id = 0);
	~MyClass();

	int get_id() const { return m_id; }

	static int num_objects() { return n_objects; }
};

int MyClass::n_objects = 0;

MyClass::MyClass(int id)
	: m_id(id)
{
	n_objects++;
	std::cout << "MyClass object(" << m_id << ") created: " << n_objects << std::endl;
}

MyClass::~MyClass()
{
	n_objects--;
	std::cout << "MyClass object(" << m_id << ") destroyed: " << n_objects << std::endl;
}

void test_SharedPtr()
{
	std::cout << "test_SharedPtr()" << std::endl;

	SharedPtr<MyClass> ptr1(new MyClass(100));
	SharedPtr<MyClass> ptr2(ptr1);
	SharedPtr<MyClass> ptr3;
	ptr3 = ptr2;

	ptr1 = SharedPtr<MyClass>(new MyClass(200));

	std::cout << "=============" << std::endl;
	std::cout << "ptr1: " << ptr1->get_id() << std::endl;
	std::cout << "ptr2: " << (*ptr2).get_id() << std::endl;
	std::cout << "ptr3: " << ptr3->get_id() << std::endl;
	std::cout << "=============" << std::endl;

	ptr2 = ptr3 = ptr1;

	std::cout << "=============" << std::endl;
	std::cout << "ptr1: " << ptr1->get_id() << std::endl;
	std::cout << "ptr2: " << (*ptr2).get_id() << std::endl;
	std::cout << "ptr3: " << ptr3->get_id() << std::endl;
	std::cout << "=============" << std::endl;

	const SharedPtr<MyClass> const_ptr(new MyClass(300));
	std::cout << "=============" << std::endl;
	std::cout << "const_ptr: " << const_ptr->get_id() << std::endl;
	std::cout << "const_ptr: " << (*const_ptr).get_id() << std::endl;
	std::cout << "=============" << std::endl;

	const MyClass* pp = (const MyClass*)ptr1;
	std::cout << "pp: " << pp->get_id() << std::endl;
}

void test_SharedArray()
{
	std::cout << "test_SharedArray()" << std::endl;

	SharedArray<int> arr1(new int[10]);
	SharedArray<int> arr2(arr1);
	SharedArray<int> arr3;
	arr3 = arr2;

	arr1[0] = 1;
	std::cout << "=============" << std::endl;
	std::cout << "arr1[0]: " << arr1[0] << std::endl;
	std::cout << "arr2[0]: " << arr2[0] << std::endl;
	std::cout << "arr3[0]: " << arr3[0] << std::endl;
	std::cout << "=============" << std::endl;

	arr1 = SharedArray<int>(new int[5]);
	arr1[0] = 2;
	arr2[0] = 3;

	std::cout << "=============" << std::endl;
	std::cout << "arr1[0]: " << arr1[0] << std::endl;
	std::cout << "arr2[0]: " << arr2[0] << std::endl;
	std::cout << "arr3[0]: " << arr3[0] << std::endl;
	std::cout << "=============" << std::endl;

	arr2 = arr3 = arr1;

	std::cout << "=============" << std::endl;
	std::cout << "arr1[0]: " << arr1[0] << std::endl;
	std::cout << "arr2[0]: " << arr2[0] << std::endl;
	std::cout << "arr3[0]: " << arr3[0] << std::endl;
	std::cout << "=============" << std::endl;
}

void compute_edge_map(const Image<RGBf>& img, Image<RGBf>& edge_map)
{
	edge_map = Image<RGBf>(img.width(), img.height(), RGBf(.0f, .0f, .0f));
	for(int y = 0; y < img.height()-1; y++) {
		for(int x = 0; x < img.width()-1; x++) {
			for(int ch = 0; ch < 3; ch++) {
				float dx = img[y][x+1][ch] - img[y][x][ch];
				float dy = img[y+1][x][ch] - img[y][x][ch];
				edge_map[y][x][ch] = std::sqrt(dx*dx + dy*dy);
			}
		}
	}
}


//additioanal features
//blurring using bilateral filters
void bilat(const Image<RGBf>& img, Image<RGBf>& bilated){
	bilated = Image<RGBf>(img.width(), img.height(), RGBf(.0f, .0f, .0f));
	int radius = 10;
	float sSigma = 1;
	float iSigma = 16;
	for(int y = radius; y < img.height()-radius;y++){
		for(int x = radius; x < img.width()-radius; x++){
			for(int ch = 0; ch < 3; ch++){
				float sWeight = 1.0 / (2.0 * sSigma * sSigma);
				float sum = 0;
				float wSum = 0;
				for(int i = -radius; i <= radius; i++){
					for(int j = -radius; j <= radius; j++){
                    	float sDis = sqrt(j * j + i * i);
            			float sWeightVal = exp(- sDis * sDis * sWeight);
						float iDis = abs(img[y + i][x + j][ch] - img[y][x][ch]);
						float iWeight = exp(- iDis * iDis / (2.0 * iSigma * iSigma));
						float weight = sWeightVal * iWeight;
						sum += weight * img[y + i][x + j][ch];
						wSum += weight;
					}
				}
				bilated[y][x][ch] = sum / wSum;
			}
		}
	}
}

//additional features
//blurring using average filter
void blurring(const Image<RGBf>& img, Image<RGBf>& blurred){
	blurred = Image<RGBf>(img.width(), img.height(), RGBf(.0f, .0f, .0f));
	int radius = 10;
	for(int y = radius; y < img.height()-radius;y++){
		for(int x = radius; x < img.width()-radius; x++){
			for(int ch = 0; ch < 3; ch++){
				float sum = 0;
				for(int i = -radius; i <= radius; i++){
					for(int j = -radius; j <= radius; j++){
						sum += img[y + i][x + j][ch];
					}
				}
				float avg = sum / ((2*radius+1) * (2*radius+1));
				blurred[y][x][ch] = avg;
			}
		}
	}
}

//additional features
//clockwise spin 90 degrees
void rightspin(const Image<RGBf>& img, Image<RGBf>& spun){
	spun = Image<RGBf>(img.height(), img.width(), RGBf(.0f, .0f, .0f));
	for(int y = 0; y < img.width(); y++) {
		for(int x = 0; x < img.height(); x++) {
			for(int ch = 0; ch < 3; ch++) {
				spun[y][x] = img[img.height() - x - 1][y];
			}
		}
	}
}

void convert_rgb_to_gray(const Image<RGBf>& rgb, Image<float>& gray)
{
	gray = Image<float>(rgb.width(), rgb.height());
	for(int y = 0; y < rgb.height(); y++) {
		for(int x = 0; x < rgb.width(); x++) {
			gray[y][x] = (rgb[y][x].r + rgb[y][x].g + rgb[y][x].b)/3.0f;
		}
	}
}

void downsample(const Image<float>& img, Image<float>& downsampled, int scale_factor)
{
	size_t w = (img.width() + scale_factor-1) / scale_factor;
	size_t h = (img.height() + scale_factor-1) / scale_factor;
	Image<float> accum(w, h, 0.0f);
	Image<int> denom(w, h, 0);
	for(int y = 0; y < img.height(); y++) {
		for(int x = 0; x < img.width(); x++) {
			int y2 = y/scale_factor;
			int x2 = x/scale_factor;
			accum[y2][x2] += img[y][x];
			denom[y2][x2]++;
		}
	}

	downsampled = Image<float>(w, h);
	for(int y = 0; y < downsampled.height(); y++) {
		for(int x = 0; x < downsampled.width(); x++) {
			downsampled[y][x] = accum[y][x] / (float)denom[y][x];
		}
	}
}

void draw_ascii_art(const Image<float>& img)
{
	static const char letters[] = "`.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
	const int n_letters = sizeof(letters) / sizeof(letters[0]);
	float minv, maxv;
	minv = maxv = img[0][0];
	for(int y = 0; y < img.height(); y++) {
		for(int x = 0; x < img.width(); x++) {
			if(img[y][x] > maxv) maxv = img[y][x];
			if(img[y][x] < minv) minv = img[y][x];
		}
	}
	for(int y = 0; y < img.height(); y++) {
		for(int x = 0; x < img.width(); x++) {
			int idx = static_cast<int>((img[y][x]-minv)*(maxv-minv) * static_cast<float>(n_letters-1));
			std::cout << letters[idx];
		}
		std::cout << std::endl;
	}
}

int main()
{
	//// Problem1 test
	std::cout << "< Problem1 test >" << std::endl;
	test_SharedPtr();
	std::cout << std::endl;
	test_SharedArray();
	std::cout << std::endl;

	//// Problem2 test
	std::cout << "< Problem2 test >" << std::endl;
	Image<RGB8b> img;
	load_bmp("input.bmp", img);
	Image<RGBf> imgf;

	convert_pixel_type(img, imgf);

	/////////////////////////////////////////////////
	// simple image operations
	/////////////////////////////////////////////////
	
	//  1. Edge detection
	Image<RGBf> edge_map;
	compute_edge_map(imgf, edge_map);
	convert_pixel_type(edge_map, img);
	save_bmp("edge.bmp", img);

	
	//2. average filter blurring
	Image<RGBf> blur_map;
	blurring(imgf, blur_map);
	convert_pixel_type(blur_map, img);
	save_bmp("blur.bmp", img);

	//3. spinning
	Image<RGBf> spun_map;
	rightspin(imgf, spun_map);
	convert_pixel_type(spun_map, img);
	save_bmp("spun.bmp", img);
	
	//4. bilateral filter blurring
	Image<RGBf> bilat_map;
	bilat(imgf, bilat_map);
	convert_pixel_type(bilat_map, img);
	save_bmp("bilat.bmp", img);

	std::cout << "2. ASCII conversion" << std::endl;
	//  2. ASCII conversion
	//     2.1. Grayscale conversion
	//     2.2. Downsampling
	//     2.3. ASCII conversion
	std::cout << "2.1. Grayscale conversion" << std::endl;
	Image<float> gray;
	convert_rgb_to_gray(imgf, gray);

	std::cout << "2.2. Downsampling" << std::endl;

	int scale_factor = 10;
	Image<float> downsampled;
	downsample(gray, downsampled, scale_factor);

	std::cout << "2.3. ASCII art drawing" << std::endl;
	draw_ascii_art(downsampled);
		
	return 0;
}

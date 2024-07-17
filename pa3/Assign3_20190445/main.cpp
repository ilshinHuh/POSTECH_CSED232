#include"header.hpp"

//artist mapping assistant
char artist::clssc(int val){
	switch(val) {
		case 0:
			return '@';
		case 1:
			return '&';
		case 2:
			return '%';
		case 3:
			return 'W';
		case 4:
			return 'X';
		case 5:
			return 'A';
		case 6:
			return 'H';
		case 7:
			return 'O';
		case 8:
			return 'T';
		case 9:
			return '*';
		case 10:
			return '^';
		case 11:
			return '+';
		case 12:
			return '-';
		case 13:
			return '.';
		case 14:
			return ' ';
		case 15:
			return ' ';
	}
	return ' ';
}

//load input image
vector<int> parser::load_image(const char* input) {
	char divider = '|';
	vector<int> loaded{};
	ifstream fileIn(input);//open input file
	
	if(fileIn.is_open()){
		string* line = new string;//dynamically allocate new string to save input
		string value;
		getline(fileIn, *line);
		stringstream ss(*line);
		while(getline(ss, value, divider)){// divide string by '|'
			loaded.push_back(stoi(value));//push divided value into vector
		}
		fileIn.close();
		delete line;
	}
	else {
		cerr << "CANNOT OPEN " << input << "!!" << endl;
	}
	return loaded;
}

//load configurations. almost same as load_image.
vector<string> parser::load_config(const char* input){
	char divider = '|';
	vector<string> loaded;
	ifstream fileIn(input);

	if(fileIn.is_open()) {
		string* line = new string;
		string value;
		getline(fileIn, *line);
		stringstream ss(*line);
		while(getline(ss, value, divider)){
			loaded.push_back(value);
		}
		fileIn.close();
		delete line;
	}
	else {
		cerr << "CANNOT OPEN " << input << "!!" << endl;
	}
	return loaded;
}

//write result in file
void parser::write_result(const char* path, const string& contents){
	ofstream myfile;
	myfile.open(path);
	myfile << contents;
	myfile.close();
}

//artist constructor
artist::artist(int Width, int Height, const vector<int>& loaded){
	width = Width;
	height = Height;
	for(int i = 0; i < height; i++){//put vector's values to pixels
		vector<int> row;
		for(int j = 0; j < width; j++){
			row.push_back(loaded[i * width + j]);
		}
		pixels.push_back(row);
	}
}

//mapper of classic
char classic::mapper(int xCoord, int yCoord){
	return clssc(getPixel(xCoord, yCoord) / 17);
}


//mapper of iclassic
char iclassic::mapper(int xCoord, int yCoord){
	if(getPixel(xCoord, yCoord) != 255)
		return clssc(14 - int(getPixel(xCoord, yCoord) / 17));//invert classic mapper
	else
		return '@';
}

//mapper of sobelx
char sobelx::mapper(int xCoord, int yCoord){
	if(xCoord == getWidth() - 1) {//if the pixel is at the end
		return ' ';
	}
	else if(abs(getPixel(xCoord, yCoord) - getPixel(xCoord + 1, yCoord)) >= 50){
		return '|';
	}
	else{
		return ' ';
	}
}

//mapper of sobely
char sobely::mapper(int xCoord, int yCoord){
	if(yCoord == getHeight() - 1) {//if the pixel is at the end
		return ' ';
	}
	else if(abs(getPixel(xCoord, yCoord) - getPixel(xCoord, yCoord + 1)) >= 50){
		return '-';
	}
	else{
		return ' ';
	}
}

//mapper of gradient
char gradient::mapper(int xCoord, int yCoord){
	int xDiff;//to save difference of pixel. x axis
	int yDiff;//" y axis
	if(xCoord < getWidth() - 1)
		xDiff = abs(getPixel(xCoord, yCoord) - getPixel(xCoord + 1, yCoord));
	else 
		xDiff = 0;

	if(yCoord < getHeight() - 1)
		yDiff = abs(getPixel(xCoord, yCoord) - getPixel(xCoord, yCoord + 1));
	else 
		yDiff = 0;

	if(xDiff >= 50 && yDiff < 50)
		return '|';
	else if(xDiff < 50 && yDiff >= 50)
		return '-';
	else if(xDiff >= 50 && yDiff >= 50)
		return '+';
	else
		return ' ';
}
/*
//mapper of average filter
char avgfilter::mapper(int xCoord, int yCoord){
	int radius = fsize / 2;
	int startx, endx, starty, endy;
	if(xCoord - radius < 0)
		startx = 0;
	else
		startx = xCoord - radius;

	if(yCoord - radius < 0)
		starty = 0;
	else
		starty = yCoord - radius;
	
	if(xCoord + radius > getWidth() - 1)
		endx = getWidth() - 1;
	else
		endx = xCoord + radius;

	if(yCoord + radius > getHeight() - 1)
		endy = getHeight() - 1;
	else
		endy = yCoord + radius;

	int sum = 0;
	int count = 0;
	for(int i = starty; i <= endy; i++){
		for(int j = startx; j<= endx; j++){
			sum += getPixel(j, i);
			count++;
		}
	}
	
	int average = 0;
	if(count > 0)
		average = sum / count;

	return clssc(average / 17);
}

//mapper of bilateral filter
char bilatfilter::mapper(int xCoord, int yCoord){
	int radius = fsize / 2;
	int startx, endx, starty, endy;
	if(xCoord - radius < 0)
		startx = 0;
	else
		startx = xCoord - radius;

	if(yCoord - radius < 0)
		starty = 0;
	else
		starty = yCoord - radius;
	
	if(xCoord + radius > getWidth() - 1)
		endx = getWidth() - 1;
	else
		endx = xCoord + radius;

	if(yCoord + radius > getHeight() - 1)
		endy = getHeight() - 1;
	else
		endy = yCoord + radius;

	double sWeight = 1.0 /  (2.0 * pow(sSigma, 2));
	double iWeight;
	double sum = 0;
	double wSum = 0;
	double sDis, sWeightVal, iDis, weight;
	for(int i = starty; i <= endy; i++){
		for(int j = startx; j<= endx; j++){
			sDis = sqrt(pow(j - xCoord, 2) + pow(i - yCoord, 2));
			sWeightVal = exp(- pow(sDis, 2) * sWeight);
			iDis = abs(getPixel(j, i) - getPixel(xCoord, yCoord));
			iWeight = exp(- pow(iDis, 2) / (2.0 * pow(iSigma, 2)));
			weight = sWeightVal * iWeight;
			sum += weight * getPixel(j, i);
			wSum += weight;
		}
	}
	
	return clssc(int(round(sum / wSum)) / 17);
}
*/
//drawer class constructor
drawer::drawer(artist* Artist){
	myArtist = Artist;
}

//draw picture
string drawer::draw(){
	string result = "";
	for(int i = 0; i < getDHeight(); i++) {
		for(int j = 0; j < getDWidth(); j++){
			result += getDPixel(j, i);//get every pixel character and eppend
		}
		result += "\n";
	}	
	return result;
}

//draw downsampled picture
string downsample::draw(){
	string result = "";
	for(int i = 0; i < getDHeight() / 2; i++){
		for(int j = 0; j < getDWidth() / 2; j++){
			result += getDPixel(j * 2, i * 2);
		}
		result += "\n";
	}
	return result;
}

//draw upsampled picture
string upsample::draw(){
	string result = "";
	for(int i = 0; i < getDHeight() * 2; i++){
		for(int j = 0; j < getDWidth() * 2; j++){
			result += getDPixel(j / 2, i / 2);
		}
		result += "\n";
	}
	return result;
}

scale::scale(artist* Artist, int xprop, int yprop) : drawer(Artist){
	xProp = xprop;
	yProp = yprop;
}

//draw scaled picture
string scale::draw(){
	string result = "";
	double X = xProp;
	double Y = yProp;
	if(xProp < 0){
		X = - 1.0 / X;	
	}
	if(yProp < 0){
		Y = - 1.0 / Y;
	}	
	for(int i = 0; i < int(getDHeight() * Y); i++){
		for(int j = 0; j < int(getDWidth() * X); j++){
			result += getDPixel(int(j / X), int(i / Y));
		}
		result += "\n";
	}
	return result;
}

int main(int argc, char *argv[]) {

  if (argc != 4) {
    cout << "argc is not 4, but " << argc << endl;
    throw;
}
  // CREATE PARSER
  parser p;
  // LOAD IMAGE AND CONFIG
  vector<int> tokens = p.load_image(argv[1]);
  vector<string> configs = p.load_config(argv[2]);
  string style_target = configs[0];
  string drawer_target = configs[1];
  char *path_output = argv[3];
  
  int width = tokens[0];
  int height = tokens[1];
  vector<int> vals = {tokens.begin() + 2, tokens.end()};
  
  // CREATE ARTIST
  artist *style;
  if (style_target == "classic") {
    style = new classic(width, height, vals);
  } else if (style_target == "iclassic") {
    style = new iclassic(width, height, vals);
  } else if (style_target == "sobelx") {
    style = new sobelx(width, height, vals);
  } else if (style_target == "sobely") {
    style = new sobely(width, height, vals);
  } else if (style_target == "gradient") {
    style = new gradient(width, height, vals);
  } 

	
/*	else if (style_target == "avgfilter"){
	int kernelsize = stoi(configs[4]);
	style = new avgfilter(width, height, vals, kernelsize);
  } else if (style_target == "bilatfilter"){
	int kernelsize = stoi(configs[4]);
	int ssigma = stoi(configs[5]);
	int isigma = stoi(configs[6]);
	style = new bilatfilter(width, height, vals, kernelsize, ssigma, isigma);
  }

*/

	else {
	throw;
  }
  
  // CREATE DRAWER
  drawer *d;
  if (drawer_target == "drawer") {
    d = new drawer(style);
  } else if (drawer_target == "upsample") {
    d = new upsample(style);
  } else if (drawer_target == "downsample") {
    d = new downsample(style);
  } else if (drawer_target == "scale") {
    int scale_x = stoi(configs[2]);
    int scale_y = stoi(configs[3]);
    d = new scale(style, scale_x, scale_y);
} else {
throw; }
  
  // PERFORM DRAWING
  string output = d->draw();
  cout << output;
  // WRITE OUTPUT
  p.write_result(path_output, output);
  delete d;
return 0; }

#include <iostream>
#include <string>

using namespace std;

string conToBinOrOct(int deciNum, int bits, int base); //function that converts decimal to binary or octal.
string conToHex(int deciNum, int bits); //function that converts hexadecimal to decimal.
int bitNum(int deciNum, int base); //function that returns number of bits required

int main(){
	int deciNum, base, bits;
	string result;

	cin >> deciNum >> base;//get decimal and base
	bits = bitNum(deciNum, base);//calculates required bits for allocating result

	if (cin.peek() != '\n'){
		cout << "INVALID INPUT!!" << endl; //print error message when input is invalid
		return 0;
	}
	else if(deciNum < 0) {
		cout << "CANNOT INPUT NEGATIVE INTEGER!!" << endl; //print error when decimal is negative
		return 0;
	}
	//call for required functions according to base input
	else if (base == 2 || base == 8){ 
		result = conToBinOrOct(deciNum, bits, base);
	}	
	else if (base == 16){
		result = conToHex(deciNum, bits);
	}
	else
		cout << "INVALID BASE!!";

	cout << result << endl;

	return 0;
}

string conToBinOrOct(int deciNum, int bits, int base){
	int* binOct = new int[bits]; // dynamically allocate int array to put result in

	for(int i = 0; i < bits; i++){
		binOct[i] = deciNum % base;
		deciNum = deciNum / base;
	} // put result in dynamically allocated int array.
	
	string binOctResult = "";
	for(int i = 0; i < bits; i++){
		binOctResult = binOctResult + to_string(binOct[bits - i - 1]);
	} //convert result to string. (easier to print) 

	delete[] binOct;//free memory
	
	return binOctResult;//return binary or octal as string
}

string conToHex(int deciNum, int bits){
	int* hexa = new int[bits]; // dynamically allocate int array to put result in

	for(int i = 0; i < bits; i++){
		hexa[i] = deciNum % 16;
		deciNum = deciNum / 16;
	} // put result in dynamically allocated int array.
	
	string hexaResult = "";
	for(int i = 0; i < bits; i++){
		if(hexa[bits - i - 1] < 10){
			hexaResult = hexaResult + to_string(hexa[bits - i - 1]);
		}
		else {
			switch(hexa[bits - i - 1]){
				case 10 :
					hexaResult += "A";
					break;
				case 11 :
					hexaResult += "B";
					break;
				case 12 :
					hexaResult += "C";
					break;
				case 13 :
					hexaResult += "D";
					break;
				case 14 :
					hexaResult += "E";
					break;
				case 15 :
					hexaResult += "F";
					break;
				}
		}
	} //convert result to string.

	delete[] hexa;//free memory
	
	return hexaResult;//return result as string
}

int bitNum(int deciNum, int base){
	int num = deciNum;
	int count = 0; //counter variable to count reqiured bits

	//count bits in for loop.
	if(base == 2){
		for(count = 0; num > 0 ; count++) {
			num = num / 2;
		}
	}
	else if(base == 8){
		for(count = 0; num > 0 ; count++) {
			num = num / 8;
		}
	}	
	else if(base == 16){
		for(count = 0; num > 0 ; count++) {
			num = num / 16;
		}
	}
	else
		return 0; //no need to check invalid base here. main function will do.

	return count;//return number of bits
}

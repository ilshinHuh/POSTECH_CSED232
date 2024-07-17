#include <iostream>
#include <string>
#include <cmath>

using namespace std;


float toDeci(const string num, int& check); //function that converts input to decimals

int main(){
	char op; //operator input
	string num1, num2; //two number input

	cin >> op >> num1 >> num2; //get input

	if(cin.peek() != '\n'){
		cout << "INVALID INPUT!!" << endl; //show error when input is invalid
		return 0;
	}

	float deciNum1, deciNum2, result; //variables to put two number inputs as decimals and calculation result
	int checker; //checker to check valid input

	checker = 0; //checker initialized to zero. error message printes when check is 1

	//call function to convert input to decimals.
	deciNum1 = toDeci(num1, checker);
	deciNum2 = toDeci(num2, checker);
	
	if (checker == 1) {
		cout << "INVALID NUMBER INPUT!!" << endl;//show error message when checker is 1
		return 0;
	}
	//calculate results when inputs are valid
	else {
		if (op == '+'){
			result = deciNum1 + deciNum2;
		}
		else if (op == '-'){
			result = deciNum1 - deciNum2;
		}
		else if (op == '*'){
			result = deciNum1 * deciNum2;
		}
		else if (op == '/'){
			result = deciNum1 / deciNum2;
		}
		else {
			cout << "INVALID OPERATOR!!" << endl; //show error when operator is invalid
			return 0;
		}

	}
	
	cout << fixed;
	cout.precision(3);
	cout << result << endl; //print result to third decimal place

	return 0;
}


float toDeci(const string num, int& check) {
	float decimal = 0; //converted decimal
	int base, subNum, remainder; //base, extracted portion of input string in integer, remainder for conversion to decimal
	string ch;//extracted portion of input string in string

	base = 1;
	
	if(num == "0")
		decimal = 0; //to prevent crash with line 107
	else if(num.substr(0,2) == "0b") { //when string prefix is 0b, convert input from binary to decimal
		ch = num.substr(2);//extract required portion of string
		for(int i = 0; i < (int)ch.length(); i++){
			if(ch[i] != '0' && ch[i] != '1'){
				check = 1;
				return 0;
			}//check if input is valid
		}
		subNum = stoi(ch);
		while(subNum > 0){
			remainder = subNum % 10;
			decimal = decimal + remainder * base;
			base = base * 2;
			subNum = subNum / 10;
		}//convert 
	}	
	else if(num.substr(0,2) == "0X") { //when string prefix is 0X, convert input fron hexa to deci
		ch = num.substr(2);
		while(!ch.empty()){
			if(ch.back() >= '0' && ch.back() <= '9'){
				decimal = decimal + ((int)ch.back() - 48) * base;//get last char of string and perform calculation. when char is integer
				base = base * 16;
				ch.pop_back();//pop last char of string
			}
			else if(ch.back() >= 'A' && ch.back() <= 'F') {
				decimal = decimal + ((int)ch.back() - 55) * base;//get last last char of string and calc. when char is A~F
				base = base * 16;
				ch.pop_back();//pop last char
			}
			else {
				check = 1;
				return 0;
			}//check if input is invalid
		}
	}
	else if(num[0] == '0') {//when string prefix is 0 convert input form octal to decimal
		ch = num.substr(1);
		for(int i = 0; i < (int)ch.length(); i++){
			if(ch[i] < '0' || ch[i] > '7'){
				check = 1;
				return 0;
			}//check invalid input
		}
	
		subNum = stoi(ch);
		while(subNum > 0){
			remainder = subNum % 10;
			decimal = decimal + remainder * base;
			base = base * 8;
			subNum = subNum / 10;
		}//convert
	}
	else {
		check = 1;
		return 0;
	}//set checker to 1 if input is neither binary or octal or hexadecimal

	return decimal;//retun decimal
}


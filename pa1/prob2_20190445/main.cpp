#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(){
	char operat[6] = ""; //operator. 6 characters max because square is 6 letters
	float firNum, secNum, result; //two input numbers and result
	
	cin >> operat >> firNum; //get operator and first number
	string op = operat; //convert operat to string
	
	if (op == "+" || op == "-" || op == "*" || op == "/") {	//operation when operator is + or - or * or /
		cin >> secNum; //get second number input
	
		if(cin.peek() == '\n'){ // when user presses enter key after giving two number inputs
			//calculate result
			if(op == "+")
				result = firNum + secNum;
			else if(op == "-")
				result = firNum - secNum;
			else if(op == "*")
				result = firNum * secNum;
			else if(op == "/" && secNum != 0)
				result = firNum / secNum;
			else if(op == "/" && secNum == 0){
				cout << "CANNOT DIVIDE BY ZERO!!" << endl; //show error message in console when operator is '/' but second input is zero.
				return 0;
			}
		
			cout << fixed;
			cout.precision(3);
			cout << result << endl;//print result to three decimal places.
			return 0;
		}
		else {
			cout << "INVALID INPUT!!" << endl; //show error message when there are more inputs than requested or input is invalid
			return 0;
		}
	} 
	else if (op == "sqrt"  || op == "square") { //operation when operator is sqrt or square
		if(cin.peek() == '\n'){ // when user presses enter key after giving one number input
			if(op == "sqrt"){
				if(firNum >= 0){
					result = sqrt(firNum);
					cout << fixed;
					cout.precision(3);
					cout << result << endl; //print result
					return 0; 
				}
				else{ //when sqrt input is negative
					result = sqrt(-firNum);
					cout << fixed;
					cout.precision(3);
					cout << result << "i" << endl;//print result with imaginary number
					return 0;
				}	
			}
			else{
				result = pow(firNum,2);
				cout << fixed;
				cout.precision(3);
				cout << result << endl; //print result
				return 0;
			}
		}
		else {
			cout << "INVALID INPUT!!" << endl; //show error message when there are more inputs than requested or input is invalid
			return 0;
		}
	}
	else
		cout << "INVALID OPERATOR!!"<< endl; //show error message when operator is invalid

	return 0;
}


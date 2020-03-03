#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdlib>
#include<string>
using namespace std;

const string OPERATORS = "+-*x/" ;
const string SEPARATOR = " ";

double parsePostfix(string expression);
string getNextToken( string &expression);


template<typename DTYPE>
class stack{
	private:
		int size;
		int used;
		DTYPE *TOP;
		DTYPE *arr;
	public:
		stack(){
			used = 0;
			size = 10;
			TOP = &arr[0];
			arr = new DTYPE[size];
			for(int i = 0; i < size;i++){
				arr[i] = 0;
			}
		
		}
		
		DTYPE push(DTYPE d){
			if(arr == NULL){
				arr = new DTYPE[10];
				arr[0] = d;
			
				TOP = &arr[0];
				used++;
				return arr[0];
			}
			
			if(used==size){
				/*
				cout << "BEFORE ALLOT" <<endl;
				this->display_array();
				*/
				DTYPE* temp = new DTYPE[size];
				memcpy(temp,arr,size*sizeof(DTYPE));
				arr = new DTYPE[size +  10];
				memcpy(arr,temp,size*sizeof(DTYPE));
				memset(arr+size,'\0',size+10);
				size += 10; 
				/*
				cout <<"AFTER ALLOT " <<endl;
				this->display_array();
				*/
			}
			
 			//cout << used << "size : "<< size <<endl;
			arr[used] = d;
			TOP = &arr[used];
			used++;
		}
		bool is_empty(){
			return (used==0) ? true : false;
		}
		DTYPE pop(){
			if(used == 0){
				cout << "STACK IS EMPTY ";
				return 1;
			}
			used--;
			DTYPE temp = arr[used];
			arr[used] = 0;
			TOP = &arr[used-1];
			return temp;
		}
		bool display_stack(){
			cout << endl << "STACK : " <<endl;
			for(int i = used-1; i >= 0;i--){
				cout << endl << setw(3) << arr[i];
			}
			cout << endl;
		}
		bool display_array(){
			cout << endl << "ARRAY : " <<endl;
			for(int i = size-1; i >= 0;i--){
				cout << endl  << "#" << i  << " "<< setw(3) << arr[i];
			}
			cout << endl;
		}
		DTYPE peak(){
			if(used != 0)
			return *TOP ;
		}
		DTYPE ret_size(){
			return this->size;
		}
		~stack(){
			if(arr)
			delete []arr;
		}
	
};
void performCalculation(stack<double> &s, char op);
string getNextToken(string &expression) {
    string token;
	int sepLoc = expression.find(SEPARATOR);
	if(sepLoc != (int) string::npos) {
        token = expression.substr(0,sepLoc);
        expression = expression.substr(sepLoc+1,expression.size()-sepLoc);
	return token;
    }
	else{
        token = expression;
        expression = "";
		return token;
    }
}

double parsePostfix(string expression) {
    stack<double> s;
	string nextToken;
	if(expression[0]>='a' && expression[0]<='z')
		return 0;
	while(expression != "") {
	
        nextToken = getNextToken(expression);
	if
 	(OPERATORS.find(nextToken) == string::npos) {
	std::string::size_type sz;
	double operand = stod(nextToken);
            s.push(operand);
        }
	else{

	char op = (nextToken.c_str()[0]);
            performCalculation(s,op);
        }
    }
	return s.pop();
}
void performCalculation(stack<double> &s, char op) {
	double result;
	double operand2 = s.pop(); 

	double operand1 = s.pop();
	
	switch(op) {
	case '+': result = operand1 + operand2;
	break;
	
	case'-': result = operand1 - operand2;
	break;

	case '*':
	case 'x': result = operand1 * operand2;
	break;

	case '/': result = operand1 / operand2;
	break;
    }
    s.push(result);
}

bool is_operand(char ch){
	if(ch>='0' && ch<='9' || ch>='a' && ch <='z')
		return true;
	return false;
}
int precedence(char ch){
	char op[5] = {'-','+','/','*','^'};
	for(int i = 0; i < 5; i++){
		if(ch==op[i]){
			return i;
		}
	}
	return -1;
}
bool is_operator(char ch){
	if(precedence(ch) > -1)
		return true;
	return false;
}

string infix_to_postfix(string infix){
	int length = infix.length();
	int i = 0;
	stack<char> s;
	string postfix;
	while(i < length){
		//cout << endl << i << endl;
		if(is_operand(infix[i])){
			
			int  digits = 0;
			string digit;
			
			
			while(is_operand(infix[i])){
				digit += infix[i];
				i++;
			}
			
			//cout << endl << digit << endl;
			postfix.append(digit);
			postfix += " ";
			i--;
			//postfix.append(&infix[i],1);
		}
		else if(infix[i] == '('){
			s.push(infix[i]);
			//s.display_array();
		}
		else if(is_operator(infix[i])){
			if(s.is_empty()){
				s.push(infix[i]);
			}
			else if(s.peak() == '('){
				s.push(infix[i]);
			}
			else if(precedence(infix[i]) > precedence(s.peak())){
				
				s.push(infix[i]);
			}
			
			else{
				if(!s.is_empty()){
					char temp = s.pop();
					postfix += temp;
					postfix += " ";
					i--;
				}
				
			}
		}
		else if(infix[i] == ')'){
			if(!s.is_empty()){
			

				while(s.peak()!='('){
					
					char temp = s.pop();
					postfix += temp;
					postfix += " ";
					if(s.is_empty()){
						break;
					}
				}
				if(!s.is_empty())
				s.pop();
			}
			
		}
		
		//cout << endl << "char : " << infix[i] << " string : " << postfix << " TOS : " << s.peak() << endl ;
		i++;
	}
	while(!s.is_empty()){
		char temp = s.pop();
		postfix += temp;
		postfix += " ";
	}
	return postfix;
}
int main(){
	int type = 0;
	istream *inp;
	ostream *out;
	ifstream s("A2-IO-Cases\\A2-IO-Cases\\A2P2-in-01.txt");
	ofstream p("A2-IO-Cases\\A2-IO-Cases\\A2P2-in-01myOUT.txt");
	
	while(type==0){
		cout << "Enter type of input : " << endl;
		cout << '\t' << "1- User input : (input from keyboard - output on screen)" << endl;
		cout << '\t' << "2- filing input : (input from file - output on file)" << endl;
		cin >> type;
		if(type==2){
			if(!(s.is_open())){
				cout << "File NOT FOUND " ;
				return 1;
			}
			inp = &s;
			out = &p;
			break;
		}
		else if(type==1){
			inp = &cin;
			out = &cout;
			break;
		}
		else if(type!=1){
			cout << "INVALID INPUT "<<endl;
		}
	}
	
	string input;
	(*inp) >> input;
	
	do{
		 
		string postfix =  infix_to_postfix(input);
		input="";
		(*out) << postfix << endl;
		double answer = parsePostfix(postfix);
		cout << endl << "Answer : " << answer;
		(*inp) >> input;
		cout << " Postfix : " << postfix;
	}while(input!="");
	
	/*
	string input = "a+b*(c+d)+a*f";
	string postfix = infix_to_postfix(input);
	cout << endl << "PostFix Notation : " << postfix;

	*/
}

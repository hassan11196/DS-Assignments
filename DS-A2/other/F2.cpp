#include <iostream>
#include <cstring>
#include<string>
#include<cstdlib>
#include <stack>
using namespace std;

bool isOperand (char x)
{
	if (x>='a' && x<='z' || x>='A' && x<='Z' || x>='0' && x<='9')
	{
		return true;
	}
	else
		return false;
}

bool isOperator (char x)
{
	switch (x)
	{
		case '*':
		case '/':
		case '+':
		case '-':
			return true;
	}
	return false;
}

int isPrecedence (char x) 
{ 
    if (x=='*') 
    	return 4; 
    else if(x=='/') 
    	return 3;
    else if(x=='+') 
		return 2; 
    else if(x=='-') 
    	return 1; 
    else
    	return -1; // Stack is empty
} 

string InfixToPostfix (string infix)
{
	stack <char> s;
	string postfix;
	int len=infix.length();
	for (int i=0;i<len;i++) //(300+23)*(43-21)/(84+7)
	{
		if (isOperand(infix[i]))
		{
			postfix=postfix+infix[i];
		}
		
		else if (infix[i]=='(')
		{
			s.push(infix[i]);
		}
		
		else if (isOperator(infix[i]))
		{
			if (s.empty())
			{
				postfix=postfix+" ";
				s.push(infix[i]);
			}
			else if (s.top()=='(')
			{
				postfix=postfix+" ";
				s.push(infix[i]);
			}
			else if (isPrecedence(s.top())<isPrecedence(infix[i]))
			{
				postfix=postfix+" ";
				s.push(infix[i]);
			}
			else
			{
				char temp;
				temp=s.top();
				s.pop();
				postfix=postfix+" ";
				postfix=postfix+temp;
				i--;
			}
		}
		
		else if (infix[i]==')')
		{
			while (s.top()!='(')
			{
				char temp;
				temp=s.top();
				s.pop();
				postfix=postfix+" ";
				postfix=postfix+temp;
			}
			s.pop();
		}
	}
	while (!s.empty())
	{
		char temp;
		temp=s.top();
		s.pop();
		postfix=postfix+" ";
		postfix=postfix+temp;
	}
	return postfix;
}

int Evaluation (string postfix)
{
	//(300+23)*(43-21)/(84+7)
	stack <int> s;
	int len=postfix.length();

	if (postfix[0]>='a' && postfix[0]<='z' || postfix[0]>='A' && postfix[0]>='Z')
	{
		cout<<"Alphabetical Expression can't be Evaluated";
		exit(1);
	}
	
	for (int i=0 ; i<len ; i++)
	{
		if (postfix[i]>='0' && postfix[i]<='9')
		{
			string temp;
			int k = 0;
			while(postfix[i]>='0' && postfix[i]<='9'){
				temp.append(&postfix[i]);
				i++;
			}
			i--;
			
			s.push(atoi(temp.c_str()));
		}
		else if (isOperator(postfix[i]))
		{
			int num2=s.top();
			s.pop();
			int num1=s.top();
			s.pop();
		
			switch (postfix[i])  
            {  
        	    case '+': 
					s.push(num1+num2); 
					break;  
            	case '-': 
					s.push(num1-num2);  
					break;  
        		case '*': 
					s.push(num1*num2);  
					break;  
        		case '/': 
					s.push(num1/num2);  
					break;  
            }  
		}
	}
	return s.top();
}

int main ()
{
	//(300+23)*(43-21)/(84+7)
	string infix="(300+23)*(43-21)/(84+7) ";
	string postfix;
	postfix=InfixToPostfix(infix);
	cout<<postfix<<endl;
	int result=Evaluation(postfix);
	cout<<result;
}


#include<iostream>
#include<fstream>

using namespace std;

int main(){
	
	int m = 0, n = 0;
	int type = 0;
	istream *some;
	ifstream s("CS201-DS-A1TestCases\\CS201-DS-A1TestCases\\A1P1-Testcases\\A1P1IO1.txt");
	while(type==0){
		cout << "Enter type of input : " << endl;
		cout << '\t' << "1- User input" << endl;
		cout << '\t' << "2- filing input" << endl;
		cin >> type;
		if(type==2){
			some = &s;
			break;
		}
		else if(type==1){
			some = &cin;
			break;
		}
		else if(type!=1){
			cout << "INVALID INPUT "<<endl;
		}
	}
	
	cout << "input : " << endl;
	(*some) >> m >> n;
	char **arr = new char*[m];
	for(int i = 0; i < m; i++){
		arr[i] = new char[n];
	}
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			(*some) >> arr[i][j];
		}
	}
	char *ptr = *arr;
	int fflag = 0, eflag = 0;
	int r = 0, c = 0;

	for(int i = 0; i  < m; i++){
		if(ptr[i] == 's'){
			ptr = ((*arr) + i)  ;
			c = i;
			cout << "r = " << r << " c = " << c << endl;
		}
	}
	
	char **mov = arr + c;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			cout <<  arr[i][j];
		}
		cout << endl;
	}
	while(!eflag){
		
		fflag = 0;
		if(mov[r][c+1] == '-' || mov[r][c+1] == 'e' ){
			c++;
			fflag=1;
		}
		else if(mov[r+1][c] == '-' || mov[r+1][c] == 'e' ){
			r++;
			fflag=1;
		}
		else if(mov[r][c-1] == '-' || mov[r][c-1] == 'e'){
			c--;
			fflag=1;
		}
		else if(mov[r-1][c] == '-' || mov[r-1][c] == 'e'){
			r--;
			fflag=1;
		}
		
		if(mov[r][c] == 'e'){
			cout << "r = " << r << " c = " << c << endl;
			eflag = 2;
			break;
		}
		else{
			mov[r][c] = 'v';
		} 
		if(fflag==1)
		cout << "r = " << r << " c = " << c << endl;
		else{
			cout << endl << "NO PLACE TO MOVE " << endl;
			break;	
		}
		
		
	}
	if(!eflag){
		cout << endl << "End Not Reached " << endl;
	}
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			cout <<  arr[i][j];
		}
		cout << endl;
	}

	
	
	
	
	return 0;
}

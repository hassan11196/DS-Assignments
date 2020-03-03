#include<iostream>
#include<fstream>

using namespace std;

int main(){
	int type = 0;
	istream *inp;
	ifstream s("CS201-DS-A1TestCasesWitoutput\\P3\\A1P3IO6.txt");
	while(type==0){
		cout << "Enter type of input : " << endl;
		cout << '\t' << "1- User input" << endl;
		cout << '\t' << "2- filing input" << endl;
		cin >> type;
		if(type==2){
			if(!(s.is_open())){
				cout << "File NOT FOUND " ;
				return 1;
			}
			inp = &s;
			break;
		}
		else if(type==1){
			inp = &cin;
			break;
		}
		else if(type!=1){
			cout << "INVALID INPUT "<<endl;
		}
	}
	int n = 0,t = 0;
	(*inp) >> n;
	int *arr = new int[n];
	for(int i = 0; i < n; i++){
		(*inp) >> arr[i];
	}	
	(*inp) >> t;
	
	int *cnt = new int[t];
	int temp_i = 0, temp_j = 0, temp_k = 0;
	for(int i = 0; i < t; i++){
		cnt[i] = 0;
		(*inp) >> temp_i >> temp_j >> temp_k;
		for(int j = temp_i; j <= temp_j; j++){
			if(arr[j] > temp_k){
				cnt[i]++;
			}
		}
	}
	
	cout << endl;
	for(int i = 0;i < t; i++){
		cout << cnt[i] << endl;
	}
	ofstream out("CS201-DS-A1TestCasesWitoutput\\P3\\A1P3IO6myout.txt");
	if(!out.is_open()){
		cout << "ERROR OPENING OUTPUT FILE. EXIT 1" << endl;
		return 1;
	}
	for(int i = 0;i < t; i++){
		out << cnt[i] << endl;
	}
	if(type == 2)
		s.close();
	
	out.close();
	delete []cnt;
	delete []arr;
	return 0;
}

#include<iostream>
#include<cstdlib>
#include<typeinfo>

using namespace std;

template <class DTYPE>
class dyn_2d_safe_arr{
	private:
		int row;
		int col;
		DTYPE **arr;
		
	public:
		dyn_2d_safe_arr(){
			row = 0;
			col = 0;
			arr = NULL;
		}
		dyn_2d_safe_arr(int r,int c){
			this->row = r;
			this->col = c;
			this->arr = new DTYPE*[r];
			for(int i = 0; i < r; i++){
				arr[i] = new DTYPE[c + 1]; // Plus 1 For null termination
				arr[i][col] = '\0';
			}
		}
		dyn_2d_safe_arr(const dyn_2d_safe_arr &obj){
			this->row = obj.row;
			this->col = obj.col;
			this->arr = new DTYPE*[row];
			for(int i = 0; i < row; i++){
				arr[i] = new DTYPE[col + 1]; // Plus 1 for null termination
				for(int j = 0; j < col; j++){
					arr[i][j] = obj.arr[i][j];
				}
				arr[i][col] = '\0'; // For null termination
			}
		}
		/*
		static dyn_2d_safe_arr resize(dyn_2d_safe_arr &obj,int r,int c){
			
		}
		dyn_2d_safe_arr resize(int r, int c){
			dyn_2d_safe_arr temp(*this);
			this->row = r;
			this->col = c;
			this->arr = new DTYPE*[row];
		}
		*/
		int row_(){
			return this->row;
		}
		int col_(){
			return this->col;
		}
		DTYPE* operator[](const int i){
			if(i >= 0 && i < row){
				return arr[i];
			}
			else{
				cout << endl << "ARRAY INDEX OUT OF BOUND." << endl;
				exit(1);
			}
		}
		DTYPE& operator()(int i,int j){
			if(i >= 0 && i < row && j < col && j >= 0){
				return arr[i][j];
			}
			else{
				//DTYPE temp;
				return arr[i][col];
				//cout << endl << "ARRAY INDEX OUT OF BOUND." << endl;
				//exit(1);
			}
		}
		bool operator()(int i,int j,DTYPE obj){
			if(i >= 0 && i < row && j < col && j >= 0){
				arr[i][j] = obj;
				return 0;
			}
			else{
				cout << endl << "ARRAY INDEX OUT OF BOUND." << endl;
				exit(1);
			}
		}
	
		bool operator=(const dyn_2d_safe_arr &obj){
			if(this == &obj){
				return false;
			}
			this->row = obj.row;
			this->col = obj.col;
			this->arr = new DTYPE*[row];
			for(int i = 0; i < row; i++){
				arr[i] = new DTYPE[col + 1]; // Plus 1 for null termination
				for(int j = 0; j < col ; j++){
					arr[i][j] = obj.arr[i][j];
				}
				arr[i][col] = '\0'; // For null termination
			}
			return true;
		}
		
		void display(){
			cout << endl << "Rows : " << this->row << " Columns : " << this->col << endl;
			for(int i = 0; i < row; i++){
				
				for(int j = 0; j < col; j++){
					cout << arr[i][j] << " "; 
				}
				cout << endl;
			}
		}
		
		void autofill(){
			for(int i = 0; i < row; i++){
				arr[i] = new DTYPE[col + 1]; // PLus 1 For null termination
				for(int j = 0; j < col; j++){
					arr[i][j] = (DTYPE)('a' + i + j);
				}
				arr[i][col] = '\0'; // For null termination
			}
		}
		
		~dyn_2d_safe_arr(){
			for(int i = 0; i < row; i++){
				delete []arr[i];
			}
			delete []arr;
			row = 0;
			col = 0;
		}
};



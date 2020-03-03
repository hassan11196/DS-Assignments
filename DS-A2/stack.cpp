#include<iostream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
using namespace std;

template<typename DTYPE>
class stack{
	private:
		unsigned int size;
		unsigned int used;
		DTYPE *TOP;
		DTYPE *arr;
	public:
		stack(){
			used = 0;
			size = 10;
			TOP = NULL;
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
		
		DTYPE pop(){
			used--;
			arr[used] = 0;
			TOP = &arr[used-1];
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
			cout << *TOP ;
		}
		DTYPE ret_size(){
			return this->size;
		}
		~stack(){
			if(arr)
			delete []arr;
		}
	
};

int main(){
	stack<int> s1;
	
	for(int i =0 ; i <20;i++){
		s1.push(i);
	}
	cout << endl;
	s1.peak();
	cout << s1.display_stack();

	cout << endl;
	for(int i =0 ; i <10;i++){
		s1.pop();
	}
	cout << endl;
	s1.peak();
	cout << s1.display_array();
	cout << endl;

	return 0;
}

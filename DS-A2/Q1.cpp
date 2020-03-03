#include<iostream>
#include<fstream>
#include<cstring>
#include<iterator>
#include<sstream>
#include<vector>
#include"dyn_2d_safe_arr_lib.cpp"

using namespace std;

template <typename T>
class queue{
	private:
		T* arr; 
		int size;
		int used;
		int front;
		int end;
		int served;
		int waiting;
	public:
		queue(){
			size = 100;
			arr = new T[size];
			used = 0; front = -1; end = -1; served = 0; waiting = 0;
		}
		T* arr_ret(){
			return this->arr;
		}
		int size_ret(){
			return this->size;
		}
		int used_ret(){
			return this->used;
		}
		int front_ret(){
			return this->front;	
		}
		int end_ret(){
			return this->end;	
		}
		int served_ret(){
			return this->served;	
		}
		int waiting_ret(){
			return this->waiting;	
		}
		
		bool is_empty(){
			return (front == -1 && end == -1) ? true:false;
		}
		T push(T data){
			cout << endl << "size : " << size << " use : " << used   <<  " front : " << front << " end : " << end << " data : " << data;
			if((end + 1 == front && used==size) || (front == 0 && end == size - 1 && used==size)){
				
				T* temp = new T[size];
				memcpy(temp,arr,size*sizeof(T));
				delete []arr;
				arr = new T[size +  10];
				if(end+1 == front){
					memcpy(arr,temp + front,(size - front)*sizeof(T));
					memcpy(arr + size - front,temp,(front)*sizeof(T));
				}
				else{
					memcpy(arr,temp,size*sizeof(T));
				}
				memset(arr+size,'\0',size+10);
				size += 10;
				
				front = 0;
				end = size - 10;
				arr[end] = data;
				used++;
				waiting++;
				return arr[end];
			}
			if(front==-1 && end==-1){
				arr[0] = data;
				front = 0;
				end = 0;
				used++;
				waiting++;
				return arr[end];
 			}
			if(front==end){
				end  = (end + 1)%size;
				arr[end] = data;
				used++;
				waiting++;
				return arr[end];
			}
			if(end+1 != front && end+1 != size - 1){
				arr[(end + 1)%size] = data;
				end  = (end + 1)%size;
				
				used++;
				waiting++;
				return arr[end];
			}
			if(front > 0 && end+1 != size - 1){
				arr[(end + 1)%size] = data;
				end  = (end + 1)%size;
				used++;
				waiting++;
				return arr[end];
			}
			arr[(end + 1)%size] = data;
			end  = (end + 1)%size;
			used++;
			waiting++;
			return arr[end];
		}
		T peak_end(){
			return arr[end];
		}
		T pop(){
			T f = arr[front];
			if(front == -1){
				cout << endl << "QUEUE IS EMPTY." << endl ;
			}
			if(end > 0)
				front++;
			if(front-1==end){
				front = -1;
				end=-1;
			}
			if(front==size)
				front = 0;
			used--;
			waiting--;
			served++;
			return f;
		}
		void display_arr(){
			cout << endl;
			cout << "size :  " << this->size << " used : " << this->used  << " front : " << this->front << " end : " 
				 << this->end << " waiting : " << this->waiting << " served : " << this->served << endl; 
			for(int  i = 0;  i < size; i++){
				cout << i << " <" << arr[i] << " >" << endl;
			}
			cout << endl;
		}
		void display_queue(){
			cout << endl;
			if(front == -1 && end == -1){
				cout << endl << "Empty Queue" << endl; 
				return ;
			}
			if(front < end){
				for(int  i = front;  i <= end; i++){
					cout << i << " <" << arr[i] << " >" << endl;
				}	
			}
			else{
				int k = front;
				for(int  i = 0;  i < waiting; i++){
					cout << k << " <" << arr[k] << " >" << endl;
					k = (k + 1) % size;  
				}
			}
			cout << endl;
		}
		~queue(){
			if(size>0)
			delete []arr;
			size = 0;
		}
};

class maze_block;

char path(int,int,dyn_2d_safe_arr<maze_block>&,string);

class maze_block{
	public:
		int row;
		int col;
		char prop;
		static dyn_2d_safe_arr<int> path_step;
		
		static void path_start(maze_block& start){
			int temp[2] = {start.row, start.col};
			path_step(0,0,start.row);
			path_step(0,1,start.col);	
		}
		
		static void path_end(maze_block &end){
			int temp[2] = {end.row, end.col};
			path_step(1,0,end.row);
			path_step(1,1,end.col);
		}
		
		static void path_insert(maze_block &s){
			int temp[2] = {s.row,s.col};
			path_step.insert_at(temp,2,path_step.row_() - 1); // Insert at second last row because last row is end
		}
		
		static void path_find_delete(maze_block &s){
			for(int i = 1; i <  path_step.row_() ; i++ ){
				if(path_step[i][0] == s.row && path_step[i][1] == s.col){
					path_step.delete_at(i);
				}
			}
		}
		
		static void path_step_display(){
			for(int i = 0; i < path_step.row_() ; i++){	
				cout << endl << path_step[i][0] << " " << path_step[i][1];				
			}
		}
			
		maze_block():row(0),col(0),prop('-'){
		}
		maze_block(int i,int j,char p):row(i),col(j),prop(p){
		}
		maze_block operator=(maze_block &obj){
			this->row = obj.row;
			this->col = obj.col;
			this->prop = obj.prop;
		}
		
	
		bool is_wall(){
			if(this==NULL)
				return false;
			return (prop == '*' ? true:false);
		}
		bool is_path(){
			if(this==NULL)
				return false;
			return ((prop == '-' || prop == 'e') ? true:false);
		}		
		bool is_visited(){
			if(this==NULL)
				return false;
			return (prop == 'v' ? true:false);
		}
		bool is_start(){
			if(this==NULL)
				return false;
			return (prop == 's' ? true:false);
		}
		bool is_end(){
			if(this==NULL)
				return false;
			return (prop == 'e' ? true:false);
		}
		bool is_back(){
			if(this==NULL)
				return false;
			return (prop == 'b' ? true:false);
		}
		
		void visit(){
			this->prop = 'v';
		}
		void back(){
			this->prop = 'r';
		}
		maze_block** vicinty(dyn_2d_safe_arr<maze_block>& maze,bool (maze_block::*is_something)() ) { // where something can be path,visited,end 
			int r = this->row; 
			int c = this->col;
			
			char possible[4] = {'\0'};
			possible[0] = (c + 1 < maze.col_() && c + 1 >= 0) ? 'a':'\0';
			possible[1] = (c - 1 < maze.col_() && c - 1 >= 0) ? 'b':'\0';
			possible[2] = (r + 1 < maze.row_() && r + 1 >= 0) ? 'c':'\0';
			possible[3] = (r - 1 < maze.row_() && r - 1 >= 0) ? 'd':'\0';
			  	
			maze_block **paths_to_go = new maze_block*[4];	
			for(int i = 0; i < 4; i++){
				paths_to_go[i] = NULL;
			}
			if(possible[0] && (maze(r,c+1).*is_something)()){
				paths_to_go[0] = &maze(r,c+1);
			}	
			else if(possible[1] && (maze(r,c-1).*is_something)()){
				paths_to_go[1] = &maze(r,c-1);
			}	
	    	else if(possible[2] && (maze(r+1,c).*is_something)()){
				paths_to_go[2] = &maze(r+1,c);
			}		
			else if(possible[3] && (maze(r-1,c).*is_something)()){
				paths_to_go[3] = &maze(r-1,c);
			}
			
			return paths_to_go;
		}
		
		static void print_solved(dyn_2d_safe_arr<maze_block> maze){ // To Print MAZE , REDUNDANT CODE
			int flag = 0;
			int r = 0, c = 0;
			for(int i = 0; i < maze.row_(); i++){
				for(int j = 0; j < maze.col_(); j++){
					if(maze(i,j).is_start()){
						cout << endl << i << " " << j ; 
						r = i;
						c = j;
						flag=1;
						break;
					}
				}
				if(flag==1)
					break;
			}
			for(int i = 0; i < maze.row_(); i++){
				for(int j = 0; j < maze.col_(); j++){
					if(maze(i,j).is_visited()){
						cout << endl << i << " " << j ; 
					}
				}
			}
		int eflag = 0,fflag = 0;
		
		while(!eflag){
		
			fflag = 0;
			if(maze(r,c+1).is_visited() || maze(r,c+1).is_end() ){
				maze(r,c+1).back();
				c++;
				fflag=1;
			}
			else if(maze(r,c-1).is_visited() || maze(r,c-1).is_end() ){
				maze(r,c-1).back();
				c--;
				fflag=1;
				
			}
			else if(maze(r+1,c).is_visited() || maze(r+1,c).is_end()){
				maze(r+1,c).back();
				r++;
				fflag=1;
			}
			else if(maze(r-1,c).is_visited() || maze(r-1,c).is_end()){
				maze(r-1,c).back();
				r--;
				fflag=1;
			}	
		
			if(maze(r,c).is_end()){
				cout << "r = " << r << " c = " << c << endl;
				eflag = 2;
				break;
			}
			if(fflag==1){
				cout << "r = " << r << " c = " << c << endl;
			}
			else{
				cout << endl << "NO PLACE TO MOVE " << endl;
				break;	
			}
		}
			
			
			flag=0;
			for(int i = 0; i < maze.row_(); i++){
				for(int j = 0; j < maze.col_(); j++){
					if(maze(i,j).is_end()){
						cout << endl << i << " " << j ; 
						flag=1;
						break;
					}
				}
				if(flag==1)
				break;
			}
		}
		
		maze_block operator=(char pr){
			this->prop = pr;
		}
		string to_string(){
			string str;
			stringstream ss(str);
			ss << "(" << (this->row) <<  "," << (this->col) << ")"; 
			ss>> str;
			return str;
		}
		friend istream& operator>> (istream& i,maze_block& obj){
			i >> obj.prop;
			return i;
		}
		friend ostream& operator<< (ostream& o,maze_block& obj){
			o << obj.prop;
			return o;
		}
	
};


int path_finder(dyn_2d_safe_arr<maze_block> &obj){
	int r = ~0, c = ~0;
	int end_r = ~0, end_c = ~0;
	
	for(int i = 0; i  < obj.row_(); i++){
		for(int j = 0; j < obj.col_(); j++){
			if(obj(i,j).is_end()){
			 end_r = i;
			 end_c = j;
			 maze_block temp(i,j,'e');
			 maze_block::path_end(temp);
			 break;
			}
		}
	}
	if(end_r == ~0 || end_c == ~0){
		return 1; // No Exit In Maze
	}
	
	
	for(int i = 0; i  < obj.row_(); i++){
		for(int j = 0; j < obj.col_(); j++){
			if(obj(i,j).is_start()){
			 r = i;
			 c = j;
			 break;
			}
		}
	}
	
	if(r == ~0 || c == ~0){
		return 1; // No Start In Maze
	}
	
	queue<maze_block> q;
	q.push(obj(r,c));
	string start_path = obj(r,c).to_string();
	vector< vector<maze_block> > path_arr;
	
	vector<maze_block> start;
	start.push_back(obj(r,c));

	while(!q.is_empty()){
		
		maze_block** possible = obj(r,c).vicinty(obj,maze_block::is_path);
		int flag= 0;
		for(int i = 0; i < 4; i++){
			if(possible[i] != NULL){
				q.push(*possible[i]);
				start.push_back(*possible[i]);
				path_arr.push_back(start);
				flag=1;
				possible[i]->visit();
			}
		}
		if(flag==0){
		
			do{
				maze_block temp(q.pop());	
			}while(temp.is_visited());
			q.push(temp);
		}
	}
	
	
	
	//char temp = path(r,c,obj,"forward");
	
	/*
	if(temp != 'e'){
		cout << "NOT RETURNING E " << endl;
		return 1;
	}
		*/
	return 0;
}

dyn_2d_safe_arr<int> maze_block::path_step(2,2);
int end_reached = 0;

char path(int r,int c,dyn_2d_safe_arr<maze_block> &maze,string direction){
	
	char pathways;
	
	if(r>maze.row_() || c > maze.col_() || r < 0 || c < 0){
		return  'O';
	}
	if(maze(r,c).is_start()){
		maze_block::path_start(maze(r,c));
		maze_block (**paths_to_end) = maze(r,c).vicinty(maze,&maze_block::is_end);
		for(int i = 0; i < 4; i++){
			if(paths_to_end[i] != NULL){
				end_reached = 1;
				delete []paths_to_end;
				return 'e';
			}
		}
	}
	else{
		maze_block (**paths_to_end) = maze(r,c).vicinty(maze,&maze_block::is_end);
		for(int i = 0; i < 4; i++){
			if(paths_to_end[i] != NULL){
				end_reached = 1;
				delete []paths_to_end;
				return 'e';
			}
		}
	}
	
		/* 	
			At first I made separate if-end conditionals to find next block, but similar code was repated all across
		 	so to minimize redundant code, I made the member function vicinty that checks all 
			adjacent blocks(right,left,down,up) of a block with coordinates (r,c).
			vicinity returns a double pointer poininting to array that holds pointers to maze_block elements in 
			dyn_2d_safe_arr<maze_block> maze.
		*/
		
		maze_block (**paths_to_go) = maze(r,c).vicinty(maze,&maze_block::is_path);
		
		for(int i = 0; i < 4; i++){
			if(paths_to_go[i] != NULL){
				(*paths_to_go[i]).visit();
				maze_block::path_insert((*paths_to_go[i]));
				pathways=path((*paths_to_go[i]).row,(*paths_to_go[i]).col,maze,"forward");
			}
		}
		
		delete []paths_to_go;
		
	if(pathways=='e'){
		return 'e';
	}
	else{ // To Back Track
		if(!end_reached){
			maze_block (**paths_to_go_back) = maze(r,c).vicinty(maze,&maze_block::is_visited);
		
			for(int i = 0; i < 4; i++){
				if(paths_to_go_back[i] != NULL){
					//(*paths_to_go_back[i]).back();
					if(maze(r,c).is_visited())
						maze(r,c).back();
					maze_block::path_find_delete(maze(r,c));
					pathways=path((*paths_to_go_back[i]).row,(*paths_to_go_back[i]).col,maze,"backward");
				}
			}
	
			delete []paths_to_go_back;	
		}
			
	}
	return '*';
}

int main(){
	int type = 0;
	int m = 0, n = 0;
	istream *inp;
	ostream *out;
	ifstream s("A2-IO-Cases\\A2-IO-Cases\\A2P1-in-01.txt");
	ofstream p("A2-IO-Cases\\A2-IO-Cases\\A2P1-in-01myOUT.txt");
	
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
	
	(*inp) >> m >> n;
	
	dyn_2d_safe_arr<maze_block> maze(m,n);
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			char temp;
			(*inp) >> temp;
			maze(i,j,maze_block(i,j,temp));
		}
	}
	cout << endl;
	
	int temp = path_finder(maze);
	if(temp != 0){
		cout << endl << "No Solution" ;
	}
	else{
		//maze.display();
		//maze_block::path_step_display();	
		for(int i = 0; i < maze_block::path_step.row_(); i++){
				(*out) << maze_block::path_step[i][0] << " " << maze_block::path_step[i][1];
				(*out) << endl;
		}
	
	}
	s.close();
	p.close();
	
	
	return 0;
}


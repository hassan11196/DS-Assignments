#include<iostream>
#include<fstream>
#include<vector>
#include<iterator>
#include"dyn_2d_safe_arr_lib.cpp"

using namespace std;

class maze_block;


class maze_arr : public dyn_2d_safe_arr<maze_block>{
	public:
		maze_arr(int r, int c) : dyn_2d_safe_arr(r,c){

		}
};
char path(int,int,maze_arr&,string);

class maze_block{
	public:
		int row;
		int col;
		char prop;
		static vector<vector <int> > steps;

		static void step_start(maze_block& start){
			vector<int> temp;
			temp.push_back(start.row);
			temp.push_back(start.col);
			maze_block::steps.insert(steps.begin(),temp);
			
		}
		static void step_end(maze_block& end){
			vector<int> temp;
			temp.push_back(end.row);
			temp.push_back(end.col);
			maze_block::steps.insert(steps.end(),temp);
		}
		static void step_find_delete(maze_block& find){
			for(int i = 0; i <  steps.size(); i++ ){
				/*
				vector<int> temp;
				temp.push_back(find.row);
				temp.push_back(find.col);
				*/
				if(steps[i][0] == find.row && steps[i][1] == find.col){
					maze_block::steps.erase(steps.begin() + i);
				}
			}
		}
		static void step_insert(maze_block& insert){
			vector<int> temp;
			temp.push_back(insert.row);
			temp.push_back(insert.col);
			maze_block::steps.push_back(temp);
		}
		static void step_display(){
			for(int i = 0; i < steps.size() ; i++){
				
				cout << endl << maze_block::steps[i][0] << " " << maze_block::steps[i][1];
				
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
			return (prop == '-' ? true:false);
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
		maze_block** vicinty(maze_arr& maze,bool (maze_block::*is_something)() ) { // where something can be path,visited,end 
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
		
		static void print_solved(maze_arr maze){
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
		friend istream& operator>> (istream& i,maze_block& obj){
			i >> obj.prop;
			return i;
		}
		friend ostream& operator<< (ostream& o,maze_block& obj){
			o << obj.prop;
			return o;
		}
	
};
void path_finder(maze_arr &obj){
	int r = 0, c = 0;
	
	for(int i = 0; i  < obj.col_(); i++){
		if(obj(0,i).is_start()){
			c = i;
			break;
			//cout << endl << " Start : r = " << r << " c = " << c << endl;
		}
	}
	
	char temp = path(r,c,obj,"forward");
	//cout << "TEMP : " << temp << endl;
}

vector < vector<int> >  maze_block::steps; 
int  lol_count = 0, end_reached = 0;

char path(int r,int c,maze_arr &maze,string direction){
	lol_count++;
	
	//cout << '\t' << "R : " << r << " C : " << c  << " lol count : "<< lol_count <<endl;
	
	char pathways;
	
	/*
	for(int i = 0; i < maze.row_(); i++){
		cout << i + 1 << " ";
		for(int j = 0; j < maze.col_(); j++){
			cout << maze(i,j);
		}
		cout << endl;
	}
	*/
	
	if(r>maze.row_() || c > maze.col_() || r < 0 || c < 0){
		cout << endl << "OUT OF LEAGUE BRUH " << endl;
		return  'O';
	}
	if(maze(r,c).is_start()){
		//cout << endl << "r : " << r << " c : " << c << endl;
		maze_block::step_start(maze(r,c));
	}
	else{
		
		maze_block (**paths_to_end) = maze(r,c).vicinty(maze,&maze_block::is_end);
		
		for(int i = 0; i < 4; i++){
			if(paths_to_end[i] != NULL){
				//cout << " r = " << (*paths_to_end[i]).row << " c = " << (*paths_to_end[i]).col << endl;
				end_reached = 1;
				maze_block::step_end(*(paths_to_end[i]));
				return 'e';
			}
		}
		
		delete []paths_to_end;

	}
	
	/*
	if(maze(r,c).is_visited()){
		cout << endl << "r : " << r  << " c : " << c << endl;
	}
	*/
	/*
	char possible[4] = {'\0'};

	possible[0] = (c + 1 < maze.col_() && c + 1 >= 0) ? 'a':'\0';
	possible[1] = (c - 1 < maze.col_() && c - 1 >= 0) ? 'b':'\0';
	possible[2] = (r + 1 < maze.row_() && r + 1 >= 0) ? 'c':'\0';
	possible[3] = (r - 1 < maze.row_() && r - 1 >= 0) ? 'd':'\0';
	  
	/*  
	if(possible[0]){
		if(maze(r,c+1).is_path()){
			maze(r,c+1).visit();
			pathways=path(r,c+1,maze);
		}	
	}
	
	if(possible[1]){
		if(maze(r,c-1).is_path()){
			maze(r,c-1).visit();
			pathways=path(r,c-1,maze);
		}
	}
	if(possible[2]){
		if(maze(r+1,c).is_path()){
			//cout << endl << "going down bruh " << endl;
			maze(r+1,c).visit();
			pathways=path(r+1,c,maze);
		}		
	}
	
	if(possible[3]){
		if(maze(r-1,c).is_path()){
			maze(r-1,c).visit();
			pathways=path(r-1,c,maze);
		}	
	}
	*/
		/* 	
			At first I made separate if-end conditionals to find next block, but similar code was repated all across
		 	so to minimize redundant code, I made the member function vicinty that checks all 
			adjacent blocks(right,left,down,up) of a block with coordinates (r,c).
			vicinity returns a double pointer poininting to array that holds pointers to maze_block elements in 
			maze_arr maze.
		*/
		
		maze_block (**paths_to_go) = maze(r,c).vicinty(maze,&maze_block::is_path);
		
		for(int i = 0; i < 4; i++){
			if(paths_to_go[i] != NULL){
				(*paths_to_go[i]).visit();
				maze_block::step_insert((*paths_to_go[i]));
				pathways=path((*paths_to_go[i]).row,(*paths_to_go[i]).col,maze,"forward");
			}
		}
		
		delete []paths_to_go;
		
		/*
		if(possible[0] && maze(r,c+1).is_path()){
			maze(r,c+1).visit();
			pathways=path(r,c+1,maze,"forward");
		}	
	
	
		else if(possible[1] && maze(r,c-1).is_path()){
			maze(r,c-1).visit();
			pathways=path(r,c-1,maze,"forward");
		}
	
	
	    else if(possible[2] && maze(r+1,c).is_path()){
			//cout << endl << "going down bruh " << endl;
			maze(r+1,c).visit();
			pathways=path(r+1,c,maze,"forward");
		}		
	
	
		else if(possible[3] && maze(r-1,c).is_path()){
			maze(r-1,c).visit();
			pathways=path(r-1,c,maze,"forward");
		}
		*/

	if(pathways=='e'){
		return 'e';
	}
	else{
		if(!end_reached){
			maze_block (**paths_to_go_back) = maze(r,c).vicinty(maze,&maze_block::is_visited);
		
			for(int i = 0; i < 4; i++){
				if(paths_to_go_back[i] != NULL){
					//(*paths_to_go_back[i]).back();
					maze(r,c).back();
					maze_block::step_find_delete(maze(r,c));
					pathways=path((*paths_to_go_back[i]).row,(*paths_to_go_back[i]).col,maze,"backward");
				}
			}
	
			delete []paths_to_go_back;	
		}
			
	}
	
	/*
	if(pathways != 'e'){
		
		if(possible[0] && maze(r,c+1).is_visited()){
			maze(r,c).back();
			pathways=path(r,c+1,maze,"bacward");
		}	
	
	
		else if(possible[1] && maze(r,c-1).is_visited()){
			maze(r,c).back();
			pathways=path(r,c-1,maze,"backward");
		}
	
	
	    else if(possible[2] && maze(r+1,c).is_visited()){
			//cout << endl << "going down bruh " << endl;
			maze(r,c).back();
			pathways=path(r+1,c,maze,"backward");
		}		
	
	
		else if(possible[3] && maze(r-1,c).is_visited()){
			maze(r,c).back();
			pathways=path(r-1,c,maze,"backward");
		}
	
	}
	*/
	return '*';
}

int main(){
	
	int m = 0, n = 0;
	int type = 0;
	istream *some;
	ifstream s("CS201-DS-A1TestCases\\CS201-DS-A1TestCases\\A1P1-Testcases\\A1P1IOcustom.txt");
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
	/*
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
	*/
	
	if(type == 1) return 0;
	
	(*some).seekg(ios_base::beg);
	(*some) >> m >> n; 
	
	maze_arr maze(m,n);
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			char temp;
			(*some) >> temp;
			maze(i,j,maze_block(i,j,temp));
			//maze_block t(i,j,temp);
			//maze(i,j) = t;
		}
	}
	cout << endl;
	for(int i = 0; i < m; i++){
		cout << i + 1 << " ";
		for(int j = 0; j < n; j++){
			cout << maze(i,j);
		}
		cout << endl;
	}
	
	path_finder(maze);
	
	maze.display();
	
	//maze_block::print_solved(maze);
	maze_block::step_display();

	return 0;
}


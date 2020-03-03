#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
	int sol[100][100];
class DynamicSafe2DArray
{
private:
	int row, col;
	char *data;
public:
	DynamicSafe2DArray():row(0),col(0),data(0)
	{

	}
	DynamicSafe2DArray(int Row,int Col):row(Row),col(Col)
	{
		Initialize();
	}
	char& operator()(int R,int C)
	{
		int returnIndex=(R*col)+C;
		return *(data+returnIndex);
	}
	void Initialize()
	{
		data=new char[row*col];
		memset(data,0,sizeof(char)*(col*row));
	}
	void DeleteAll()
	{
		if(data != 0)
			delete data;
		data=0;
	}
	const char& operator()(int R,int C)const
	{
		int returnIndex=(R*col)+C;
		return *(data+returnIndex);
	}
	DynamicSafe2DArray& operator=(DynamicSafe2DArray& rhs)
	{
		if (this!=&rhs)
		{
			DeleteAll();
			Initialize();
			memcpy(data,rhs.data,sizeof(char)*(row * col));
		}
		return *this;
	}
	int getRow()const
	{
		return row;
	}
	int getCol()const
	{
		return col;
	}
	DynamicSafe2DArray(DynamicSafe2DArray& rhs)
	{
		Initialize();
		memcpy(this->data,rhs.data,sizeof(char)*(row*col));
	}
	
	bool openPath(DynamicSafe2DArray& rhs, int curr_row, int curr_col)
	{
		if(curr_row >=0 || curr_row < getRow() && curr_col >=0 || curr_col < getCol() && rhs(curr_row,curr_col) == 1)
		{
			return true;
		}
		return false;
		
	}


	
	void Display()
	{
		for(int i=0;i<row*col;i++)
		{
			cout<<data[i]<<" ";
			if((i + 1)%col==0)
				cout<<endl;
		}
	}
	friend ifstream& operator>>(ifstream& infile,DynamicSafe2DArray &rhs);
	~DynamicSafe2DArray()
	{
		if (data != 0)
			DeleteAll();
	}

};

void Search(int row_pos,int col_pos,DynamicSafe2DArray &maze);
int main()
{
	ifstream infile;
	infile.open("input.txt");
	DynamicSafe2DArray test;
	infile>>test;
	cout<<test.getRow()<<endl<<test.getCol()<<endl;
	Search(test.getRow()-1,test.getCol()-1,test);
	
	
	
	
	return 0;
}


ifstream& operator>>(ifstream& infile,DynamicSafe2DArray &rhs)
{
	infile>>rhs.row>>rhs.col;
	cout << endl << " r :  " << rhs.row << " c : " << rhs.col << endl;
	rhs.Initialize();
	char trash;
	for(int i=0;i<rhs.getRow();i++)
	{
		for (int j=0;j<rhs.getCol();j++)
		{
			infile>>rhs(i,j);
			cout << rhs(i,j);
			//cout << "	";
			//infile>>trash;
			//cout << trash;
		}
		cout << endl;
	}
	return infile;
}
int step(DynamicSafe2DArray &maze,int row_pos, int col_pos)
{
	if(maze(row_pos,col_pos) == 'e') 
    { 
        sol[row_pos][col_pos] = 1; 
        return true; 
    } 
    if(maze.openPath(maze,row_pos,col_pos)== true)
    {
    	sol[row_pos][col_pos]=1;
    	if (step(maze, row_pos+1, col_pos) == true) 
            return true; 
        if (step(maze, row_pos, col_pos+1) == true) 
            return true; 
        if (step(maze, row_pos-1, col_pos) == true) 
            return true;
        if (step(maze, row_pos, col_pos-1) == true) 
            return true;
  
        sol[row_pos][col_pos] = 0; 
        return false; 
    	
	}
	return false;
}
void Search(int row_pos, int col_pos,DynamicSafe2DArray &maze)
{
bool start=false;
	for(int i=0;i < maze.getRow(); i++)
	{
		for(int j=0; j < maze.getCol(); j++)
		{
	        
			if( maze(i,j) == 's')
			{
				row_pos=i;
				col_pos=j;
				start=true;
			}
			
		}
	}
	step(maze,row_pos,col_pos);
	for(int i=0;i<maze.getRow();i++)
	{
		for(int j=0;j<maze.getCol();j++)
		{
			cout << sol[i][j];
		}
		cout<<endl;
	}


}

	
	







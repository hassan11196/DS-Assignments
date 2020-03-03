#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>
#include<limits>
#include<ctime>
#include<cmath>
using namespace std;


int rand_arrival(float rate,int last){
	srand(1);
	rate *= 1000;
	return (int(rate*40) + rand()%((int(1.1*rate))*60));
}
int rand_sec(int minute_min,int minute_max){
	srand(99);
	return (minute_min*60 + rand()%((minute_max - minute_min)*60));
}

template <typename T>
class customer_queue{
	private:
		T* arr; 
		int size;
		int used;
		int front;
		int end;
		int served;
		int waiting;
	public:
		customer_queue(){
			size = 10000;
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
			//cout << endl << "size : " << size << " use : " << used   <<  " front : " << front << " end : " << end << " data : " << data;
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
		~customer_queue(){
			if(size>0)
			delete []arr;
			size = 0;
		}
};
class customer{
	private:
		int arrival_time;
		int service_start_time;
		int service_end_time;
		int wait_time;
		int service_time;
	public:
		customer(){
			
		}
		customer(int arrival_time,int service_start_time,int service_end_time,int wait_time,int service_time){
			
		}
		customer(int arrival,int service_start,int service){
			this->arrival_time = arrival;
			this->service_time = service;
			this->service_start_time = service_start;
			this->service_end_time = this->service_start_time + this->service_time;
			this->wait_time = this->service_start_time - this->arrival_time;
 		}
 		int arrival_time_ret(){
 			return this->arrival_time;
		}
		int service_start_time_ret(){
			return this->service_start_time;
		}
		int service_end_time_ret(){
			return 	this->service_end_time;
		}
		int wait_time_ret(){
			return this->wait_time;
		}
		int service_time_ret(){
			return this->service_time;
		}
		friend ostream& operator<< (ostream &o, customer &obj){
			o << obj.arrival_time << " " << obj.service_start_time << " " << obj.service_end_time  << " "
			  << obj.wait_time << " " << obj.service_time;
			return o;
		}
		customer operator=(customer &rhs){
			arrival_time = rhs.arrival_time;
			service_start_time = rhs.service_start_time;
			service_end_time = rhs.service_end_time;
			wait_time = rhs.wait_time;
			service_time = rhs.service_time;
		} 
};
// arrival_rate is number of customers per hour
// total_time is 18 hours in seconds
bool POS(float arrival_rate,int avg_service_time_min,int avg_service_time_max,long int total_time){
 	int clock = 0;
	int arrival_time = 0;
	int service_start_time = 0;
	int service_time = 0;
	customer_queue<customer> cq;
	int hours[total_time];
	int num_hours = total_time;
	total_time *= 3600; // Conversion in Seconds
	int first_hour = 3600;
	int hr = 0;
	while(clock < total_time){
		if(cq.is_empty()){
			arrival_time = abs(rand_arrival(arrival_rate,arrival_time));
			service_start_time = arrival_time;
		}
		else{
			arrival_time += abs(rand_arrival(arrival_rate,arrival_time));
			int last_end_time  = cq.peak_end().service_end_time_ret();
			service_start_time = (arrival_time > last_end_time) ? arrival_time : last_end_time; 
			//cout << endl << "compare : "<< arrival_time << " " << last_end_time << endl; 
		}
		service_time = abs(rand_sec(avg_service_time_min,avg_service_time_max));
		cq.push(customer(arrival_time,service_start_time,service_time));
		clock = arrival_time;
		if(clock > first_hour){
			hours[hr] = cq.used_ret();
			first_hour += 3600;
			hr++;
		}
	}
	int total_customers = cq.used_ret();
	customer *cust = cq.arr_ret();
	int arr_waits[total_customers];
	int arr_service_time[total_customers];
	int arr_arrival_time[total_customers];
	long int total_service_time = 0;
	long int total_wait_time = 0;
	long int total_sum_time = 0;
	long int first_part_wait_time = 0;
	int first_part_customers = 0;
	for(int  i = 0 ; i < total_customers; i++){
		arr_arrival_time[i] = cust[i].arrival_time_ret();
		arr_waits[i] = cust[i].wait_time_ret();
		arr_service_time[i] = cust[i].service_time_ret();
		total_wait_time += arr_waits[i]; 
		total_service_time += arr_service_time[i];
		total_sum_time += arr_waits[i] + arr_service_time[i]; 
	}
	for(int i = 0 ;i < num_hours; i ++){
		
		cout << endl << "Hour : " << i+1 << endl;
		long int part_service_time = 0;
		long int part_wait_time = 0;
		long int part_sum_time = 0;
		int start=0;
		if(i==0)
			start = 0;
		else
			start = hours[i-1];
		int part_customers = hours[i] - start;	
		int diff = 0;
		for(int  j = start ; j < hours[i]; j++){
		
			if(j==0)
				diff = arr_arrival_time[0];
			else{
				diff += (arr_arrival_time[j] - arr_arrival_time[j-1] );
			}
			arr_waits[j] = cust[j].wait_time_ret();
			arr_service_time[j] = cust[j].service_time_ret();
			part_wait_time += arr_waits[j]; 
			part_service_time += arr_service_time[j];
			part_sum_time += arr_waits[j] + arr_service_time[j]; 
		}
		if(i==0){
			first_part_wait_time = part_wait_time;
			first_part_customers = part_customers;
		}
			
			
		float part_mean_arrival_time = diff / part_customers;
		float part_mean_wait = part_wait_time / part_customers;
		float part_mean_service_time = part_service_time / part_customers;
		float part_mean_sum_time = part_sum_time / part_customers;
		float first_part_mean_wait = first_part_wait_time / part_customers;
		cout << endl << "Number of Customers : " << part_customers
			 << endl << "Mean Arrival Time : " << part_mean_arrival_time << "(Seconds) or " << part_mean_arrival_time/60 << "(Minutes)"
			 << endl << "Mean Wait Time : " << first_part_mean_wait << "(Seconds) or " << first_part_mean_wait/60 << "(Minutes)"
			 << endl << "Mean Service Time : " << part_mean_service_time << "(Seconds) or " << part_mean_service_time/60 << "(Minutes)"
			 << endl << "Mean Total Time Per Customer " << part_mean_sum_time << "(Seconds) or " << part_mean_sum_time/60 << "(Minutes)" 
			 << endl << "*****************************************************************" << endl;
	}
	
	float mean_wait = total_wait_time / total_customers;
	float mean_service_time = total_service_time / total_customers;
	float mean_sum_time = total_sum_time / total_customers;
	float utilisation = total_service_time / clock;
	float first_part_mean_wait = first_part_wait_time / first_part_customers;
	cout << endl << "Overall : " << endl;
	cout << endl << "Arrival Rate : " << arrival_rate << "(no. of customers / sec) or " <<  arrival_rate*60*60 << "(no. of customers / hours)"  
		 << endl << "Avg Service Time Minimum : " << avg_service_time_min << "(minutes)"
		 << endl << "Avg Service Time Maximium : " << avg_service_time_max << "(minutes)"
		 << endl << "Total Time : " << total_time << "(Seconds) or " << total_time/60 << "(Minutes)" << total_time/3600 << "(Hours)"
		 << endl << "Mean Wait Time : " << first_part_mean_wait << "(Seconds) or " << first_part_mean_wait/60 << "(Minutes)" 
		 << endl << "Mean Service Time : " << mean_service_time << "(Seconds) or " << mean_service_time/60 << "(Minutes)"
		 << endl << "Mean Total Time Per Customer " << mean_sum_time << "(Seconds) or " << mean_sum_time/60 << "(Minutes)"
		 << endl << "POS utilization Time :  " << utilisation ;
	if(first_part_mean_wait/60 > 3)
		return true;
	return false;
}


int main(){
	
	bool test = POS(float((float)15/(60 * 60)),3,8,18);
	if(test)
		cout << endl << "Another POS needs to be installed." << endl;
	else{
		cout << endl <<  "No need for another POS." << endl;
	} 
	return 0;
}

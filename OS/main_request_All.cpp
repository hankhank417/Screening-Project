#include<iostream>
#include<cstdlib>
#include<pthread.h>
#include<iomanip>
#include<sstream>
#include<mutex>
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3
using namespace std;

class Bank {
	public:
		~Bank();
		int request_resources(int customer_id, int resources[]);
		int release_resources(int customer_id, int resources[]);
		bool isFinish(int customer_id);
};

struct thread_context{
	int customer_id;
	Bank* bank;
};

int available[NUMBER_OF_RESOURCES];
int resources[NUMBER_OF_RESOURCES] = {10,5,7};
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] ={{7,5,3},
														{3,2,2},
														{9,0,2},
														{2,2,2},
														{4,3,3}};
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = {{0,1,0},
															{3,0,2},
															{3,0,2},
															{2,1,1},
															{0,0,2}};
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int request[NUMBER_OF_RESOURCES];
bool finished[NUMBER_OF_CUSTOMERS];
bool satisfy[NUMBER_OF_CUSTOMERS];
mutex gMutex;
bool isSafe = true;

void* customer(void* context);
bool lackResources();
void countAvailableNeed();
void printAll();
string to_string(int arr[], int size);

int main(){
	Bank* bank = new Bank();
	cout<<"Inilializing thread..."<<endl;
	thread_context** tContext = new thread_context*[NUMBER_OF_CUSTOMERS];
	for(int customer_id=0; customer_id<NUMBER_OF_CUSTOMERS; customer_id++){
		tContext[customer_id] = new thread_context();
		tContext[customer_id]->customer_id = customer_id;
		tContext[customer_id]->bank = bank;
		finished[customer_id] = false;
		satisfy[customer_id] = false;
	}
	
	countAvailableNeed();
	printAll();
	
	cout<<"Starting request/release..."<<endl<<endl;
	pthread_t customer_threads[NUMBER_OF_CUSTOMERS];
	for(int i=0; i<NUMBER_OF_CUSTOMERS; i++)
		pthread_create(&customer_threads[i], NULL, &customer, reinterpret_cast<void*>(tContext[i]));
	
	// Wait for threads to finish.
	for(int i=0; i<NUMBER_OF_CUSTOMERS; ++i)
		pthread_join(customer_threads[i], NULL);

	if(isSafe){
		cout<<endl<<"Safe !"<<endl<<endl;
	}else{
		cout<<endl<<"Unafe !"<<endl<<endl;
	}
	
	system("Pause");
	return 0;
}

void* customer(void* context){
	thread_context* tc = reinterpret_cast<thread_context*>(context);
	int *resources = new int[NUMBER_OF_RESOURCES];
	while(true){
		gMutex.lock();
		for(int i=0; i<=NUMBER_OF_RESOURCES; i++) resources[i] = need[tc->customer_id][i];
		if(tc->bank->request_resources(tc->customer_id, resources)){
			if(tc->bank->release_resources(tc->customer_id, resources)){
				finished[tc->customer_id] = true;
				for(int i=0; i<NUMBER_OF_CUSTOMERS; i++) satisfy[i] = false;
				printAll();
				gMutex.unlock();
				break;
			}
		}else{
			satisfy[tc->customer_id] = true;
		}
		if(lackResources()){
			isSafe = false;
			gMutex.unlock();
			break;
		}
		gMutex.unlock();
	}
}

Bank::~Bank(){}

int Bank::request_resources(int customer_id, int request[]){
	cout<<"Customer "<<customer_id<<" requesting "<<to_string(request, NUMBER_OF_RESOURCES)<<endl;
	for (int i=0; i<NUMBER_OF_RESOURCES; ++i){
		if (request[i]>need[customer_id][i] || request[i]>available[i]){
			cout<<"Customer "<<customer_id<<" requesting illegal !"<<endl;
			return 0;
		}
	}
	for(int i=0; i<NUMBER_OF_RESOURCES; i++){
        available[i] -= request[i];
        allocation[customer_id][i] += request[i];
        need[customer_id][i] -= request[i];
    }
	return 1;
}

int Bank::release_resources(int customer_id, int release[]){
	int allocation_temp[NUMBER_OF_RESOURCES];
    if(isFinish(customer_id)){
    	for(int i=0; i<NUMBER_OF_RESOURCES; i++){
    		allocation_temp[i] = allocation[customer_id][i] - release[i];
            available[i] += allocation[customer_id][i];
            allocation[customer_id][i]=0;
        }
        cout<<"Customer "<<customer_id<<" Finished !"<<endl;
        cout<<"Customer "<<customer_id<<" releasing "<<to_string(allocation_temp, NUMBER_OF_RESOURCES)<<endl;
        return 1;
	}else{
		for(int i=0; i<NUMBER_OF_RESOURCES; i++){
	        available[i] += release[i];
	        allocation[customer_id][i] -= release[i];
	        need[customer_id][i] += release[i];
	    }
	    cout<<"Customer "<<customer_id<<" can't Finished !"<<endl;
	    cout<<"Customer "<<customer_id<<" releasing "<<to_string(release, NUMBER_OF_RESOURCES)<<endl;
	    return 0;
	}
}

bool Bank::isFinish(int customer_id){
	for(int i=0; i<NUMBER_OF_RESOURCES; ++i) if(need[customer_id][i] != 0) return false;
	return true;
}

bool lackResources(){
	for(int i=0; i<NUMBER_OF_CUSTOMERS; ++i) if(!finished[i]^satisfy[i]) return false;
	return true;
}

void countAvailableNeed(){
	for(int i=0; i<NUMBER_OF_RESOURCES; i++){
		int sum = 0;
		for(int j=0; j<NUMBER_OF_CUSTOMERS; j++){
			sum += allocation[j][i];
			need[j][i] = maximum[j][i]-allocation[j][i];
		}
		available[i] = resources[i]-sum;
	}
}

void printAll(){
	cout<<endl;
	cout<<setw(10)<<"Process"<<setw(14)<<"Allocation"<<setw(12)<<"Need"<<setw(12)<<"Max"<<setw(13)<<"Available"<<endl;
	cout<<setw(10)<<""<<setw(14)<<"A  B  C"<<setw(12)<<"A  B  C"<<setw(12)<<"A  B  C"<<setw(13)<<"A  B  C"<<endl;
	for(int i=0; i<NUMBER_OF_CUSTOMERS; i++){
		cout<<setw(9)<<"P"<<i;
		cout<<setw(7)<<"";
		for(int j=0; j<NUMBER_OF_RESOURCES; j++) cout<<allocation[i][j]<<"  ";
		cout<<setw(3)<<"";
		for(int j=0; j<NUMBER_OF_RESOURCES; j++) cout<<need[i][j]<<"  ";
		cout<<setw(3)<<"";
		for(int j=0; j<NUMBER_OF_RESOURCES; j++) cout<<maximum[i][j]<<"  ";
		cout<<setw(4)<<"";
		if(i==0) for(int j=0; j<NUMBER_OF_RESOURCES; j++) cout<<available[j]<<"  ";
		cout<<endl;
	}
	cout<<endl;
}

string to_string(int arr[], int size){
	stringstream ss;
	string delimeter = "";
	ss<<"[ ";
	for (int i=0; i<size; i++){
		ss<<delimeter<<arr[i];
		delimeter = ", ";
	}
	ss<<" ]";
	return ss.str();
}

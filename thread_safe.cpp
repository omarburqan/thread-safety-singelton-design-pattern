#include <iostream>
#include <pthread.h>
#include <stdlib.h>

using namespace std;
  
pthread_mutex_t mutex_thread = PTHREAD_MUTEX_INITIALIZER;  

class Singleton{
	public:

		static Singleton* GetInstance(){
			if(NULL == s_instance)
			{
				pthread_mutex_lock(&mutex_thread);
				if(NULL == s_instance)
				{
					s_instance = new Singleton();
					cout << " New Singelton ID : " << pthread_self() << endl;
				}
				pthread_mutex_unlock(&mutex_thread);

			}
			if( NULL != s_instance){
				cout << " old Singelton ID : " << pthread_self() << endl;
				return s_instance;      

			}
			pthread_exit(NULL);	
		}  


		~Singleton(){}	
		static void* get(void* args){
			return 	(void*)Singleton::GetInstance();
		
		}
	private:	
		Singleton(){
		}
	
		static Singleton* s_instance;


};


 Singleton* Singleton::s_instance = 	NULL;
using std::cout;
using std::endl;

int main(){
	pthread_t producer[15];

    int index;


    for (index = 0; index < 15; ++index) {
    	
    	int rc = pthread_create(&producer[index], NULL, Singleton::get, NULL);
        if (rc) {
             cout << "Error:unable to create thread,producer" << rc << endl;
             exit(-1);
        }
    }
    for (index = 0; index < 15; ++index)
		pthread_join(producer[index], NULL);
	
	return 0;
	
}










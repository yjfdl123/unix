/**
  *@brief xxx
  *@author chenliyong
  *@date Mon 06 Mar 2017 05:14:24 PM CST
**/
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace std;
struct Thdata{
	int threadid;
	pthread_mutex_t mutex;
	int total;
};
void *writebook(void* data)
{
	Thdata* thdata = (Thdata*)data;
	pthread_mutex_lock(&thdata->mutex);
//printf("totaladdr:%ld\n",&thdata->total);
	thdata->total++;
	printf("pid:%d\twrite book%d\n", pthread_self(),thdata->total);
	pthread_mutex_unlock(&thdata->mutex);
	
    return (void* )(pthread_self());
}
void* sellbook(void* data)
{
	Thdata* thdata = (Thdata*)data;
	pthread_mutex_lock(&thdata->mutex);
	thdata->total--;
	printf("pid:%d\t sell book%d\n", pthread_self(),thdata->total);
	pthread_mutex_unlock(&thdata->mutex);
	return (void*)0;

}
int main(){
	cout<<"begin"<<endl;
	int maxthreads=10;
	pthread_t threads[maxthreads];
	pthread_mutex_t mutex ;
	pthread_mutex_init(&mutex, NULL);
	Thdata thdata;
	thdata.threadid = 0;
	thdata.mutex = mutex;
	thdata.total = 0;
	for (int i=0;i<maxthreads;i++)
	{
		thdata.threadid = i;
		printf("start thread %d\n",i);
		int ret = pthread_create(&threads[i], NULL, writebook, &thdata );
		if (ret!=0){
			cout<<"create thread"<<i<<"wrong"<<endl;
		}
		//sleep(0.5);
	}
	for (int i=0;i<maxthreads;i++){
		void* data;
		pthread_join(threads[i],&data);
		//printf("pid:%ld\n", *(int*)data);
        //cout<< (*(int*)data)<<endl;

	}
    return 0;

}

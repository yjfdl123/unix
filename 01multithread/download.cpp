#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
using namespace std;
sem_t sem;

void* downloader(void* data)
{
    if (sem_wait(&sem) == 0){
        printf("tid:%ld\t begin\n",pthread_self());
        sleep(5);
        printf("tid:%ld\t end\n",pthread_self());
        sem_post(&sem); 
    }else{
        printf("tid:%ld\t fail\n",pthread_self());
    }
    return (void*)0;
}
void control_download()
{
    int tnum=5;
    int maxdnum = 2;
    if (sem_init(&sem, 0, maxdnum)==0){
        cout<<"succ"<<endl;
    }else{
        cout<<"fail"<<endl;
    }
    int snum = 0;
    sem_getvalue(&sem, &snum);
    cout<<"snum:"<<snum<<endl;
    pthread_t threads[tnum];
    for (int i=0;i<tnum;i++)
    {
        int ret = pthread_create( &threads[i], NULL, downloader, NULL);
        if (ret == -1)
        {
            printf("%dth bad\n",i);
        }
    }
    void * ret;
    for (int i=0;i<tnum;i++){
        pthread_join(threads[i],NULL);
    }
    sem_destroy(&sem);
}
int main()
{
    cout<<"downloader:"<<endl;
    int totalbytes = 0;
    control_download();
    return 0;
}

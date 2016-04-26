#include <stdio.h>
#include <sys/sem.h>
// #include <linux/sem.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHMKEY_S 75
#define SHM_S_SIZE 1024
#define SHMKEY_T 100
#define SHM_T_SIZE 1024
#define SEM_KEY 125
#define S_FULL 0
#define S_EMPTY 1
#define T_FULL 2
#define T_EMPTY 3

union semun   
{  
    int val;     
    struct semid_ds  *buf;    
    unsigned short *array;  
}sem_union; 

void P(int semid,int index)
{
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op = -1;
	sem.sem_flg = 0;
	semop(semid, &sem ,1);
	return;
}

void V(int semid,int index)
{
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op = 1;
	sem.sem_flg = 0;
	semop(semid, &sem ,1);
	return;
}
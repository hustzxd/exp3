#include "copy.h"

int semid;
int shmid_t;
int *addr_t;

int main()
{
	//read file
	semid = semget(SEM_KEY,4,IPC_CREAT|0666);
	if(semid == -1){
		printf("in put.c semid get error!\n");
		exit(1);
	}
	shmid_t = shmget(SHMKEY_T,SHM_T_SIZE,0777);
	if(shmid_t == -1){
		printf("in put.c shmid_t get error!\n");
		exit(1);
	}
	addr_t = shmat(shmid_t,0,0);
	if(addr_t == -1){
		printf("in put.c addr_t get error!\n");
		exit(1);
	}
	int i;
	for(i=0;i<10;i++){
		P(semid,T_FULL);
		printf("in put%d ",i);
		printf("string = %d\n", *addr_t);

		V(semid,T_EMPTY);
	}
	return 0;
}
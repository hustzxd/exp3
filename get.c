#include "copy.h"

int semid;
int shmid_s;
int *addr_s;

int main()
{
	//read file
	semid = semget(SEM_KEY,4,IPC_CREAT|0666);
	if(semid == -1){
		printf("in get.c semid get error!\n");
		exit(1);
	}
	shmid_s = shmget(SHMKEY_S,SHM_S_SIZE,0777);
	if(shmid_s == -1){
		printf("in get.c shmid_s get error!\n");
		exit(1);
	}
	addr_s = shmat(shmid_s,0,0);
	if(addr_s == -1){
		printf("in get.c addr get error!\n");
		exit(1);
	}
	int i;
	for(i=0;i<10;i++){
		P(semid,S_EMPTY);
		printf("in get%d\n",i);
		
		*addr_s = i;

		V(semid,S_FULL);

	}
	
	return 0;
}
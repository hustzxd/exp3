#include "copy.h"

int semid;
int shmid_s;
int shmid_t;
char *addr_s;
char *addr_t;

int main(){

	semid = semget(SEM_KEY,4,IPC_CREAT|0666);
	if(semid == -1){
		printf("in copy.c semid get error!\n");
		exit(1);
	}

	shmid_s = shmget(SHMKEY_S,SHM_S_SIZE,0777);
	if(shmid_s == -1){
		printf("in copy.c shmid_s get error!\n");
		exit(1);
	}
	addr_s = shmat(shmid_s,0,0);

	shmid_t = shmget(SHMKEY_T,SHM_T_SIZE,0777);
	if(shmid_t == -1){
		printf("in copy.c shmid_t get error!\n");
		exit(1);
	}
	addr_t = shmat(shmid_t,0,0);
	int i;

	while(1){
		i++;
		P(semid,S_FULL);
		P(semid,T_EMPTY);

		printf("in copy%d ",i);
		// *addr_t = *addr_s;
		strcpy(addr_t,addr_s);
		printf("*addr_t is %s\n", addr_t);
		if(*addr_t == NULL){
			V(semid,T_FULL);
			V(semid,S_EMPTY);
			break;
		}
		V(semid,T_FULL);
		V(semid,S_EMPTY);
	}
	
	return 0;
}

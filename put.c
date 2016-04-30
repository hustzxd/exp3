#include "copy.h"

int semid;
int shmid_t;
char *addr_t;

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
	FILE *pf;
	pf = fopen("a_cy.txt","w");
	int i=0;
	char c[SHM_T_SIZE];
	while(1){
		i++;
		P(semid,T_FULL);
		printf("in put%d ",i);
		printf("addr_t = %s\n", addr_t);

		if(*addr_t == NULL){
			V(semid,T_EMPTY);
			break;
		}
		strcpy(c,addr_t);
		fwrite(c,sizeof(char),SHM_T_SIZE,pf);
		V(semid,T_EMPTY);
	}
	return 0;
}
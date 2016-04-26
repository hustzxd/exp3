#include "copy.h"

int semid;
int shmid_s;
int shmid_t;
int ret;


int main()
{
	//create sem 
	union semun semopts;
	semid = semget(SEM_KEY,4,IPC_CREAT|0666);
	if(semid == -1)
	{
		printf("semget error!\n");
		exit(1);
	}
	semopts.val = 0;
	ret = semctl(semid,S_FULL,SETVAL,semopts);
	if(ret == -1)
	{
		printf("semctl error!\n");
		exit(1);
	}
	semopts.val = 1;
	ret = semctl(semid,S_EMPTY,SETVAL,semopts);
	if(ret == -1){
		printf("semctl error!\n");
		exit(0);
	}
	semopts.val = 0;
	ret = semctl(semid,T_FULL,SETVAL,semopts);
	if(ret == -1){
		printf("semctl error!\n");
		exit(1);
	}
	semopts.val = 1;
	ret = semctl(semid,T_EMPTY,SETVAL,semopts);
	if(ret == -1){
		printf("semctl error!\n");
		exit(1);
	}

	//create shm S and T
	shmid_s = shmget(SHMKEY_S,SHM_S_SIZE,0777|IPC_CREAT);
	if(shmid_s == -1){
		printf("main shmid_s shmget error!\n");
		exit(1);
	}
	shmid_t = shmget(SHMKEY_T,SHM_T_SIZE,0777|IPC_CREAT);
	if(shmid_t == -1){
		printf("main shmid_t shmget error!\n");
		exit(1);
	}

	int p1,p2,p3;
	if((p1 = fork())==0)
	{
		ret = execv("./get",NULL);
		if(ret == -1){
			printf("./get error!\n");
			exit(1);
		}
	}
	else
	{
		if((p2 = fork())==0)
		{
			ret = execv("./copy",NULL);
			if(ret == -1){
				printf("./copy error!\n");
				exit(1);
			}
		}
		else
		{
			if((p3 = fork())==0)
			{
				ret = execv("./put",NULL);
				printf("./put error!\n");
				exit(1);
			}
		}
	}

	wait(p1);
	wait(p2);
	wait(p3);
	//delete sem shm
	ret = shmctl(shmid_s,IPC_RMID,0);
	if(ret == -1){
		printf("shmid_s IPC_RMID error!\n");
		exit(1);
	}
	ret = shmctl(shmid_t,IPC_RMID,0);
	if(ret == -1){
		printf("shmid_t IPC_RMID error!\n");
		exit(1);
	}
	ret = semctl(semid,S_FULL,IPC_RMID,0);
	if(ret == -1){
		printf("semid rm error\n");
		exit(1);
	}
	// ret = semctl(semid,S_EMPTY,IPC_RMID,0);
	// ret = semctl(semid,T_FULL,IPC_RMID,0);
	// ret = semctl(semid,T_EMPTY,IPC_RMID,0);
	printf("back to main over!\n");
}
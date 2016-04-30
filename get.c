#include "copy.h"

int semid;
int shmid_s;
char *addr_s;
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

	FILE *pf = fopen("a.txt","r");
	if(pf == NULL){
		printf("open a.txt error!\n");
		exit(1);
	}
	int i = 0;
	// char c[SHM_S_SIZE + 1];
	char c[SHM_S_SIZE];
	size_t size;
	// char cc[SHM_S_SIZE];
	while((size = fread(c,1,sizeof(c),pf))>0){
		// printf("%s\n", c);
		i++;
		P(semid,S_EMPTY);
		printf("in get%d size = %d ",i,size);
		// c[size] = '\0';
		strcpy(addr_s,c);
		// *addr_s = *c;
		// strcpy(c,cc);
		int j;
		for(j=0;j<SHM_S_SIZE;j++)
			c[j] = ' ';
		printf("addr_s = %s\n", addr_s);
		V(semid,S_FULL);
	}
	fclose(pf);

	P(semid,S_EMPTY);
	*addr_s = NULL;
	V(semid,S_FULL);
	return 0;
}
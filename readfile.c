
#include <stdio.h>
#include <stdlib.h>


int main()
{
	FILE *pf = fopen("makefile","r");
	if(pf == NULL){
		printf("open a.txt error!\n");
		exit(1);
	}
	char c[1024];
	while(fread(c,sizeof(char),1024,pf)>0){
		printf("%s\n", c);
	}
	fclose(pf);
	return 0;
}
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
typedef int pid_t;
int main(){
	int numbers[36],fd[2];
	int i,index = 0;
	pid_t pid;
	for(i=2;i<=35;i++){
		numbers[index++]=i;
	}
	while(index>0){
		pipe(fd);
		if((pid = fork())<0){
				fprintf(2,"fork orr\n");
				exit(0);
				}
		else if(pid>0){
		close(fd[0]);
		for(i=0;i<index;i++){
			write(fd[1],&numbers[i],sizeof(numbers[i]));
			}
		close(fd[1]);
		wait((int*)0);
		exit(0);
		}else{
		close(fd[1]);
		int prime = 0;
		int temp = 0;
		index = -1;
		while(read(fd[0],&temp,sizeof(temp)) != 0){
		if(index<0)prime = temp,index++;
		else{
			if(temp%prime!=0)numbers[index++]=temp;
		}}
		printf("prime %d\n",prime);
		close(fd[0]);
		}}
	exit(0);
}

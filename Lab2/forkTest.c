/**
* func:	利用fork()创建子进程
*	利用kill()杀死进程
* auth:	CJX
**/
#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<wait.h>
int main()
{
	pid_t pid1,pid2;
	pid1 = fork();//创建子进程1
	if(pid1 < 0){
		printf("子进程1创建失败\n");
	}
	else if (pid1 == 0){ 
		printf("子进程1正在执行……\n");
	}
	else{ 
		printf("父进程正在执行……\n");
		pid2 = fork();//创建子进程2
		if(pid2 < 0){
			printf("子进程2创建失败\n");
		}
		else if (pid2 == 0){ 
			printf("子进程2正在执行……\n");
		}
	
		sleep(5);//父进程运行一段时间

		if(kill(pid1,SIGTERM)==0){//杀死子进程1
			printf("子进程1被父进程杀死\n");
		}
		else{
			printf("子进程1杀死失败\n");
		}
		wait(NULL);

		if(kill(pid2,SIGTERM)==0){//杀死子进程2
			printf("子进程2被父进程杀死\n");
		}
		else{
			printf("子进程2杀死失败\n");
		}		
		printf("父进程结束\n");
	}

	return 0;
}

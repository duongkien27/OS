#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
int main(int argc, char** argv)
{
	printf("\nMa tien trinh dang chay: %d", (int)getpid());
	printf("\nThuoc nhom: %d",(int)getpgrp());
	printf("\nMa tien trinh cha: %d", (int)getppid());
	//get
	int which = PRIO_PROCESS;
	id_t pid;
	int priority;
	int ret;
	pid = getpid();
	ret = getpriority(which,pid);
	printf("\nPriority: %d",ret);
	printf("\n");
	//set priority
	int input;
	printf("\nNhap vao tien trinh muon xu li: ");
	scanf("%d",&input);
	printf("\nNhap vao nice value(priority) muon dat cho tien trinh: ");
	scanf("%d",&priority);
	int ret1;
	int ret2;
	int flag;
	ret1 = getpriority(which, input);
	flag = setpriority(which, input, priority);
	ret2 = getpriority(which, input);
	printf("\nMa tien trinh: %d",input);
        printf("\nPriority ban dau: %d",ret1);
	printf("\nPriority hien tai: %d",ret2);
        printf("\n");
	//kill
	int input2;
	printf("\nNhap vao tien trinh muon kill: ");
	scanf("%d",&input2);
	id_t pid2;
	pid2 = (id_t)input2;
	//kill
        int i,h;
        printf("Ban co chac chan muon huy tien trinh %d khong? (0-Khong; 1-Co)\n",(int)getpid());
        scanf("%d",&i);
        if(i==1)
        {
                kill(pid2, SIGTERM);
        }
        else
	{
                printf("\nTien trinh chua bi huy!\n");
	}
	printf("PID: %d - Terminated!\n", input2);
}

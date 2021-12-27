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

	//get
	int p1,p2,p3;
	printf("Nhap ma tien trinh: \n");
	printf("P1: ");
	scanf("%d",&p1);
	printf("P2: ");
	scanf("%d",&p2);
	printf("P3: ");
	scanf("%d",&p3);
	int which = PRIO_PROCESS;
	int n1,n2,n3;
	int ret;
	//set priority
	int input;
	printf("\nNhap vao nice value(priority) muon dat cho tien trinh: \n");
	printf("N1: ");
	scanf("%d",&n1);
	printf("N2: ");
	scanf("%d",&n2);
	printf("N3: ");
	scanf("%d",&n3);
	int ret1,ret2,ret3;
	int flag1,flag2,flag3;
	ret1 = getpriority(which, p1);
	ret2 = getpriority(which, p2);
	ret3 = getpriority(which, p3);
	flag1 = setpriority(which, p1, n1);
	flag2 = setpriority(which, p2, n2);
	flag3 = setpriority(which, p3, n3);
	ret1  = getpriority(which, p1);
	ret2  = getpriority(which, p2);
	ret3  = getpriority(which, p3);
	printf("\nP1: %d - N1: %d",p1,n1);
	printf("\nP2: %d - N2: %d",p2,n2);
	printf("\nP3: %d - N3: %d",p3,n3);
        printf("\n");
}

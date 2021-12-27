#include <stdlib.h>
#include <stdio.h>
/*
Group members
    1) Muhammad Yamin (021-19-0029)
    2) Muhammad Fahad Shahzad (051-19-0003)
    3) Muhammad Akram (051-19-0033)
    4) Irfan Ullah (051-19-0008)
    5) Wasid Khan (021-19-0022 )
*/


// method 1 for first come first server algorithm
void fcfs(){
	int job_number;
	    printf("Total Number of Processes: ");
	    scanf("%d",&job_number);

	    int arrival_time[job_number],burst_time[job_number],completion_time[job_number],
	    turnaround_time[job_number],waiting_time[job_number];
	    printf("-------------------------------------------");
	    printf("\n Notations Used\n");
	    printf("AT= arrival_time\t BT= burst_time\nCT=completion_time \t TAT= turnaround_time \n WT =waiting_time\n");
	    printf("-------------------------------------------");
	    printf("\nEnter Arrival Time and Burst Time for each Job\n");
	    printf("   AT BT \n");
	    // loop control variables
	    int i,j;
	    for(i=0; i<job_number; i++)
	    {
		printf("J%d-",i+1);
		scanf("%d %d",&arrival_time[i],&burst_time[i]);
	    }

	    int flag=0,time=0;
	    float avg_turnaround_time=0,avg_waiting_time=0;

	    for(i=0; i<job_number; i++)
	    {
		if(flag<arrival_time[i])
		{
		    time=arrival_time[i]-flag;
		}

		flag=flag+burst_time[i]+time;
		time=0;
		completion_time[i]=flag;
		turnaround_time[i]=completion_time[i]-arrival_time[i];
		avg_turnaround_time=avg_turnaround_time+turnaround_time[i];
		waiting_time[i]=turnaround_time[i]-burst_time[i];
		avg_waiting_time=avg_waiting_time+waiting_time[i];
	    }
	    printf("\n-------------------------------------------\n");
	    printf("After Calculations The following Results have been found\n");
	    printf("  AT BT CT TAT WT\n");

	    for(i=0; i<job_number; i++)
	    {
		printf("J%d-%d %d %d %d %d\n",i+1,arrival_time[i],burst_time[i],completion_time[i],
		turnaround_time[i],waiting_time[i]);
	    }

	    printf("Average Turnaround Time=%f ",avg_turnaround_time/job_number);
	    printf("\nAverage Waiting Time=%f",avg_waiting_time/job_number);
	    printf("\n");
}

// method 2 for shortest job first algorithm

void sjf(){
int num_job,i,j;
    printf("Total Number of Processes:");
    scanf("%d",&num_job);
    int arrival_time[num_job],burst_time[num_job];
    printf("Arrival times:\n");
    for(i=0;i<num_job;i++)
    scanf("%d",&arrival_time[i]);
    printf("Burst times:\n");
    for(i=0;i<num_job;i++)
    scanf("%d",&burst_time[i]);
    int Bt[num_job],Ct[num_job];
    for(i=0;i<num_job;i++)
    Bt[i]=burst_time[i];
    int count=0;
    j=0;
    while(j<num_job)
    {
        int min_limit=1000,index=-1;
        for(i=0;i<num_job;i++)
        {
            if(Bt[i]==min_limit)
            {
                if(arrival_time[i]<arrival_time[index])
                index=i;
            }
            
            else if(Bt[i]<min_limit)
            {
                if(arrival_time[i]<=count)
                {
                    min_limit=Bt[i];
                    index=i;
                }
            }
            
        }
        if(index!=-1)
        {
            Ct[index]=burst_time[index]+count;
            count+=burst_time[index];
            j++;
            Bt[index]=1001;
        }
        else
        count++;
    }
    
    int TAT[num_job],WT[num_job];
    
    for(i=0;i<num_job;i++)
    TAT[i]=Ct[i]-arrival_time[i];
    
    for(i=0;i<num_job;i++)
    WT[i]=TAT[i]-burst_time[i];
    
    printf("\nProcess Table:\nPid\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<num_job;i++)
    printf("P%d\t%d\t%d\t%d\t%d\t%d\n",(i+1),arrival_time[i],burst_time[i],Ct[i],TAT[i],WT[i]);
    
    float avg_var=0;
    for(i=0;i<num_job;i++)
    avg_var+=(float)TAT[i];
    printf("\nAverage Turnaround Time: %f",avg_var/num_job);
    avg_var=0;
    for(i=0;i<num_job;i++)
    avg_var+=(float)WT[i];
    printf("\nAverage Waiting Time: %f",avg_var/num_job);
    printf("\n");

}

// method 3 for shortest remaining time first
void srtf(){

    int n,i,j;
    printf("Total Number of Processes:");
    scanf("%d",&n);
    int arrival_time[n],burst_time[n];
    printf("Arrival time of the processes:\n");
    for(i=0;i<n;i++)
    scanf("%d",&arrival_time[i]);
    printf("Burst times:\n");
    for(i=0;i<n;i++)
    scanf("%d",&burst_time[i]);
    int Bt[n],completion_time[n],response_time[n];
    for(i=0;i<n;i++)
    Bt[i]=burst_time[i];
    for(i=0;i<n;i++)
    response_time[i]=-1;
    int count=0,prev=-1;
    j=0;
    while(j<n)
    {
        int min=1000,ind=-1;
        for(i=0;i<n;i++)
        {
            if(Bt[i]==min && Bt[i]>0)
            {
                if(arrival_time[i]<arrival_time[ind])
                ind=i;
            }
            
            else if(Bt[i]<min && Bt[i]>0)
            {
                if(arrival_time[i]<=count)
                {
                    min=Bt[i];
                    ind=i;
                }
            }
            
        }
        
        if(ind!=-1)
        Bt[ind]-=1;
        
        if(ind!=prev && response_time[ind]==-1)
        {
            response_time[ind]=count-arrival_time[ind];
        }
        
        count++;
        
        if(Bt[ind]==0 && ind!=-1)
        {
            completion_time[ind]=count;
            j++;
        }
        prev=ind;
    }
    
    int turnaround_time[n],WT[n];
    
    for(i=0;i<n;i++)
    turnaround_time[i]=completion_time[i]-arrival_time[i];
    
    for(i=0;i<n;i++)
    WT[i]=turnaround_time[i]-burst_time[i];
    
    printf("\nProcess Table:\nPid\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(i=0;i<n;i++)
    printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",(i+1),arrival_time[i],burst_time[i],completion_time[i],turnaround_time[i],WT[i],response_time[i]);
    
    float for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)turnaround_time[i];
    printf("\nAverage turnaround_time: %f",for_avg/n);
    for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)WT[i];
    printf("\nAverage Waiting Time: %f",for_avg/n);
    for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)response_time[i];
    printf("\nAverage Response Time: %f",for_avg/n);
    printf("\n");
}

// method 4 for round robin algoritm
void rr(){
	int n,i,j,time_quanta,len=0;
    printf("Total Number of Processes:");
    scanf("%d",&n);
    int arrival_time[n],burst_time[n];
    printf("Arrival times:\n");
    for(i=0;i<n;i++)
    scanf("%d",&arrival_time[i]);
    printf("Burst times:\n");
    for(i=0;i<n;i++)
    scanf("%d",&burst_time[i]);
    printf("Enter Time Quanta:");
    scanf("%d",&time_quanta);
    int Bt[n],Ct[n],Rt[n];
    for(i=0;i<n;i++)
    {
        Bt[i]=burst_time[i];
        len+=burst_time[i];
        Rt[i]=-1;
    }
    int ready[len];
    int count=0,front=0,rear=-1,dec=0;
    j=0;
    printf("\nGantt chart:\n|");
    while(j<n)
    {
        int found=0;
        if(front>rear)
        {
            for(i=0;i<n;i++)
            if(arrival_time[i]==count)
            {
                ready[++rear]=i;
                found=1;
            }
            if(found==0)
            {
                if(dec==0)
                {
                    printf("%d-Idle-",count);
                    dec=1;
                }
                count++;
            }
        }
        else
        {
            int k,ind=ready[front++],dec=0;
            
            printf("%d-P%d-",count,(ind+1));
            
            if(Rt[ind]==-1)
            Rt[ind]=count-arrival_time[ind];
            
            if(Bt[ind]<=time_quanta)
            {
                for(k=0;k<Bt[ind];k++)
                {
                    count++;
                    for(i=0;i<n;i++)
                    {
                        if(arrival_time[i]==count)
                        ready[++rear]=i;
                    }
                }
                Bt[ind]=0;
                Ct[ind]=count;
                j++;
            }
            else
            {
                for(k=0;k<time_quanta;k++)
                {
                    count++;
                    for(i=0;i<n;i++)
                    {
                        if(arrival_time[i]==count)
                        ready[++rear]=i;
                    }
                }
                Bt[ind]-=time_quanta;
                ready[++rear]=ind;
            }
        }
    }
    
    printf("%d|\n",count);
    
    int turnaround_time[n],waiting_time[n];
    
    for(i=0;i<n;i++)
    turnaround_time[i]=Ct[i]-arrival_time[i];
    
    for(i=0;i<n;i++)
    waiting_time[i]=turnaround_time[i]-burst_time[i];
    
    
    printf("\nProcess Table:\nPid\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(i=0;i<n;i++)
    printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",(i+1),arrival_time[i],burst_time[i],Ct[i],turnaround_time[i],waiting_time[i],Rt[i]);
    
    float for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)turnaround_time[i];
    printf("\nAverage Turnaround Time: %f",for_avg/n);
    for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)waiting_time[i];
    printf("\nAverage Waiting Time: %f",for_avg/n);
    for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)Rt[i];
    printf("\nAverage Response Time: %f",for_avg/n);
    printf("\n");
}

// method 5 for preemptive priority alogritm
void pp(){

    int n,i,j;
    printf("Total Number of Processes:");
    scanf("%d",&n);
    int arrival_time[n],burst_time[n],priority_num[n];
    printf("Enter the Arrival time of Processes:\n");
    for(i=0;i<n;i++)
    scanf("%d",&arrival_time[i]);
    printf("Enter the Burst time:\n");
    for(i=0;i<n;i++)
    scanf("%d",&burst_time[i]);
    printf("Priority:\n");
    for(i=0;i<n;i++)
    scanf("%d",&priority_num[i]);
    int Bt[n],completion_time[n],response_time[n],Pr[n];
    for(i=0;i<n;i++)
    Bt[i]=burst_time[i];
    for(i=0;i<n;i++)
    Pr[i]=priority_num[i];
    for(i=0;i<n;i++)
    response_time[i]=-1;
    int counter=0,prev=-1,dec=0;
    j=0;
    printf("\nWhich Priority do You Want ?\n");
    int choice;
    printf("Option:\n1.Low number High priority.\n2.Low number Low priority.\n>>>");
    scanf("%d",&choice);
    printf("\nGantt chart:\n|");
    switch(choice)
    {
        case 1:
            while(j<n)
            {
                int min=1000,ind=-1;
                for(i=0;i<n;i++)
                {
                    if(Pr[i]==min && Bt[i]>0)
                    {
                        if(arrival_time[i]<arrival_time[ind])
                        ind=i;
                    }
                    
                    else if(Pr[i]<min && Bt[i]>0)
                    {
                        if(arrival_time[i]<=counter)
                        {
                            min=Pr[i];
                            ind=i;
                        }
                    }
                    
                }
                
                if(ind!=-1)
                {
                    Bt[ind]-=1;
                    if(ind!=prev)
                    printf("%d-P%d-",counter,(ind+1));
                }
                else
                {
                    if(dec==0)
                    printf("%d-Idle-",counter);
                    dec=1;
                }
                
                if(ind!=prev && response_time[ind]==-1)
                response_time[ind]=counter-arrival_time[ind];
                
                counter++;
                
                if(Bt[ind]==0 && ind!=-1)
                {
                    completion_time[ind]=counter;
                    j++;
                    dec=0;
                }
                prev=ind;
            }
        break;
        case 2:
            while(j<n)
            {
                int max=-10,ind=-1;
                for(i=0;i<n;i++)
                {
                    if(Pr[i]==max && Bt[i]>0)
                    {
                        if(arrival_time[i]<arrival_time[ind])
                        ind=i;
                    }
                    
                    else if(Pr[i]>max && Bt[i]>0)
                    {
                        if(arrival_time[i]<=counter)
                        {
                            max=Pr[i];
                            ind=i;
                        }
                    }
                    
                }
                
                if(ind!=-1)
                {
                    Bt[ind]-=1;
                    if(ind!=prev)
                    printf("%d-P%d-",counter,(ind+1));
                }
                else
                {
                    if(dec==0)
                    printf("%d-Idle-",counter);
                    dec=1;
                }
                
                
                if(ind!=prev && response_time[ind]==-1)
                response_time[ind]=counter-arrival_time[ind];
                
                counter++;
                
                if(Bt[ind]==0 && ind!=-1)
                {
                    completion_time[ind]=counter;
                    j++;
                    dec=0;
                }
                prev=ind;
            }
        break;
        default:
            printf("Wrong choice..\n");
        break;
    }

    
    printf("%d|\n",counter);
    
    int turnaround_time[n],waiting_time[n];
    
    for(i=0;i<n;i++)
    turnaround_time[i]=completion_time[i]-arrival_time[i];
    
    for(i=0;i<n;i++)
    waiting_time[i]=turnaround_time[i]-burst_time[i];
    
    printf("\nProcess Table:\nPid\tPr\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++)
    printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",(i+1),priority_num[i],arrival_time[i],burst_time[i],completion_time[i],turnaround_time[i],waiting_time[i]);
    
    float for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)turnaround_time[i];
    printf("\nAverage Tunaround Time: %f",for_avg/n);
    for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)waiting_time[i];
    printf("\nAverage Waiting Time: %f",for_avg/n);
    for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)response_time[i];
    printf("\nAverage Response Time: %f",for_avg/n);
    printf("\n");

}
// method 6 for round non preemptive priority algoritm

void npp(){
  int n,i,j;
    printf("Total Number of Processes:");
    scanf("%d",&n);
    int arrival_time[n],burst_time[n],num_priority[n];
    printf("Enter the Arrival time:\n");
    for(i=0;i<n;i++)
    scanf("%d",&arrival_time[i]);
    printf("Enter the Burst time for processes:\n");
    for(i=0;i<n;i++)
    scanf("%d",&burst_time[i]);
    printf("Priority:\n");
    for(i=0;i<n;i++)
    scanf("%d",&num_priority[i]);
    int Pr[n],completion_time[n];
    for(i=0;i<n;i++)
    Pr[i]=num_priority[i];
    int counter=0,dec=0;
    j=0;
    int choice;
    printf("Option:\n1.Low number High priority.\n2.Low number Low priority.\n>>>");
    scanf("%d",&choice);
    
    printf("\nGantt chart:\n|");
    switch(choice)
    {
        case 1:
            while(j<n)
            {
                int min=1000,index=-1;
                for(i=0;i<n;i++)
                {
                    if(Pr[i]==min)
                    {
                        if(arrival_time[i]<arrival_time[index])
                        index=i;
                    }
                    
                    else if(Pr[i]<min)
                    {
                        if(arrival_time[i]<=counter)
                        {
                            min=Pr[i];
                            index=i;
                        }
                    }
                    
                }
                if(index!=-1)
                {
                    printf("%d-P%d-",counter,(index+1));
                    completion_time[index]=burst_time[index]+counter;
                    counter+=burst_time[index];
                    j++;
                    Pr[index]=1001;
                    dec=0;
                }
                else
                {
                    if(dec==0)
                    printf("%d-Idle-",counter);
                    counter++;
                    dec=1;
                }
            }
        break;
        case 2:
            while(j<n)
            {
                int max=-1,index=-1;
                for(i=0;i<n;i++)
                {
                    if(Pr[i]==max)
                    {
                        if(arrival_time[i]<arrival_time[index])
                        index=i;
                    }
                    
                    else if(Pr[i]>max)
                    {
                        if(arrival_time[i]<=counter)
                        {
                            max=Pr[i];
                            index=i;
                        }
                    }
                    
                }
                if(index!=-1)
                {
                    printf("%d-P%d-",counter,(index+1));
                    completion_time[index]=burst_time[index]+counter;
                    counter+=burst_time[index];
                    j++;
                    Pr[index]=-2;
                    dec=0;
                }
                else
                {
                    if(dec==0)
                    printf("%d-Idle-",counter);
                    counter++;
                    dec=1;
                }
            }
        break;
        default:
            printf("Wrong choice..\n");
        break;
    }
    
    printf("%d|\n",counter);
    
    int turnaround_time[n],waiting_time[n];
    
    for(i=0;i<n;i++)
    turnaround_time[i]=completion_time[i]-arrival_time[i];
    
    for(i=0;i<n;i++)
    waiting_time[i]=turnaround_time[i]-burst_time[i];
    
    printf("\nProcess Table:\nPid\tPr\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++)
    printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",(i+1),num_priority[i],arrival_time[i],burst_time[i],completion_time[i],turnaround_time[i],waiting_time[i]);
    
    float for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)turnaround_time[i];
    printf("\nAverage Turnaround Time: %f",for_avg/n);
    for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)waiting_time[i];
    printf("\nAverage Waiting Time: %f",for_avg/n);
    printf("\n");
}
// Main Method to call all the above methods  on user choice
int main()
{
	printf("\n------------------------------------------\n ");
	printf(" Main Menu for Process Scheduling Algorithm\n");
	printf("------------------------------------------\n\n");
	printf("Press 1 for 'FIRST COME FIRST SERVE' \n");
	printf("Press 2 for 'SHORTEST JOB FIRST' \n");
	printf("Press 3 for 'SHORTEST REMAINING TIME FIRST' \n");
	printf("Press 4 for 'ROUND ROBIN' \n");
	printf("Press 5 for 'PREEMPTIVE PROPERTY' \n");
	printf("Press 6 for 'NON PREEMPTIVE PROPERTY' \n");
	printf("Press 0 for 'EXIT' \n");
	printf("\n------------------------------------------\n");
	int choice ;
	printf("Enter Your Choice : ");
	 scanf("%d",&choice);	
	
     
     switch(choice)
     {
         case 1:
           	fcfs();
           break;
         case 2:
           	sjf();
           break;
         case 3:
           	srtf();
           break;
         case 4:
           	rr();
           break;
         case 5:
           	pp();
           break;
         case 6:
           	npp();
           break;           
         case 0:
         	exit(1);
          break;	           
         default:
           printf("Invalid Choice! Try Again.");
    }
    return 0;
}

	

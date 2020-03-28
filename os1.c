/*This is the scheduler that uses a preemptive priority scheduling algorithm based on dynamically changing priority with 1 or 2 
created by Aakash Kumar*/
#include<stdio.h>
struct processes
{
	int priority;
	int waitingTime;
	int arrivalTime;
	int processesId;
	int burstTime;
	
};
int Totaltime,burstTime=0; 
int total=-1,i=-1; /*Total = no of processes entered in cpu*/
struct processes queue[100],result[100],swap;
//Number of processes
int createprocesses()
{
	int n;
	printf("enter the number of processes you want to enter:");
	scanf("%d",&n);
	return n;
}

void execute()
{
	if(total>=0)
	{
		int wait,j;
		//change  by 1burst time of priority in excecution
		if(burstTime!=0 && queue[0].burstTime!=0)
		{
			queue[0].burstTime--;
			burstTime--;
			queue[0].priority++;
			queue[0].arrivalTime=Totaltime+1;
			Totaltime++;
		//cahnge by 2 wait and priority of waiting processes	
			for(wait=1;wait<=total;wait++)
			{
				queue[wait].priority+=2;
				queue[wait].waitingTime=++queue[wait].waitingTime;
			}
		}
		//if processes gets completed ,put in result queue
		if(queue[0].burstTime==0)
		{
			i++;
			result[i]=queue[0];
			for(wait=0;wait<total;wait++)
			{
				queue[wait]=queue[wait+1];
			}
			total--;
		}
		//to sort the processes again in by priority
		for(wait=0;wait<total;wait++)
		{
			for(j=0;j<total;j++)
			{
				if(queue[wait].priority<=queue[j].priority)
				{
					swap=queue[wait];
					queue[wait]=queue[j];
					queue[j]=swap;
				}
			}
		}
		if(queue[0].priority<=queue[1].priority && total>=1)
		{
			swap=queue[0];
			for(wait=0;wait<total;wait++)
			{
				queue[wait]=queue[wait+1];
			}
			queue[total]=swap;
		}
	}
}
/*Sort the array according to arrival time and if arrival time is equal
then sort according to burst time*/
void main()
{
	int l,j,n=createprocesses(),count=0;
	float avgWaitingTime=0;
	struct processes processesCreate[n];
	for(l=0;l<n;l++)
	{
		processesCreate[l].processesId=l+1;
		printf("\nEnter the arrival time of process[%d]: ",l+1);
		scanf("%d",&processesCreate[l].arrivalTime);
		printf("\nEnter the burst time of process[%d]: ",l+1);
		scanf("%d",&processesCreate[l].burstTime);
		processesCreate[l].priority=0;
		processesCreate[l].waitingTime=0;
		burstTime=burstTime+processesCreate[l].burstTime;
	}
	for(l=0;l<n;l++)
	{
		for(j=0;j<n;j++)
		{
		if(processesCreate[l].arrivalTime<processesCreate[j].arrivalTime)
		{
			swap=processesCreate[l];
			processesCreate[l]=processesCreate[j];
			processesCreate[j]=swap;
		}
		if(processesCreate[l].arrivalTime==processesCreate[j].arrivalTime)
		{
			if(processesCreate[l].burstTime<=processesCreate[j].burstTime)
			{
			swap=processesCreate[l];
			processesCreate[l]=processesCreate[j];
			processesCreate[j]=swap;
			}
	 	}
	    }
}//	printing the sorted processes id with respect to arrival time.
	printf("VALUES ENTERED:\n*(TABLE SORTED ACCORDING TO THE AARIVAL TIME)\n\n");
	printf("                          processes TABLE \n\n");

	printf("	processes ID        ARRIVAL TIME            SERVICE TIME \n\n");

	for(l=0;l<n;l++)
	{
		printf("      	 %d          	     %d           	       %d\n\n",processesCreate[l].processesId,processesCreate[l].arrivalTime,processesCreate[l].burstTime );
	}
	Totaltime=processesCreate[0].arrivalTime;
	for(j=processesCreate[0].arrivalTime;j<=processesCreate[n-1].arrivalTime;j++)
	{
		for(l=0;l<n;l++)
		{
			if(processesCreate[l].arrivalTime==j && count!=n)
			{
				total++;
				queue[total]=processesCreate[l];
				count++;
			}
			if(count==n)
				break;
		}
		execute();
		Totaltime++;
	while(burstTime!=0 && count==n)
	{
		execute();
		Totaltime++;
	}
	if(count==n)
		break;
	}
	printf("processes in last form:\n\n");
	printf("	    		FINAL EXECUTION TABLE \n\n");
	printf("    processes ID         ARRIVAL TIME            SERVICE TIME         WAITING TIME\n");
	for(l=0;l<n;l++)
	{
		for(j=0;j<n;j++)
		{
			if(result[l].processesId==processesCreate[j].processesId)
			{
	printf("  	%d                 %d                       %d                	%d\n\n",result[l].processesId,processesCreate[j].arrivalTime,processesCreate[j].burstTime,result[l].waitingTime);
			break;
			break;
			}
		}
		avgWaitingTime+=(result[l].waitingTime);
	}
	printf("Average Waiting Time :%.2f\n",avgWaitingTime/n);}
	

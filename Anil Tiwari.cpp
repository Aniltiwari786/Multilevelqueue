#include<stdio.h>
    struct process_structure {
	        int process_id, arrival_time, burst_time, priority;
		int w_flag,waiting_time;
		int turnaround_time;
    };
int main() {
    int limit, count;
    int time_quantum;
    int waiting_time;
int i, j;
    printf("\nQueue Level 1 : Fixed priority preemptive Scheduling\nQueue Level 2 : Round Robin Scheduling\n\n");
    printf("Enter Total Number of Processes   : ");
    scanf("%d", & limit);
    printf("Enter Time Quantum for Round Robin: ");
    scanf("%d", & time_quantum);
    struct process_structure p1[limit];
    struct process_structure p2[limit];
    struct process_structure processTree[limit];
    int flag = 1;
    int Qlevel;
    int q1 = 0, q2 = 0;
    //Enter Process Details Here	
    for (count = 0; count < limit; count++) {
        while (flag) {
            printf("\nLevel[1/2]\t : ");
            scanf("%d", & Qlevel);
            if (Qlevel == 1 || Qlevel == 2) {
                break;
            }
            printf("!! Enter Level Again !!");
        }
        if (Qlevel == 1) {
            printf("Process ID       : ");
            scanf("%d", & p1[q1].process_id);
           printf("Arrival Time     : ");
            scanf("%d", & p1[q1].arrival_time);
            printf("Burst Time       : ");
            scanf("%d", & p1[q1].burst_time);
            printf("Process Priority : ");
            scanf("%d", & p1[q1].priority);
	    p1[q1].w_flag=0;
            p1[q1].waiting_time=0;
            p1[q1].turnaround_time=0;	
            processTree[count]=p1[q1];
            q1++;
        } else {
            printf("Process ID       : ");
            scanf("%d", & p2[q2].process_id);
            printf("Arrival Time     : ");
            scanf("%d", & p2[q2].arrival_time);
            printf("Burst Time       : ");
            scanf("%d", & p2[q2].burst_time);
            p2[q2].w_flag=0;
            p2[q2].waiting_time=0;
          p2[q2].priority=-1;	
	    processTree[count]=p2[q2];	
            q2++;
        }
    }
    /// -------------------------------------------------- Queue 1 --------------------------------------------------------------///
    printf("\n\n \t\t\tLEVEL 1 QUEUE IS Running\n\n");
struct process_structure temp;
	//Login to sort process on basis of arrival_time//
    for (i = 1; i < q1; i++)
        for (j = 0; j < q1 - i; j++) {
            if (p1[j].arrival_time > p1[j + 1].arrival_time) {
                temp = p1[j];
                p1[j] = p1[j + 1];
                p1[j + 1] = temp;
            }
        }
	//Logic to run processes
    for (i = 0; i < q1; i++) {
        printf("\nProcess ID:%d\t Arrival Time:%d \tPriority: %d\tBurst Time:%d", p1[i].process_id, p1[i].arrival_time, p1[i].priority, p1[i].burst_time);
    }
    printf("\n\n");
int total_process_L1 = q1;
    i = 0;
    int run;
    for (run = 0;; run++) {
        if (q1 == 0) {
            break;
        }
 //premepts previous process
        if (p1[i].priority > p1[i + 1].priority && p1[i + 1].arrival_time == run) {
            p2[q2] = p1[i];
	    p1[i].priority=-1;	
            p2[q2].arrival_time = run;
	    p2[q2].w_flag=0;
            p2[q2].priority = -1;
            printf("\n----------------------------------------------------------------\n");
            printf("\t\t\t\t\tprocess %d is moved to Queue 2\n--------------------------------------------------------------------\n", p1[i].process_id);
            q1--;
            q2++;
                       i++;
        }
        if (p1[i].arrival_time <= run && p1[i].burst_time != 0) {
		if(p1[i].w_flag==0)
		{	
			p1[i].waiting_time+=((run)-p1[i].arrival_time);
			p1[i].w_flag=1;
		}
            printf("\nProcess ID:%d  Priority: %d Burst Time %d time %d", p1[i].process_id, p1[i].priority, p1[i].burst_time, run);
		 p1[i].burst_time--;
            } else if (p1[i].burst_time == 0) {
            printf("\n---------------------------------------------------------------------\n");
            printf("\t\t\t\t\tprocess %d Finised\n-----------------------------------------------------------------------",  p1[i].process_id);
            q1--;
	    run--;
            i++;
        }
    }
    int k=0;
    for (i = 0; i < total_process_L1; i++) {
	 for(k=0;k<limit;k++)
	{	
		if(p1[i].process_id==processTree[k].process_id)
		{	
			processTree[k].waiting_time=p1[i].waiting_time;
		}
	}
	}
	 printf("\n\n");
//-----------------------------------------------------------------------//
    /// Round Robin Queue 2///
//sorting on basis of arrival time
    printf("\n\n LEVEL 2 QUEUE IS Running\n\n");
    for (i = 1; i < q2; i++) {
        for (j = 0; j < q2 - i; j++) {
            if (p2[j].arrival_time > p2[j + 1].arrival_time) {
                temp = p2[j];
                p2[j] = p2[j + 1];
                p2[j + 1] = temp;
            }
        }
    }
//-----------------------------------------------------------------------//
    int total_process_L2 = q2;
    for (i = 0; i < q2; i++) {
        printf("\nProcess ID:%d\t Arrival Time:%d \tBurst Time:%d", p2[i].process_id, p2[i].arrival_time, p2[i].burst_time);
    }
printf("\n\n");
//-----------------------------------------------------------------------//
    i = 0;
    int resetter = 0;
    for (run;; run++) 
     {
        if (total_process_L2 == 0)
        {
            break; }
	if(p2[i].burst_time == 0)
        {
            printf("\n---------------------------------------------------------------------\n");
            printf("\t\t\t\t\tprocess %d Finised\n-----------------------------------------------------------------------", p2[i].process_id);
            i++;
	    run--;
            total_process_L2--;
            resetter = 0;
            continue;
        }
        else if (resetter == time_quantum)
        {
            printf("\n\n!! Time Quantum Complete of %d seconds !!! \n", resetter);	
            p2[q2] = p2[i];
	    p2[q2].arrival_time=run;	
            i++;
	    q2++;
            resetter = 0;
        }
        if (p2[i].arrival_time <= run && p2[i].burst_time != 0)
        {
 		if(resetter==0&&p2[i].process_id!=p2[i-1].process_id)
		{	
			p2[i].waiting_time+=(run-p2[i].arrival_time);

			p2[i].w_flag=1;
		} 
		printf("\nProcess ID:%d  Burst Time %d time %d", p2[i].process_id, p2[i].burst_time, run);
		p2[i].burst_time --;
        }
	 else if (p2[i].burst_time == 0)
	 {

            printf("\n-----------------------\n");
            printf("\t\t\t\t\tprocess %d Finised\n-----------------------------", p2[i].process_id);
            i++;
	    run--;
            total_process_L2--;
	    resetter = 0;
        }
      resetter++;
    }
 for (i = 0; i < q2; i++) {
	 for(k=0;k<limit;k++)
	{	
		if(p2[i].process_id==processTree[k].process_id)
		{	
			processTree[k].waiting_time=p2[i].waiting_time;
		}}}
	float avg_wait_time=0;
float avg_turn_time=0;
   for (i = 0; i < limit; i++) {
	processTree[i].turnaround_time=processTree[i].burst_time+processTree[i].waiting_time;
        printf("\n| Process ID:%d | Arrival Time:%d | Burst Time:%d | waiting Time:%d  | Turn Time:%d |", processTree[i].process_id, processTree[i].arrival_time,processTree[i].burst_time, processTree[i].waiting_time,processTree[i].turnaround_time);
	avg_wait_time+=processTree[i].waiting_time;
	avg_turn_time+=processTree[i].turnaround_time;
    }
   printf("\n\n");
	avg_wait_time/=limit;
        avg_turn_time/=limit;
	printf("Average Waiting Time    : %.2f\n",avg_wait_time);
        printf("Average TurnAround Time : %.2f\n",avg_turn_time);
}

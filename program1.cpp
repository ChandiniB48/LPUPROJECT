
#include<iostream>
using namespace std;
 
// Function to find the waiting time for all
// processes
void findWaitingTime(int processes[], int n,
             int bt[], int wt[], int quantum)
{

    int rem_bt[n];
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] =  bt[i];
 
    int t = 0; 
    while (1)
    {
        bool done = true;
        for (int i = 0 ; i < n; i++)
        {
            
            if (rem_bt[i] > 0)
            {
                done = false; 
 
                if (rem_bt[i] > quantum)
                {
                    
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                
                    t = t + rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == true)
          break;
    }
}
// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n,
                        int bt[], int wt[], int tat[])
{                                                      // calculating turnaround time by adding bt[i] + wt[i]
    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}
 
// Function to calculate average time
void findavgTime(int processes[], int n, int bt[],
                                     int quantum,int pr[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
                                                                 // Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt, quantum);
                                                                 // Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);
                                                                  // Display processes along with all details
    cout << "Processes "<< "priority" << " Burst time "
         << " Waiting time " << " Turn around time\n";
    for (int i=0; i<n; i++)                             // Calculate total waiting time and total turnaround time
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << i+1 << "\t\t" << pr[i] << "\t" << bt[i] <<"\t "
             << wt[i] <<"\t\t " << tat[i] <<endl;
    }
 
    cout << "Average waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
         << (float)total_tat / (float)n;
}
void priority(int p[],int n,int bt[],int pr[])
{int wt[20],tat[20],i,j,total=0,pos,temp,avg_wt,avg_tat;
	//sorting burst time, priority and process number in ascending order using selection sort
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(pr[j]>pr[pos])
                pos=j;
        }
 
        temp=pr[i];
        pr[i]=pr[pos];
        pr[pos]=temp;
 
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
 
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
    wt[0]=0;            //waiting time for first process is zero
    for(i=1;i<n;i++)      //calculate waiting time
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
        total+=wt[i];
    }
 
    avg_wt=total/n;      //average waiting time
    total=0;
 
    cout<<"\nProcess\t    priority    \tBurst Time    \tWaiting Time\tTurnaround Time";
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];     //calculate turnaround time
        total+=tat[i];
        cout<<"\nP["<<p[i]<<"]\t\t  "<<pr[i]<<"\t\t"<<bt[i]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
    }
 
    avg_tat=total/n;     //average turnaround time
    cout<<"\n\nAverage Waiting Time="<<avg_wt;
    cout<<"\nAverage Turnaround Time="<<avg_tat<<"\n";
 
}

int main()
{
    // process id's
    int processes[] = { 1, 2, 3,4,5,6};
    int n = sizeof processes / sizeof processes[0];   // Burst time of all processes
    int burst_time[] = {20,25,25,15,10,10};         //arrival time
    int at[]={0,25,30,60,100,105};                 //priority
    int pr[]={40,30,30,35,5,10};
    priority(processes,n,burst_time,pr);
    int quantum = 10;                                 // Time quantum
    findavgTime(processes, n, burst_time, quantum,pr);
    return 0;
}

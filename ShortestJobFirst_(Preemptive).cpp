///Shortest Job First (Preemptive)
#include <bits/stdc++.h>
using namespace std;

#define ck(XX) cout<<XX<<endl
#define Fin freopen("in.txt", "r", stdin)

struct process{
    int id;
    int bt;//burst time
    int art;//arriving time
    int rt;//remaining time

    int st;//start time
    int et;//end time
    int wt;//waiting time
    int tat;//turn around time

    process (){st = -1;}
};

bool operator < (process p1, process p2)
{
    return p1.art<p2.art;
}

int n; // total number of process
process p[10000];

void inputProcess()
{
    cout<<"Enter process id, burst time and arriving time\n";
    for(int i=0; i<n; i++)
    {
        cin>>p[i].id>>p[i].bt>>p[i].art;
        p[i].rt = p[i].bt;
    }
    return;
}

void calculateWT()
{
    for(int i=0; i<n; i++)
    {
        p[i].wt = p[i].et - p[i].art - p[i].bt;
    }
    return;
}

void calculateTAT()
{
    for(int i=0; i<n; i++)
    {
        p[i].tat = p[i].bt + p[i].wt;
    }
    return;
}

void SJFP()
{
    int totalWT = 0;
    int totalTAT = 0;

    int completed = 0;
    int time=0;
    int processIndex = -1;


    while(completed < n)
    {
        int mn = 1000000;
        for(int i=0; p[i].art <= time && i<n; i++)
        {
            if(p[i].rt>0 && mn>p[i].rt)
            {
                processIndex = i;
                mn = p[i].rt;
            }
        }

        if(processIndex == -1)
        {
            time++;
            continue;
        }

        if(p[processIndex].st == -1) p[processIndex].st = time;
        time++;
        p[processIndex].rt--;
        if(p[processIndex].rt == 0)
        {
            completed++;
            p[processIndex].et = time;
            processIndex = -1;
        }
    }
    calculateWT();
    calculateTAT();

    for(int i=0; i<n; i++)
    {
        totalWT = totalWT + p[i].wt;
        totalTAT = totalTAT + p[i].tat;
    }

    cout<<"\nID\tBT\tWT\tTAT\n";
    for(int i=0; i<n; i++)
    {
        cout<<p[i].id<<"\t"<<p[i].bt<<"\t"<<p[i].wt<<"\t"<<p[i].tat<<endl;
    }

    cout<<"Average Waiting Time : "<<(double)totalWT/n<<endl;
    cout<<"Average Turn Around Time : "<<(double)totalTAT/n<<endl;
    return;

}

int main()
{
    //Fin;
    cout<<"Enter total number of processes : ";
    cin>>n;

    inputProcess();
    sort(p, p+n);

    SJFP();

    return 0;
}

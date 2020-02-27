///Priority Scheduling (Non Preemptive)

#include <bits/stdc++.h>
using namespace std;

struct process{
    int id;
    int bt;
    int pt; //priority
    int wt;
    int tat;
};
bool operator < (process p1, process p2)
{
    return p1.pt>p2.pt;
}

int n; // total number of process
process p[1000];

void inputProcess()
{
    cout<<"Enter process id, burst time and priority\n";
    for(int i=0; i<n; i++)
    {
        cin>>p[i].id>>p[i].bt>>p[i].pt;
    }
    return;
}

void calculateWT()
{
    p[0].wt = 0;

    for(int i=1; i<n; i++)
    {
        p[i].wt = p[i-1].wt + p[i-1].bt;
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

void PSNP()
{
    int totalWT = 0;
    int totalTAT = 0;

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
    cout<<"Enter total number of processes : ";
    cin>>n;

    inputProcess();
    sort(p, p+n);

    PSNP();
}


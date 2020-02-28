///Round Robin

#include <bits/stdc++.h>
using namespace std;

struct process{
    int id;
    int bt;
    int ext;//execution time
    int wt;
    int tat;
};
bool operator < (process p1, process p2)
{
    return p1.id<p2.id;
}

int n; // total number of process
int q; //amount of quantum
process p[1000];

void inputProcess()
{
    cout<<"Enter process id and burst time\n";
    for(int i=0; i<n; i++)
    {
        cin>>p[i].id>>p[i].bt;
        p[i].wt = 0;
        p[i].ext = 0;
    }
    return;
}

void calculateWT()
{
    int remProcess = n; //remaining process
    int i = 0;
    int qp; //remaining quantum
    while(remProcess != 0)
    {
        qp = q; //remaining quantum
        if(p[i].ext == p[i].bt)
        {
            i = ((i+1)%n);
            continue;
        }

        if(p[i].ext+q > p[i].bt) qp = p[i].bt-p[i].ext; //calculating remaining quantum

        p[i].ext+=qp;
        if(p[i].ext == p[i].bt) remProcess--;

        for(int j=0; j<n; j++)
        {
            if(j == i || p[j].ext == p[j].bt) continue;

            p[j].wt+=qp;
        }
        i = ((i+1)%n);
    }
}

void calculateTAT()
{
    for(int i=0; i<n; i++)
    {
        p[i].tat = p[i].bt + p[i].wt;
    }
    return;
}


void RoundRobin()
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
    cout<<"Enter the amount of quantum : ";
    cin>>q;

    inputProcess();
    sort(p, p+n);
    RoundRobin();

    return 0;
}

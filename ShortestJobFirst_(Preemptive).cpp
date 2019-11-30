///Shortest Job First (Preemptive)

/// INCOMPLETE

#include <bits/stdc++.h>
using namespace std;

struct process{
    int id;
    int bt;//burst time
    int art;//arriving time

    int st;//start time
    int et;//end time
    int wt;//waiting time
    int tat;//turn around time

    process(){st=-1};
    process(int _id, int _bt, int _art)
    {
        id = _id;
        bt = _bt;
        art = _art;
    }
};

bool operator < (process p1, process p2)
{
    return p1.bt < p2.bt;
}

int n; // total number of process
int startingArt = 0;
vector <process> p[10000];

void inputProcess()
{
    cout<<"Enter process id, burst time and arriving time\n";
    int id,bt,art;
    for(int i=0; i<n; i++)
    {
        cin>>id>>bt>>art;
        p[art].push_back(process(id,bt,art));
        startingArt = min(startingArt,art);
    }
    return;
}

void SJFP()
{
    int completed = 0;
    priority_queue <process> pq;

    for(int i=0; i<p[startingArt].size(); i++)
    {
        pq.push(p[startingArt][i]);
    }

    for(int i=0; completed < n; i++)
    {
        process temp = pq.top();
        pq.pop();

        if(pq.bt == 0)
        {
            pq.ed = i;
        }
    }
}

int main()
{
    cout<<"Enter total number of processes : ";
    cin>>n;

    inputProcess();
    SJFP();
}

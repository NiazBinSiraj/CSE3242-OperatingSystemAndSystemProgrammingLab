#include <bits/stdc++.h>
using namespace std;

#define Fin freopen("in.txt","r",stdin)


int p; //number of processes
int r; //number of resources
int allocation[100][100];
int mx[100][100];
int available[100];

bool finish[100];
int work[100];
int need[100][100];
int request[100];
vector <int> safeSequence;

bool isValid(int pi)
{
    for(int i=0; i<r; i++)
    {
        if(need[pi][i]>work[i]) return false;
    }
    return true;
}

void calculateNeed()
{
    for(int i=0; i<p; i++)
    {
        for(int j=0; j<r; j++)
        {
            need[i][j] = mx[i][j] - allocation[i][j];
        }
    }
    return;
}

bool safety()
{
    //initialization
    safeSequence.clear();
    for(int i=0; i<p; i++) finish[i] = false;
    for(int i=0; i<r; i++) work[i] = available[i];

    //Safety Check
    int pi = 0;
    for(int j=0; j<50; j++)
    {
        if(finish[pi] == false && isValid(pi) == true)
        {
            safeSequence.push_back(pi);
            finish[pi] = true;
            for(int i=0; i<r; i++)
            {
                work[i] = work[i]+allocation[pi][i];
            }
        }
        pi = (pi+1)%p;
        if(safeSequence.size() == p) return true;
    }
    return false;
}

bool resourceRequest(int pid)
{
    //available = available - request
    for(int i=0; i<r; i++)
    {
        available[i] = available[i] - request[i];
    }
    //allocation = allocation + request
    for(int i=0; i<r; i++)
    {
        allocation[pid][i] = allocation[pid][i] + request[i];
    }
    //need = need - request
    for(int i=0; i<r; i++)
    {
        need[pid][i] = need[pid][i] - request[i];
    }

    if(safety() == true) return true;
    else
    {
        //Restoring Resource Allocation State
        for(int i=0; i<r; i++)
        {
            available[i] = available[i] + request[i];
        }
        for(int i=0; i<r; i++)
        {
            allocation[pid][i] = allocation[pid][i] - request[i];
        }
        for(int i=0; i<r; i++)
        {
            need[pid][i] = need[pid][i] + request[i];
        }
        return false;
    }
}

void printSafeSequence()
{
    cout<<"\nThe Safe Sequence is : ";
    for(int i=0; i<p; i++)
    {
        cout<<safeSequence[i]<<" ";
    }
    cout<<endl;
    return;
}


int main()
{
    //Fin;
    cout<<"Enter total number of processes : ";
    cin>>p;

    cout<<"Enter total number of resources : ";
    cin>>r;

    cout<<"Enter the allocation of processes : \n";
    for(int i=0; i<p; i++)
    {
        for(int j=0; j<r; j++)
        {
            cin>>allocation[i][j];
        }
    }
    cout<<"Enter maximum needs of processes: \n";
    for(int i=0; i<p; i++)
    {
        for(int j=0; j<r; j++)
        {
            cin>>mx[i][j];
        }
    }
    cout<<"Enter available resources: \n";
    for(int i=0; i<r; i++)
    {
        cin>>available[i];
    }

    calculateNeed();

    if(safety() == true)
    {
        int cmd;
        while(1)
        {
            cout<<"The System is in Safe state."<<endl;
            cout<<"Press 1 to request resource, Press 0 to Exit : "<<endl;
            cin>>cmd;
            if(cmd == 1)
            {
                int pid;
                cout<<"Enter process id : ";
                cin>>pid;
                pid--;
                cout<<"Enter requested resources for process p["<<pid<<"] : ";
                for(int i=0; i<r; i++)
                {
                    cin>>request[i];
                }

                bool valid = true;
                for(int i=0; i<r; i++)
                {
                    if(request[i] > need[pid][i])
                    {
                        cout<<"Requested resources can not be greater than needed resources.\n";
                        valid = false;
                        break;
                    }
                }
                if(valid == false) continue;

                valid = true;
                for(int i=0; i<r; i++)
                {
                    if(request[i]>available[i])
                    {
                        cout<<"Not Enough Resources. P["<<pid<<"] must wait.\n";
                        valid = false;
                        break;
                    }
                }
                if(valid == false) continue;

                //running Resource Request Algorithm
                if(resourceRequest(pid) == true)
                {
                    cout<<"The Resources has been allocated.\n";
                    printSafeSequence();
                }
                else
                {
                    cout<<"Request Can't be granted because the system will be in an unsafe state.\n";
                }
            }
            else return 0;
        }
    }
    else cout<<"There is an Unsafe State in The System."<<endl;

    return 0;
}

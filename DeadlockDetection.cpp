#include <bits/stdc++.h>
using namespace std;

#define Fin freopen("in.txt","r",stdin)


int p; //number of processes
int r; //number of resources
int allocation[100][100];
int request[100][100];
int available[100];

bool finish[100];
int work[100];
vector <int> safeSequence;

bool isValid(int pi)
{
    for(int i=0; i<r; i++)
    {
        if(request[pi][i]>work[i]) return false;
    }
    return true;
}

bool safety()
{
    //initialization
    for(int i=0; i<p; i++)
    {
        bool finished = true;
        for(int j=0; j<r; j++)
        {
            if(allocation[i][j] != 0)
            {
                finished = false;
                break;
            }
        }

        if(finished == true) finish[i] = true;
        else finish[i] = false;
    }
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

void printSafeSequence()
{
    cout<<"There is no deadlock situation in the system.\n";
    cout<<"\nThe Safe Sequence is : ";
    for(int i=0; i<p; i++)
    {
        cout<<safeSequence[i]<<" ";
    }
    cout<<endl;
    return;
}

void printDeadlockedProcess()
{
    cout<<"The system is in a deadlocked state.\n";
    cout<<"The deadlocked processes are : ";
    for(int i=0; i<p; i++)
    {
        if(finish[i] == false) cout<<"p"<<i<<" ";
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
    cout<<"Enter requested resources of processes: \n";
    for(int i=0; i<p; i++)
    {
        for(int j=0; j<r; j++)
        {
            cin>>request[i][j];
        }
    }
    cout<<"Enter available resources: \n";
    for(int i=0; i<r; i++)
    {
        cin>>available[i];
    }

    if(safety() == true) printSafeSequence();
    else printDeadlockedProcess();

    return 0;
}

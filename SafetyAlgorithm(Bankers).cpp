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
vector <int> safeSequence;

bool isValid(int pi)
{
    for(int i=0; i<r; i++)
    {
        if(need[pi][i]>work[i]) return false;
    }
    return true;
}

bool safety()
{
    //initialization
    for(int i=0; i<p; i++) finish[i] = false;
    for(int i=0; i<r; i++) work[i] = available[i];

    //calculateNeed
    for(int i=0; i<p; i++)
    {
        for(int j=0; j<r; j++)
        {
            need[i][j] = mx[i][j] - allocation[i][j];
        }
    }

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
    Fin;
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
    cout<<"Enter maximum needs of processes: ";
    for(int i=0; i<p; i++)
    {
        for(int j=0; j<r; j++)
        {
            cin>>mx[i][j];
        }
    }
    cout<<"Enter available resources: ";
    for(int i=0; i<r; i++)
    {
        cin>>available[i];
    }

    if(safety() == true) printSafeSequence();
    else cout<<"There is an Unsafe State in The System."<<endl;

    return 0;
}

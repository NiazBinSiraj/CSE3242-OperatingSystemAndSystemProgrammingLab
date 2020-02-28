#include <bits/stdc++.h>
using namespace std;

int h; // number of holes
int p; // number processes
int hSize[100];
int pSize[100];
int allocation[100];

int thSize[100];

void PrintOutput()
{
    cout<<"Process No\tProcess Size\tHole No\tHole Size\n";
    for(int i=0; i<p; i++)
    {
        if(allocation[i] == -1) cout<<i+1<<"\t\t"<<pSize[i]<<"\t\tNot Allocated\n";
        else cout<<i+1<<"\t\t"<<pSize[i]<<"\t\t"<<allocation[i]+1<<"\n";
    }
    return;
}

void FirstFit()
{
    for(int i=0; i<p; i++)
    {
        allocation[i] = -1;
        for(int j=0; j<h; j++)
        {
            if(pSize[i] <= thSize[j])
            {
                thSize[j] -= pSize[i];
                allocation[i] = j;
                break;
            }
        }
    }
    cout<<"First Fit Allocation : \n";
    PrintOutput();
    return;
}

void BestFit()
{
    for(int i=0; i<p; i++)
    {
        allocation[i] = -1;
        int minSpace = 10000;
        int holeIndex = -1;
        for(int j=0; j<h; j++)
        {
            if(pSize[i] <= thSize[j] && thSize[j] < minSpace)
            {
                minSpace = thSize[j];
                holeIndex = j;
            }
        }
        if(holeIndex == -1) continue;

        allocation[i] = holeIndex;
        thSize[holeIndex] -= pSize[i];
    }
    cout<<"Best Fit Allocation : \n";
    PrintOutput();
    return;
}

void WorstFit()
{
    for(int i=0; i<p; i++)
    {
        allocation[i] = -1;
        int maxSpace = -1;
        int holeIndex = -1;
        for(int j=0; j<h; j++)
        {
            if(pSize[i] <= thSize[j] && thSize[j] > maxSpace)
            {
                maxSpace = thSize[j];
                holeIndex = j;
            }
        }
        if(holeIndex == -1) continue;

        allocation[i] = holeIndex;
        thSize[holeIndex] -= pSize[i];
    }
    cout<<"Worst Fit Allocation : \n";
    PrintOutput();
    return;
}



int main()
{
    cout<<"Enter total number of holes : ";
    cin>>h;
    cout<<"Enter total number of processes : ";
    cin>>p;

    cout<<"Enter size of each hole : ";
    for(int i=0; i<h; i++)
    {
        cin>>hSize[i];
    }
    cout<<"Enter size of each process : ";
    for(int i=0; i<p; i++)
    {
        cin>>pSize[i];
    }

    copy(hSize, hSize+h, thSize);
    FirstFit();
    copy(hSize, hSize+h, thSize);
    BestFit();
    copy(hSize, hSize+h, thSize);
    WorstFit();

    return 0;
}

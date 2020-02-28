#include <bits/stdc++.h>
using namespace std;
#define MS(XX,YY) memset(XX,YY,sizeof(XX))

int p; //total number of pages
int f; //total number of frames
int pages[100];

int pageFault;
int inFrame[100];

bool pageInFrame(int page)
{
    for(int i=0; i<f; i++)
    {
        if(inFrame[i] == page) return true;
    }
    return false;
}

void FIFO()
{
    int fn = 0;//Frame No
    int hit=0;

    MS(inFrame,-1);

    for(int i=0; i<p; i++)
    {
        if(pageInFrame(pages[i]) == false)
        {
            inFrame[fn] = pages[i];
            fn = (fn+1)%f;
        }
        else
        {
            hit++;
        }
    }
    pageFault = p-hit;
    return;
}

int main()
{
    cout<<"Enter total Number of pages : ";
    cin>>p;
    cout<<"Enter total Number of frames : ";
    cin>>f;

    cout<<"Insert Pages : ";
    for(int i=0; i<p; i++)
    {
        cin>>pages[i];
    }

    FIFO();
    cout<<"Page Fault : "<<pageFault<<endl;
    return 0;
}

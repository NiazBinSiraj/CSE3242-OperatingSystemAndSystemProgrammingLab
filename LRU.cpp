#include <bits/stdc++.h>
using namespace std;
#define MS(XX,YY) memset(XX,YY,sizeof(XX))
#define Fin freopen("in.txt","r",stdin)

int p; //total number of pages
int f; //total number of frames
int pages[100];

int pageFault;
int inFrame[100];
int frameWeight[100];

void printInFrame()
{
    for(int i=0; i<f; i++)
    {
        cout<<inFrame[i]<<" ";
    }
    cout<<endl;
    return;
}

void incFrameWeight(int frame)
{
    for(int i=0; i<f; i++)
    {
        if(i==frame) frameWeight[i] = 1;
        else if(inFrame[i] != -1) frameWeight[i]++;
    }
    return;
}

bool pageInFrame(int page)
{
    for(int i=0; i<f; i++)
    {
        if(inFrame[i] == page)
        {
            incFrameWeight(i);
            return true;
        }
    }
    return false;
}

int findFrame()
{
    int mx = -1;
    int frame;

    for(int i=0; i<f; i++)
    {
        if(inFrame[i] == -1) return i;

        if(frameWeight[i] > mx)
        {
            mx = frameWeight[i];
            frame = i;
        }
    }
    return frame;
}

void LRU()
{
    int hit=0;

    MS(inFrame,-1);
    cout<<endl;

    //printInFrame();
    for(int i=0; i<p; i++)
    {
        int fn = findFrame();


        if(pageInFrame(pages[i]) == false)
        {
            inFrame[fn] = pages[i];
            incFrameWeight(fn);
        }
        else
        {
            hit++;
        }

        //printInFrame();
    }
    pageFault = p - hit;
    return;
}

int main()
{
    //Fin;
    cout<<"Enter total Number of pages : ";
    cin>>p;
    cout<<"Enter total Number of frames : ";
    cin>>f;

    cout<<"Insert Pages : ";
    for(int i=0; i<p; i++)
    {
        cin>>pages[i];
    }

    LRU();
    cout<<"Page Fault : "<<pageFault<<endl;
    return 0;
}

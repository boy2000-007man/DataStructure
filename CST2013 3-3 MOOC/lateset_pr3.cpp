#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
using namespace std;

int max_to_min[200002];
int min_to_max[200002];
void swap(int &a,int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
class minHeap
{
//private:
    public:
    int* array1;
    int theSize1;

    minHeap()
    {
        array1 = new int[200002];
        memset(array1,-1,sizeof(array1));
        theSize1 =0;
    }
    int size()
    {
        return theSize1;
    }
    void print();
    int Insert(int theData);  //返回最终落下的位置 
    void Delete(int pos);
    int first();
    int percolateUp(int i)
    {
        while(i/2 >= 1)
        {
            int j = i/2;
            if (array1[j] <= array1[i]) break;
            swap(min_to_max[j],min_to_max[i]);
            swap(max_to_min[min_to_max[j]], max_to_min[min_to_max[i]]);
            swap(array1[j], array1[i]);
            i = j;
        }
        return i;
    }
    void percolateDown(int size, int i)
    {
        int j;
        while((i*2<=theSize1 && array1[i]>array1[i*2]) || (i*2+1<=theSize1 && array1[i]>array1[i*2+1]))
        {
            if (i*2+1<=theSize1 && array1[i*2]>array1[i*2+1]) j=i*2+1;
            else j=i*2;
            swap(min_to_max[j],min_to_max[i]);
            swap(max_to_min[min_to_max[j]], max_to_min[min_to_max[i]]);
            swap(array1[j],array1[i]); 
            i = j;
        }
    }
} heap1;
class maxHeap
{
public:
    int* array2;
    int theSize2;

    maxHeap()
    {
        array2 = new int[200002];
        memset(array2,-1,sizeof(array2));
        theSize2 =0;
    }
    void print();
    int Insert(int theData); //返回最终落下的位置 
    void Delete(int pos);
    int first();
    int percolateUp(int i)
    {
        while(i/2 >= 1)
        {
            int j = i/2;
            if (array2[j] >= array2[i]) break;
            swap(max_to_min[j],max_to_min[i]);
            swap(min_to_max[max_to_min[j]], min_to_max[max_to_min[i]]);
            swap(array2[j], array2[i]);
            i = j;
        }
        return i;
    }
    void percolateDown(int size, int i)
    {
        int j;
        while((i*2<=theSize2 && array2[i]<array2[i*2]) || (i*2+1<=theSize2 && array2[i]<array2[i*2+1]))
        {
            if (i*2+1<=theSize2 && array2[i*2]<array2[i*2+1]) j=i*2+1;
            else j=i*2;
            swap(max_to_min[j],max_to_min[i]);
            swap(min_to_max[max_to_min[j]], min_to_max[max_to_min[i]]);
            swap(array2[j],array2[i]);
            i = j;
        }
    }
}heap2;
int minHeap::Insert(int theData)
{
    array1[++theSize1] = theData;
    int pos = theSize1;
    return percolateUp(pos);
}
void minHeap::Delete(int pos)
{
    int one = array1[pos];
    array1[pos] = array1[theSize1--];
    if (pos>1 && array1[pos] < array1[pos/2])
    {
        percolateUp(pos);
        return;
    }
    percolateDown(theSize1,pos);
}

int maxHeap::Insert(int theData)
{
    array2[++theSize2] = theData;
    int pos = theSize2;
    return percolateUp(pos);
}
void maxHeap::Delete(int pos)
{
    int one = array2[pos];
    array2[pos] = array2[theSize2--];
    if ((pos*2<=theSize2&&array2[pos]<array2[pos*2]) || (pos*2+1 <= theSize2 && array2[pos]<array2[pos*2+1])){
        percolateDown(theSize2,pos);
        return;
    }
    percolateUp(pos);
}
void maxHeap::print()
{
    for(int i=1;i<=theSize2;i++)
        cout<<array2[i]<< ' ';
    cout << endl;
}
void minHeap::print()
{
    for(int i=1;i<=theSize1;i++)
        cout<<array1[i]<< ' ';
    cout << endl;
}
int main()
{
    /*for (int i=1;i<=4;++i)
    {
        max_to_min[i] = min_to_max[i]=i;
    }
    for (int i=0;i<4;++i)
    {
        int n;
        cin >> n;
        int pos2 = heap2.Insert(n);
        int pos1 = heap1.Insert(n);
        max_to_min[pos2] = pos1;
        min_to_max[pos1] = pos2;
        cout << "heap1:" ; heap1.print();
        cout << "heap2:" ; heap2.print();
        cout << endl;
        cout << "heap1_to_heap2:"; 
        for (int j=1;j<=heap1.size();++j)
            cout << min_to_max[j] << ' ';
        cout << endl;
        cout << "heap2_to_heap1:";
        for (int j=1;j<=heap1.size();++j)
            cout << max_to_min[j] << ' ';
        cout << endl << endl;
    }
    for (int i=0;i<4;++i)
    {
        cout << "min=" << heap1.array1[1] << "\n";
        int pos = min_to_max[1];
        heap1.Delete(1,'a');
        heap2.Delete(pos,'a');
        
    }*/
    int n;//cin >> n; 
    scanf("%d\n", &n);
    char a;
    int number;
    int out[n], x=0;
    for (int i=1;i<=200000;++i)
    {
        max_to_min[i] = min_to_max[i]=i;
    }
    for (int i=0;i<n;++i)
    {
        //cin >> a;
        scanf("%c", &a);
        if (a=='I')
        {
            //cin >> number;
            scanf("%d\n",&number);
            int pos1 = heap1.Insert(number);
            int pos2 = heap2.Insert(number);
            min_to_max[pos1] = pos2;
            max_to_min[pos2] = pos1;
        }
        else if (a=='H')
        {
            if (i!=n-1) scanf("\n");
            if (heap1.size() == 0)
            {
                out[x++] = 0;
                continue;
            }
            out[x++] = heap2.array2[1];
            int pos_1 = max_to_min[1];
            max_to_min[1] = max_to_min[heap2.theSize2];
            min_to_max[max_to_min[heap2.theSize2]] = 1;
            heap2.Delete(1);
            min_to_max[pos_1] = min_to_max[heap1.theSize1];
            max_to_min[min_to_max[heap1.theSize1]] = pos_1;
            heap1.Delete(pos_1);
        }
        else if (a=='L')
        {
            if (i!= n-1)scanf("\n");
            if (heap1.size() == 0)
            {
                out[x++] = 0;
                continue;
            }
            out[x++] = heap1.array1[1];
            int pos_2 = min_to_max[1];
            min_to_max[1] = min_to_max[heap1.theSize1];
            max_to_min[min_to_max[heap1.theSize1]] = 1;
            heap1.Delete(1);
            max_to_min[pos_2] = max_to_min[heap2.theSize2];
            min_to_max[max_to_min[heap2.theSize2]] = pos_2;
            heap2.Delete(pos_2);
        }
    }
    for (int i=0;i<x;++i)
        printf("%d\n", out[i]);
    
    system("pause");
    return 0;
}

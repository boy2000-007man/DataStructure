#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
using namespace std;

int max_to_min[200002];
int min_to_max[200002];
class minHeap
{
private:
    int* array;
    int theSize;
public:
    minHeap()
    {
        array = new int[200002];
        theSize =0;
    }
    int size()
    {
        return theSize;
    }
    void print();
    int Insert(int theData);  //返回最终落下的位置 
    void Delete(int pos);
    int first();
} heap1;
class maxHeap
{
private:
    int* array;
    int theSize;
public:
    maxHeap()
    {
        array = new int[200002];
        theSize =0;
    }
    void print();
    int Insert(int theData); //返回最终落下的位置 
    void Delete(int pos);
    int first();
}heap2;
//插入函数，主要是将元素下滚，hole上滚，因为插入的位置是在最后，

//故hole在最后，所以像hole中滚动就是下滚

int minHeap::Insert(int theData)
{
//最后一个元素的下一个位置形成一个hole，以便接受滚下来的元素
    int hole = ++theSize;

//hole向前移动的结束条件是hole到头或者hole的父节点元素比要插入的元素小
    for(; hole > 1 && array[hole/2] > theData; hole = hole/2){
        int temp1 = min_to_max[hole/2];
        min_to_max[hole] = temp1;
        max_to_min[temp1] = hole;
        //int temp2 = min_to_max[hole];
        /*min_to_max[hole/2] = min_to_max[hole];
        min_to_max[hole] = temp1;
        
        max_to_min[temp2] = hole/2;
        max_to_min[temp1] = hole;*/
//hole的父节点元素滚入到hole，hole=hole/2实现了hole滚动到父节点
        array[hole]=array[hole/2];
    }
//hole滚动到合适位置了，将要插入的元素填入到hole
    array[hole]=theData;
    return hole;
}

//删除指定位置元素的函数，该位置以前的位置不动，以后的位置主要是将元素上滚，

//hole下滚，因为删除后是拿最后一个元素来作为删除后剩下的hole的值，

//很大，故hole要下滚
void minHeap::Delete(int pos)
{
//删除的位置大于heap的边界，返回错误

//删除的位置留下一个hole
    int hole = pos;

//最后一个元素的值放入到tmp，也就是hole中，准备比较，然后下滚
    int tmp = array[theSize--];

//hole还有子节点，也就是hole还有下滚的余地
    while(hole*2 <= theSize)
    {
        int child;

//hole只有一个子节点，则child只能是这个值
        if(hole*2 == theSize)
            child = hole*2;

//这个if else是拿hole两个子节点中教小的值和hole作比较，

//让较小的值滚上来成为较大值的父节点，

//hole替代较小值的位置
        if(array[hole*2]>array[hole*2+1])  ////////////////////////////////////////
        {
            child = hole*2+1;
        }
        else
        {
            child = hole*2;
        }

//较小子节点上滚
        array[hole] = array[child];
        min_to_max[hole] = min_to_max[child];
        max_to_min[min_to_max[child]] = hole;

//hole下滚
        hole = child;
    }

//hole没有下滚的余地了，将hole中填上滚之前的heap的最后一个元素
    array[hole] = tmp;
    max_to_min[hole] = max_to_min[theSize+1];
    min_to_max[max_to_min[theSize+1]] = hole;
}

int minHeap::first()
{
    return array[1] ;
    /*for(int i=1;i<=theSize;i++)
        cout<<array[i]<<endl;*/
}





//插入函数，主要是将元素下滚，hole上滚，因为插入的位置是在最后，

//故hole在最后，所以像hole中滚动就是下滚

int maxHeap::Insert(int theData)
{
//最后一个元素的下一个位置形成一个hole，以便接受滚下来的元素
    int hole = ++theSize;

//hole向前移动的结束条件是hole到头或者hole的父节点元素比要插入的元素小
    for(; hole > 1 && array[hole/2] < theData; hole = hole/2){
        int temp1 = max_to_min[hole/2];
        max_to_min[hole] = temp1;
        min_to_max[temp1] = hole;
//hole的父节点元素滚入到hole，hole=hole/2实现了hole滚动到父节点
        array[hole]=array[hole/2];
    }
    /*int temp1 = max_to_min[];
        int temp2 = max_to_min[hole];
        max_to_min[hole/2] = max_to_min[hole];
        
        max_to_min[hole] = temp1;
        min_to_max[temp2] = hole/2;
        min_to_max[temp1] = hole;
*/
//hole滚动到合适位置了，将要插入的元素填入到hole
    array[hole]=theData;
    return hole;
}

//删除指定位置元素的函数，该位置以前的位置不动，以后的位置主要是将元素上滚，

//hole下滚，因为删除后是拿最后一个元素来作为删除后剩下的hole的值，

//很大，故hole要下滚
void maxHeap::Delete(int pos)
{
//删除的位置大于heap的边界，返回错误
    /*if(theSize < pos)
    {    
        cout<<"error!"<<endl;
        return;
    }*/

//删除的位置留下一个hole
    int hole = pos;

//最后一个元素的值放入到tmp，也就是hole中，准备比较，然后下滚
    int tmp = array[theSize--];

//hole还有子节点，也就是hole还有下滚的余地
    while(hole*2 <= theSize)
    {
        int child;

//hole只有一个子节点，则child只能是这个值
        if(hole*2 == theSize)
            child = hole*2;

//这个if else是拿hole两个子节点中教小的值和hole作比较，

//让较小的值滚上来成为较大值的父节点，

//hole替代较小值的位置
        if(array[hole*2]<array[hole*2+1])  ////////////////////////////////////////
        {
            child = hole*2+1;
        }
        else
        {
            child = hole*2;
        }
///////// 上滚时间可以减少、、、、、、、、、、、、、、、、、、 
//较小子节点上滚
        array[hole] = array[child];
        
        max_to_min[hole] = max_to_min[child];
        min_to_max[max_to_min[child]] = hole;
        /*int temp1 = max_to_min[child]; 
        int temp2 = max_to_min[hole];
        max_to_min[child] = max_to_min[hole];
        
        max_to_min[hole] = temp1;
        min_to_max[temp2] = child;
        min_to_max[temp1] = hole;*/
//hole下滚
        hole = child;
    }

//hole没有下滚的余地了，将hole中填上滚之前的heap的最后一个元素
    array[hole] = tmp;
    min_to_max[hole] = min_to_max[theSize+1];
    max_to_min[min_to_max[theSize+1]] = hole;
    //max_to_min[hole] = max_to_min[child];
    
}

int maxHeap::first()
{
    return array[1] ;
    /*for(int i=1;i<=theSize;i++)
        cout<<array[i]<<endl;*/
}
void maxHeap::print()
{
    for(int i=1;i<=theSize;i++)
        cout<<array[i]<<endl;
}
void minHeap::print()
{
    for(int i=1;i<=theSize;i++)
        cout<<array[i]<<endl;
}
int main()
{
    //////minHeap heap1;
    //maxHeap heap2;
    //ifstream fin("input.txt");
    int n; scanf("%d\n", &n);
    char a;
    int number;
    int out[n], x=0;
    for (int i=0;i<n;++i)
    {
        scanf("%c", &a);
        if (a=='I')
        {
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
            out[x++] = heap2.first();
            int pos_1 = max_to_min[1];
            heap2.Delete(1);
            /*for (int j=1;j<=heap1.size();++j)
                cout << max_to_min[j] << ' ';
            system("pause");
            */heap1.Delete(pos_1);
            /*for (int k=1;k<=heap1.size();++k)
            {
                max_to_min[k]--;
                min_to_max[k]--;
            }*/
        }
        else if (a=='L')
        {
            if (i!= n-1)scanf("\n");
            if (heap1.size() == 0)
            {
                out[x++] = 0;
                continue;
            }
            out[x++] = heap1.first();
            int pos_2 = min_to_max[1];
            heap1.Delete(1);
            heap2.Delete(pos_2);
            /*for (int k=1;k<=heap1.size();++k)
            {
                max_to_min[k]--;
                min_to_max[k]--;
            }*/
        }
        /*cout << "max_to_min:"; 
        for (int j=1;j<=heap1.size();++j)
            cout << max_to_min[j] << ' ';
        cout << endl << "min_to_max:" ;
        for (int j=1;j<=heap1.size();++j)
            cout << min_to_max[j] << ' ';
        cout << endl;*/
    }
    for (int i=0;i<x;++i)
        printf("%d\n", out[i]);
    system("pause");
    return 0;
}

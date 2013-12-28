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
    int Insert(int theData);  //�����������µ�λ�� 
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
    int Insert(int theData); //�����������µ�λ�� 
    void Delete(int pos);
    int first();
}heap2;
//���뺯������Ҫ�ǽ�Ԫ���¹���hole�Ϲ�����Ϊ�����λ���������

//��hole�����������hole�й��������¹�

int minHeap::Insert(int theData)
{
//���һ��Ԫ�ص���һ��λ���γ�һ��hole���Ա���ܹ�������Ԫ��
    int hole = ++theSize;

//hole��ǰ�ƶ��Ľ���������hole��ͷ����hole�ĸ��ڵ�Ԫ�ر�Ҫ�����Ԫ��С
    for(; hole > 1 && array[hole/2] > theData; hole = hole/2){
        int temp1 = min_to_max[hole/2];
        min_to_max[hole] = temp1;
        max_to_min[temp1] = hole;
        //int temp2 = min_to_max[hole];
        /*min_to_max[hole/2] = min_to_max[hole];
        min_to_max[hole] = temp1;
        
        max_to_min[temp2] = hole/2;
        max_to_min[temp1] = hole;*/
//hole�ĸ��ڵ�Ԫ�ع��뵽hole��hole=hole/2ʵ����hole���������ڵ�
        array[hole]=array[hole/2];
    }
//hole����������λ���ˣ���Ҫ�����Ԫ�����뵽hole
    array[hole]=theData;
    return hole;
}

//ɾ��ָ��λ��Ԫ�صĺ�������λ����ǰ��λ�ò������Ժ��λ����Ҫ�ǽ�Ԫ���Ϲ���

//hole�¹�����Ϊɾ�����������һ��Ԫ������Ϊɾ����ʣ�µ�hole��ֵ��

//�ܴ󣬹�holeҪ�¹�
void minHeap::Delete(int pos)
{
//ɾ����λ�ô���heap�ı߽磬���ش���

//ɾ����λ������һ��hole
    int hole = pos;

//���һ��Ԫ�ص�ֵ���뵽tmp��Ҳ����hole�У�׼���Ƚϣ�Ȼ���¹�
    int tmp = array[theSize--];

//hole�����ӽڵ㣬Ҳ����hole�����¹������
    while(hole*2 <= theSize)
    {
        int child;

//holeֻ��һ���ӽڵ㣬��childֻ�������ֵ
        if(hole*2 == theSize)
            child = hole*2;

//���if else����hole�����ӽڵ��н�С��ֵ��hole���Ƚϣ�

//�ý�С��ֵ��������Ϊ�ϴ�ֵ�ĸ��ڵ㣬

//hole�����Сֵ��λ��
        if(array[hole*2]>array[hole*2+1])  ////////////////////////////////////////
        {
            child = hole*2+1;
        }
        else
        {
            child = hole*2;
        }

//��С�ӽڵ��Ϲ�
        array[hole] = array[child];
        min_to_max[hole] = min_to_max[child];
        max_to_min[min_to_max[child]] = hole;

//hole�¹�
        hole = child;
    }

//holeû���¹�������ˣ���hole�����Ϲ�֮ǰ��heap�����һ��Ԫ��
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





//���뺯������Ҫ�ǽ�Ԫ���¹���hole�Ϲ�����Ϊ�����λ���������

//��hole�����������hole�й��������¹�

int maxHeap::Insert(int theData)
{
//���һ��Ԫ�ص���һ��λ���γ�һ��hole���Ա���ܹ�������Ԫ��
    int hole = ++theSize;

//hole��ǰ�ƶ��Ľ���������hole��ͷ����hole�ĸ��ڵ�Ԫ�ر�Ҫ�����Ԫ��С
    for(; hole > 1 && array[hole/2] < theData; hole = hole/2){
        int temp1 = max_to_min[hole/2];
        max_to_min[hole] = temp1;
        min_to_max[temp1] = hole;
//hole�ĸ��ڵ�Ԫ�ع��뵽hole��hole=hole/2ʵ����hole���������ڵ�
        array[hole]=array[hole/2];
    }
    /*int temp1 = max_to_min[];
        int temp2 = max_to_min[hole];
        max_to_min[hole/2] = max_to_min[hole];
        
        max_to_min[hole] = temp1;
        min_to_max[temp2] = hole/2;
        min_to_max[temp1] = hole;
*/
//hole����������λ���ˣ���Ҫ�����Ԫ�����뵽hole
    array[hole]=theData;
    return hole;
}

//ɾ��ָ��λ��Ԫ�صĺ�������λ����ǰ��λ�ò������Ժ��λ����Ҫ�ǽ�Ԫ���Ϲ���

//hole�¹�����Ϊɾ�����������һ��Ԫ������Ϊɾ����ʣ�µ�hole��ֵ��

//�ܴ󣬹�holeҪ�¹�
void maxHeap::Delete(int pos)
{
//ɾ����λ�ô���heap�ı߽磬���ش���
    /*if(theSize < pos)
    {    
        cout<<"error!"<<endl;
        return;
    }*/

//ɾ����λ������һ��hole
    int hole = pos;

//���һ��Ԫ�ص�ֵ���뵽tmp��Ҳ����hole�У�׼���Ƚϣ�Ȼ���¹�
    int tmp = array[theSize--];

//hole�����ӽڵ㣬Ҳ����hole�����¹������
    while(hole*2 <= theSize)
    {
        int child;

//holeֻ��һ���ӽڵ㣬��childֻ�������ֵ
        if(hole*2 == theSize)
            child = hole*2;

//���if else����hole�����ӽڵ��н�С��ֵ��hole���Ƚϣ�

//�ý�С��ֵ��������Ϊ�ϴ�ֵ�ĸ��ڵ㣬

//hole�����Сֵ��λ��
        if(array[hole*2]<array[hole*2+1])  ////////////////////////////////////////
        {
            child = hole*2+1;
        }
        else
        {
            child = hole*2;
        }
///////// �Ϲ�ʱ����Լ��١����������������������������������� 
//��С�ӽڵ��Ϲ�
        array[hole] = array[child];
        
        max_to_min[hole] = max_to_min[child];
        min_to_max[max_to_min[child]] = hole;
        /*int temp1 = max_to_min[child]; 
        int temp2 = max_to_min[hole];
        max_to_min[child] = max_to_min[hole];
        
        max_to_min[hole] = temp1;
        min_to_max[temp2] = child;
        min_to_max[temp1] = hole;*/
//hole�¹�
        hole = child;
    }

//holeû���¹�������ˣ���hole�����Ϲ�֮ǰ��heap�����һ��Ԫ��
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

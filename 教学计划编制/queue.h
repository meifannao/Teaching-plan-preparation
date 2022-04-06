#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

/*typedef struct Node Node;
typedef struct LinkNode LinkNode;
typedef struct Graph Graph;
typedef struct Node
{
    char CourseName[30];  //�γ�����
    char Course[10];             //�γ̺�
    double Score;              //�γ�ѧ��
    int isBase;                //�Ƿ�δ������
    int isCenter;              //�Ƿ�δ���Ŀ�
    int NumberOfPrimary;    //�ÿγ�ֱ�����޿γ�����
    int NumberOfFollow;
    LinkNode *Primary;
    LinkNode *Follow;      //�ÿγ�ֱ�����޿γ�����ָ��
}Node;

typedef struct LinkNode
{
    char Course[5];             //�γ̺�
    LinkNode *next;
}LinkNode;



typedef struct Graph
{
    Node *GraphPointer;    //ͼ�еĿγ�����
    int NumberOfCourse;    //ͼ�пγ̽ڵ������
    int NumOfSorted;       //�ѽ����������еĿγ̽ڵ�����
    int *SortedCourse;     //����������������
    //int *InDegree;        //������

}Graph;*/

typedef struct queue
{
    int data[100];
    int front, rear;
} SeqQueue;


SeqQueue* Init_SeqList()
{
    SeqQueue *q;
    q = (SeqQueue*)malloc(sizeof(SeqQueue));
    q -> front = q -> rear = 0;
    return q;
}

int Empty_SeqList(SeqQueue *q)
{
    if(q -> front == q -> rear)
        return 1;
    return 0;
}

int In_SeqList(SeqQueue *q, int x)
{
    if((q -> rear + 1) % 100 == q -> front)
    {
        printf("����\n");
        return 0;
    }
    else
    {
        q -> data[q -> rear] = x;
        q -> rear = (q -> rear + 1) % 100;
        return 1;
    }
}


int Out_SeqList(SeqQueue *q, int *x)
{
    if(q -> front == q -> rear)
    {
        printf("�ӿ�\n");
        return 0;
    }
    else
    {
        *x = q -> data[q -> front];
        q -> front = (q -> front + 1) % 100;
        return 1;
    }
}




#endif // QUEUE_H_INCLUDED

#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

/*typedef struct Node Node;
typedef struct LinkNode LinkNode;
typedef struct Graph Graph;
typedef struct Node
{
    char CourseName[30];  //课程名称
    char Course[10];             //课程号
    double Score;              //课程学分
    int isBase;                //是否未基础课
    int isCenter;              //是否未核心课
    int NumberOfPrimary;    //该课程直接先修课程数量
    int NumberOfFollow;
    LinkNode *Primary;
    LinkNode *Follow;      //该课程直接先修课程链表指针
}Node;

typedef struct LinkNode
{
    char Course[5];             //课程号
    LinkNode *next;
}LinkNode;



typedef struct Graph
{
    Node *GraphPointer;    //图中的课程数组
    int NumberOfCourse;    //图中课程节点的数量
    int NumOfSorted;       //已进入拓扑序列的课程节点数量
    int *SortedCourse;     //存放拓扑排序的数组
    //int *InDegree;        //存放入度

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
        printf("队满\n");
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
        printf("队空\n");
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

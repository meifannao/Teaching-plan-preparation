#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef struct Node Node;
typedef struct LinkNode LinkNode;
typedef struct Graph Graph;
typedef struct Term STU;
typedef struct Node
{
    char Course[10];             //�γ̺�
    char CourseName[30];  //�γ�����
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

}Graph;

typedef struct Term  //��¼ѧ����Ϣ
{
    int Count;     //��¼��ǰѧ�ڰ����˶����ſ�
    double SumScore;//��¼��ǰѧ�ڵ�ѧ��
    int course[50]; //��¼��ǰѧ�ڵĿγ���Ϣ
} STU;


#endif // GRAPH_H_INCLUDED

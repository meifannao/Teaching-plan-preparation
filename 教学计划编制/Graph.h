#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef struct Node Node;
typedef struct LinkNode LinkNode;
typedef struct Graph Graph;
typedef struct Term STU;
typedef struct Node
{
    char Course[10];             //课程号
    char CourseName[30];  //课程名称
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

}Graph;

typedef struct Term  //记录学期信息
{
    int Count;     //记录当前学期安排了多少门课
    double SumScore;//记录当前学期的学分
    int course[50]; //记录当前学期的课程信息
} STU;


#endif // GRAPH_H_INCLUDED

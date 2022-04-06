#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Graph.h"
#include "prior.h"

typedef struct Node Node;
typedef struct LinkNode LinkNode;
typedef struct Graph Graph;

void BuildGraph();
void Input_info();
void TopSort();
int Arrange2();
int Arrange1();
void printf0();
void Input();
void Meau();
void write();
void Flush();


Graph g;
FILE *fp;
double SumScore;


STU arr[13];
const int Size = 50;
int CourseNum;
double MaxScore,TheMax;
int main()
{
    printf0();
    Input();
    BuildGraph();
    TopSort();
    Meau();
    return 0;
}

int Location(char id[5])
{
    for(int i = 0; i < Size; i ++ )
    {
        if(strcmp(g.GraphPointer[i].Course, id) == 0)
        {
            return i;
        }
    }
    return -1;
}

void BuildGraph()
{
    g.GraphPointer = (Node*)malloc(Size * sizeof(Node));
    g.NumberOfCourse = Size;
    g.NumOfSorted = 0;
    g.SortedCourse = (int*)malloc(Size * sizeof(int));
    for(int i = 0; i < Size; i ++ )
    {
        g.GraphPointer[i].Primary = NULL;
        g.GraphPointer[i].Follow = NULL;
        g.NumOfSorted = 0;
        g.NumberOfCourse = 0;
        g.GraphPointer[i].NumberOfPrimary = 0;
        g.GraphPointer[i].NumberOfFollow = 0;
    }
    Input_info();
}


void Input_info()
{
    fp = fopen("课程信息.txt", "rt");
    if(fp == NULL)
    {
        printf("课程信息文件打开失败\n");
        return;
    }

    printf("课程信息如下\n");
    printf("课程号       课程名称                    课程学分                    是否基础课              是否专业核心课\n");
    for(int i = 0; i < Size; i ++ )
    {
        fscanf(fp," %s %s %lf", g.GraphPointer[i].Course, g.GraphPointer[i].CourseName, &g.GraphPointer[i].Score);
        printf("%s         %-24s     %.1lf", g.GraphPointer[i].Course, g.GraphPointer[i].CourseName, g.GraphPointer[i].Score);
        int num = 0;
        TheMax = (TheMax > g.GraphPointer[i].Score) ? TheMax : g.GraphPointer[i].Score;
        SumScore += g.GraphPointer[i].Score;
        char str[5];
        fscanf(fp, " %d", &num);
        while(num --)
        {
            LinkNode *p = (LinkNode*)malloc(sizeof(LinkNode));
            fscanf(fp," %s", str);
            strcpy(p -> Course, str);
            p -> next = g.GraphPointer[i].Primary;
            g.GraphPointer[i].Primary = p;
            g.GraphPointer[i].NumberOfPrimary ++;

            LinkNode *q = (LinkNode*)malloc(sizeof(LinkNode));
            int pos = Location(str);
            strcpy(q -> Course, g.GraphPointer[i].Course);
            q -> next = g.GraphPointer[pos].Follow;
            g.GraphPointer[pos].Follow = q;
            g.GraphPointer[pos].NumberOfFollow ++;
        }
        fscanf(fp, "%d%d", &g.GraphPointer[i].isBase, &g.GraphPointer[i].isCenter);
        if(g.GraphPointer[i].isBase == 1 && g.GraphPointer[i].isCenter == 1) printf("                         是                      是\n");
        if(g.GraphPointer[i].isBase == 1 && g.GraphPointer[i].isCenter == 0) printf("                         是                      不是\n");
        if(g.GraphPointer[i].isBase == 0 && g.GraphPointer[i].isCenter == 1) printf("                         不是                    是\n");
        if(g.GraphPointer[i].isBase == 0 && g.GraphPointer[i].isCenter == 0) printf("                         不是                    不是\n");

    }
    fclose(fp);
    system("pause");
}

void TopSort()
{
    Flush();
    Priorty_Queue *q = Init_Priorty(2 * Size);  //初始化清空优先队列
    int InDegree[Size];                         //节点的入度数组
    int vis[Size];                              //判断节点是否进入拓扑序列
    memset(InDegree, 0, sizeof(InDegree));
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < Size; i ++ )
    {
        if(g.GraphPointer[i].NumberOfPrimary == 0)  //将无先修课程的节点入队
        {
             PNode *x = (PNode*)malloc(sizeof(PNode));
             x -> level = g.GraphPointer[i].NumberOfFollow;
             x -> point = i;
             if(g.GraphPointer[i].isBase || g.GraphPointer[i].isCenter)
             {
                 x -> level += 100;     //对于基础课和核心课程将优先级加100,保证能将其安排在前几个学期
             }
             Insert(q, x);
        }
        InDegree[i] = g.GraphPointer[i].NumberOfPrimary;   //记录节点的入度
    }
    while(!Empty_Prior(q))
    {
        PNode *t;
        t = Delete(q);     //从优先队列中取出后继课程最多的节点
        int now = t -> point;
        vis[now] = 1;
        g.SortedCourse[g.NumOfSorted ++] = now;    //节点进入拓扑序列

        LinkNode *p = g.GraphPointer[now].Follow;
        while(p != NULL)   // 遍历后继课程
        {
            int pos = Location(p -> Course);
            if(vis[pos] == 0)
            {
                InDegree[pos] --;
                if(InDegree[pos] == 0)
                {
                    PNode *x = (PNode*)malloc(sizeof(PNode));
                    x -> level = g.GraphPointer[pos].NumberOfFollow;    //节点的后继课程数量作为优先队列的判断条件
                    x -> point = pos;
                    if(g.GraphPointer[pos].isBase || g.GraphPointer[pos].isCenter)
                    {
                        x -> level += 100;
                    }
                    Insert(q, x);
                }
            }
            p = p -> next;
        }
    }
    if(g.NumOfSorted < Size)
    {

        printf("\033[31m课程存在相互为先修课的关系,请检查!!!\033[0m\n");
        system("pause");
        exit(0);
    }
    else
    {
        printf("拓扑排序结果为:");
        for(int i = 0; i < g.NumOfSorted; i ++ )
        {
            if(i % 2 == 0) printf("\n");
            int pos = g.SortedCourse[i];
            printf("%-10s %-30s", g.GraphPointer[pos].Course, g.GraphPointer[pos].CourseName);
            if(i != g.NumOfSorted - 1) printf(" -> ");
        }
        printf("\n\n");
    }
    system("pause");
    Flush();
}

int Arrange2()
{
    int vis[Size];
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= CourseNum; i ++ )
    {
        double limscore = 0;

        for(int j = 0; j < g.NumOfSorted; j ++ )
        {
            int pos = g.SortedCourse[j];
            if(g.GraphPointer[pos].isBase || g.GraphPointer[pos].isCenter)
            {
                if(g.GraphPointer[pos].NumberOfPrimary)
                {
                    if(vis[pos] == 0)
                    {
                        int flag = 1;
                        LinkNode *tmp = g.GraphPointer[pos].Primary;
                        while(tmp != NULL)
                        {
                            int idx = Location(tmp -> Course);
                            if(vis[idx] == 0 || vis[idx] == i)
                            {
                                flag = 0;
                                break;
                            }
                            tmp = tmp -> next;
                        }
                        if(flag && limscore + g.GraphPointer[pos].Score <= MaxScore)
                        {

                            vis[pos] = i;
                            arr[i].course[arr[i].Count ++] = pos;
                            limscore += g.GraphPointer[pos].Score;
                        }
                    }
                }
                else
                {
                    if(vis[pos] == 0 && limscore + g.GraphPointer[pos].Score <= MaxScore)
                    {
                        vis[pos] = i;
                        arr[i].course[arr[i].Count ++] = pos;
                        limscore += g.GraphPointer[pos].Score;
                    }
                }
            }
        }

        for(int j = 0; j < g.NumOfSorted; j ++ )
        {
            int pos = g.SortedCourse[j];
            if(g.GraphPointer[pos].NumberOfPrimary)
            {
                if(vis[pos] == 0)
                {
                    int flag = 1;
                    LinkNode *tmp = g.GraphPointer[pos].Primary;
                    while(tmp != NULL)
                    {
                        int idx = Location(tmp -> Course);
                        if(vis[idx] == 0 || vis[idx] == i)
                        {
                            flag = 0;
                            break;
                        }
                        tmp = tmp -> next;
                    }
                    if(flag && limscore + g.GraphPointer[pos].Score <= MaxScore)
                    {

                        vis[pos] = i;
                        arr[i].course[arr[i].Count ++] = pos;
                        limscore += g.GraphPointer[pos].Score;
                    }
                }
            }
            else
            {
                if(vis[pos] == 0 && limscore + g.GraphPointer[pos].Score <= MaxScore)
                {
                    vis[pos] = i;
                    arr[i].course[arr[i].Count ++] = pos;
                    limscore += g.GraphPointer[pos].Score;
                }
            }
        }
        arr[i].SumScore = limscore;
    }
    for(int i = 0; i < Size; i ++ )
    {
        if(vis[i] == 0)
        {
            printf("\033[31m课程未排完,请增加学分上限\033[0m\n");
            system("pause");
            exit(0);
            return 0;
        }
    }
    write();
    return 1;
}

int Arrange1()  //学期负担均匀
{
   // printf("%lf\n", SumScore);
    int vis[Size];      //记录课程是否安排及安排在第几个学期
    double tmp = ceil(SumScore / CourseNum);
    double lim = tmp < MaxScore ? tmp : MaxScore;  //计算最大学分上限
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= CourseNum; i ++ )
    {
        double limscore = 0;   //当前学期的学分
        for(int j = 0; j < g.NumOfSorted; j ++ )
        {
            int pos = g.SortedCourse[j];
            if(g.GraphPointer[pos].NumberOfPrimary)
            {
                if(vis[pos] == 0)
                {
                    int flag = 1;
                    LinkNode *tmp = g.GraphPointer[pos].Primary;  //遍历先修课程
                    while(tmp != NULL)
                    {
                        int idx = Location(tmp -> Course);
                        if(vis[idx] == 0 || vis[idx] == i)  //如果先修课程未安排或者安排在本学期则后继课程不能安排
                        {
                            flag = 0;
                            break;
                        }
                        tmp = tmp -> next;
                    }
                    if(flag && limscore + g.GraphPointer[pos].Score <= lim)  //如果先修课程安排且学分不超过上限完则可以安排进当前学期
                    {

                        vis[pos] = i;
                        arr[i].course[arr[i].Count ++] = pos;
                        limscore += g.GraphPointer[pos].Score;
                    }
                }
            }
            else
            {
                if(vis[pos] == 0 && limscore + g.GraphPointer[pos].Score <= lim)  //如果没有先修课程且不超过学分上限则可以安排
                {
                    vis[pos] = i;
                    limscore += g.GraphPointer[pos].Score;
                    arr[i].course[arr[i].Count ++] = pos;
                }
            }
        }
        arr[i].SumScore = limscore;
    }
    int cnt = CourseNum;
    for(int i = 0; i < Size; i ++ )
    {
        if(vis[i] == 0 && arr[cnt].SumScore + g.GraphPointer[i].Score <= MaxScore)
        {
            vis[i] = cnt;
            arr[cnt].course[arr[cnt].Count ++] = i;
            arr[cnt].SumScore += g.GraphPointer[i].Score;
        }
    }

    for(int i = 0; i < Size; i ++ ) //判读课程是否排完
    {
        if(vis[i] == 0)
        {
            printf("\033[31m课程未排完,请增加学分上限\033[0m\n");
            system("pause");
            exit(0);
            return 0;
        }
    }
    write();
    return 1;
}

void Input()
{
    Flush();
    printf("请输入学期数(最大学期数为12)\n");
    while(1)
    {
        scanf("%d", &CourseNum);
        if(CourseNum > 12 || CourseNum < 0)
        {
            printf("\033[31m输入有误!!!请重新输入!!!\033[0m\n");
        }
        else break;
    }

    printf("请输入学期最大学分上限\n");
    while(1)
    {
        scanf("%lf", &MaxScore);
        if(MaxScore < 0)
        {
            printf("\033[31m输入有误!!!请重新输入!!!\033[0m\n");
        }
        else break;
    }
    printf("输入完成!!!");
    system("pause");
    Flush();
}

void printf0()   // 界面
{
    system("title 教学计划编制");
    system("date /T");
    system("TIME /T");
    printf("╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪\n");
    printf("╔═════════════════════╧╧ 欢迎进入教学计划编制系统 ╧╧══════════════════════════╗  \n\n");
    printf("║                   指导老师 : x x x                                       ║\n\n");
    printf("║                   学    生 : x x x                                       ║\n\n");
    printf("║                   班    级 : xx                                          ║\n\n");
    printf("║                   学    号 : xxxxxxx                                     ║\n\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════╝\n");
    system("pause");
}

void Meau()
{
    printf("请选择排课方式:\n");
    printf("使学期负担尽可能均匀请输入1:\n");
    printf("优先安排基础课和专业核心课请输入2:\n");
    int flag;
    scanf("%d", &flag);
    if(flag == 1)
    {
        Arrange1();
    }
    else if(flag == 2)
    {
        Arrange2();
    }
    else
    {
        printf("\033[31m 输入有误请重新输入\033[0m\n");
        system("pause");
        Meau();
    }
}

void write()
{
    system("cls");
    fp = fopen("结果.txt", "w");
    for(int i = 1; i <= CourseNum; i ++ )
    {
        fprintf(fp, "第%d学期课程安排如下:\n", i);
        printf("第%d学期课程安排如下:\n", i);
        for(int j = 0; j < arr[i].Count; j ++ )
        {
            int pos = arr[i].course[j];
            fprintf(fp, "课程号:%-14s 课程名称:%-44s 学分:%.1lf\n", g.GraphPointer[pos].Course, g.GraphPointer[pos].CourseName, g.GraphPointer[pos].Score);
            printf("课程号:%-14s 课程名称:%-44s 学分:%.1lf\n", g.GraphPointer[pos].Course, g.GraphPointer[pos].CourseName, g.GraphPointer[pos].Score);
        }
        printf("学期总学分为: %.1lf\n\n", arr[i].SumScore);
        fprintf(fp ,"学期总学分为: %.1lf\n\n", arr[i].SumScore);
    }
    system("pause");
}


void Flush()
{
    system("cls");
    system("date /T");
    system("TIME /T");;
}

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
    fp = fopen("�γ���Ϣ.txt", "rt");
    if(fp == NULL)
    {
        printf("�γ���Ϣ�ļ���ʧ��\n");
        return;
    }

    printf("�γ���Ϣ����\n");
    printf("�γ̺�       �γ�����                    �γ�ѧ��                    �Ƿ������              �Ƿ�רҵ���Ŀ�\n");
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
        if(g.GraphPointer[i].isBase == 1 && g.GraphPointer[i].isCenter == 1) printf("                         ��                      ��\n");
        if(g.GraphPointer[i].isBase == 1 && g.GraphPointer[i].isCenter == 0) printf("                         ��                      ����\n");
        if(g.GraphPointer[i].isBase == 0 && g.GraphPointer[i].isCenter == 1) printf("                         ����                    ��\n");
        if(g.GraphPointer[i].isBase == 0 && g.GraphPointer[i].isCenter == 0) printf("                         ����                    ����\n");

    }
    fclose(fp);
    system("pause");
}

void TopSort()
{
    Flush();
    Priorty_Queue *q = Init_Priorty(2 * Size);  //��ʼ��������ȶ���
    int InDegree[Size];                         //�ڵ���������
    int vis[Size];                              //�жϽڵ��Ƿ������������
    memset(InDegree, 0, sizeof(InDegree));
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < Size; i ++ )
    {
        if(g.GraphPointer[i].NumberOfPrimary == 0)  //�������޿γ̵Ľڵ����
        {
             PNode *x = (PNode*)malloc(sizeof(PNode));
             x -> level = g.GraphPointer[i].NumberOfFollow;
             x -> point = i;
             if(g.GraphPointer[i].isBase || g.GraphPointer[i].isCenter)
             {
                 x -> level += 100;     //���ڻ����κͺ��Ŀγ̽����ȼ���100,��֤�ܽ��䰲����ǰ����ѧ��
             }
             Insert(q, x);
        }
        InDegree[i] = g.GraphPointer[i].NumberOfPrimary;   //��¼�ڵ�����
    }
    while(!Empty_Prior(q))
    {
        PNode *t;
        t = Delete(q);     //�����ȶ�����ȡ����̿γ����Ľڵ�
        int now = t -> point;
        vis[now] = 1;
        g.SortedCourse[g.NumOfSorted ++] = now;    //�ڵ������������

        LinkNode *p = g.GraphPointer[now].Follow;
        while(p != NULL)   // ������̿γ�
        {
            int pos = Location(p -> Course);
            if(vis[pos] == 0)
            {
                InDegree[pos] --;
                if(InDegree[pos] == 0)
                {
                    PNode *x = (PNode*)malloc(sizeof(PNode));
                    x -> level = g.GraphPointer[pos].NumberOfFollow;    //�ڵ�ĺ�̿γ�������Ϊ���ȶ��е��ж�����
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

        printf("\033[31m�γ̴����໥Ϊ���޿εĹ�ϵ,����!!!\033[0m\n");
        system("pause");
        exit(0);
    }
    else
    {
        printf("����������Ϊ:");
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
            printf("\033[31m�γ�δ����,������ѧ������\033[0m\n");
            system("pause");
            exit(0);
            return 0;
        }
    }
    write();
    return 1;
}

int Arrange1()  //ѧ�ڸ�������
{
   // printf("%lf\n", SumScore);
    int vis[Size];      //��¼�γ��Ƿ��ż������ڵڼ���ѧ��
    double tmp = ceil(SumScore / CourseNum);
    double lim = tmp < MaxScore ? tmp : MaxScore;  //�������ѧ������
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= CourseNum; i ++ )
    {
        double limscore = 0;   //��ǰѧ�ڵ�ѧ��
        for(int j = 0; j < g.NumOfSorted; j ++ )
        {
            int pos = g.SortedCourse[j];
            if(g.GraphPointer[pos].NumberOfPrimary)
            {
                if(vis[pos] == 0)
                {
                    int flag = 1;
                    LinkNode *tmp = g.GraphPointer[pos].Primary;  //�������޿γ�
                    while(tmp != NULL)
                    {
                        int idx = Location(tmp -> Course);
                        if(vis[idx] == 0 || vis[idx] == i)  //������޿γ�δ���Ż��߰����ڱ�ѧ�����̿γ̲��ܰ���
                        {
                            flag = 0;
                            break;
                        }
                        tmp = tmp -> next;
                    }
                    if(flag && limscore + g.GraphPointer[pos].Score <= lim)  //������޿γ̰�����ѧ�ֲ���������������԰��Ž���ǰѧ��
                    {

                        vis[pos] = i;
                        arr[i].course[arr[i].Count ++] = pos;
                        limscore += g.GraphPointer[pos].Score;
                    }
                }
            }
            else
            {
                if(vis[pos] == 0 && limscore + g.GraphPointer[pos].Score <= lim)  //���û�����޿γ��Ҳ�����ѧ����������԰���
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

    for(int i = 0; i < Size; i ++ ) //�ж��γ��Ƿ�����
    {
        if(vis[i] == 0)
        {
            printf("\033[31m�γ�δ����,������ѧ������\033[0m\n");
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
    printf("������ѧ����(���ѧ����Ϊ12)\n");
    while(1)
    {
        scanf("%d", &CourseNum);
        if(CourseNum > 12 || CourseNum < 0)
        {
            printf("\033[31m��������!!!����������!!!\033[0m\n");
        }
        else break;
    }

    printf("������ѧ�����ѧ������\n");
    while(1)
    {
        scanf("%lf", &MaxScore);
        if(MaxScore < 0)
        {
            printf("\033[31m��������!!!����������!!!\033[0m\n");
        }
        else break;
    }
    printf("�������!!!");
    system("pause");
    Flush();
}

void printf0()   // ����
{
    system("title ��ѧ�ƻ�����");
    system("date /T");
    system("TIME /T");
    printf("�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n\n");
    printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�k�k ��ӭ�����ѧ�ƻ�����ϵͳ �k�k�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[  \n\n");
    printf("�U                   ָ����ʦ : x x x                                       �U\n\n");
    printf("�U                   ѧ    �� : x x x                                       �U\n\n");
    printf("�U                   ��    �� : xx                                          �U\n\n");
    printf("�U                   ѧ    �� : xxxxxxx                                     �U\n\n");
    printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
    system("pause");
}

void Meau()
{
    printf("��ѡ���ſη�ʽ:\n");
    printf("ʹѧ�ڸ��������ܾ���������1:\n");
    printf("���Ȱ��Ż����κ�רҵ���Ŀ�������2:\n");
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
        printf("\033[31m ������������������\033[0m\n");
        system("pause");
        Meau();
    }
}

void write()
{
    system("cls");
    fp = fopen("���.txt", "w");
    for(int i = 1; i <= CourseNum; i ++ )
    {
        fprintf(fp, "��%dѧ�ڿγ̰�������:\n", i);
        printf("��%dѧ�ڿγ̰�������:\n", i);
        for(int j = 0; j < arr[i].Count; j ++ )
        {
            int pos = arr[i].course[j];
            fprintf(fp, "�γ̺�:%-14s �γ�����:%-44s ѧ��:%.1lf\n", g.GraphPointer[pos].Course, g.GraphPointer[pos].CourseName, g.GraphPointer[pos].Score);
            printf("�γ̺�:%-14s �γ�����:%-44s ѧ��:%.1lf\n", g.GraphPointer[pos].Course, g.GraphPointer[pos].CourseName, g.GraphPointer[pos].Score);
        }
        printf("ѧ����ѧ��Ϊ: %.1lf\n\n", arr[i].SumScore);
        fprintf(fp ,"ѧ����ѧ��Ϊ: %.1lf\n\n", arr[i].SumScore);
    }
    system("pause");
}


void Flush()
{
    system("cls");
    system("date /T");
    system("TIME /T");;
}

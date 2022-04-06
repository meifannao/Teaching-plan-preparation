#ifndef PRIOR_H_INCLUDED
#define PRIOR_H_INCLUDED

typedef struct Prior_Node
{
    int point; //所指向的节点
    int level; //节点的优先级别即节点的后续课程数量,基础课或专业课优先级为无穷
}PNode;

typedef struct priorityqueue
{
    PNode *_node; //课程信息数组
    int Capacity; //最大容量
    int size;   //当前容量
}Priorty_Queue;


int Empty_Prior(Priorty_Queue *H)
{
    if(H -> size == 0) return 1;
    return 0;
}

Priorty_Queue* Init_Priorty(int Size)
{
    Priorty_Queue *H = (Priorty_Queue*)malloc(sizeof(Priorty_Queue));
    H -> _node = (PNode*)malloc((Size + 1) * sizeof(PNode));
    if(H -> _node == NULL)
    {
        printf("优先队列创建失败!!!\n");
    }
    H -> Capacity = Size;
    H -> size = 0;
    H -> _node[0].level = 1e9; //初始在0号节点放置无穷大节点
    H -> _node[0].point = -1;
    return H;
}

void Insert(Priorty_Queue *H, PNode *x)
{
    int i;
    if(H -> size == H -> Capacity)
    {
        printf("堆满!!!\n");
    }

    for( i = ++ (H -> size) ; H -> _node[i / 2].level < x -> level; i /= 2)  //找到节点的合适位置
    {
        H -> _node[i] = H -> _node[i / 2];

    }
    H -> _node[i].level = x -> level;//将节点的插入到合适位置
    H -> _node[i].point = x -> point;
}

PNode* Delete(Priorty_Queue *H)
{
    int i, Child;
    PNode *Min, *Last;
    Min = (PNode*)malloc(sizeof(PNode));
    Last = (PNode*)malloc(sizeof(PNode));
    if(H -> size == 0)
    {
        printf("堆空!!!\n");
        return &(H -> _node[0]);
    }
    Min -> level = H -> _node[1].level;
    Min -> point = H -> _node[1].point;
    Last -> level = H -> _node[H ->size].level;
    Last -> point = H -> _node[H ->size].point;
    H -> size --;
    for(i = 1; i * 2 <= H -> size; i = Child)
    {
        Child = i * 2;
        if(Child != H -> size && H -> _node[Child].level < H -> _node[Child + 1].level)
            Child ++;
        if(Last -> level < H -> _node[Child].level)
        {
            H -> _node[i].level = H -> _node[Child].level;
            H -> _node[i].point = H -> _node[Child].point;
        }
        else break;
    }
    H -> _node[i].level = Last -> level;
    H -> _node[i].point = Last -> point;
    return Min;
}

#endif // PRIOR_H_INCLUDED

#ifndef PRIOR_H_INCLUDED
#define PRIOR_H_INCLUDED

typedef struct Prior_Node
{
    int point; //��ָ��Ľڵ�
    int level; //�ڵ�����ȼ��𼴽ڵ�ĺ����γ�����,�����λ�רҵ�����ȼ�Ϊ����
}PNode;

typedef struct priorityqueue
{
    PNode *_node; //�γ���Ϣ����
    int Capacity; //�������
    int size;   //��ǰ����
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
        printf("���ȶ��д���ʧ��!!!\n");
    }
    H -> Capacity = Size;
    H -> size = 0;
    H -> _node[0].level = 1e9; //��ʼ��0�Žڵ���������ڵ�
    H -> _node[0].point = -1;
    return H;
}

void Insert(Priorty_Queue *H, PNode *x)
{
    int i;
    if(H -> size == H -> Capacity)
    {
        printf("����!!!\n");
    }

    for( i = ++ (H -> size) ; H -> _node[i / 2].level < x -> level; i /= 2)  //�ҵ��ڵ�ĺ���λ��
    {
        H -> _node[i] = H -> _node[i / 2];

    }
    H -> _node[i].level = x -> level;//���ڵ�Ĳ��뵽����λ��
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
        printf("�ѿ�!!!\n");
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

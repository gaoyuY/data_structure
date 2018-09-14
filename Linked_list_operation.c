/*************************************************************************
> File Name: Linked_list_operation.c
> Author:gaoyu
> Mail:2282940822 
> Created Time: 2018年09月10日 星期一 15时14分21秒
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data; //表示每个结点内的数据
    struct Node *next; //用来指向下一个节点

}Node, *LinkedList;
Node insert(LinkedList head, Node *node, int index) {

    Node *p, ret;
    p = &ret;
    ret.data = 0;
    ret.next = head;
    while (p->next && index) {
        p = p->next;
        --index;
    }

    if (index == 0) {
        node->next = p->next;
        p->next = node;
        ret.data = 1;
    }
    return ret;

}
void output(LinkedList head) {

    Node *p = head;
    while (p) {
        printf("%d", p->data);
        if (p->next) {
            printf(" ");
        }
        p = p->next;
    }
    printf("\n");

}

void clear(LinkedList head) {

    Node *p, *q;
    p = head;
    while (p) {
        q = p->next;
        free(p);
        p = q;

    }
    return ;

}

int main() {

    LinkedList linkedlist = NULL;
    Node *p, ret;
    int n, num, loc;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &loc, &num);
        p = (Node *)malloc(sizeof(Node));
        p->data = num;
        p->next = NULL;
        ret = insert(linkedlist, p, loc);
        linkedlist = ret.next;
        printf("%s\n", ret.data ? "success" : "failed");

    }

    output(linkedlist);
    clear(linkedlist);
    return 0;

}

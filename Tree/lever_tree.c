/*************************************************************************
	> File Name: lever_tree.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年10月26日 星期五 15时58分31秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR 0
#define OK 1

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node, *pNode;

typedef struct Stack {
    pNode *data;
    int size, top;
} Stack, *pStack;

typedef struct Queue {
    pNode *data;
    int head, tail, len, cnt;
} Queue, *pQueue;

void init_queue(pQueue q, int len) {
    q->data = (pNode *)malloc(sizeof(pNode) * len);
    q->len = len;
    q->head = 0;
    q->tail = -1;
    q->cnt = 0;
}


int push_queue(pQueue q, pNode e) {
    if (q->cnt == q->len) {
        return ERROR;
    }
    q->tail = (q->tail + 1) % q->len;
    q->data[q->tail] = e;
    ++(q->cnt);
    return OK;
}

int empty_queue(pQueue q) {
    return q->cnt == 0;
}

int pop_queue(pQueue q) {
    if (empty_queue(q)) {
        return ERROR;
    }
    ++(q->head);
    --(q->cnt);
    return OK;
}

pNode front_queue(pQueue q) {
    return q->data[q->head];
}

void clear_queue(pQueue q) {
    if (!q) return ;
    free(q->data);
    free(q);
}

void init_stack(Stack *s, int len) {
    s->data = (pNode *)malloc(sizeof(pNode) * len);
    s->size = len;
    s->top = -1;
}


int push_stack(Stack *s, pNode e) {

    if (s->top >= s->size - 1) {

        return ERROR;

    }

    s->data[++(s->top)] = e;

    return OK;

}

 

int empty_stack(Stack *s) {

    return s->top == -1;

} 

int pop_stack(Stack *s) {
    if (empty_stack(s)) {
        return ERROR;
    }
    --(s->top);
    return OK;
}

pNode top_stack(Stack *s) {
    return s->data[s->top];
}

void clear_stack(Stack *s) {
    free(s->data);
    free(s);
}

pNode init(char data) {
    pNode p = (pNode)malloc(sizeof(Node));
    p->data = data;
    p->lchild = NULL;
    p->rchild = NULL;
    return p;
}

void clear(pNode p) {
    if (!p) return ;
    if (p->lchild) {
        clear(p->lchild);
    }
    if (p->rchild) {
        clear(p->rchild);
    }
    free(p);
}

pNode build(char *str, int *node_num) {
    pNode p = NULL, last_p = NULL;
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    init_stack(stack, strlen(str));
    int k = 0;
    while (str[0]) {
        switch (str[0]) {
            case '(' :
                k = 0;
                push_stack(stack, p);
                p = NULL;
                break;
            case ')' :
                last_p = top_stack(stack);
                pop_stack(stack);
                break;
            case ',' :
                k = 1;
                p = NULL;
                break;
            case ' ':
                break;
            default :
                p = init(str[0]);
                if (!empty_stack(stack) && k == 0) {
                    top_stack(stack)->lchild = p;
                } else if (!empty_stack(stack) && k == 1) {
                    top_stack(stack)->rchild = p;
                }
                ++(*node_num);
                break;
        }
        ++str;
    }
    if (p && !last_p) last_p = p;
    clear_stack(stack);
    return last_p;
}

void output(pNode p, int node_num) {
    if (node_num == 0) {
        return ;
    }
    printf("%c", p->data);
    pQueue q = (pQueue)malloc(sizeof(Queue));
    pNode temp_p;
    init_queue(q, node_num);
    push_queue(q, p);
    while (!empty_queue(q)) {
        temp_p = front_queue(q);
        if (temp_p->lchild) {
            printf(" %c", temp_p->lchild->data);
            push_queue(q, temp_p->lchild);
        }
        if (temp_p->rchild) {
            printf(" %c", temp_p->rchild->data);
            push_queue(q, temp_p->rchild);
        }
        pop_queue(q);
    }
    clear_queue(q);
    return ;
}

int main() {
    char str[100] = {0}, ch;
    int ind = 0;
    scanf("%s", str);
    int node_num = 0;
    pNode p = build(str, &node_num);
    output(p, node_num);
    clear(p);
    return 0;
}

 

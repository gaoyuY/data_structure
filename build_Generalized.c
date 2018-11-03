/*************************************************************************
	> File Name: build_Generalized.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年10月28日 星期日 18时18分17秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
} Node;

typedef struct Stack {
    Node **data; //节点的地址
    int top, size;
} Stack;

Stack *initStack (int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (Node **)malloc(sizeof(Node *) * n);
    s->size = n;
    s->top = -1;
    return s;
}


int empty (Stack *s) {
    return s == NULL || s->top == -1;
}

void pop (Stack * s)  {
    if (empty(s)) return;
    s->top -= 1;
    return;
}


void push (Stack *s, Node *root) {
    if (s->top + 1 == s->size) return;
    s->data[++(s->top)] = root;
    return;
}


Node *top (Stack *s) {
    if (empty(s)) return NULL;
    return s->data[s->top];
}

void clearStack(Stack *s) {
    if (!s) return;
    free(s->data);
    free(s);
    return;
}

Node *getNewNode (int key) {
    Node *p = (Node *)malloc (sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

void clearTree(Node * root) {
    if (!root) return;
    clearTree(root->lchild);
    clearTree(root->rchild);
    free(root);
    return;
}

Node *build(const char *str) {
    Node *p = NULL, *root = NULL;
    Stack *s = initStack(100);
    int k = 0;
    while (str[0]) {
        switch (str[0]) {
            case '(': {
                push(s, p);
                k = 0;
            }
                break;
            case ')': {
                pop (s);
            }break;
            case ',': {
                k = 1;
            } break;

            case ' ':
                break;
            default : {
                p = getNewNode(str[0]);
                if (!root) root = p; //记录根节点
                if (empty(s)) break;
                if (k == 0) 
                    top(s)->lchild = p;
                else 
                    top(s)->rchild = p;
            } break;
        }
        str++;
    }
    return root;
}



//前序遍历
void output (Node *root, const char *last_output ) {
    if (!root)  return;
    printf ("%c", root->key);
    output (root->lchild, "");
    output (root->rchild, "");
    printf("%s", last_output);
    return;
}

int main () {
    char str[100];
    Node *root = NULL;
    while (scanf ("%[^\n]s", str) != EOF) {
        getchar();
        output (root = build(str), "\n"); 
        clearTree(root);
    }
    return 0;
}

/*************************************************************************
	> File Name: tire.c
	> Author: GaoYu
	> Mail: 
	> Created Time: 2018年12月30日 星期日 21时38分29秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE_CNT 26
#define BASE 'a'
typedef struct Node {
    int flag;
    struct Node *next[BASE_CNT];
} Node;


Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    for (int i = 0; i < BASE_CNT; i++) {
        p->next[i] = NULL;
    }
    p->flag = 0;
    return p;
}

void  insert (Node *node, const char *str) {
    Node *p = node;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BASE] == NULL) 
            p->next[str[i] - BASE] = getNewNode(); 
        p = p->next[str[i] - BASE];
    }
}

int search (Node *node, char *str) {
    Node *p = node;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BASE] == NULL) return 0; 
        p = p->next[str[i] - BASE];
    }
    p->flag = 1;
    return 1;
}


int main () {
    Node *root = getNewNode();
    int n, ans = 0;
    int op;
    char str[100];
    while (scanf ("%s", str) != EOF) {
        scanf ("%d", &n);
        int flag = 0;
        switch (n) {
            case 1: {
                printf ("insert %s to tire\n", str);
                insert(root, str);
            } break;
            case 2: {
                printf ("search %s to tire\n", str);
                flag = search(root, str);
                printf ("%d\n", flag);
            } break;
            default :
                break;
        }
    }
    return 0;
}

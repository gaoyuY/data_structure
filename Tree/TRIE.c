/*************************************************************************
	> File Name: TRIE.c
	> Author: GaoYu
	> Mail: 
	> Created Time: 2019年01月06日 星期日 19时25分56秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE_cnt 26
#define BASE 'a'

typedef struct Node {
    int flag;//表示当前节点是否独立成词
    struct Node *next[BASE_cnt];
} Node;

Node *getNewNode () {
    Node *p = (Node *)malloc(sizeof(Node));
    for (int i = 0; i < BASE_cnt; i++) {
        p->next[i] = NULL;//初始化每个孩子节点均为空
    } 
    p->flag = 0;//初始均不独立成词
    return p;
}

void insert (Node *node,const char *str) {
    Node *p = node;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BASE] == NULL) p->next[str[i] - BASE] = getNewNode();
        p = p->next[str[i] - BASE];  
    }
    p->flag = 1;
    return ;
}

int search (Node *node, const char *str) {
    Node *p = node;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BASE] == NULL){
            return 0;
        } 
        p = p->next[str[i] - BASE];  
    }
    return  p->flag;//如果查找到的单词最后一个相匹配字符，独立成词，就表示查找成功，反之失败
}


void clear (Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < 26; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}


int main () {
    Node *root = getNewNode();
    char str[100];
    int op;
    while (scanf ("%d%s", &op, str) != EOF) {
        switch (op) {
            case 1: {
                printf ("insert %s to trie\n", str);
                insert (root, str);
            } break;
            case 2: {
                int flag = search(root, str);
                printf ("search %s from trie =  %d \n", str, flag);
            } break;
            default:
                break;
        }
    }

    return 0;
}

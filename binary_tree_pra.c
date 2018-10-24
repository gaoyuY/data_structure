/*************************************************************************
	> File Name: binary_tree_pra.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年10月24日 星期三 20时03分49秒
 ************************************************************************/

/**********************计蒜客 神奇的二叉树*************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node;

Node *init(char data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

Node *build(char *pre_str, char *in_str, int len) {
    Node *p = init(pre_str[0]);
    int pos = strchr(in_str, pre_str[0]) - in_str;
    if (pos > 0) {
        p->lchild = build(pre_str + 1, in_str, pos);
    }
    if (len - pos - 1 > 0) {
        p->rchild = build(pre_str + pos + 1, in_str + pos + 1, len - pos - 1);
    }
    return p;

}

void postorder1(Node *node) {
    if (node->lchild) {
        postorder1(node->lchild);
    }
    if (node->rchild) {
        postorder1(node->rchild);
    }
    printf("%c", node->data);

}

void postorder2(Node *node) {
    if (node->rchild) {
        postorder2(node->rchild);
    }
    if (node->lchild) {
        postorder2(node->lchild);
    }
    printf("%c", node->data);
}

int main() {
    char *pre_str, *in_str;
    pre_str = (char *)malloc(sizeof(char) * 55);
    in_str = (char *)malloc(sizeof(char) * 55);
    scanf("%s%s", pre_str, in_str);
    Node *root = build(pre_str, in_str, strlen(pre_str));
    postorder1(root);
    printf("\n");
    postorder2(root);
    printf("\n");
    return 0;

}

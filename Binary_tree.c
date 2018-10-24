/*************************************************************************
	> File Name: Binary_tree.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年10月23日 星期二 19时00分38秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node *l, *r;
} Node;


Node *init (int data) {//初始化
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->l = p->r = NULL;
    return p;
}

void clear (Node *node) {//释放空间
    if (node == NULL) return;
    clear(node->l);
    clear(node->r);
    free(node);
    return;
}


Node *build() {//建立一棵树
    Node *root = init(1);
    root->l = init(2);
    root->r = init(3); 
    root->l->l = init(6);
    root->l->r = init(7);
    root->l->l->r = init(12);
    root->r->l = init(5);
    root->r->r = init(9);
    root->r->l->l = init(10);
    root->r->l->r = init(11);

  return root;
}

int height (Node *root) {//求树高
    if (root == NULL) return 0;
    int lh = height(root->l), rh = height(root->r);
    return (lh > rh ? lh :rh) + 1;
}


void pre(Node *root) { // 前序遍历 （根左右）
    if (root == NULL) return;
    printf("%d ", root->data);
    pre(root->l);
    pre(root->r);
    return;
}


void inorder (Node *root) {//中序遍历 （左根右）
 if (root == NULL) return;
    inorder(root->l);
    printf("%d ", root->data);
    inorder(root->r);
    return;
}

void back (Node *root) {//后序遍历 （左右根）
    if (root == NULL) return;
    back(root->l);
    back(root->r);
    printf("%d ", root->data);
    return;
}


int main() {
    Node *root = build();
    printf("height(root) = %d\n", height(root));
    pre(root);
    printf("\n");
    inorder(root);
    printf("\n");
    back(root);
    printf ("\n");
    clear(root);

    return 0;
}

/*************************************************************************
	> File Name: Tree_Huffman1.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年10月28日 星期日 21时00分06秒
 ************************************************************************/


#include<stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>


typedef struct Node {
    int key, freq;
    struct Node *lchild, *rchild;
} Node;


Node *getNewNode (int key, int freq) {
    Node *p= (Node *)malloc(sizeof(Node));
    p->key = key;
    p->freq = freq;
    p->lchild = p->rchild = NULL;
    return p;
}


void clear (Node *root) {
    if (!root ) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return;
}

void swap_node (Node *p, Node *q) {
    Node temp = *p;
    *p = *q;
    *q = temp;
    return;
}


Node * build_haffman(Node **arr, int n) {
    Node INIT_NODE = {0, INT32_MAX, NULL, NULL};
    Node *first = &INIT_NODE, *second = &INIT_NODE;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 2; j < n - i; j++) {
            if (arr[j]->freq < first->freq) {
                second = first;
                first = arr[j];
            } else if (arr[j]->freq < second->freq) {
                second = arr[j];
            } 
        }
        Node *temp = getNewNode(0, first->freq + second->freq);
        temp->lchild = first;
        temp->rchild = second;
        printf ("%d %d\n", first->freq, second->freq);
        swap_node(arr[n - i - 1], first);
        swap_node(arr[n - i - 2], second);
        arr[n - i - 2] = temp;
    }

    return arr[0];
}

void extract_code(Node *root, char (*code)[20], int k, char *buff) {
    buff[k] = 0;
    if (root->key) {
        strcpy(code[root->key], buff);
        return;
    }
    buff[k] = '0';
    extract_code(root->lchild, code, k + 1, buff);
    buff[k] = '1';
    extract_code(root->rchild, code, k + 1, buff);
    return;
}


int main () {
    int n;
    Node **arr = (Node **)malloc(sizeof (Node *) * n);
    scanf ("%d", &n);
    Node *root;
    for (int i = 0; i < n; i++) {
        char key[10];
        int freq;
        scanf ("%s%d", key, &freq);
        arr[i] = getNewNode(key[0], freq);
    }
    root = build_haffman(arr, n);
    //提取编码
    char code[256][20] = {0}, buff[20];
    extract_code(root, code, 0, buff); //0为层号
    for (int i = 0; i < 256; i++) {
        if (code[i][0] == 0) continue;
        printf ("%c : %s\n", i, code[i]);
    }
    return 0;
}

/*************************************************************************
	> File Name: Tree_Huffman.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年10月28日 星期日 20时01分30秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

/********************利用堆 建立哈夫曼树****************
 *测试数据 ：6                 输出：a : 010  (或011)
             a 123                   b : 1
             b 789                   c : 0000
             c 123                   d : 0001
             d 56                    e : 001
             e 789                   f : 011 (或010)
             f 94
 *
 *
 */


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

void swap_node (Node **p, Node **q) {
    Node *temp = *p;
    *p = *q;
    *q = temp;
    return;
}


Node * build_haffman(Node **arr, int n) {
    for (int i = 0; i < n - 1; i++) { 
        for (int j = 0; j < n - i - 2; j++) {
            if (arr[j]->freq < arr[n - i - 1]->freq) {
                swap_node(arr + j, arr + n - i - 1);
            } 
            if (arr[j]->freq < arr[n - i - 2]->freq) {
                swap_node(arr + j, arr + n - i - 2);
            } 
        }
        Node *temp = getNewNode(0, arr[n - i - 1]->freq + arr[n - i - 2]->freq);
        temp->lchild = arr[n - i - 1];
        temp->rchild = arr[n - i - 2];
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

void output (Node *root) {
    if (!root) return;
    printf ("%d ", root->freq);
    if (root->lchild)
        output(root->lchild);
    if (root->rchild) 
        output(root->rchild);

    return;
}
int main () {
    int n;
    scanf ("%d", &n);
    Node **arr = (Node **)malloc(sizeof(Node *) * n);
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
    output(root);
    return 0;
}

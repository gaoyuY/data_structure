/*************************************************************************
> File Name: Heap_Tree_Huffman.c
> Author:gaoyu
> Mail:2282940822 
> Created Time: 2018年11月03日 星期六 14时25分56秒
************************************************************************/

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

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    int freq;
    struct Node *lchild, *rchild;
} Node;

typedef struct Heap {
    struct Node **data;
    int size, cnt;
} Heap;


void getNewNode (Node * p, int key, int freq) {
    p->key = key;
    p->freq = freq;
    p->lchild = p->rchild = NULL;
    return;
}

void init (Heap *h, int n) {
    h->data = (Node **)malloc(sizeof(Node*) * (n + 1));
    h->size = n;
    h->cnt = 0;
    return;
}

void swap (Node **a, Node **b) {
    Node *temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void push (Heap *heap, Node *node) {
    if (heap->cnt == heap->size) return;
    heap->data[++heap->cnt] = node;
    int ind = heap->cnt;
    while (ind >> 1 >= 1) {
        if (heap->data[ind]->freq >= heap->data[ind >> 1]->freq) break;
        swap(&heap->data[ind], &heap->data[ind >> 1]);
        ind >>= 1;
    }
    return;
}

int empty (Heap *heap) {
    if (heap->cnt == 0) return 1;
    return 0;
}

Node *top (Heap *heap) {
    return heap->data[1];
}

void pop (Heap *heap) {
    if (heap->cnt == 0) return;
    heap->data[1] = heap->data[heap->cnt--];
    int ind = 1;
    while (ind << 1 <= heap->cnt) {
        int temp = ind;
        if (heap->data[temp]->freq > heap->data[ind << 1]->freq) temp = ind << 1;
        if ((ind << 1 | 1) <= heap->cnt && heap->data[temp]->freq > heap->data[ind << 1| 1]->freq) temp = ind << 1 | 1;
        if (temp == ind)    break;
        swap(&heap->data[temp], &heap->data[ind]);
        ind = temp;
    }
    return;
}


void extract_code (Node *root, char (*code)[20], int k, char *buff) {
    buff[k] = 0;
    if (root->key) {
        strcpy (code[root->key], buff);
        return;
    }

    buff[k] = '0';
    extract_code(root->lchild, code, k + 1, buff);
    buff[k] = '1';
    extract_code(root->rchild, code, k + 1, buff);
    return;
}

void clear_heap (Heap *heap) {
    if (heap == NULL) return;
    free(heap->data);
    free(heap);
    return;
}


void clear_node (Node *root) {
    if (root == NULL) return;
    clear_node(root->lchild);
    clear_node(root->rchild);
}
void output (Node *root) {
    if (root == NULL) return;
    printf ("%d ", root->freq);
    output(root->lchild);
    output(root->rchild);
    return;
}


int main () {
    int n;
    scanf ("%d", &n);
    Heap *heap =(Heap *)malloc(sizeof(Heap));
    init(heap, n);
    for (int i = 0; i < n; i++) {
        char key[10];
        int freq;
        scanf ("%s %d", key, &freq);
        Node *node = (Node *)malloc (sizeof(Node));
        getNewNode(node, key[0], freq);
        push(heap, node);
    }
    
    while (heap->cnt != 1) {
        Node *c = (Node *)malloc(sizeof(Node));
        Node *a;
        a = top(heap);
        pop(heap); 
        Node *b;
        b = top(heap);
        pop(heap);
        
        c->freq = a->freq + b->freq;
        c->lchild = a;
        c->rchild = b;
        push(heap, c);
    }
    
    char code[256][20] = {0}, buff[20];
    extract_code(top(heap), code, 0, buff);
    for (int i = 0; i < 256; i++) {
        if (code[i][0] == 0) continue;
        printf ("%c : %s\n", i, code[i]);
    }
    output(top(heap));

    return 0;

}

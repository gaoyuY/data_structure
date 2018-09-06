/*************************************************************************
	> File Name: UnionSet.c
	> Author: GaoYu
	> Mail:2282940822@qq.com 
	> Created Time: 2019年01月20日 星期日 16时48分22秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>

typedef struct UnionSet {
    int *fa;//父节点编号
    int size;//总结点数量
} UnionSet;

UnionSet *init (int n) {
    UnionSet *u = (UnionSet *)calloc(sizeof(UnionSet), 1);
    u->fa = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        u->fa[i] = i;
    }
    u->size = n;
    return u;
}

int find (UnionSet *u, int x) {
    if (u->fa[x] != x) return find(u, u->fa[x]);
    return x;
}

int merge(UnionSet *u, int a, int b) {
    int fa_a = find(u, a), fa_b = find(u, b);
    if (fa_a == fa_b) return 0;
    u->fa[fa_a] = fa_b; 
    return 1;
}

void clear (UnionSet *u) {
    if (u == NULL) return ;
    free(u->fa);
    free(u);
    return ;
}

void ouput (UnionSet *u) {
    for (int i = 0; i < u->size; i++) {
        printf ("(%d, %d)\t", i, u->fa[i]);
        if (i + 1 < u->size && (i + 1) % 5 == 0) printf ("\n");
    }
    return ;
}

int main () {
    srand(time(0));
    int op, a, b;
    #define MAX_op 10
    #define Max_N 10
    UnionSet *u = init(Max_N);
    for (int i = 0; i < MAX_op; i++) {
        op = rand() % 4;
        a = rand() % MAX_op;
        b = rand() % Max_N;
        switch (op) {
            case 0 : {
                printf ("find %d <--> %d = %d\n", a, b, find(u, a) == find(u, b));
            } break;
            default : {
                printf ("union %d <--> %d = %d\n", a, b, merge(u, a, b));
            } break;
        }
        ouput(u);
        printf ("\n");
    }

    return 0;
}

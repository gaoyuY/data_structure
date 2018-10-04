/*************************************************************************
	> File Name: tree_old.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年10月23日 星期二 19时35分40秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#define MAX_N 1000
#define MAX_k 20

struct Edge {
    int v, n;
} g[MAX_N << 1];
int head[MAX_N + 5] = {0}, cnt = 0;

inline void add(int a, int b) {
    g[++cnt].v = b;
    g[cnt].n = head[a];
    head[a] = cnt;
    return;
}

//gas[i][j]->i点往上走2^j步，所能到达的祖先节点编号
int gas[MAX_N][MAX_k] = {0}, dep[MAX_N] = {0};

void dfs (int u, int father) { 
    gas[u][0] = father;
    dep[u] = dep[father] + 1;
    for (int i = 1; i < MAX_k; i++) {
        gas[u][i] = gas[gas[u][i - 1]][i - 1];
    }

    for (int i = head[u]; i; i = g[i].n) {
        if (g[i].v == father) continue;
        dfs(g[i].v, u);
    }

    return;
}

int lca (int a, int b){ 
    if (dep[b] < dep[a]) {
        a ^= b;
        b ^= a;
        a ^= b; //b为较深节点
    }
    int l = dep[b] - dep[a];
    for (int i = 0; i < MAX_k; i++) {
        if ((l & (1 << i))) 
            b = gas[b][i];
    }
    if (a == b) //如果对齐后，就找到了
        return a;
    for (int i = MAX_k - 1; i >= 0; i--) {
        if (gas[a][i] != gas[b][i])
            a = gas[a][i], b= gas[b][i];
    }

    return gas[a][0];
}


int main () {

    int n, a, b;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf ("%d %d", &a, &b);
        add(a, b);
        add(b, a);
    }
    
    dfs(1, 0);//1结点为根
    while (scanf ("%d%d", &a, &b) != EOF) {
        printf ("lca(%d,%d) = %d, a->b = %d\n",a, b, lca(a,b), dep[a] + dep[b] - 2 * dep[lca(a, b)]);
    }

    return 0;
}

/*************************************************************************
> File Name: lianxi.c
> Author:gaoyu
> Mail:2282940822 
> Created Time: 2018年09月09日 星期日 20时28分56秒
************************************************************************/

/***************************************************顺序表的插入，删除，查找，遍历 ******************************************************/
#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef struct Vector {
    int size, length;
    int *data;

} Vector;

void init(Vector *vector, int size) {//初始化
    vector -> size = size;
    vector -> length = 0;
    vector -> data = (int *)malloc(sizeof(int) * size);

}

void expand(Vector *vector) {//扩容
    int *old_data = vector -> data;
    vector -> size = vector -> size * 2;
    vector -> data = (int *)malloc(sizeof(int) * vector -> size);
    for (int i = 0; i < vector -> length; i++) {
        vector -> data[i] = old_data[i];

    }
    free(old_data);

}

int insert(Vector *vector, int loc, int value) {//插入
    if (loc < 0 || loc > vector -> length) {
        return 0;

    }
    if (vector -> length >= vector -> size) {
        expand(vector);

    }
    for (int i = vector -> length; i > loc; i--) {
        vector -> data[i] = vector -> data[i - 1];

    }
    vector -> data[loc] = value;
    vector -> length ++;
    return 1; 

}

int search(Vector *vector, int value) {//查找
    for (int i = 0; i < vector -> length; i++) {
        if (vector -> data[i] == value) {
            return 1;

        }

    }
    return 0;

}

int delete_node(Vector *vector, int index) {//删除
    if (index < 0 || index >= vector -> length) {
        return 0;

    }
    for (int i = index + 1; i < vector -> length; i++) {
        vector -> data[i - 1] = vector -> data[i];

    }
    vector ->length = vector -> length - 1;
    return 1;

}

void print(Vector *vector) {//遍历
    for (int i = 0; i < vector -> length; i++) {
        if (i > 0) {
            printf(" ");

        }
        printf ("%d", vector -> data[i]);

    }
    printf ("\n");

}

void clear(Vector *vector) {//释放空间
    free(vector -> data);
    free(vector);

}

int main() {
    Vector *a = (Vector *)malloc(sizeof(Vector));
    init(a, 20);
    int m;
    scanf ("%d", &m);
    while(m--) {
        int t, c, b;
        scanf ("%d", &t);
        if (t == 1) {//插入
            scanf("%d%d", &c, &b);
            if (insert(a, c, b) == 0) {
                printf ("failed\n");

            }else {
                printf ("success\n");

            }

        }else if (t == 2) {//删除
            scanf ("%d", &c);
            if (delete_node(a, c) == 0) {
                printf ("failed\n");

            }else {
                printf ("success\n");

            }

        }else if (t == 3) {//查找
            scanf ("%d", &c);
            if (search(a, c) == 0) {
                printf ("failed\n");

            }else {
                printf ("success\n");

            }

        }else {//遍历
            print(a);


        }

    }

    return 0;

}


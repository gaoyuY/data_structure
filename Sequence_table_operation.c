/*************************************************************************
> File Name: Sequence_table_operation.c
> Author:gaoyu
> Mail:2282940822 
> Created Time: 2018年09月09日 星期日 13时27分00秒
************************************************************************/

/***************************************************顺序表的查找，删除，遍历************************************************************/
#include<stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef struct Vector {
    int size, length;
    int *data;

} Vector;

void init(Vector *vector, int size) { //初始化
    vector->size = size;
    vector->length = 0;
    vector->data = (int *)malloc(sizeof(int) * size);

}

void expand(Vector *vector) { //扩容
    int *old_data = vector->data;
    vector->size = vector->size * 2;
    vector->data = (int *)malloc(sizeof(int) * vector->size);
    for (int i = 0; i < vector->length; ++i) {
        vector->data[i] = old_data[i];

    }
    free(old_data);

}

int insert(Vector *vector, int loc, int value) {//插入
    if (loc < 0 || loc > vector->length) {
        return ERROR;

    }
    if (vector->length >= vector->size) {
        //return ERROR;
        expand(vector);

    }
    for (int i = vector->length; i > loc; --i) {
        vector->data[i] = vector->data[i - 1];

    }
    vector->data[loc] = value;
    vector->length++;
    return OK;

}

int search(Vector *vector, int value) {//查找
    for (int i = 0; i < vector->length; ++i) {
        if (vector->data[i] == value) {
            return i;

        }

    }
    return -1;

}

int delete_node(Vector *vector, int index) {//删除节点
    if (index < 0 || index >= vector->length) {
        return ERROR;

    }
    for (int i = index + 1; i < vector->length; ++i) {
        vector->data[i - 1] = vector->data[i];

    }
    vector->length = vector->length - 1;
    return OK;

}

void print(Vector *vector) {//输出
    for (int i = 0; i < vector -> length; i++) {
        if (i > 0) {
            printf (" ");

        }
        printf ("%d", vector -> data[i]);

    }
    printf ("\n");

}

void clear(Vector *vector) {//释放空间
    free(vector->data);
    free(vector);

}

int main() {
    Vector *a = (Vector *)malloc(sizeof(Vector));
    init(a, 100);
    printf("%d\n", insert(a, 0, 1));
    printf("%d\n", insert(a, 0, 2));
    print(a);
    printf("%d\n", delete_node(a, 1));
    print(a);
    printf("%d\n", search(a, 0));
    printf("%d\n", search(a, 1));
    clear(a);
    return 0;

}

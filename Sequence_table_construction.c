/*************************************************************************
	> File Name: Sequence_table.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年08月28日 星期二 17时01分55秒
 ***********************************************************************/
 /*顺序表的构造，插入和扩容*/

#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1

typedef struct Vector {
    int size, length;
    int *data;
}Vector;

void init (Vector *vector, int size) {
    vector -> size = size;
    vector ->length = 0;
    vector ->data = (int *)malloc(sizeof(int) * size);
}

void expand(Vector *vector) {
    int *old_data;
    old_data = vector -> data;
    vector -> size = vector -> size * 2;
    vector -> data = (int *)malloc(sizeof(int) * vector -> size);
    for (int i = 0; i < vector -> length; i++) {
        vector -> data[i] = old_data[i];
    }
    free(old_data);
}

int insert(Vector *vector, int loc, int value) {
    int flag = 0;
    if (loc < 0 || loc > vector ->length) {
        return ERROR;
    }
    if (vector -> length >= vector -> size) {
        expand(vector);
        flag++;
    }
    for (int i = vector -> length; i > loc; i--) {
        vector -> data[i] = vector -> data[i - 1];
    }
    vector -> data[loc] = value;
    vector -> length++;
    if (flag == 0)
        return OK;
    else
        return 2;
}

void clear (Vector *vector) {
    free(vector -> data);
    free(vector);
}

int main () {
    Vector *a = (Vector *)malloc(sizeof(Vector));
    init(a, 5);
    int n;
    int p, q;
    scanf ("%d", &n);
    while (n--) {
        scanf ("%d%d", &p, &q);
        int m = insert(a, p, q);
        if (m == 1) {
            printf("success\n");
        }
        else if (m == 2) {
            printf ("expand\n");
            printf ("success\n");
        }else {
            printf("failed\n");
        }
    }
    return 0;
}

/*输入数据
 * 7
 * 0 1
 * 2 2
 * 1 3
 * 1 4
 * 2 5
 * 3 6
 * 4 7
 * */

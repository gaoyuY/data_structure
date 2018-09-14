/*************************************************************************
> File Name: lianxi.c
> Author:gaoyu
> Mail:2282940822 
> Created Time: 2018年09月12日 星期三 21时54分56秒
************************************************************************/

#include<stdlib.h>
#include <stdio.h>
#include<math.h>

typedef struct Vector {
    int size, length;
    int *data;

}Vector;

void init (Vector *vector, int size) {
    vector->size = size; //顺序表的当前最大容量
    vector->length = 0;   //当前顺序表的元素个数
    vector->data = (int *)malloc(sizeof(int) * size);

}
void expand (Vector *vector) {
    int *old_data;
    old_data = vector->data;
    vector->size = vector->size * 2;
    vector->data = (int *)malloc(sizeof(int) * vector->size);
    for (int i = 0; i < vector->length; i++) {
        vector->data[i] = old_data[i];

    }
    free(old_data);

}
int insert (Vector *vector, int loc, int value) {
    if (loc < 0 || loc > vector->length) {
        return 0;

    }
    if (vector->length > vector->size) {
        expand(vector);

    }
    for (int i = vector->length; i > loc; i--) {
        vector->data[i] = vector->data[i - 1];

    }
    vector->data[loc] = value;
    vector->length++;
    return 1;

} 
int reverse (Vector *vector, int begin, int end) {
    int flag;
    while (begin < end) {
        flag = vector->data[begin];
        vector->data[begin] = vector->data[end];
        vector->data[end] = flag;
        ++begin;
        --end;

    }
    return 1;

}
void output (Vector *vector) {
    /* if (vector->length == 1) {
    *         printf ("%d", vector->data[0]);
    *             }  */
    for (int i = 0; i < vector->length; i++) {
        if (i == vector->length ) {
            printf ("%d\n", vector->data[i]);

        }else {
            printf ("%d ", vector->data[i]);

        }

    }
}
void clear(Vector *vector) {
    free(vector->data);
    free(vector);

}
int main () {
    int n , m, a;
    Vector *vector = (Vector *)malloc(sizeof(Vector));
    scanf ("%d%d", &n, &m);
    init(vector, n);
    for (int i = 1; i <= n; ++i) {
        scanf ("%d", &a);
        insert(vector, i - 1, a);

    }

    // 将顺序表分三步翻转
    reverse(vector, 0, m - 1); //第一步:翻转前m个
    reverse(vector, m, n - 1); //第二步:翻转剩下的 (现在的顺序表是最终结果的翻转值)
    reverse(vector, 0, n - 1); //第三步:将整个顺序表翻转(得到最终结果)

    output(vector);
    clear(vector);

}

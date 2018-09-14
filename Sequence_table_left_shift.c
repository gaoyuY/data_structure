/*************************************************************************
	> File Name: Sequence_table_left_shift.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年09月12日 星期三 20时09分01秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
typedef struct Vector {
    int size, length;
    int *data;
}Vector;

int init (Vector *vector, int size) {
    vector->size = size;
    vector->data =(int *)malloc(sizeof(int) * size);
    if (vector->data == NULL) {
        return ERROR;
    }
    vector->length = 0;
    return OK;
}

int insert(Vector *vector, int loc, int value) {
    
}

int main () {

}

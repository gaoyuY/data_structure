/*************************************************************************
	> File Name: Circular_queue.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年09月14日 星期五 20时03分19秒
 ************************************************************************/
/**********************循环队列****************************/
#include<stdio.h>
#include<stdlib.h>

typedef struct Queue {
    int *data;
    int head, tail, length, count;
}Queue;

void init (Queue *queue, int length) {//初始化
    queue->data = (int *)malloc(sizeof (int) * length);
    queue->length = length;
    queue->head = 0;
    queue->tail = -1;
    queue->count = 0;
}

int push (Queue *queue, int element) {//入队
    if(queue->count >= queue->length) {
        return 0;
    }
    queue->tail =(queue->tail + 1) % queue->length;
    queue->data[queue->tail] = element;
    queue->count++;
    return 1;
}

void output(Queue *queue) {//输出队列
    int i = queue->head;
    do{
        printf ("%d ", queue->data[i]);
        i = (i + 1) % queue->length;

    }while (i != (queue->tail + 1) % queue->length);

    printf("\n");
}

int front (Queue *queue) {//队首元素值
    return queue->data[queue->head];
}

int pop (Queue *queue){//出队列
    queue->head = (queue->head = 1) % queue->length;
    queue->count--;
}

int empty (Queue *queue) {//空队列
    return queue->count == 0;
}


void clear (Queue *queue) {//释放空间
    free(queue->data);
    free(queue);
}


int main () {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    init(queue, 100);
    int m;
    scanf ("%d", &m);
    for(int i = 1; i <= m; i++) {
        push(queue, i);
    }
    output(queue);
    if (!empty(queue)) {
        printf("%d\n", front(queue));
        pop(queue);
    }
    output(queue);
    clear(queue);

    return 0;
}

/*************************************************************************
	> File Name: queue_operation.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年09月14日 星期五 16时45分36秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
typedef struct Queue {//结构体
    int *data;              //用来保存队列中每个元素的编号
    int head , tail, length;//head和tail分别表示队列的队首 和 队尾在数组中的位置，length用于记录数组的长度。
}Queue;

void init (Queue *queue, int length) {//初始化
    queue->data = (int *)malloc(sizeof (int) * length);
    queue->length = length;
    queue->head = 0;
    queue->tail = -1;
}

int push (Queue *queue, int element) { //入队
    if (queue->tail + 1 >= queue->length) {
        return 0;
    }
    queue->tail++;
    queue->data[queue->tail] = element;

    return 1;
}

void output (Queue *queue) {//输出队列元素
    for (int i = queue->head; i <= queue->tail; i++) {
        printf ("%d ", queue->data[i]);
    }

    printf("\n");
}

int front (Queue *queue) { //输出队首元素
    return queue->data[queue->head];
}

void pop (Queue *queue) { //出队
    queue->head++;
}

int empty (Queue *queue) {//空队列
    return queue->head > queue->tail;
}
void clear(Queue *queue) {//释放空间
    free(queue->data);
    free(queue);
}

int main() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    init(queue, 100);
    for (int i = 1; i <= 10; i++) {
        push(queue, i);
    }
    output(queue);
    if (!empty(queue)) {
        printf ("%d\n", front(queue));
        pop(queue);
    }

    output(queue);
    clear(queue);

    return 0;
 }

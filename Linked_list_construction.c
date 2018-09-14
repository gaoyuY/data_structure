/*************************************************************************
> File Name: Linked_list_construction.c
> Author:gaoyu
> Mail:2282940822 
> Created Time: 2018年09月10日 星期一 15时15分39秒
************************************************************************/
/*************************************************链表遍历函数的创建和使用*****************************************************************/
/******************************************************输出 ： 1 2 3 4 5 6 7 8 9 10 ******************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;

}Node, *LinkedList;

LinkedList insert (LinkedList head, Node *node, int index) {//index 表示插入结点后，这个节点是第index个结点
    if (head == NULL) {
        if (index != 0) {
            return head;

        }
        head = node;
        return head;
    }
    Node *current_node = head;
    int count = 0;
    while (current_node->next != NULL && count < index - 1) {
        current_node = current_node->next;
        count++;
    }
    if (count == index - 1) {
        node->next = current_node->next;
        current_node->next = node;
    }
    return head;
}

void output (LinkedList head) {
    if (head == NULL) {
        return;

    }
    Node *current_node = head;  //用来遍历整个链表
    while (current_node != NULL) {
        printf ("%d ", current_node->data);
        current_node = current_node->next;

    }
    printf ("\n");

}

void clear (LinkedList head) {
    Node *current_node = head;
    while (current_node != NULL) {
        Node *delete_node = current_node;
        current_node = current_node->next;
        free(delete_node);

    }

}

int main () {
    LinkedList linkedlist = NULL;
    for (int i = 1; i <= 10; i++) {
        Node *node = (Node *)malloc(sizeof(Node));
        node->data = i;
        node->next = NULL;
        linkedlist = insert(linkedlist, node, i - 1);

    }

    output(linkedlist);
    clear(linkedlist);

    return 0;

}


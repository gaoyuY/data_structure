/*************************************************************************
	> File Name: Circular_LinkedList_list_operation.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年09月12日 星期三 19时14分43秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
}Node, *LinkedList;

LinkedList insert (LinkedList head, Node *node, int index) {
    if (head == NULL) {
        if (index != 0) {
            return head;
        }
        head = node;
        head->next = head;
        return head;
    }

    if (index == 0) {
        node->next = head->next;
        head->next = node;
        return head;
    }
    
    Node *current_node = head->next;
    int count;
    while (current_node != head && count < index - 1) {
        current_node = current_node->next;
        count++;
    }
    if (count == index - 1) {
        node->next =current_node->next;
        current_node->next = node;
    }

    if (node == head->next) {
        head = node;
    }

    return head;
}

void output_josephus (LinkedList head, int m) {
    Node *current_node = head;
    head = NULL;
    while (current_node->next != current_node) {
        for (int i = 1;  i < m; i++) {
            current_node =current_node->next ;
        }

        printf ("%d ", current_node->next);
        Node *delete_node = current_node->next;
        free(delete_node);
    }

    printf ("%d\n", current_node->data);
    free(current_node);
}

int main () {
    LinkedList linkedlist = NULL;
    int n, m;
    scanf ("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        Node *node = (Node *)malloc(sizeof(Node));
        node->data = i;
        node->next = NULL;
        linkedlist = insert(linkedlist, node, i - 1);
    }
    output_josephus(linkedlist, m);
    return 0;
}

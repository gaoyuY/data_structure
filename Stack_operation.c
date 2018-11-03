/*************************************************************************
	> File Name: Stack_operation.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年09月27日 星期四 16时04分21秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ERROR 0
#define OK 1

typedef struct Stack {
    int *elements;
    int max_size, top_index;
} Stack;

void init(Stack *s, int length) {
    s->elements = (int *)malloc(sizeof(int) * length);
    s->max_size = length;
    s->top_index = -1;
}

int push(Stack *s, int element) {
    if (s->top_index >= s->max_size) {
        return 0;
    }
    s->top_index++;
    s->elements[s->top_index] = element;
    return 1;
}

int pop(Stack *s) {
    if(s->top_index < 0) {
        return 0;
    }
    s->top_index--;
    return 1;
}

int top(Stack *s) {
    return s->elements[s->top_index];
}

int empty(Stack *s) {
    /*if (s->top_index < 0) {
        return 1;
    }else {
        return 0;
    }*/
    return (s->top_index == -1);
}

int precede(int a, int b) {
    int m , n;
    if (a == '+' || a == '-') {
        m = 1;
    }else {
        m = 2;
    }
    if(b == '+' || b == '-') {
        n = 1;
    }else {
        n = 2;
    }
    return m > n;
}
int operate(int thera, int a, int b) {
	if (thera == '+') {
        return a + b;
    } else if (thera == '-') {
        return b - a;
    }else if (thera == '*') {
        return a * b;
    }else {
        return b / a;
    }
}
void calc(Stack *numbers, Stack *operators) {
    int a = top(numbers);
    pop(numbers);
    int b = top(numbers);
    pop(numbers);
    push(numbers, operate(top(operators), a, b));
    pop(operators);
}

void clear(Stack *s) {
    free(s->elements);
    free(s);
}

int main() {
    
    Stack *numbers = (Stack *)malloc(sizeof(Stack));
    init(numbers, 20);
  	Stack *operators = (Stack *)malloc(sizeof(Stack));
    init(operators, 20);
    char *buffer = (char *)malloc(sizeof (char) * 21);
    scanf ("%[^\n]s", buffer);
    int m = strlen(buffer);
    for (int i = 0; i < m; i++) {
        if (isdigit(buffer[i])) {
            push(numbers, buffer[i] - '0');
        } else {
            while (!empty(operators) && !precede(buffer[i], top(operators))) {
                calc(numbers, operators);
            }
            push(operators, buffer[i]);
        }
    }
    while (!empty(operators)) {
        calc(numbers, operators);
    }
    printf("%d\n", top(numbers));
    clear(numbers);
    clear(operators);
    free(buffer);
    return 0;
}

/*************************************************************************
	> File Name: Expression_evaluation.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年09月15日 星期六 16时32分04秒
 ************************************************************************/

/***************************************表达式求值************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
        return 0;
    }else {
        return 1;
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
    int m, a;
    char b;
    scanf ("%d", &m);
    Stack *numbers = (Stack *)malloc(sizeof(Stack));
    init(numbers, m);
  	Stack *operators = (Stack *)malloc(sizeof(Stack));
    init(operators, m);
    char *buffer = (char *)malloc(m + 1);
    scanf ("%s", buffer);
    for (int i = 0; i < m; i++) {
        if (isdigit(buffer[i])) {   //isdigit() 判断一个数是否为阿拉伯数字,包含在头文件<ctype.h>
            push(numbers, buffer[i] - '0');
        } else {
            while (!empty(operators) && !precede(buffer[i], top(operators))) {//运算符栈不为空且栈顶运算符优先级高
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

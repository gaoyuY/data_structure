/*************************************************************************
	> File Name: Expression_evaluation.c
	> Author:gaoyu
	> Mail:2282940822 
	> Created Time: 2018年09月15日 星期六 09时48分59秒
 ************************************************************************/
/**********************表达式求值******************************************/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct Stack {
    int *elements;
    int max_size, top_index;
}Stack;

void init (Stack *s, int length) {//初始化
    s->elements = (int *)malloc(sizeof(int) * length);
    s->max_size = length;
    s->top_index = -1;

}

int push (Stack *s, int element) {//入栈
    if (s->top_index >= s->max_size) {
        return 0;
    }
    s->top_index++;
    s->elements[s->top_index] = element;
    return 1;
}

int pop (Stack *s) {//出栈
    if (s->top_index < 0) {
        return 0;
    }
    s->top_index--;
    return 1;
}

int top(Stack *s) {//返回栈顶元素
    return s->elements[s->top_index];
}

int empty (Stack *s) {//判断栈是否为空
    if (s->top_index < 0) {
        return 1;
    }else {
        return 0;
    }
}

int precede (char a, char b){ //判断优先级函数precede()
    if (a == '+' && b == '*') {
        return 1;
    }else {
        return 0;
    }
}

int operate (char thera, int a, int b) {//根据运算符thetra计算a和b的值，并返回计算结果
    if (thera == '+') {
        return a + b;
    }else {
        return a * b;
    }
}

void calc (Stack *numbers, Stack *operators) {//从数字栈numbers里弹出两个元素，用运算符栈栈顶的运算符计算结果，然后把结果加入到numbers里
    int a = top(numbers);
    pop(numbers);
    int b = top(numbers);
    pop(numbers);
    push (numbers, operate(top(operators), a, b));
    pop(operators);
}


void clear (Stack *s) {
    free(s->elements);
    free(s);
}


int main () {
    int n; 
    scanf("%d", &n);
    Stack *numbers = (Stack *)malloc(sizeof(Stack));
    init(numbers, n);
    Stack *operators = (Stack *)malloc(sizeof(Stack));
    init(operators, n);
    char *buffer = (char *)malloc(sizeof(char) * (n + 1));
    scanf ("%s", buffer);
    int i = 0;
    while (i < n) {
        if (isdigit(buffer[i])) {
            push (numbers, buffer[i] - '0');
            i++;
        }else {
            if (empty(operators) || precede(buffer[i], top(operators))) {
                push(operators, buffer[i]);
                i++;
            }else {
                calc(numbers, operators);
            }
        }
    }
    while (!empty(operators)) {
        calc(numbers, operators);
    }

    printf ("%d\n", top(numbers));
    clear(numbers);
    clear(operators);
    free(buffer);


    return 0;
}

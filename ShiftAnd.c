/*************************************************************************
	> File Name: ShiftAnd.c
	> Author: GaoYu
	> Mail: 
	> Created Time: 2019年01月02日 星期三 14时55分20秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BASE 128

int ShiftAnd (char *str, char *pattern) {
    int code[BASE] = {0}, len = 0; //code[]计算每个字符的编码
    for (len = 0; pattern[len]; len++) {//将模式串处理到字符编码中
        code[pattern[len]] |= (1 << len);
        printf("%d\n", code[pattern[len]]);
    }

    int p = 0;
    for (int i = 0; str[i]; i++) {
        p = (p << 1 | 1) & code[str[i]]; //公式
        if (p & (1 << (len - 1))) //公式
        {printf ("p = %d \n", p);
            return i - len + 1;
        }
    }
    return -1;
}

int main () {
    char str[100], pattern[30];
    while (scanf("%s%s", str, pattern) != EOF) {
        int num = ShiftAnd(str, pattern);
        printf ("ShiftAnd : %d\n", num);
    }
    return 0;
}

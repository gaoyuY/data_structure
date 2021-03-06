/*************************************************************************
	> File Name: string_algorithm.c
	> Author: GaoYu
	> Mail: 
	> Created Time: 2018年12月12日 星期三 10时00分43秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>

//暴力算法　
int BF (const char *text, const char *pattern, int *p_cnt) {
    
    #define cnt (*p_cnt)
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    for (int i = 0; i  < len1 - len2 + 1; i++, cnt++) {
        int flag = 1;
        for (int j = 0; pattern[j] &&flag; j++, cnt++) {
            if (text[i + j] == pattern[j]) continue;
            flag = 0;
        }
        if (flag) return 1;
    }
    #undef cnt
    return 0;
}

//KMP算法
int KMP(const char *text, const char *pattern, int *p_cnt) {
    #define cnt (*p_cnt)
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    int  *next = (int *)malloc (sizeof(int) * len2);
    next[0] = -1;
    int j = -1;
    for (int i = 1; i < len2; i++, cnt++) {
        while (j != -1 && pattern[j + 1] != pattern[i])  j = next[j], cnt++;
        if (pattern[j + 1] == pattern[i]) {
            j += 1;
        }
        next[i] = j;
    }
    j = -1;//指向模式串
    for (int i = 0; text[i]; i++, cnt++) {
        while (j != -1 && pattern[j + 1] != text[i]) j = next[j], cnt++;
        if (pattern[j + 1] == text[i]) j += 1;
        if (pattern[j + 1] == 0) return 1;//模式串匹配完成，０代表"\0"
    }
   
    #undef cnt
    return 0;
}


int main () {
    char str1[] = "hello world";
    int cnt = 0;
    printf ("BF(%s, %s) = %d\n", str1, "wor", BF(str1, "wor", &cnt));
    printf ("BF search : %d\n", cnt);
    cnt = 0;
    printf ("KMP(%s, %s) = %d\n", str1, "wor", KMP(str1, "wor", &cnt));
    printf ("KMP search : %d\n", cnt);
    return 0;

}

/*************************************************************************
	> File Name: plalindrome.c
	> Author: GaoYu
	> Mail: 
	> Created Time: 2019年01月13日 星期日 15时18分54秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
/*O(n*n*n)
int is_valid (char *str, int i, int j) {
    while (i < j) {
        if (str[i++] != str[j--]) return 0;
    }
    return 1;
}


int main () {
    char str[1000];
    scanf ("%s", str);
    for (int i = 0; str[i]; i++) {
        for (int j = i; str[j]; j++) {
            if(is_valid(str, i, j)) {
                printf ("%d %d\n", i, j);
            } 
        }
    }

    return 0;
}*/


void expand(char *str, int i, int j, int n) {
    while (i >= 0 && j < n && str[i] == str[j]) {
        char c = str[j + 1];
        str[j + 1] = 0;
        printf ("%s\n", str + i);
        str[j + 1] = c;
        i--, j++;
    }
    return ;
}

int main () {
    char str[1000];
    scanf ("%s", str);
    int len = strlen(str);
    for (int i = 0; str[i]; i++) {
        expand(str, i, i, len);
        expand (str, i, i + 1, len);   
    }
    return 0;
}








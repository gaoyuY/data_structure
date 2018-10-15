/*************************************************************************
	> File Name: KMP_string.c
	> Author: GaoYu
	> Mail: 
	> Created Time: 2018年12月12日 星期三 19时13分25秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int KMP_string (char *str1, char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int next[len2];
    next[0] = -1;
    int k = -1;
    //next 数组
    for(int i = 1; i < len2; i++) {
        while (k != -1 && str2[k + 1] != str2[i]) k = next[k];
        if (str2[k + 1] == str2[i]) k++;
        next[i] = k;
    }

    k = -1;
    //查找文本串中是否包含模式串
    for (int i = 0; i < len1; i++) {
        while (k != -1 && str2[k + 1] != str1[i]) k = next[k];
        if (str2[k + 1] == str1[i]) k++;
        if (str2[k + 1] == 0) return 1;
    }
    return 0;
}


int main () {
    
    char str1[20], str2[10];
    scanf ("%s", str1);
    scanf ("%s", str2);
    int ans = KMP_string(str1, str2);
    printf ("%d\n", ans);

    return 0;
}

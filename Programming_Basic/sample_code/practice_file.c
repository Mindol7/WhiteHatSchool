#include <stdio.h>


int main() {
    FILE *fp;
    fp = fopen("test2.txt", "w+");
    int i = 1;
    while(1) {
        if (i > 5) break;

        printf("%d라인에 작성할 내용을 입력하세요.\n", i++);
        char str[100];
        fgets(str, sizeof(str), stdin);

        fprintf(fp, "%s", str);
    }

    printf("파일열기\n");
    rewind(fp);
    char tmp[100];
    while(fgets(tmp, sizeof(tmp), fp)){
        printf("%s", tmp);
    }

    fclose(fp);
    return 0;
}
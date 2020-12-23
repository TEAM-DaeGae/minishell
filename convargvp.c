// File Name: convargvp.c (라)
// Description: alias 또는 쉘/환경변수가 들어오면 원래 값으로 치환

#include "minishell.h"

// Function : void convargvp(char **argvp)
// Input    : command를 분리한 argument vector
// Purpose  : 명령어 중 환경/쉘 변수 또는 alias 별칭이 있을 경우 원래 값으로 치환하여 argvp에 다시 저장함
void convargvp(char **argvp)
{
    int n, start=0, end=0, i=0, j=0;
    char *name, *value, *tmp;
    char argtmp[MAXSIZE] = {0};
    char alias[8][MAXSIZE] = {0};
    list_t *t;

    for(n=0; argvp[n]!=NULL; n++)
    {
        if(strcmp(argvp[0], "unalias") == 0) // unalias라면 치환하지 않음
            break;

        // 인자가 alias 인자라면 원래대로 치환
        t = ahead->next;
        while(t != atail)
        {
            if(strcmp(argvp[n], t->name) == 0)
            {
                // alias 배열에 value의 명령어 구분하여 넣어줌
                // ex> 'ls -l'이였다면 ls와 -l 저장
                strcpy(argtmp, t->value);
                argtmp[0] = ' ';
                argtmp[strlen(argtmp)-1] = '\0';
                tmp = strtok(argtmp, " ");
                strcpy(alias[i++], tmp);
                while(tmp = strtok(NULL, " "))
                {
                    strcpy(alias[i], tmp);
                    i++;
                }

                // argvp에 있는 인자들을 새로이 치환된 alias 인자들이
                // 들어올 수 있도록 공간 확보 차원에서 뒤로 옮김
                while(argvp[++end]);
                for(end; end>n; end--)
                {
                    argvp[end+i-1] = argvp[end];
                }

                // 비어있는 공간에 alias 인자 삽입
                for(start=n, j=0; j<i; start++, j++)
                {
                    tmp = (char *)malloc(strlen(alias[j])+1);
                    strcpy(tmp, alias[j]);
                    argvp[start] = tmp;
                }
            }
            t = t->next;
        }

        // 인자 중에 쉘/환경 변수가 있다면
        if(argvp[n][0] == '$')
        {
            // 쉘 변수일 경우
            if(argvp[n][1] > 48 && argvp[n][1] < 58)
            {
                tmp = shell[argvp[n][1]-49];
                value = (char *)malloc(strlen(tmp)+1);
                strcpy(value, tmp);
                argvp[n] = value;
            }
            // 환경 변수일 경우
            else
            {
                name = strtok(argvp[n], "$");
                tmp = (char *)getenv(name);
                value = (char *)malloc(strlen(tmp)+1);
                strcpy(value, tmp);
                argvp[n] = value;
            }
        }
    }
}
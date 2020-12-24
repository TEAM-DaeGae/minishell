// File Name: convargvp.c (라)
// Description: alias 또는 쉘/환경변수가 들어오면 원래 값으로 치환

#include "mysh.h"

//////////////////////////////////////////////////////////////////////
// Function : void convargvp(char **argvp)
// Input    : command를 분리한 argument vector
// Purpose  : 명령어 중 환경/쉘 변수 또는 alias 별칭이 있을 경우 원래 값으로 치환하여 argvp에 다시 저장함
//////////////////////////////////////////////////////////////////////
void convargvp(char **argvp)
{
    int n, start=0, end=0, i=0, j=0;
    char *name, *value, *tmp;
    char argtmp[MAXSIZE] = {0};
    char alias[8][MAXSIZE] = {0};
    list_t *t;

    for(n=0; argvp[n]!=NULL; n++)
    {
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
// File Name: incmdproc.c (마)
// Description: 쉘 내부에서 처리되는 명령어들을 구현

#include "minishell.h"

// Function : int incmdproc(char **argvp)
// Input    : command를 분리한 argument vector
// Output   : 쉘 내부 명령어 처리를 했으면 1, 안했으면 0
// Purpose  : 명령어가 쉘 내부 명령이라면 그에 해당하는 함수를 호출
int incmdproc(char **argvp)
{
    int n = 1;

    // argvp가 쉘 내부 명령이라면 그에 따른 함수를 호출
    if(strcmp(argvp[0], "set") == 0)
        __set(argvp);
    else if(strcmp(argvp[0], "export") == 0)
        __export(argvp);
    else if(strcmp(argvp[0], "env") == 0)
        __env(argvp);
    else if(strcmp(argvp[0], "cd") == 0)
        __cd(argvp);
    else if(strcmp(argvp[0], "pwd") == 0)
        __pwd(argvp);
    else if(strcmp(argvp[0], "alias") == 0)
        __alias(argvp);
    else if(strcmp(argvp[0], "unalias") == 0)
        __unalias(argvp);
    else if(strcmp(argvp[0], "umask") == 0)
        __umask(argvp);
    else if(strcmp(argvp[0], "echo") == 0)
        __echo(argvp);
    else if(strcmp(argvp[0], "trap") == 0)
        __trap(argvp);
    else if(strcmp(argvp[0], "kill") == 0)
        __kill(argvp);
    else if(strcmp(argvp[0], "history") == 0)
        hisproc(argvp);
    else if(strcmp(argvp[0], "exit") == 0)
        __exit(argvp);
    else
        n = 0;

    // 위 명령어 중 어느 것에도 해당이 안되었으면
    // 1을 리턴함
    return n;
}

// Function : void __set(char **argvp)
// Input    : command를 분리한 argument vector
// Output   : 없음
// Purpose  : 인자가 있으면 쉘 변수 설정하고 인자가 없으면 쉘 변수를 출력함
void __set(char **argvp)
{
    int n;
    // 아무런 인자가 없으면 쉘 변수 출력
    if(argvp[1] == 0)
    {
        // 쉘 변수를 출력
        for(n=0; n<9; n++)
        {
            if(strlen(shell[n]) == 0)
                break;
            printf("$%d : %s\n", n+1, shell[n]);
        }
    }
    // 인자가 있으면 순서대로 쉘 변수 할당
    else
    {
        // 쉘 변수 초기화
        memset(shell, 0, sizeof(shell));

        // 인자를 쉘 변수에 저장
        for(n=1; argvp[n] != NULL; n++)
        {
            if(n > 9)
                break;
            strcpy(shell[n-1], argvp[n]);
        }
    }
}

// Function : void __export(char **argvp)
// Input    : command를 분리한 argument vector
// Output   : 없음
// Purpose  : 환경 변수를 설정한다.
void __export(char **argvp)
{
    char tmp[MAXSIZE];
    char *name, *value;

    // 공백이 존재하게 받으면 실행시키지 않음
    // ex> PWD = /root 등
    if(argvp[2])
        perror("Can't set environment value\nusage : [NAME]=[VALUE]");
    // 정확한 값을 받았으면 환변경수 set
    else
    {
        strcpy(tmp, argvp[1]);
        name = strtok(tmp, "=");
        value = strtok(NULL, "");
        setenv(name, value, 1);
    }
}

// Function : void __env(char **argvp)
// Input    : command를 분리한 argument vector
// Output   : 없음
// Purpose  : 환경 변수를 출력한다.
void __env(char **argvp)
{
    int n;
    for(n=0; environ[n] != NULL; n++)
        printf("%s\n", environ[n]);
}


// Function : void __cd(char **argvp)
// Input    : command를 분리한 argument vector
// Output   : 없음
// Purpose  : argvp에 저장된 상대 경로 또는 절대 경로 위치로 현재 위치를 이동한다.
void __cd(char **argvp)
{
    char curpath[MAXSIZE];

    // 현재 디렉토리 OLDPWD에 저장
    getcwd(curpath, MAXSIZE);
    setenv("OLDPWD", curpath, 1);

    // 디렉토리 변경하고 변경한 디렉토리 PWD에 저장
    chdir(argvp[1]);
    getcwd(curpath, MAXSIZE);
    setenv("PWD", curpath, 1);
}

// Function : void __pwd(char **argvp)
// Input    : command를 분리한 argument vector
// Output   : 없음
// Purpose  : 현재 위치를 절대경로로 화면에 출력한다.
void __pwd(char **argvp)
{
    char buf[MAXSIZE] = {0};
    getcwd(buf, MAXSIZE);
    printf("%s\n", buf);
}

// Function : void __alias(char **argvp)
// Input    : command를 분리한 argument vector
// Output   : 없음
// Purpose  : 명령어 라인을 하나의 별칭으로 설정하고 alias 리스트에 추가
void __alias(char **argvp)
{
    list_t *t;
    int n;
    char *name, *value;
    char alias[MAXSIZE] = {0};

    // alias 명령어만 쳤으면 alias list 출력
    if(argvp[1] == 0)
    {
        t = ahead->next;
        while(t != atail)
        {
            printf("%s=%s\n", t->name, t->value);
            t = t->next;
        }
    }
    else
    {
        // argvp로 분리되어있는 alias 내용을 합침
        n = 1;
        while(argvp[n] != NULL)
        {
            strcat(alias, argvp[n]);
            strcat(alias, " ");
            n++;
        }
        alias[strlen(alias)-1] = '\0';

        // 새로운 alias list entry에 name과 value 저장
        t = (list_t *)malloc(sizeof(list_t));
        name = strtok(alias, "=");
        value = strtok(NULL, "");
        t->name = (char *)malloc(strlen(name)+1);
        t->value = (char *)malloc(strlen(value)+1);
        strcpy(t->name, name);
        strcpy(t->value, value);

        // alias list의 마지막에 삽입
        t->prev = atail->prev;
        t->next = atail;
        atail->prev->next = t;
        atail->prev = t;
    }
}

// Function : void __unalias(char **argvp)
// Input    : command를 분리한 argument vector
// Output   : 없음
// Purpose  : 설정된 별칭을 alias 리스트에서 제거
void __unalias(char **argvp)
{
    list_t *t, *del;

    // alias list를 순회
    t = ahead->next;
    while(t != atail)
    {
        // 삭제할 alias가 존재하면 list에서 제거함
        if(strcmp(t->name, argvp[1]) == 0)
        {
            del = t;
            del->prev->next = del->next;
            del->next->prev = del->prev;
            t = t->next;
            free(del);
        }
        else
            t = t->next;
    }
}

// Function : void __umask(char **argvp)
// Input    : command를 분리한 argument vector
// Output   : 없음
// Purpose  : 사용자 파일 생성 마스크값을 설정하거나 출력한다.
void __umask(char **argvp)
{
    mode_t mode;
    int n[3] = {0};
    int oct, i, err=0;

    // 인자가 없거나 -S 옵션이면 현재 umask 모드 출력
    // umask(0)하면 umask값이 0으로 바뀌므로
    // mode를 통하여 원래대로 복귀시켜놓음
    if(argvp[1] == 0 || strcmp(argvp[1], "-S") == 0)
    {
        printf("%03o\n", mode = umask(0));
        umask(mode);
    }
    // 설정 값이 있으면 해당 값으로 umask 설정
    else
        {
        // 인자 중에 숫자가 아닌 것이 있는지 검색
        for(i=0; i<3; i++)
        {
            if(argvp[1][i] < 48 || argvp[1][i] > 57)
                err = 1;
        }

        // 인자수가 틀리거나 인자 중에 숫자가 아닌 것이 있으면 에러
        if(strlen(argvp[1]) != 3 || err == 1)
            perror("Can't set umask");
        else
        {
            n[0] = (int)(argvp[1][0]-48);
            n[1] = (int)(argvp[1][1]-48);
            n[2] = (int)(argvp[1][2]-48);

            oct = 64*n[0] + 8*n[1] + n[2];
            umask(oct);
        }
    }
}

//////////////////////////////////////////////////////////////////////
// Function : void __echo(char **argvp)
// ============================================
// Input    : command를 분리한 argument vector
// Output   : 없음
// Purpose  : 인자들을 화면에 출력한다.
//////////////////////////////////////////////////////////////////////
void __echo(char **argvp)
{
    int n;
    char *name, *value;

    for(n=1; argvp[n]!=NULL; n++)
    {
        // 환경변수 또는 쉘 변수라면 원래 값으로 치환하여 출력
        if(argvp[n][0] == '$')
        {
            // 쉘 변수라면
            if(argvp[n][1] > 48 && argvp[n][1] < 58)
            {
                printf("%s ", shell[argvp[n][1]-49]);
            }
            // 환경 변수라면
            else
            {
                name = strtok(argvp[n], "$");
                value = (char *)getenv(name);
                printf("%s ", value);
            }
        }
        // 일반 값이라면 그대로 출력
        else
        {
            printf("%s ", argvp[n]);
        }
    }
    printf("\n");
}

// Function : void __trap(char **argvp)
// Input    : command를 분리한 argument vector
// Output   : 없음
// Purpose  : trapporc() 함수 호출
void __trap(char **argvp)
{
    trapproc(argvp);
}

// Function : void __kill(char **argvp)
// Input    : command를 분리한 argument vector
// Output   : 없음
// Purpose  : 프로세스에 시그널 신호를 보냄
void __kill(char **argvp)
{
    int signo;
    int pid;

    // 시그널과 pid를 얻어옴
    signo = issig(argvp[1]);
    pid = atoi(argvp[2]);

    // 해당 pid에 signo 신호를 보냄
    if(kill(pid, signo) == -1)
        perror("Failed to send signal");
}

// Function : void __exit(char **argvp)
// Input    : command를 분리한 argument vector
// Output   : 없음
// Purpose  : 인자를 상태값으로 가지고 프로세스 종료
void __exit(char **argvp)
{
    int n;

    // 넘어온 인자에 따른 exit number 설정
    if(argvp[1])
        n = atoi(argvp[1]);
    else
        n = 0;

    // history 파일 저장
    sav_list(argvp);

    // canonical mode로 복원
    reset_keypress();

    exit(n);
}

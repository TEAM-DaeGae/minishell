// File Name: terminalio.c (다)
// Description: 터미널 상에서 입력 처리

#include "minishell.h"

// Input    : command(명령어 라인)
// Output   : commnad에 내용이 있으면 1, 없으면 0
// Purpose  : 터미널에서 개행문자까지 입력받아서 command에 저장

int getcommand(char *command)
{
    int n = 0
    space_chk = 0;
    char path[MAXSIZE] = {0};
    char c;
    nowhistory = histail;

    fflush(NULL);

    // 프롬프트를 띄우고 명령 입력을 대기
    curpath = (char *)getenv("PWD");
    printf("[%s@%s]$ ", userinfo->pw_name, curpath);
    sprintf(path, "[%s@%s]$ ", userinfo->pw_name, curpath);

    // 명령 입력을 받음
    while((c = fgetc(stdin)))
    {
        // enter key를 입력받으면 입력 종료
        if(c == 10)
        {
            fputc('\n', stdout);
            break;
        }

        // Ctrl+D를 입력받으면 입력 종료
        if(c == 4)
        {
            fputc('\n', stdout);
            return 0;
        }

        // backspace key를 제외한 입력 무시
        if((c <= 26) && (c != 8))
            break;

        switch(c)
        {
            case 8: // backspace key를 입력받을 때 처리
                if(n == 0)
                    break;

                fputc('\b', stdout);
                fputc(' ', stdout);
                fputc('\b', stdout);
                command[--n] = (char)0;
                break;

            
            case 27: // ^[ (esc) 기호이면서
                if((c = fgetc(stdin)) != 91) // [ 기호가 아니면 switch문 탈출
                    break;

            switch(fgetc(stdin)) // [ 기호가 들어왔다면
            {
                case 65: // ^[[A 기호, 즉 key가 up일 때 history 내용 출력
                    nowhistory = nowhistory->prev;
                    if(nowhistory != hishead)
                    {
                        fprintf(stdout, "\r%80s", " ");
                        fprintf(stdout, "\r%s%s", path,
                        nowhistory->value);
                        strcpy(command,
                        nowhistory->value);
                        n = strlen(command);
                    }
                    else
                    {
                        nowhistory = hishead->next;
                    }
                    break;
                
                case 66: // ^[[B 기호, 즉 key가 down일 때 history 내용 출력
                    nowhistory = nowhistory->next;
                    if(nowhistory != histail)
                    {
                        fprintf(stdout, "\r%80s", " ");
                        fprintf(stdout, "\r%s%s", path,
                        nowhistory->value);
                        strcpy(command,
                        nowhistory->value);
                        n = strlen(command);
                    }
                    else
                    {
                        fprintf(stdout, "\r%80s", " ");
                        fprintf(stdout, "\r%s", path);
                        n = 0;
                    }
                    break;
                    
                case 67: // ^[[C 기호, 즉 key가 right일 때 아무 처리 안함
                    break;
                
                case 68: // ^[[D 기호, 즉 key가 left일 때 아무 처리 안함
                    break;
            }
            break;

            // 그 외 일반적인 문자이면
            default:
                fputc(c, stdout);
                command[n++] = (char)c;
                break;
        }
    }
    command[n] = '\0';

    
    if(strlen(command) == 0) // 아무런 입력이 없었으면 프롬프트 다시 띄움
        return 0;

    
    for(n=0; n<strlen(command); n++) // 공백만 포함된 문자열이면 프롬프트 다시 띄움
    if(command[n] != ' ' && command[n] != '\t')
        return 1;

    return 0;
}


// Function : void set_keypress(void)
// Purpose  : 터미널을 non-canonical mode로 변경

void set_keypress(void)
{
    struct termios term;

    tcgetattr(0, &termstat);
    memcpy(&term, &termstat, sizeof(struct termios));

    term.c_lflag &= (~ICANON);
    term.c_lflag &= (~ECHO);
    term.c_cc[VTIME] = 0;
    term.c_cc[VMIN] = 1;

    tcsetattr(0, TCSANOW, &term);
}

// Function : void reset_keypress(void)
// Purpose  : 터미널을 canonical mode로 변경

void reset_keypress(void)
{
    tcsetattr(0, TCSANOW, &termstat);
}
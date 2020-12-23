#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "./libft/libft.h"

# define MAXSIZE 1024
// 리다이렉션 명령 처리시 파일 open을 위한 flag 및 mode
# define OUTFLAG (O_WRONLY | O_CREAT | O_TRUNC)
# define APPFLAG (O_WRONLY | O_CREAT | O_APPEND)
# define FMODE(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

extern  char **environ;// 환경 변수
char    shell[9][MAXSIZE];// 쉘 변수(9개)

char    abspath[MAXSIZE];// mysh가 위치한 절대 경로
char    *curpath;// 현재 경로
int     background;// 백그라운드 여부 체크
int     work_num;// 작업 번호

struct passwd   *userinfo;// 사용자 정보 구조체
struct termios  termstat;// terminal io stat 구조체

#endif
// (가)
// mysh 구현을 위하여 필요한 각종 함수원형 및 변수 정의

#ifndef __MYSH_H__
#define __MYSH_H__

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <signal.h>
#include <termio.h>

#define MAXSIZE 1024

// 리다이렉션 명령 처리시 파일 open을 위한 flag 및 mode
#define OUTFLAG (O_WRONLY | O_CREAT | O_TRUNC)
#define APPFLAG (O_WRONLY | O_CREAT | O_APPEND)
#define FMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

extern char		**environ; // 내부의 환경 변수
char			shell[9][MAXSIZE]; // 쉘 변수(9개)

char			abspath[MAXSIZE]; // mysh가 위치한 절대 경로
char			*curpath; // 현재 경로
int				background; // 백그라운드 여부 체크
int				work_num; // 작업 번호


struct passwd	*userinfo; // 사용자 정보 구조체
struct termios	termstat; // terminal io stat 구조체

// list 사용을 위하여 정의한 list 구조체
typedef struct	list
{
	char		*name;
	char		*value;
	struct list	*prev;
	struct list *next;
}				list_t;

// sigaction 정보를 저장하기 위한 sigactlist 구조체
typedef struct	sigactlist
{
	char				*command;
	int					signo;
	struct sigactlist	*prev;
	struct sigactlist	*next;
}				siglist_t;

list_t			*hishead; // history list head
list_t			*histail; // history list tail

list_t			*ahead; // alias list head
list_t			*atail; // alias list tail

list_t			*nowhistory; // 현재 history를 지정

siglist_t		*sighead; // signal action list head
siglist_t		*sigtail; // signal action list tail


int				hiscount; // history 개수


// 쉘의 입력 처리 함수
int		getcommand(char *command);

// fork를 이용한 실질적인 명령어 수행 처리 함수
int		forkproc(char **argvp);

// 인자 내 쉘/환경변수 치환 함수
void	convargvp(char **argvp);

// 쉘 커맨드 처리 함수
int		incmdproc(char **argvp);
// 쉘 커맨드 함수들
void	__set(char **argvp);
void	__export(char **argvp);
void	__env(char **argvp);
void	__cd(char **argvp);
void	__pwd(char **argvp);
void	__alias(char **argvp);
void	__unalias(char **argvp);
void	__umask(char **argvp);
void	__echo(char **argvp);
void	__trap(char **argvp);
void	__kill(char **argvp);
void	__exit(char **argvp);

// history 처리 함수
void	hisproc(char **argvp);
void	init_list(void);
void	open_list(void);
void	add_list(char *command);
void	del_list(char **argvp);
void	prn_list(char **argvp);
void	sav_list(char **argvp);

// trap 처리 함수
void	sig_init_list(void);
void	trapproc(char **argvp);
void	siglist(void);
void	trapprint(void);
void	trapdel(char **argvp);
void	trapconnect(char **argvp);
void	handler(int signo);

// redirction 및 pipe 처리 함수
void	pipeproc(char **argvp);
void	redirectproc(char **argvp);
int		ispipe(char **argvp);
void	redirectionin(char **argvp);
void	redirectionout(char **argvp, int choice);

// usage 처리 함수
int		showusage(char **argvp);
void	usage_myls(void);
void	usage_myfind(void);
void	usage_mygrep(void);
void	usage_env(void);
void	usage_export(void);
void	usage_set(void);
void	usage_history(void);
void	usage_alias(void);
void	usage_unalias(void);
void	usage_pwd(void);
void	usage_umask(void);
void	usage_trap(void);

#endif //__MYSH_H__

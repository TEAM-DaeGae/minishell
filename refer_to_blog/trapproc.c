// trap 명령 수행(시그널-명령 연결 및 해제)

#include "mysh.h"

// signal list
char	sig[31][16] = {"SIGHUP", "SIGINT", "SIGQUIT", "SIGILL",\
					"SIGTRAP", "SIGABRT", "SIGBUS", "SIGFPE",\
					"SIGKILL", "SIGUSR1", "SIGSEGV", "SIGUSR2",\
					"SIGPIPE", "SIGALRM", "SIGTERM", "SIGSTKFLT",\
					"SIGCHLD", "SIGCONT", "SIGSTOP", "SIGTSTP",\
					"SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU",\
					"SIGXFSZ", "SIGVTALRM", "SIGPROF", "SIGWINCH",\
					"SIGIO", "SIGPWR", "SIGSYS"};

//////////////////////////////////////////////////////////////////////
// Function : void trapproc(char **argvp)
// ============================================
// Input : command를 분리한 argument vector
// Output : 없음
// Purpose : trap 인자에 따른 각 함수를 호출
//////////////////////////////////////////////////////////////////////
void	trapproc(char **argvp)
{
	// trap 다음의 인자가
	// 인자가 없을 경우
	if(argvp[1] == NULL)
			trapprint();
	// -l 옵션일 경우 정의된 시그널 번호/이름 출력
	else if(strcmp(argvp[1], "-l") == 0)
			siglist();
	// -p 옵션이거나 없는 경우 현재 연결된 시그널-명령 리스트 출력
	else if(strcmp(argvp[1], "-p") == 0)
			trapprint();
	// 시그널 번호/이름일 경우 연결된 명령 제거
	else if(issig(argvp[1]))
			trapdel(argvp);
	else if(strcmp(argvp[1], "-") == 0)
			trapdel(argvp);
	// 명령과 시그널 번호/이름이 둘 다 들어올 경우 명령 연결
	else if(argvp[2] != NULL)
			trapconnect(argvp);
	// 그 외 경우 에러 메세지 출력
	else
			perror("Wrong trap option");
}

//////////////////////////////////////////////////////////////////////
// Function : void sig_init_list(void)
// ============================================
// Input : 없음
// Output : 없음
// Purpose : signal action list 초기화
//////////////////////////////////////////////////////////////////////
void	sig_init_list(void)
{
	sighead = (siglist_t *)malloc(sizeof(siglist_t));
	sigtail = (siglist_t *)malloc(sizeof(siglist_t));

	sighead->command = NULL;
	sighead->signo = 0;
	sighead->prev = sighead;
	sighead->next = sigtail;
	sigtail->command = NULL;
	sigtail->signo = 0;
	sigtail->prev = sighead;
	sigtail->next = sigtail;
}

//////////////////////////////////////////////////////////////////////
// Function : int issig(char *signal)
// ============================================
// Input : 시그널 번호 / 이름
// Output : 시그널이면 해당 시그널 번호, 아니면 0
// Purpose : 인자가 시그널 번호 / 이름인지 확인
//////////////////////////////////////////////////////////////////////
int		issig(char *signal)
{
	int	n;

	// sig 값이 없으면 0 리턴
	if(signal == NULL)
			return 0;
	// sig 값이 숫자라면 해당 값 리턴
	else if(atoi(signal) != 0)
	{
			return atoi(signal);
	}
	// sig 값이 문자라면
	else
	{
		// signal list에서 일치하는 signal을 찾아서 해당 signal number를 리턴
		for(n=0; n<31; n++)
		{
			if(strcmp(signal, sig[n]) == 0)
					break;
		}
		if(n == 31)
				return 0;
		else
				return n+1;
	}
}

//////////////////////////////////////////////////////////////////////
// Function : void siglist(void)
// =============================================
// Input : 없음
// Output : 없음
// Purpose : 시그널 리스트 출력
//////////////////////////////////////////////////////////////////////
void	siglist(void)
{
	int n;

	// signal 31개 리스트를 화면에 출력한다.
	for(n=1; n<32; n++)
	{
		printf("%2d) %-12s", n, sig[n-1]);

		if(n%4 == 0 || n == 31)
				printf("\n");
	}
}

//////////////////////////////////////////////////////////////////////
// Function : void trapprint(void)
// ============================================
// Input : 없음
// Output : 없음
// Purpose : trap으로 연결된 시그널-명령 리스트 출력
//////////////////////////////////////////////////////////////////////
void	trapprint(void)
{
	siglist_t	*t;

	// signal action list 출력
	t = sighead->next;
	while(t != sigtail)
	{
		printf("trap -- '%s' %s\n", t->command, sig[t->signo-1]);
		t = t->next;
	}
}

//////////////////////////////////////////////////////////////////////
// Function : void trapdel(char **argvp)
// ============================================
// Input : command를 분리한 argument vector
// Output : 없음
// Purpose : 시그널 번호/이름으로 연결된 명령을 제거
//////////////////////////////////////////////////////////////////////
void	trapdel(char **argvp)
{
	int					signo;
	struct sigaction	act;
	siglist_t			*t;
	
	if(strcmp(argvp[1], "-") == 0)
			signo = issig(argvp[2]);
	else
			signo = issig(argvp[1]);
	
	t = sighead->next;
	
	while(t != sigtail)
	{
		// 제거할 시그널 넘버가 존재하면
		if(t->signo == signo)
		{
			// SIG_INT면 ignore로 그 외는 default로 핸들러 설정
			if(signo == 2)
					act.sa_handler = SIG_IGN;
			else
					act.sa_handler = SIG_DFL;
			act.sa_flags = 0;
			sigaction(signo, &act, NULL);

			// 리스트에서 제거
			t->prev->next = t->next;
			t->next->prev = t->prev;
			free(t);
			break;
		}
		else
			t = t->next;
	}
}

//////////////////////////////////////////////////////////////////////
// Function : void trapconnect(char **argvp)
// ============================================
// Input : command를 분리한 argument vector
// Output : 없음
// Purpose : 시그널 번호/이름으로 명령을 연결
//////////////////////////////////////////////////////////////////////
void	trapconnect(char **argvp)
{
	char				command[MAXSIZE] = {0};
	int					signo, i, j;
	struct sigaction	oldact, act;
	siglist_t			*t, *walker;

	// argvp의 인자수를 센다.
	i = 1;
	while(argvp[i] != NULL)
		i++;

	// argvp로 분리되어있는 명령을 합침
	for(j=1; j<i-1; j++)
	{
		strcat(command, argvp[j]);
		strcat(command, " ");
	}
	command[strlen(command)-1] = '\0';

	// command가 ' '로 쌓여있다면 제거함
	if(command[0] == '\'')
	{
		command[strlen(command)-1] = '\0';
		strcpy(command, command+1);
	}

	// 시그널 번호 찾음
	signo = issig(argvp[i-1]);

	// 시그널 정보(명령, 시그널 번호) 저장
	t = (siglist_t *)malloc(sizeof(siglist_t));
	t->command = (char *)malloc(strlen(command)+1);
	strcpy(t->command, command);
	t->signo = signo;

	// 기존에 해당 시그널 설정이 존재했으면 리스트 제거
	walker = sighead->next;
	while(walker != sigtail)
	{
		// 해당 시그널이 설정이 존재하면
		if(walker->signo == signo)
		{
			// 리스트에서 제거
			walker->prev->next = walker->next;
			walker->next->prev = walker->prev;
			free(walker);
			break;
		}
		else
			walker = walker->next;
	}

	// 시그널 처리(sigaction)
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigaction(signo, &act, NULL);

	// 시그널 리스트의 마지막에 추가
	t->prev = sigtail->prev;
	t->next = sigtail;
	sigtail->prev->next = t;
	sigtail->prev = t;
}

//////////////////////////////////////////////////////////////////////
// Function : void handler(int signo)
// ============================================
// Input : 시그널 번호
// Output : 없음
// Purpose : 시그널 번호에 해당하는 명령이 설정되어 있으면 수행
//////////////////////////////////////////////////////////////////////
void	handler(int signo)
{
	char		command[MAXSIZE] = {0};
	char		*buff;
	char		**argvp;
	int			buff_count, n;
	siglist_t	*t;

	// 해당 시그널에 해당하는 명령을 찾음
	t = sighead->next;
	while(t != sigtail)
	{
		if(t->signo == signo)
		{
			strcpy(command, t->command);
			break;
		}
		else
			t = t->next;
	}

	////////////////////////////////////////////////////////////////////////////
	//
	// [ 찾은 명령을 실행시킬 수 있게 char** 형태로 분해함 ]
	//
	// buff에 명령을 임시 저장
	buff = (char *)malloc(strlen(command)+1);
	strcpy(buff, command);

	// buff로 토큰의 수를 셈
	if(strtok(buff, " ") != NULL)
			for(buff_count = 1; strtok(NULL, " ") != NULL; buff_count++);

	// 각 토큰을 가리키는 포인터들이 들어갈 인자 배열 만듬
	argvp = (char **)malloc((buff_count+1)*sizeof(char *));

	// 토큰을 가리키는 포인터들을 인자 배열에 넣음
	*argvp = strtok(command, " ");
	for (n = 1; n < buff_count; n++)
	{
		*(argvp + n) = strtok(NULL, " ");

		// 인자 중에 백그라운드 표시가 있으면 체크하고 &는 argvp에 포함시키 않음
		if (strcmp(*(argvp +n), "&") == 0)
		{
			background = 1;
			buff_count -= 1;
		}
	}
	*(argvp + buff_count) = NULL;
	fputc('\n', stdout);
	//
	//
	////////////////////////////////////////////////////////////////////////////
	
	// 쉘 내부 명령이라면 수행하고 아니면 forkproc()함수로 수행
	if (incmdproc(argvp) == 0)
			forkproc(argvp);
}

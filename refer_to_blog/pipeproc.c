// (자)
// 파이프, 리다이렉션 명령어 처리

#include "mysh.h"

//////////////////////////////////////////////////////////////////////
// Function : int ispipe(char **argvp)
// ============================================
// Input : command를 분리한 argument vector
// Output : 명령어가 파이프 / 리다이렉션이면 1, 아니면 0
// Purpose : 명령어가 파이프 / 리다이렉션인지 여부 확인
//////////////////////////////////////////////////////////////////////
int		ispipe(char **argvp)
{
	int	n, check = 0;

	for(n=0; argvp[n]!=NULL; n++)
	{
		if(strcmp(argvp[n], "<") == 0)
		{
			check = 1;
			break;
		}
		else if(strcmp(argvp[n], ">") == 0)
		{
			check = 1;
			break;
		}
		else if(strcmp(argvp[n], ">>") == 0)
		{
			check = 1;
			break;
		}
		else if(strcmp(argvp[n], "|") == 0)
		{
			check = 1;
			break;
		}
		else
			check = 0;
	}

	return check;
}

//////////////////////////////////////////////////////////////////////
// Function : void pipeproc(char **argvp)
// ============================================
// Input : command를 분리한 argument vector
// Output : 없음
// Purpose : 명령어 내 파이프 / 리다이렉션 기호가 존재하면
// 그에 따른 처리를 해 줌
//////////////////////////////////////////////////////////////////////
void	pipeproc(char **argvp)
{
	int		n, i, j;
	int		subpid;
	int		status;
	int		exist = 0;
	int		fds[2];
	char	**argvp2 = (char **)malloc(16*sizeof(char *));

	// '|'를 찾아냄
	for(n=0; argvp[n]!=NULL; n++)
	{
		if(strcmp(argvp[n], "|") == 0)
		{
			exist = 1;
			break;
		}
	}

	// '|' 앞의 명령은 argvp로 뒷 명령은 argvp2로 옮김
	// '|'가 존재했다면
	if(exist)
	{
		argvp[n] = NULL;
		for(i=n+1, j=0; argvp[i]!=NULL; i++, j++)
		{
			argvp2[j] = (char *)malloc(strlen(argvp[i])+1);
			strcpy(argvp2[j], argvp[i]);
			argvp[i] = NULL;
		}
		argvp2[j] = NULL;
	}
	// '|'가 존재하지 않는다면
	else
	{
		argvp2 = argvp;
	}

	// '|'가 존재하면
	// fork()를 이용하여 각 명령어 처리
	if(exist)
	{
		// 파이프 처리
		pipe(fds);
		
		if((subpid = fork()) < 0)
		{
			perror("Can't fork process");
			exit(1);
		}
		// 자식 프로세스의 수행 결과는 표준 출력 보냄
		else if(subpid)
		{
			dup2(fds[1], STDOUT_FILENO);
			close(fds[0]);
			close(fds[1]);
			redirectproc(argvp);
			exit(1);
		}
		// 부모 프로세스일 경우 자식의 결과를 표준 입력으로 받음
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
	}
	// A|B 일 경우 B에 해당하는 부분 처리
	redirectproc(argvp2);
	exit(1);
}

//////////////////////////////////////////////////////////////////////
// Function : void redirection proc(char **argvp)
// ============================================
// Input : command를 분리한 argument vector
// Output : 없음
// Purpose : 명령 중에 리다이렉션이 포함되면 처리해 줌
//////////////////////////////////////////////////////////////////////
void	redirectproc(char **argvp)
{
	int		n;
	int		check[3] = {0};
	char	tmppath[MAXSIZE] = {0};

	// 명령어 내 어떤 리다이렉션 기호가 포함되어 있는지 확인
	for(n=0; argvp[n]!=NULL; n++)
	{
		if(strcmp(argvp[n], "<") == 0)
				check[0] = 1;
		else if(strcmp(argvp[n], ">") == 0)
				check[1] = 1;
		else if(strcmp(argvp[n], ">>") == 0)
				check[2] = 1;
	}

	// check의 경과에 따라서 '<' 또는 '>', '>>' 처리를 해줌
	if((check[1] == 1) || (check[2] == 1))
			redirectionout(argvp, check[1]);
	if(check[0] == 1)
			redirectionin(argvp);

	// 쉘 내부 명령어라면 수행하고 아니면 if문 내의 명령들로 수행
	if(incmdproc(argvp) == 0)
	{
		// 명령어가 myls, myfind, mygrap이라면 execv로 수행
		if((strcmp(*argvp, "myls") == 0) || (strcmp(*argvp, "myfind") == 0) ||
				(strcmp(*argvp, "mygrep") == 0))
		{
			sprintf(tmppath, "%s/%s/%s", abspath, *argvp, *argvp);
			execv(tmppath, argvp);
		}
		// 그 외 일반 리눅스 명령이라면 execvp로 수행
		else
		{
			execvp(*argvp, argvp);
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Function : void redirectionout(char **argvp, int choice)
// ============================================
// Input : command를 분리한 argument vector, '>' '>>' 구분 인자
// Output : 없음
// Purpose : 명령어 내 프로그램의 표준 출력을 파일로 재지향
//////////////////////////////////////////////////////////////////////
void	redirectionout(char **argvp, int choice)
{
	int	outfd, n;

	// 지향할 파일을 찾음
	for(n=0; argvp[n]!=NULL; n++)
	{
		if((strcmp(argvp[n], ">") == 0) || (strcmp(argvp[n], ">>") == 0))
				break;
	}

	// '>' 이였다면
	if(choice == 1)
	{
		// 지향할 파일을 염
		if((outfd = open(argvp[n+1], OUTFLAG, FMODE)) == -1)
				perror("Can't open file for redirection out");
	}
	// '>>' 이였다면
	else
	{
		// 지향할 파일을 염
		if((outfd = open(argvp[n+1], APPFLAG)) == -1)
				perror("Can't open file for redirection out");
	}

	// > 또는 >> 이므로 파일을 stdout으로 dup함
	if(dup2(outfd, STDOUT_FILENO) == -1)
			perror("Can't duplicate outfd to STDOUT_FILENO");

	// argvp에서 파일 부분을 제거한다.
	argvp[n] = NULL;
	argvp[n+1] = NULL;

	// outfd 닫음
	close(outfd);
}

//////////////////////////////////////////////////////////////////////
// Function : void redirectionin(char **argvp)
// ============================================
// Input : command를 분리한 argument vector
// Output : 없음
// Purpose : 명령어 내 프로그램의 표준 입력을 파일로 재지향
//////////////////////////////////////////////////////////////////////
void	redirectionin(char **argvp)
{
	int	infd, n;

	// 지향할 파일을 염
	if((infd = open(argvp[2], O_RDONLY)) == -1)
			perror("Can't open file for redirection in");

	// < 이므로 파일을 stdin으로 dup함
	if(dup2(infd, STDIN_FILENO) == -1)
			perror("Can't duplicate infd to STDIN_FILENO");

	// 수행할 프로그램만 argvp에 남겨둔다.
	for(n=0; argvp[n]!=NULL; n++)
			if(strcmp(argvp[n], "<") == 0)
					break;
	argvp[n] = NULL;
	argvp[n+1] = NULL;

	// infd 닫음
	close(infd);
}

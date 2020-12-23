// (차)
// 명령어 사용법 출력

#include "mysh.h"

//////////////////////////////////////////////////////////////////////
// Function : int showusage(char **argvp)
// ============================================
// Input : command를 분리한 argument vector
// Output : usage 출력하면 1 아니면 0
// Purpose : 명령어의 사용법 출력
//////////////////////////////////////////////////////////////////////
int		showusage(char **argvp)
{
	int n, check = 0;
	
	// --help 옵션이 있는지 확인
	for(n=0; argvp[n]!=NULL; n++);
	if(strcmp(argvp[n-1], "--help") == 0)
			check = 1;
	
	if(check == 1)
	{
		if(strcmp(argvp[0], "myls") == 0)
				usage_myls();
		else if(strcmp(argvp[0], "myfind") == 0)
				usage_myfind();
		else if(strcmp(argvp[0], "mygrep") == 0)
				usage_mygrep();
		else if(strcmp(argvp[0], "env") == 0)
				usage_env();
		else if(strcmp(argvp[0], "export") == 0)
				usage_export();
		else if(strcmp(argvp[0], "set") == 0)
				usage_set();
		else if(strcmp(argvp[0], "history") == 0)
				usage_history();
		else if(strcmp(argvp[0], "alias") == 0)
				usage_alias();
		else if(strcmp(argvp[0], "unalias") == 0)
				usage_unalias();
		else if(strcmp(argvp[0], "pwd") == 0)
				usage_pwd();
		else if(strcmp(argvp[0], "umask") == 0)
				usage_umask();
		else if(strcmp(argvp[0], "trap") == 0)
				usage_trap();
		else
				return 0;

		return 1;
	}
	else
			return 0;
}

void	usage_myls(void)
{
	printf("usage: myls [-ail] [path]\n");
	printf(" -a \t\t do not hide entries starting with .\n");
	printf(" -i \t\t print index number of each file\n");
	printf(" -l \t\t use a long listing format\n");
}

void	usage_myfind(void)
{
	printf("usage: myfind [path] [option] [pattern]\n");
	printf(" -name \t\t File's name matches pattern\n");
	printf(" -perm \t\t File's permmision matches pattern\n");
	printf(" -user \t\t File is owned by user pattern\n");
	printf(" -group \t\t File belongs to group pattern\n");
	printf(" -type \t\t File is of type pattern\n");
	printf("\t\t\t b\tblock (buffered) special\n");
	printf("\t\t\t c\tcharacter (unbuffered) specail\n");
	printf("\t\t\t d\tdirectory\n");
	printf("\t\t\t p\tnamed pipe (FIFO)\n");
	printf("\t\t\t f\tregular file\n");
	printf("\t\t\t l\tsymbolic link\n");
	printf("\t\t\t s\tsocket\n");
}

void	usage_mygrep(void)
{
	printf("usage: mygrep [-inR] [pattern] [path]\n");
	printf(" -i \t\t ignore case distinctions\n");
	printf(" -n \t\t print line number with output lines\n");
	printf(" -R \t\t handle directories to recurse\n");
}

void	usage_env(void)
{
	printf("usage: env\n");
}

void	usage_export(void)
{
	printf("usage: export [name[=value] ...]\n");
}

void	usage_set(void)
{
	printf("usage: set [arg ...]\n");
}

void	usage_history(void)
{
	printf("usage: history [-c] [-d offset] [n] or history -w [filename]\n");
	printf(" -c \t\t delete history list\n");
	printf(" -d \t\t delete offset of history list\n");
	printf(" n \t\t print history list of last [n] count\n");
	printf(" -w \t\t write history list to [filename]\n");
}

void	usage_alias(void)
{
	printf("usage: alias [name[=value] ...]\n");
}

void	usage_unalias(void)
{
	printf("usage: unalias [name ...]\n");
}

void	usage_pwd(void)
{
	printf("usage: pwd\n");
}

void	usage_umask(void)
{
	printf("usage: umask [-S] [mode]\n");
	printf(" -S \t\t print current umask\n");
}

void usage_trap(void)
{
	printf("usage: trap [arg] [signal_spec ...] or trap [-lp]\n");
	printf(" -l \t\t print trap signal_spec list\n");
	printf(" -p \t\t print setting trap list\n");
}

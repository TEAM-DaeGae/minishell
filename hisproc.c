// history 기능을 구현한 부분

#include "mysh.h"

list_t	*head;
list_t	*tail;

//////////////////////////////////////////////////////////////////////
// Function : void hisproc(char **argvp)
// ============================================
// Input : command를 분리한 argument vector
// Output : 없음
// Purpose : 각 옵션에 따른 각 함수 호출
//////////////////////////////////////////////////////////////////////
void	hisproc(char **argvp)
{
	if(argvp[1] == NULL)
			prn_list(argvp);
	else if(strcmp(argvp[1], "-c") == 0)
			del_list(argvp);
	else if(strcmp(argvp[1], "-d") == 0)
			del_list(argvp);
	else if(strcmp(argvp[1], "-w") == 0)
			sav_list(argvp);
	else if(atoi(argvp[1]) != 0)
			prn_list(argvp);
}

//////////////////////////////////////////////////////////////////////
// Function : void init_list(void)
// ============================================
// Input : 없음
// Output : 없음
// Purpose : history / alias list 초기화
//////////////////////////////////////////////////////////////////////
void	init_list(void)
{
	// history list 초기화
	hishead = (list_t *)malloc(sizeof(list_t));
	histail = (list_t *)malloc(sizeof(list_t));

	hishead->name = NULL;
	hishead->value = NULL;
	hishead->prev = hishead;
	hishead->next = histail;
	histail->name = NULL;
	histail->value = NULL;
	histail->prev = hishead;
	histail->next = histail;

	// alias list 초기화
	ahead = (list_t *)malloc(sizeof(list_t));
	atail = (list_t *)malloc(sizeof(list_t));
	
	ahead->name = NULL;
	ahead->value = NULL;
	ahead->prev = ahead;
	ahead->next = atail;
	atail->name = NULL;
	atail->value = NULL;
	atail->value = NULL;
	atail->prev = ahead;
	atail->next = atail;

	// history 내용 파일에서 메모리 공간으로 저장
	open_list();
}

//////////////////////////////////////////////////////////////////////
// Function : void open_list(void)
// ============================================
// Input : 없음
// Output : 없음
// Purpose : history 파일에서 history 목록을 읽어와서 history list에 저장
//////////////////////////////////////////////////////////////////////
void	open_list(void)
{
	FILE	*fp;
	char	line[MAXSIZE];
	char	*history;
	int		n, hismax;
	list_t	*t = hishead;
	list_t	*l;

	// 환경변수에서 history의 최대 크기를 받아옴
	hismax = atoi(getenv("HISTSIZE"));

	// 파일이 존재하면 내용을 읽어서 리스트 작성
	if((fp = fopen("history", "r")) > 0)
	{
		for(n=1; n<=hismax; n++)
		{
			// 파일에서 한줄 씩 읽어와서 history 리스트에 추가
			if(fgets(line, MAXSIZE, fp) > 0)
			{
				if(line[strlen(line)-1] == '\n')
						line[strlen(line)-1] = '\0';
				
				l = (list_t *)malloc(sizeof(list_t));
				l->value = (char *)malloc(strlen(line)+1);
				strcpy(l->value, line);

				l->prev = t;
				l->next = t->next;
				t->next->prev = l;
				t->next = l;

				t = t->next;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Function : void add_list(char *command)
// ============================================
// Input : command(명령어 한 라인)
// Output : 없음
// Purpose : 명령어 라인을 history list에 추가
//////////////////////////////////////////////////////////////////////
void	add_list(char *command)
{
	char	*tmp;
	list_t	*t;
	int		hismax = 1000;

	// history list가 꽉 찼으면 가장 앞에 노드 삭제
	if(hiscount == hismax)
	{
		t = hishead->next;
		t->prev->next = t->next;
		t->next->prev = t->prev;
		free(t);
	}

	// history list에 명령어 추가
	t = (list_t *)malloc(sizeof(list_t));
	t->value = (char *)malloc(strlen(command)+1);
	strcpy(t->value, command);
	
	t->prev = histail->prev;
	t->next = histail;
	histail->prev->next = t;
	histail->prev = t;
	
	hiscount++;
}

//////////////////////////////////////////////////////////////////////
// Function : void del_list(char **argvp)
// ============================================
// Input : command를 분리한 argument vector
// Output : 없음
// Purpose : history list에서 인자값에 따라서 목록 삭제
//////////////////////////////////////////////////////////////////////
void	del_list(char **argvp)
{
	int		n;
	list_t	*t, *del;

	// offset 위치의 history 삭제
	if(argvp[2] != 0)
	{
		n = atoi(argvp[2]);
		t = hishead;

		// offset 위치만큼 이동
		while(n > 0)
		{
			t = t->next;
			n--;
		}

		// offset이 history의 범위를 넘지 않았으면 삭제 수행
		if(t != hishead || t != histail)
		{
			t->prev->next = t->next;
			t->next->prev = t->prev;
			free(t);
			hiscount--;
		}
	}
	// history 전부 삭제
	else
	{
		t = hishead->next;
		while(t != histail)
		{
			del = t;
			t = t->next;
			free(del);
		}

		hishead->next = histail;
		histail->prev = hishead;
		hiscount = 0;
	}
}

//////////////////////////////////////////////////////////////////////
// Function : void prn_list(char **argvp)
// ============================================
// Input : command를 분리한 argument vector
// Output : 없음
// Purpose : history list 내용 화면에 출력
//////////////////////////////////////////////////////////////////////
void	prn_list(char **argvp)
{
	int		n;
	list_t	*t;

	// 인자가 없으면 history 전부 출력
	if(argvp[1] == 0)
	{
		t = hishead->next;
		while(t != histail)
		{
			printf("%s\n", t->value);
			t = t->next;
		}
	}
	// 출력 목록 개수가 지정되어 있으면
	else
	{
		n = atoi(argvp[1]);
		t = histail;

		// n개의 위치만큼 뒤에서부터 이동
		for(n; n>0; n--)
		{
			t = t->prev;
			if(t == hishead->next)
					break;
		}

		// 이동한 위치에서부터 마지막까지 출력
		while(t != histail)
		{
			printf("%s\n", t->value);
			t = t->next;
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Function : void sav_list(char **argvp)
// ============================================
// Input : command를 분리한 argument vector
// Output : 없음
// Purpose : 인자가 있으면 해당 파일에 없으면 history 파일에
// history 목록 출력
//////////////////////////////////////////////////////////////////////
void	sav_list(char **argvp)
{
	list_t	*t = hishead->next;
	FILE	*fp;

	// 파일이름이 없으면 history 파일 open
	if(argvp[2] == NULL)
			fp = fopen("history", "w");
	// 파일이름이 존재하면 해당 파일 open
	else
			fp = fopen(argvp[2], "w");

	// 열린 파일에 history list 출력
	while(t != histail)
	{
		fprintf(fp, "%s\n", t->value);
		t = t->next;
	}

	// 열린 파일 닫음
	fclose(fp);
}

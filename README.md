# 1. 과제 소개

> *The objective of this project is for you to **create a simple shell**. Yes, your own little bash or zsh. You will learn a lot about processes and file descriptors.*
>
> With Minishell, you’ll be able to travel through time and come back to problems people faced when Windows didn’t exist.



## 1.1. Instructions

- You must program ***a mini UNIX command interpreter***.

- 이 인터프리터는 명령 프롬프트(예를 들면 `$> `)를 띄워야하고, 사용자가 enter 키를 눌러 명령줄(command line)을 입력할 때 까지 기다려야 한다.

  - 프롬프트는 명령이 완전히 실행된 후에만 다시 표시된다.

- PATH 변수 및 상대/절대 경로에 기반한 실행 파일(The executable)을 올바르게 찾아 실행한다.

  - 실행 파일을 찾을 수없는 경우 오류 메시지를 표시하고 프롬프트를 다시 표시해야 한다.

- 다음과 같은 쉘 내장 함수를 구현한다.

  - `echo` (with option `-n`)
  - `cd` (with only relative or absolute path)
  - `pwd`
  - `export`
  - `unset`
  - `env` (without any options and any arguments)
  - `exit`

- `;` 로 명령어를 분리할 수 있어야 한다.

- 다음 기능을 일반 bash와 동일하게 동작해야하도록 구현한다.

  - multiline commands를 제외한 `'` , `"`  
  - file descriptor aggregation를 제외한 리다이렉션(`<`, `>`, `>>`)
  - 파이프(`|`) 
  - 환경변수(`$` followed by characters)
  - `$?` 
  - `ctrl-C`, `ctrl-D`, `ctrl-\` 

  

## 1.2. Allowed Functions

- malloc, free
- read, write, open, close,
- opendir, readdir, closedir
- getcwd, chdir
- stat, lstat, fstat
- fork, execve
- wait, waitpid, wait3, wait4
- signal, kill
- exit
- strerror, errno
- dup, dup2, pipe

## 1.3. Flow Chart

![image](https://user-images.githubusercontent.com/37580034/107724272-d4b8d580-6d26-11eb-9e3c-8a208f35b28a.png)




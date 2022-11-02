### 트리를 어떻게 만드는가?
1. root 우선순위 >= now 우선순위
	- now left에 root 달기
	- root update
2. root 우선순위 < now 우선순위
	- 1) now가 연산자인 경우
		- now left에 root right 달기
		- root right에 now 달기
	- 2) now가 연산자가 아닌 경우
		- now를 root의 오른쪽 끝 달기

### 트리 우선순위 (<< heredoc은 별도 로직으로 처리)
1. ||, &&
2. <, >, >>, |,
3. (괄호안 커맨드), CMD

### 처리해야 할 것
- token_type
	- string, pipe(|), command, '

### 케이스 정리
1. $ > pwd || ls
	- output: pwd

2. $ > pwd || ls && ls
	- output: ls

3. $ > pwd || (ls && ls)
	- output: pwd

4. ls&&ls
5. ls < |ls > out 
   - 뒤에 명령어도 실행되지 않음.

6. echo "str | " echo  " "| cat -e
	- output: str |  echo  $
7. echo "hello" || << ls : heredoc일 때는 || 무시한다.
	- 
8. grep "M" << ls |
	-
9. grep "M" << ls > out 
	- out에 담김
10. grep "M" << ls | >> out
	- out에 담기지 않음
11. echo '$fortytwo "axs"' "ahah"
	- $fortytwo "axs" ahah
	- ' '를 토큰에 담을 필요가 있나?
12.  grep "hello" && grep "h" << mks
13. (ls | ls && (ls && ls | ls)) || ls  >> filepath

```c
if (is_builtin < 0)
	return (-1);
if (lstat(command[0], &f) != -1)
{
	if (f.st_mode & S_IFDIR)
	{
		change_dir(command[0], 0);
		return (0);
	}
	else if (f.st_mode & S_IXUSR)
		return (run_cmd(ft_strdup(command[0]), command));
}
ft_putstr("minishell: command not found: ");
```
### 처리를 해야 하는가?
- 1. grep "M" |


### 처리순서
1. readinput
2. analyze input
	- 1) tokenize
	- 2) syntax check(< , <|)
	- 3) parse
3. execute
	- 1) traverse tree

### tokenize
1. 입력의 끝이 있으면 현재 판단 중인 문자열을 토큰으로 본다.
2. 이전 문자가  operator의 일부이면서 현재 문자가 따옴표가 아니고 이전 문자와 연결해서 opertor취급이 되면 operator의 일부임
3. 이전문자가 opertor 

###
1. 입력의 끝이 인식되면 현재 토큰(있는 경우)이 구분됩니다.
2. 이전 문자가 연산자의 일부로 사용되었고 현재 문자가 인용되지 않고 이전 문자와 함께 사용하여 연산자를 형성할 수 있는 경우 해당 (연산자) 토큰의 일부로 사용됩니다
3. 이전 문자가 연산자의 일부로 사용되었고 현재 문자를 이전 문자와 함께 사용하여 연산자를 구성할 수 없는 경우 이전 문자를 포함하는 연산자가 구분됩니다
4. 현재 문자가 <백슬래시>, 작은따옴표 또는 큰따옴표이고 인용되지 않은 경우 인용된 텍스트의 끝까지 후속 문자에 대한 인용에 영향을 미칩니다. 인용에 대한 규칙은 인용에 설명된 대로입니다.
5. 현재 문자가 따옴표 없는 '$' 또는 '`'인 경우 쉘은 매개변수 확장(매개변수 확장), 명령 대체(명령 대체)

### readline
- -lreadline 

### ctrl d
- 치다가 ctrl d 는 아무것도 안해야 하고, 아무것도 없는 상태에서 ctrl d는 종

### rl_replace_line
- terminal에서 eof를 날리면 
  	- 문자열이 buffer에 있으면 아무 응답 없고,
	- 문자열이 없다면 :D종료
		- :D없애주기 위해서 rl_replace_line이 필요. 
- -lreadline의 상세경로를 적어주면, exit가 개행이 포함되어 출력된다. 
	- $ gcc main.c -lreadline -L/opt/homebrew/opt/readline/lib/ -I /opt/homebrew/opt/readline/include
	- 이 경로를 추가하면 개행 추가. 
```c 
printf("\033[1A"); // 한줄 커서 위로(맨왼쪽끝)
printf("\033[7C"); // cursor move right
```


1.  

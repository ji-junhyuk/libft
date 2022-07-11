## try : 0%
> initial_errors: Files besides the allowed ones were found on repository
- 불필요한 헤더 선언 (stdddef.h)
- list.h 중복 선언 (불필요한 파일이 있으면 채점조차 되지 않음, norm error)
- static 사용 권장
- 과제 첫평가 받아보고, 실수 없으면 뒤에 평가 이어서 잡는게 옳다!

## 1 retry : 125%
> 1. bonus파트에서 인자 에러 처리를 할꺼면 일관되게 하자.
> t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
```c
lst에 대한 널 처리는 했지만, 함수포인터에 관해서 하지 않았다.
lst는 lstclear함수도 있고, 비어 있는 리스트를 받을 확률이 높기 때문에 널처리를 했다고 말하는게 좋았을 듯 싶다.
```
> 2. 모든 파일에 #include "libft.h"를 선언했다. 효율적이지 않다.
```c
libft.h가 필요하지 않은 함수에 대해선 선언하지 않는다.
libft과제에서 사용한 라이브러리는 <stdlib.h>와 <unistd.h>인데, 컴파일 시간까지 고려한다면 필요한 함수에서만 인클루드 해주는게 좋아보인다.
```
> 3. Makefile re 옵션
```Makefile
re: fclean all

fclean과 all이 병렬적으로 실행되기 때문에 오류날 가능성이 있다. 안전하게 직렬로 바꿔주어야 한다. (-j 옵션을 사용할 경우)

re:	
	make fclean
	make all
	
make re -j 6 (6하드코어 사용)
```

### > 개선사항 
1. ft_memchr
```c
return ((void *)&p[idx]);
// p[idx]라는 값에 접근하고 그 주소에 다시 접근하는 것보다 (p + idx)로 한번에 주소에 접근하는 게 효율적이다.
```
2. ft_strnstr
```c
while (*haystack && ++cnt <= len - ft_strlen(needle))
// 반복문을 돌 때마다 ft_strlen함수를 호출하는 것은 비효율적이다.
```
3. ft_strjoin
```c
ft_strcat(copy, s1);
ft_strcat(copy, s2);
// 이어붙일 때 처음부터 찾는 건 비효율적이다. s1의 길이만큼 당겨주도록 하자.
```
4. ft_lstadd_back
```
마지막 노드를 찾을 때 이미 구현된 함수(ft_lstlast)를 사용하자.
```
5. ft_strtrim
```
<map>
set이 담고 있는 문자를 1로 초기화한다. 모든 문자를 순회하는 것이 아닌(s1) map에 담긴 문자만 순회하면서 속도를 올릴 수 있다.
```

6. 나는 return문을 너무 많이 사용하고 있는 게 아닌가?
```
return문을 줄이면서 코드도 줄여진다면 줄이는게 맞다. 간결한 코드
```
# Libft
> 이 프로젝트의 목적은 흔히 쓰이는 함수들을 재구성하여 이후의 모든 프로젝트에서 사용될 C 라이브러리를 제작하는 것입니다.

## Contents
- [Libft](#libft)
  - [Contents](#contents)
  - [Part 1 - Libc functions](#part-1---libc-functions)
	- [ft_isalpha](#ft_isalpha)
	- [ft_isdigit](#ft_isdigit)
	- [ft_isalnum](#ft_isalnum)
	- [ft_isascii](#ft_isascii)
	- [ft_isprint](#ft_isprint)
	- [ft_toupper](#ft_toupper)
	- [ft_tolower](#ft_tolower)
	- [ft_strchr](#ft_strchr)
	- [ft_strrchr](#ft_strrchr)
	- [ft_strlen](#ft_strlen)
	- [ft_strncmp](#ft_strncmp)
	- [ft_strlcpy](#ft_strlcpy)
	- [ft_strlcat](#ft_strlcat)
	- [💫ft_strnstr](#ft_strnstr)
	- [ft_atoi](#ft_atoi)
	- [ft_memset](#ft_memset)
	- [ft_bzero](#ft_bzero)
	- [ft_memchr](#ft_memchr)
	- [ft_memcpy](#ft_memcpy)
	- [ft_memcmp](#ft_memcmp)
	- [ft_memmove](#ft_memmove)
	- [ft_calloc](#ft_calloc)
	- [ft_strdup](#ft_strdup)
  - [Part 2 - Additional functions](#part-2---additional-functions)
	- [ft_substr](#ft_substr)
	- [ft_strjoin](#ft_strjoin)
	- [ft_strtrim](#ft_strtrim)
	- [ft_split](#ft_split)
	- [ft_itoa](#ft_itoa)
	- [ft_strmapi](#ft_strmapi)
	- [ft_striteri](#ft_striteri)
	- [ft_putchar_fd](#ft_putchar_fd)
	- [ft_putstr_fd](#ft_putstr_fd)
	- [ft_putendl_fd](#ft_putendl_fd)
	- [ft_putnbr_fd](#ft_putnbr_fd)
  - [Bouns](#bouns)
	- [ft_lstnew](#ft_lstnew)
	- [ft_lstadd_front](#ft_lstadd_front)
	- [ft_lstsize](#ft_lstsize)
	- [ft_lstlast](#ft_lstlast)
	- [ft_lstadd_back](#ft_lstadd_back)
	- [ft_lstdelone](#ft_lstdelone)
	- [ft_lstclear](#ft_lstclear)
	- [ft_lstiter](#ft_lstiter)
	- [ft_lstmap](#ft_lstmap)
  - [Question](#question)
	- [size_t형에 대하여](#size_t형에-대하여)
	- [문자를 다루는 함수의 매개변수가 int형인 이유](#문자를-다루는-함수의-매개변수가-int형인-이유)
	- [void* 형에 대하여](#void*-형에-대하여)
	- [라이브러리 코드의 읽히는 부분이 const인 이유](#라이브러리-코드의-읽히는-부분이-const인-이유)
	- [const char * vs char const *](#const-char-*-vs-char-const-*)
	- [mapping에 대하여](#mapping에-대하여)
	- [정적(Static) 변수에 대하여](#정적(Static)-변수에-대하여)

## Part 1 - Libc functions

### ft_strlen
```c
size_t  ft_strlen(const char *s)
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

--------------------------------------------------

### ft_memset
```c
void    *memset(void *b, int c, size_t len);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_bzero
```c
void    ft_bzero(void *s, size_t n);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_memmove
```c
void    *ft_memmove(void *dst, const void *src, size_t len);
```
- ft_memcpy와 다른 점은 주소가 겹칠 때 비파괴복사를 수행한다는 것이다.

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_memcmp
```c
int ft_memcmp(const void *s1, const void *s2, size_t n);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_memchr
```c
void *memchr(const void *s, int c, size_t n)
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_memcpy
```c
void    *ft_memcpy(void *dst, const void *src, size_t n);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_isalpha
```c
int ft_isalpha(int c)
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

### ft_isdigit
```c
int ft_isdigit(int c)
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_isalnum
```c
int ft_isalnum(int c)
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_isascii
```c
int ft_isascii(int c)
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_isprint
```c
int ft_isprint(int c)
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---
### ft_toupper
```c
int ft_toupper(int c)
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---
### ft_tolower
```c
int ft_tolower(int c)
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---
### ft_strchr
```c
char    *ft_strchr(const char *s, int c);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_strrchr
```c
char    *ft_strrchr(const char *s, int c);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_strlcat
```c
size_t  strlcat(char * restrict dst, const char * restrict src, size_t dstsize);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_strlcpy
```c
size_t  strlcpy(char * restrict dst, const char * restrict src, size_t dstsize)
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_atoi
```c
int atoi(const char *str)
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

--------

### ft_strnstr
```c
char    *strnstr(const char *haystack, const char *needle, size_t len)
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_strncmp
```c
int ft_strncmp(const char *s1, const char *s2, size_t n)
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_calloc
```c
void    *ft_calloc(size_t count, size_t size);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_strdup
```c
char    *strdup(const char *s1);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

## Part 2 - Additional functions

### ft_substr
```c
char    *ft_substr(char const *s, unsigned int start, size_t len);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_strjoin
```c
char    *ft_strjoin(char const *s1, char const *s2);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_strtrim
```c
char    *ft_strtrim(char const *s1, char const *set);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_split
```c
char    **ft_split(char const *s, char c);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_itoa
```c
char    *ft_itoa(int n);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_strmapi
```c
char    *ft_strmapi(char const *s, char (*f)(unsigned int, char));
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_striteri
```c
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_putchar_fd
```c
void    ft_putchar_fd(char c, int fd);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_putstr_fd
```c
void ft_putstr_fd(char *s, int fd);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_putendl_fd
```c
void    ft_putendl_fd(char *s, int fd);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_putnbr_fd
```c
void    ft_putnbr_fd(int n, int fd);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

## Bouns

### ft_lstnew
```c
t_list	*ft_lstnew(void *content);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_lstsize
```c
int    ft_lstsize(t_list *lst);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_lstlast
```c
t_list    *ft_lstlast(t_list *lst);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_lstadd_front
```c
void    ft_lstadd_front(t_list **lst, t_list *new);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_lstadd_back
```c
void    ft_lstadd_back(t_list **lst, t_list *new);
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_lstdelone
```c
void    ft_lstdelone(t_list *lst, void (*del)(void*));
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_lstclear
```c
void    ft_lstclear(t_list **lst, void (*del)(void*));
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_lstiter
```c
void    ft_lstiter(t_list *lst, void (*f)(void *));
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---

### ft_lstmap
```c
t_list    *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
```

<div align = "right">
	<b><a href = "#Contents">↥ top</a></b>
</div>

---


## Issue

### 1. 왜 ar 명령어를 사용하여 라이브러리를 생성하여야 하고 libtool 명령어는 사용이 금지되었는가?
`ar`은 유닉스의 초창기부터 사용되었다고 한다. `libtool`은 동적 및 정적 라이브러리 모두 지원하는 GNU 도구이며 ar을 능가하는 훨씬 많은 기능을 가지고 있다고 한다.

단순히 정적 라이브러리를 위한 과제이므로 `ar`사용을 강제하는 것으로 보인다.

### 2. 왜 size_t 자료형을 사용할까? (unsigned int와 차이점)
시스템에서 어떤 객체나 값이 포함할 수 있는 최대 크기의 데이터를 표현하는 타입이다. 크기에 음수는 필요 없기에 unsigned형으로 나타낸다.

`size_t`의 경우 32비트 운영체제에서는 부호 없는 32비트 정수(unsigned int), 64비트 운영체제에서는 부호 없는 64비트 정수(unsigned long long)으로 `고정된 크기`를 가진다. 하지만 `unsigned int`는 `운영체제마다 크기가 다르다`.


### 3. const 위치에 따른 차이는 무엇인가?
> 1. 자료형 앞에 const가 오는 경우
- 포인터 변수 앞에 const가 오는 경우도 해당한다. ex) char **ft_split(char const *s, char c)
- 변수에 저장된 값의 변경을 허용하지 않는다.
```c
const double PI = 3.14;
PI = 3.141592; // error

int num1 = 42;
int num2 = 21;
const int *ptr = &num1;
ptr = &num2; // possible
*ptr = num2; // error
```
> 2. 변수 앞에 const가 오는 경우
- 변수 주소를 변경하는 것을 허용하지 않는다.
```c
int num1 = 42;
int num2 = 21;
int *const ptr = &num1;
*ptr = num2; // possible
ptr = &num2; // error
```
> 3. 둘 다 const가 오는 경우
- 값과 주소의 변경을 허용하지 않는다.
```c
int num1 = 42;
int num2 = 21;
const int *const ptr = &num1;
*ptr = num2; // error
ptr = &num2; // error
```
###  4. 정적(static) 변수의 특징은 무엇인가?
- `데이터영역`에 저장된다. 데이터 영역은 `프로그램의 시작과 함께 할당되며, 프로그램이 종료되면 소멸`한다.
- `자신이 선언된 소스 파일 안에서만 사용`할 수 있고, 외부에서는 가져다 쓸 수 없다.
- 선언과 동시에 0으로 초기화된다.
- 매개변수로 사용할 수 없다.

###  5. 메모리 관련 함수는 왜 unsigned char로 쓰는가?
- 컴퓨터의 정보 처리 단위는 1byte가 효율적이고, 메모리가 공간을 의미하고 공간에서 음수는 필요하지 않기에 unsigned char 로 계산한다.

### 6. 메모리 관련 함수와 문자열 함수 차이(memcpy, strcpy 등)
- 문자열의 끝은 NULL인 것에 반해, 메모리 영역은 NULL도 유효한 공간으로 보기 때문에 크기 n을 명시적으로 지정해주어야 한다.

### 7. memset의 동작방식
- memset은 1byte단위로 초기화를 한다. 1byte가 아닌 자료형에 대해선 0 과 -1 이외의 값으로 초기화하면 예상했던 결과와 다르다.
- 왜 -1은 제대로 작동할까? 2의 보수법을 취하는데 -1 은 바이트를 1로 초기화한다. 11111111 1111111 1111111 1111111은 -1을 나타내므로 제대로 동작하게 된다.
- 그렇다면 1초기화는 어떻게 동작할까?
```c
int arr[1];
memset(arr, 1, sizeof(int) * 1);
printf("%d ", (arr[0]));
```
> 내가 생각한 결과 00000001 00000001 00000001 00000001
> 실제 출력 결과 : 10000000 10000000 10000000 1 (1684309)
> 엔디안 방식(낮은 주소에 데이터의 낮은 바이트(LSB, Least Significant Bit)부터 저장)으로 출력되는 것을 확인할 수 있다. 

# get_next_line
> 이 프로젝트의 목적은 파일 디스크립터로부터 읽혀진, 개행으로 끝나는 한 줄을 반환하는 함수를 코드화 하는 것입니다.
```c
char *get_next_line(int fd); 
```
- [get_next_line](#get_next_line)
	- [💫평가](#평가)
	- [💫개선사항](#개선사항)
	- [💫생각해보기](#생각해보기)
## 평가
### try : 62%(crash)
1. crash
	- read에 실패했을 경우 temp[-1]에 접근한다.
```c
while (!ft_strchr(temp, '\n'))
{
	read_size = read(fd, temp, BUFFER_SIZE);
	temp[read_size] = '\0';
	if (read_size == 0)
		break ;
	if (read_size == -1)
	{
		if (buffer)
			free(buffer);
		return (0);
	}
```

2. ssize_t
	- read의 리턴 값은 int가 아니라 ssize_t다.
```c
int read_size;
```

3. 불필요한 리턴문
```c
next_line = ft_substr(buffer, len + 1, ft_strlen(buffer + len + 1));
//if (!next_line)
//{
//	free(buffer);
//	return (0);
//}
free(buffer);
return (next_line);
```

4. 읽기에 실패하면 NULL이 반환된다. NULL이 반환되는 이유를 모른다. #error 전처리기 지시문을 사용해보자.
```c
#if BUFFER_SIZE < 1
# error invalid BUFFER_SIZE
#endif
```

## 개선사항
1. malloc은 운영체제에서 메모리를 할당받는 비용이 큰 함수이다. change_next_line에서 ft_substr(), free()에서 `ft_memmove`를 통해 효율적으로 개선할 수 있다.
2. open_max값은 사용자가 임의로 변경할 수 있다.
```bash
$ ulimit -a 
$ ulimit -n 49152 // 클러스터 아이맥 기준
```
3. list로 구현하든 배열로 구현하든 trade-off라고 생각한다. 장단점을 말하기.

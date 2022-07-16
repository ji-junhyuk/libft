# get_next_line
> 이 프로젝트의 목적은 파일 디스크립터로부터 읽혀진, 개행으로 끝나는 한 줄을 반환하는 함수를 코드화 하는 것입니다.
```c
char *get_next_line(int fd); 
```
- [get_next_line](#get_next_line)
	- [💫평가](#평가)
	- [개선사항](#개선사항)
	- [알아가기](#알아가기)
	- [참고자료](#참고자료)
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
$ ulimit -n 49152 // 클러스터 아이맥 기준 최대값
```
3. list로 구현하든 배열로 구현하든 trade-off라고 생각한다. 장단점을 말하기.
4. list로 구현해보기.

### 생각해보기
	- 엄청 큰 파일에서 BUFFER_SIZE가 매우 작은 경우
	- 작은 파일에서 BUFFER_SIZE가 매우 큰 경우
## 알아가기

### ssize_t는 무엇인가요?
- ssize_t는 `signed size type`로서 반환값으로 해당 `IO 함수의 실패여부`를 알려준다.

### 정적(static) 변수는 무엇인가요?
- 프로그램이 운영체제로 부터 할당받는 대표적인 메모리 공간은 1. `코드(code)영역` 2.`데이터(data)` 3.`스택(stack)` 4.`힙(heap)` 영역이 있다. 
- `정젹(static) 변수`는 `데이터(data)영역`에 할당되며, 데이터 영역은 `프로그램의 시작 시 할당`되고 `종료되면 소멸`한다.

### CTRL-D와 CTRL_C의 차이는 무엇인가요?
- CTRL-D는 `파일의 끝(eof)`을 의미합니다.
- CTRL-C는 `중단`을 의미합니다. 즉, 수행 중인 작업을 중지합니다. 기술적으로 많은 프로그램에서 최상위 수준으로 돌아가는 INT 신호를 보냅니다 .
 
### 리다이렉션이란 무엇인가요?
-  리다이렉션(Redirection)이란 방향을 변경하는 것을 의미합니다. `표준 입력`을 받거나 `표준 출력`을 하는 것 뿐만 아니라, `파일로 표준 입력`을 받고, `파일로 표준 출력을 받는 등의 기능`을 할 수 있습니다.
	- `<` : 파일의 내용을 명령어의 입력으로 사용합니다.
	- `>` : 명령어의 결과(표준 출력)를 파일에 덮어씁니다.
	- `>>` : 명령어의 결과를 파일에 추가합니다.
- 사용법
	- [명령어] 1>[파일] : [명령어] > [파일] 과 같은 의미로, 표준 출력을 [파일]에 덮어씁니다.
	- [명령어] 2>[파일] : [명령어] 실행 시, 에러가 발생한다면, 에러 내용을 [파일]에 덮어씁니다.
	- [명령어] 1>[파일] 2>[파일2] : [명령어] 실행 시, 결과는 [파일]에, 에러는 [파일 2]에 덮어씁니다.
	- [명령어] 1>[파일] 2>[파일] : [명령어] 실행 시, 표준 출려과 에러를 모두 [파일]에 씁니다. 
		- `[명령어] 1> [파일] 2> /dev/null` : 표준 에러(stderr)는 표시되지 않고, 아예 삭제됩니다.
		- `[명령어] > [파일] 2>&1` : 표준 출력(stdout)을 [파일]에 쓰고, 표준 에러(2)를 &1로 보내라는(>) 의미입니다. 이때 &1은, 표준 출력(1)으로 보내는데 백그라운드(&)로 보내라는 의미이다. (백그라운드는 화면에 보이지 말고, 안 보이게 처리해라는 의미)

### 파이프(|)와 리다이렉션의 차이점은 무엇인가요?
- Pipe는 출력을 다른 프로그램 이나 유틸리티 로 넘길 때 사용합니다.
- Redirection은 출력을 파일 이나 스트림으로 넘길 때 사용합니다.

---

### 파일 디스크립터
- 시스템으로부터 할당받은, 파일(File)을 대표하는 음수가 아닌 정수

### > 1. FD table
- File Descriptor Table이며, 머신 단위가 아니라 프로세스 단위로 할당되는 테이블
- 프로세스가 생성되면 기본적으로 0(stdin, 표준 입력), 1(stdout, 표준 출력), 2(stderr, 표준 에러) `index`가 활성화된다. 해당 공간에는 `File table의 주소`를 갖게 된다.

### > 2. File table
- FD Table이 프로세스 단위로 할당되었다면, File Table은 머신 단위의 할당으로 생성된다. 
- 프로세스에 의해 open된 파일의 읽기/쓰기 동작을 지원하기 위한 테이블. 파일이 열릴 때마다 하나씩 할당된다. 따라서, 만약 하나의 프로세스가 A라는 파일을 3번 open한다면, A의 File Table Entry가 3개 생성된다.
- 이 테이블 Entry 안에는 open_flag, file_offset, ref_cnt, VFS table을 가리키는 포인터가 들어있다.

### > 3. VFS i-node(Virtual File System)
- 프로세스들이 사용하고 있는 파일의 i-node를 담고 있는 테이블이다. File Table과는 달리, 만약 하나의 프로세스가 A라는 파일을 3번 open해도 i-node Table Entry는 하나밖에 할당되지 않는다.
- inode를 전체적으로 탐색하게 되면 파일 시스템에 대한 액세스 성능이 굉장히 좋지 않으므로, 이를 극복하기 위해 파일을 열 때마다 사용된 inode를 기록하는 행위가 발생한다. 이 때 기록되는 공간이 VFS inode Cache이며, 내부적으로 기록하며 유지하는 inode는 고유하다. 따라서 파일이 열리게 되면 VFS inode Cache를 먼저 탐색한 후에 전체 탐색에 들어가게 된다.

### > 파일 디스크립터가 할당되는 과정
> fd = open("A", O_WRONLY);
1. 커널은 파일시스템에서 파일 A를 찾아 해당 파일의 i-node를 이용해 vfs inode table에 빈 공간에 할당한다. 만약 A의 i-node가 이미 할당되어있는 경우, ref_cnt(reference counter)만 하나 증가시킨다.
2. i-node에 파일에 쓰기권한이 있는지 확인한다.
3. 권한이 있다면 file table의 Entry에 open_flag, file_offset, ref_cnt, VFS i-node table entry 포인터 등의 정보를 할당
4. File descriptor table을 index 0부터 탐색하여, (fd가) 할당되지 않은 index에 file table entry를 가리키는 포인터를 저장한다.
5. 저장한 곳의 index를 반환한다.

---

### 운영체제
- 컴퓨터는 크게 하드웨어와 소프트웨어로 구분된다.
- 소프트웨어는 운영체제와 응용 프로그램으로 다시 구분된다.
- 운영체제는 커널과 시스템 프로그램으로 구분된다.
cf. 커널과 함께 시스템 프로그램, 뿐만 아니라 이들을 쉽게 설치할 수 있는 기능까지 제공하는 것을 '배포판'이라고 한다.
- '운영체제'는 커널과 함께 사용자 편의를 위한 시스템 프로그램을 포함한다.
- '커널'은 컴퓨터 자원을 관리하는 운영체제의 핵심 부분을 말한다.
	- 추상화란 물리적으로 하나 뿐인 하드웨어를 여러 사용자들이 번갈아 사용하게 중재함으로서, 마치 한 개의 하드웨어가 여러개인 것처럼 보여지도록 하는 기술을 말한다.
	- 커널이 추상화하여 관리하는 물리적 자원들과 이를 추상화한 자원을 칭하는 용어 간 대응 관계는 아래와 같다.
```
CPU : 태스크(task)

메모리 : 페이지(page), 세그먼트(segment)

디스크 : 파일(file)

네트워크 : 소켓(socket)
```

- 커널을 구성하는 자원 관리자들은 아래와 같이 크게 5가지
	1. 태스크(task)관리자
	2. 메모리(memory)관리자
	3. 파일 시스템(file system)관리자
	4. 네트워크(network)관리자
	5. 디바이스 드라이버(device driver)관리자
- 커널은 사용자가 물리적인 하드웨어에 접근하고 사용할 수 있도록 돕는 역할을 한다.
 
## 참고자료
- 메모리구조http://www.tcpschool.com/c/c_memory_structure#:~:text=%EB%A9%94%EB%AA%A8%EB%A6%AC%EC%9D%98%20%EC%8A%A4%ED%83%9D(stack)%20%EC%98%81%EC%97%AD,(stack%20frame)%EC%9D%B4%EB%9D%BC%EA%B3%A0%20%ED%95%A9%EB%8B%88%EB%8B%A4.
- CTRL-C와 CTRL-D의 차이 https://superuser.com/questions/169051/whats-the-difference-between-c-and-d-for-unix-mac-os-x-terminal#:~:text=Ctrl%20C%20tells%20the%20terminal,as%20a%20desire%20to%20exit.
- 파이프와 리다이렉션의 차이 https://rottk.tistory.com/entry/Redirection%EA%B3%BC-Pipe%EC%9D%98-%EC%B0%A8%EC%9D%B4%EA%B0%80-%EB%AC%B4%EC%97%87%EC%9D%B8%EA%B0%80%EC%9A%94
- bash 리다이렉션 https://bio-info.tistory.com/87
- FD가 할당되는 과정 https://m.blog.naver.com/songblue61/221391888403
- 파일 등등 https://bigpel66.oopy.io/library/42/inner-circle/3 
- 커널의 개념과 커널의 구조 https://5equal0.tistory.com/entry/Linux-Kernel-%EC%BB%A4%EB%84%90%EC%9D%98-%EA%B0%9C%EB%85%90%EA%B3%BC-%EC%BB%A4%EB%84%90%EC%9D%98-%EA%B5%AC%EC%A1%B0

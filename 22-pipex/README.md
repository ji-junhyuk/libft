# pipex

### pipe
```c
#include <unistd.h>

int	pipe(int fildes[2]);
```
- `create descriptor pair` for interprocess communication.
- allows `unidirectional` data flow.
- By convention, fd[0]: read_end, fd[1]: write_end
	- Data written to file[1] appears on file[0].
- pipe persists until all of its associated descriptors are closed.
- return
	- success	: 0
	- fail		: -1

### dup
```c
#include <unistd.h>

int dup(int oldfd) 
```
![1](https://user-images.githubusercontent.com/67992469/192779576-e4d296e1-3978-4e29-977d-f21f0db1c127.png)
- duplicates an existing object descriptor
	- The new descriptor returned by the call is the `lowest numbered descriptor` currently not in use by the process.
	- if the copy successful, original and copy file descriptors may be `used interchangeably`.
	- both refer to the same open file description and thus `share file offset` and `file status flags`.
### dup2
```c
#include <unistd.h>

int dup2(int oldfd, int newfd);
```
- if the descriptor newfd was previously open, it is silently close before being reused.
- if oldfd is not a valid file descriptor, the call fails, and newfd is not closed.
- if oldfd is a valid file descriptor, and newfd has the same value as oldfd, then dup2() does nothing, and returns newfd.
- calling the printf function after calling dup2(fd, STDOUT_FILENO); writes to the file opened with fd.

### execve
```c
#include <unistd.h>

int execve(const char *path, char *const argv[], char *const envp[])
```
- 프로세스는 exec 호출로 프로그램 이미지가 바뀌어도 다음은 변하지 않는다.
	- 프로세스 ID, 부모 프로세스 ID, 프로세스 그룹 ID, 세션 ID
	- 실제 사용자 ID, 실제 그룹 ID, 보조 그룹 ID
	- 현재 디렉토리, root 디렉토리
	- 지연 시그널, alarm 발생까지 남은 시간
	- 지원 제약, tms_utime, tms_stime, tms_cutime
	- 파일 생성 모드의 마스크, 프로세스 시그널 마스

### wait
```c
#include <sys/wait.h>

pid_t	wait(int *stat_loc);
```
- wait 함수는 여러 개의 자식 프로세스 중에 어느 하나라도 종료하면 종료한 자식 프로세스 ID를 반환합니다. 만약 종료하는 프로세스가 없으면 블록 상태로 계속 기다립니다. 그리고 종료 상태값은 staloc에 저장됩니다. 만약 자식 프로세스가 없을 때에는 -1을 리턴합니다.

### waitpid
```c
#include <sys/wait.h>

pid_t	waitpid(pid_t pid, int *stat_loc, int options);
```
- waitpid 함수는 프로세스 id를 첫 번째 인자로 전달할 수 있으며 이 값에 따라 대기할 프로세스는 달라집니다. 양수는 해당 pid값을 갖는 자식 프로세스를 기다립니다. 0일 때는 자신과 같은 그룹에 있는 프로세스의 자식 프로세스의 종료를 기다립니다. -1일 때는 모든 하위 프로세스를 기다리며 -1보다 작은 값일 때는 절대값과 같은 자식 프로세스의 종료를 기다립니다.

그리고 세 번째 인자로 옵션을 전달할 수 있으며 WNOHANG일 때는 종료를 기다리지 않고 바로 리턴합니다. 이는 이미 종료한 프로세스의 종료 상태값을 확인하기 위한 목적으로 사용합니다. 그리고 WUNTRACED일 때는 종료 뿐만 아니라 멈춤일 때에도 반환합니다.

### unlink
```c
#include <unistd.h >

int unlink(const char *pathname);
```
- 반환 값: 실패 시 -1, 성공 시 0
- unlink는 파일의 연결 계수를 1 줄이는 시스템 호출입니다. 만약 unlink 호출 시 연결 계수를 줄였을 때 연결 계수가 0이면 파일을 삭제합니다. 만약 현재 특정 프로세스에서 해당 파일을 사용 중일 때 unlink 함수를 호출하면 연결 계수를 1 줄여도 0이 아닙니다. 이 때는 파일을 바로 삭제하지 않고 해당 파일에 접근하고 있는 작업이 모두 완료하여 연결 계수가 0으로 바뀌면 삭제합니다.

### access
```c
#include <unistd.h >

int access(const char *pathname, int mode);
```
- 반환 값: 실패 시 -1, 성공 시 0

- access 함수의 두 번째 입력 매개 변수에는 확인하고자 하는 모드를 전달할 수 있으며 다음의 네 개의 매크로 상수를 정의하고 있습니다.
	- R_OK: 읽기 권한 확인
	- W_OK: 쓰기 권한 확인
	- X_OK: 실행 권한 확인
	- F_OK: 파일 존재 여부 확인

## Subject
### Allowed function
```c
open, close, read, write,
malloc, free, `perror`,
`strerror`, `access`, `dup`, `dup2`,
`execve`, exit, `fork`, `pipe`,
`unlink`, `wait`, `waitpid`
```

### Mandatory
```c
/pipex file1 cmd1 cmd2 file2
```
- It must take 4 arguments:
	- file1 and file2 are `file names`.
	- cmd1 and cmd2 are `shell commands` with their parameters.
- example
```c
./pipex infile "ls -l" "wc -l" outfile

- Should behave like: < infile ls -l | wc -l > outfile
```
```c
./pipex infile "grep a1" "wc -w" outfile

- Should behave like: < infile grep a1 | wc -w > outfile
```

### Bonus
- Handle multiple pipes.
- example
```c
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2

- Should behave like: < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```

- Support « and » when the first parameter is "here_doc".
- example
```c
./pipex here_doc LIMITER cmd cmd1 file

- Should behave like: cmd << LIMITER | cmd1 >> file
```

## 참고자료
- 리다이렉션 2>&1 https://inpa.tistory.com/entry/%EB%A6%AC%EB%88%85%EC%8A%A4-devnull-%EB%A6%AC%EB%8B%A4%EC%9D%B4%EB%A0%89%EC%85%98-%EA%B8%B0%ED%98%B8-%EC%A2%85%EB%A5%98

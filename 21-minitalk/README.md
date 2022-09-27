# 09.26(월) ~ 09.27(화)
- minitalk 마무리.
- 통신
### Mandatory
```c
SERVER         |          CLIENT
                          1. KILL(bit)
						  2. usleep()
while (1)
	3.pause;
```
- 깨어나면, 비트를 저장하여 출력하는 역할을 수행한다.
- 2.usleep을 하는 이유는 무엇일까? KILL을 보내고, SERVER에서 비트를 저장하여 출력하는데, 저장하거나 출력하는 일련의 과정에서 KILL이 또 한번 들어온다면 KILL -> (처리되지 않음) -> KILL이 되어 기존 작업이 interrrupt로 소실되게 된다(비트 저장 못하고 사라짐). 
- usleep을 50한 이유는 Server가 비트를 처리하기까지 기다려주는 시간이다.(5분동안 출력하는 긴 문자열도 터지지 않는다)
- 3. pause를 쓰는 이유는 클라이언트에서 비트를 몇개 받았는지 기록하기 위함이다. pause를 쓰지 않는다면, interrupt횟수를 count하는 전역변수가 하나 더 필요하게 된다. (전역 변수 하나는 비트를 저장하는 char형 변수를 선언한다, 어떤 시그널을 받지 모르기에 이는 전역변수가 합당하다.)

### BONUS(양방향 통신)
```c
SERVER			|			CLIENT
							1. usleep()
							2. KILL(bit)
							3. pause()
void signal()
{
	5. 비트저장() // 0번 비트는 저장하지 않음, 이 단계가 없
	6. usleep()
	7. kill() // 비트를 잘 받았다고 보내줌
}
while (1)
{
	4. pause();
	8. 한 바이트를 받으면 출력 후 초기화
}
```
- 흐름을 보면, CLIENT는 1.usleep을 하고 KILL을 통해 pause 중인 SERVER를 깨우고, 자신은 pause를 한다. 깨어난 Server는 5.usleep을 한 후 KILL을 한다.
- 1번 usleep은 왜 하는 걸까?
	- interrupt가 들어오면, 핸들러 함수를 처리하면서 kill을 보낸다. 여기서 8번의 과정이 남아 있을 수 있다. 바로 kill을 보내게 되면 pause하고 있는 클라이언트가 다시 kill(비트를 보내기 때문에) 출력하지 못하고 클라이언트 interrupt로 인해 과정이 소실된다. (터미널에 이상한 문자열이 계속 출력되는 경우가 여기에 해당한다)
- 6번 usleep은 왜 하는 걸까?
	- 테스트해보았을 때 KILL(client->server), KILL(server->client)가 그 아랫줄 pause가 실행되기 전에 일어날 수 있다(신호 부하를 주었을 떄 그렇다)
		- 이 상황은 교착상태가 일어나 deadlock에 빠지게 된다. (문자열이 멈춘 경우가 여기에 해당한다)

###  signal vs sigaction
- signal은 사용하지 않는 것이 좋다. 호출 시 default핸들러를 설정하기 때문에 신호 2개가 연달아오면 핸들러 설정에 있어서 경쟁상태가 된다.
 
- sigaction
sigaddset, sigemptyset을 활용하려면 sigprocmask를 통해 특정 신호를
block하거나 unblock할 수 있다. (SIGKILL, SIGSTOP 제외)

https://stackoverflow.com/questions/231912/what-is-the-difference-between-sigaction-and-signal

# 09,25(일)
- 무슨 이유에서 터지는지 모르겠다. 영어문자도 안보내짐.
 
# 09.23(금)
- 한빈이와 한빈이컴퓨터로 보너스 구현까지 완료
	- usleep과 pause와 kill, sigaction을 통한 양방향 통신
	- bit를 쪼갤 때, 비트연산하는 재귀함수와 Unicode를 처리하기 위한 2진수의 보수.(유니코드는 앞자리가 1로 시작해서 음수를 읽는데, 기존 방식에서는 ascii를 양수로 읽는다. 아 이부분도 정말 헤매면서 결론을 냈는데, 헷갈리네.
 
- 일요일날 할 것
	 - [O] 처음부터 코드 작성하고 완성까지.
	 - [O] 필요한 개념들 핵심만 보기 좋게 정리.


## allowd functions
### signal
```c
#include <signal.h>

void (*signal(int sig, void (*func)(int)))(int);

typedef void (*sig_t) (int);
sig_t signal(int sig, sig_t func);
```
- SIGKILL 및 SIGSTOP 신호를 제외하고, signal() 함수를 사용하면 신호를 포착하거나 무시하거나 인터럽트를 생성할 수 있다. 
- signal을 사용하면 도메인 외부에서 프로세스를 조작할 수 있을 뿐만 아니라 해당 프로세스 자식 프로세스를 조작할 수 있다.
- SIG_DFL은 기본 동작을 재설정한다. 신호를 무시하려면 func가 SIG_IGN이어야 한다.
- SIG_IGN을 사용하지 않으면 신호의 추가 발생이 자동으로 차단되고 func가 호출된다.
- `처리된 신호는 함수가 반환될 때 차단 해제되고 신호가 발생했을 때 중단된 위치에서 프로세스가 계속`됩니다. 

#### return value
- 호출이 성공하면 이전 작업이 반환됩니다.
- 그렇지 않으면 SIG_ERR이 반환되고 전역 변수 errno가 오류를 나타내도록 설정됩니다.

### sigaction
```
#include <signal.h>

struct  sigaction {
	 union __sigaction_u __sigaction_u;		/* signal handler */
	 sigset_t sa_mask;						/* signal mask to apply */
	 int     sa_flags;						/* see signal options below */
};

union __sigaction_u {
	 void    (*__sa_handler)(int);
	 void    (*__sa_sigaction)(int, siginfo_t *, void *);
};

int		sigaction(int sig, const struct sigaction *restrict act, struct sigaction *restrict oact);
```
- 일반적으로 `신호는 더 이상 발생하지 못하도록 차단`되고 `현재 프로세스 컨텍스트가 저장되고 새 컨텍스트가 작성`됩니다. 
- 프로세스는 `신호가 전달되는 핸들러를 지정하거나 신호가 무시되도록 지정`할 수 있습니다.
- 프로세스는 신호가 발생할 때 시스템이 `기본 조치`를 취하도록 지정할 수도 있습니다.
- `신호도 차단될 수 있으며`, 이 경우 차단 해제될 때까지 `전달이 연기`됩니다.
- 일반적으로 `신호 처리기는 프로세스의 현재 스택에서 실행`됩니다. 이것은 신호가 `특별한 신호 스택에서 취해지도록 핸들러별로 변경될 수 있습니다`.
- 신호 루틴(Signal routines)은 일반적으로 호출을 차단한 신호로 실행되지만 다른 신호가 아직 발생할 수 있습니다.
- 전역 신호 마스크(global signal mask)는 현재 프로세스로의 `전달이 차단된 신호 집합`을 정의합니다. 프로세스의 신호 마스크는 상위(보통 비어 있음)의 신호 마스크에서 초기화됩니다. sigprocmask(2) 호출로 변경되거나 신호가 프로세스에 전달될 때 변경될 수 있습니다.
프로세스.
- 신호는 프로세스가 운영 체제에 진입할 때마다 전달될 수 있습니다(예: 시스템 호출, 페이지 폴트 또는 트랩, 또는 클록 인터럽트 동안).
- 여러 신호를 동시에 전달할 준비가 된 경우 트랩으로 인해 발생할 수 있는 모든 신호가 먼저 전달됩니다.
- `추가 신호는 동시에 처리될 수 있으며`, 각 신호는 `첫 번째 명령 이전에 이전 신호에 대한 처리기를 인터럽트하는 것`으로 나타납니다.
- `보류 중인 신호 세트는 sigpending(2) 시스템 호출에 의해 반환`됩니다.
- 포착된 신호가 전달되면 프로세스의 현재 상태가 저장되고 새 신호 마스크가 계산되며(아래 설명 참조) 신호 처리기가 호출됩니다.
- 핸들러에 대한 호출은 신호 처리 루틴이 정상적으로 반환되면 프로세스가 신호 전달 이전부터 컨텍스트에서 실행을 재개하도록 정렬됩니다.
- 프로세스가 다른 컨텍스트에서 재개하려면 이전 컨텍스트 자체를 복원하도록 정렬해야 합니다.
- 신호가 프로세스에 전달되면 프로세스의 신호 처리기 동안(또는 sigprocmask(2) 시스템 호출이 수행될 때까지) 새 신호 마스크가 설치됩니다.
- 이 마스크는 현재 신호 마스크 세트, 전달될 신호 및 호출할 핸들러와 관련된 신호 마스크의 합집합을 취함으로써 형성됩니다.
- sigaction() 시스템 호출은 `sig로 지정된 신호에 대한 작업을 할당`합니다.
- act가 0이 아니면 지정된 신호를 전달할 때 사용할 액션(SIG_DFL, SIG_IGN 또는 핸들러 루틴)과 마스크를 지정합니다.
- oact가 0이 아니면 신호에 대한 이전 처리 정보가 사용자에게 반환됩니다.
- 신호 처리기가 설치되면 일반적으로 다른 `sigaction() 시스템 호출이 수행되거나 execve(2)가 수행될 때까지` 설치된 상태로 유지됩니다.
- 신호별 기본 동작은 sa_handler를 SIG_DFL로 설정하여 재설정할 수 있습니다.
- sa_handler가 `SIG_DFL`이면 `신호에 대한 기본 동작은 신호를 버리는 것`이고, `신호가 보류 중`이면 신호가 `마스킹되더라도 보류 중인 신호는 폐기`됩니다.
- sa_handler가 SIG_IGN으로 설정되면 신호의 현재 및 보류 중인 인스턴스가 무시되고 폐기됩니다.
 
### sigemptyset
```
#include <signal.h>

int sigaddset(sigset_t *set, int signo);
int sigdelset(sigset_t *set, int signo);
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigismember(const sigset_t *set, int signo);
```	
- 이 함수는 sigset_t에 저장된 신호 세트를 조작합니다. sigemptyset() 또는 sigfillset()은 객체를 다른 용도로 사용하기 전에 sigset_t 유형의 모든 객체에 대해 호출해야 합니다.
	- `sigemptyset()` 함수는 신호 세트를 비어 있도록 초기화합니다.
	- `sigfillset()` 함수는 모든 신호를 포함하도록 신호 세트를 초기화합니다.
	- `sigaddset()` 함수는 지정된 신호 signo를 신호 세트에 추가합니다.
	- `sigdelset()` 함수는 신호 세트에서 지정된 신호 signo를 삭제합니다.
	- `sigismember()` 함수는 지정된 신호 signo가 신호 세트에 포함되어 있는지 여부를 반환합니다.
- 이러한 기능은 포함 파일 <signal.h>에 매크로로 제공됩니다. 이름이 정의되지 않은 경우 실제 함수를 사용할 수 있습니다(#undef 이름 포함).
- sigismember() 함수는 신호가 집합의 구성원이면 1을 반환하고 그렇지 않으면 0을 반환합니다. 다른 함수는 0을 반환합니다.
 
#### return value
- sigismember() 함수는 신호가 집합의 구성원이면 1을 반환하고 그렇지 않으면 0을 반환합니다. 다른 함수는 0을 반환합니다.

### kill
- man 2 kill
```c
int kill(pid_t pid, int signo);
```
- pid: signal을 보낼 대상
	- 0: 자신이 속한 process group 내 모든 process
	- -1: 현재 process가 가진 권한으로 signal을 보낼 수 있는 모든 process
	- < -1: GID == |pid| 인 process group
- signo: 보낼 시그널 번호
- Return
	- 0: Success
	- -1: Fail
		- errno = EINVAL -> 유효하지 않은 signo
		- errno = EPERM -> signal을 보낼 권한이 없음
		- errno = ESRCH -> 대상 process가 존재하지 않음(or zombie)

### getpid
```
#include <unistd.h>

pid_t
getpid(void);

pid_t
getppid(void);
```
- getpid()는 호출 프로세스의 프로세스 ID를 반환합니다. ID는 고유한 것으로 보장되며 임시 파일 이름을 구성하는 데 유용합니다.
- getppid()는 호출 프로세스의 부모 프로세스 ID를 반환합니다.
 
#### error
- getpid() 및 getppid() 함수는 `항상 성공`하며 오류를 나타내기 위해 예약된 반환 값이 없습니다.

### pause
```
#include <unistd.h>

int pause(void);
```
- 일시 중지는 `sigsuspend(2)`에 의해 더 이상 사용되지 않습니다.
- pause() 함수는 kill(2) 함수나 간격 타이머에서 신호가 수신될 때까지 호출 스레드를 일시 중지합니다. (settimer(2)를 참조하십시오.) pause() 동안 시작된 신호 처리기가 종료되면 pause() 호출이 반환됩니다.

### sleep
- sleep 명령은 최소 초 동안 실행을 일시 중단합니다.
- sleep 명령이 신호를 받으면 표준 동작을 취합니다.
- The sleep utility exits 0 on success, and >0 if an error occurs. 

### usleep
```c
int usleep(useconds_t microseconds); ```
- 시스템 활동 또는 제한으로 인해 수면 시간이 불확실해질 수 있습니다.

## subject
### Mandatory
- The `executable files` must be named client and server.
- You can use `one global variable` but it must be justified.
- On the mandatory part you are allowed to use the following functions:
◦ write
◦ ft_printf and any equivalent YOU coded
◦ signal
◦ sigaction
◦ sigemptyset
◦ sigaddset
◦ kill
◦ getpid
◦ malloc
◦ free
◦ pause
◦ sleep
◦ usleep
◦ exit
- You must create a `communication program` in the form of a client and server.
- The server must be launched first, and `after being launched it must display its PID`
- The `client` will take as parameters:
	- The `server PID`.
	- The `string` that should be sent. 
- The client must communicate the string passed as a parameter to the server. Once
the string has been `received, the server must display it`.
- Communication between your programs should ONLY be done using `UNIX signals`.
- The server must be able to display the string pretty quickly. By quickly we mean
that if you think it is too long, then it is probably too long (hint: 1 second for 100
characters is COLOSSAL)
- Your `server` should be able to `receive strings from several clients in a row`, without
needing to be restarted.
- You can only use the `two signals SIGUSR1 and SIGUSR2`.
```
Linux system do NOT queue signals when you already have pending
signal of this type! bonus time?
Linux 시스템은 이 유형의 보류 중인 신호가 이미 있을 때 신호를 큐에 넣지 않습니다! 보너스 타임?
```

### Bonus
- The server confirms every signal received by sending a signal to the client.
- support Unicode characters!

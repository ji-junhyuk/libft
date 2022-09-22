# 09.22(목) Minitalk 과제 시작

- client에서 kill로 SIGUSR1을 보내면, Server에서는 27784 user-defined signal 1로 종료된다. 왜이렇지?
	- SIGUSR1이 사용자가 정의한 신호 아닌가?
	- 
- 문자열을 어떻게 보내지? kill이라는 것으로 server를 알려줄 수 있는데, 데이터를 어떻게 보내지? sigaction이라는 것은 특정한 signal이 왔을 때 어떤 행동(함수 호출)하는 것인데. 
	- 1. client가 kill로 신호를 보내면서, 문자열을 함께 보내는 방법은 무엇인가?
	- 2. server는 kill로 신호를 받으면서, sigaction을 통해 받은 문자열을 출력을 한다.
		- 받은 문자열의 끝을 어떻게 알지? 널 문자를 포함한 문자열을 보내준다?
- 구조
```
1. server는 클라이언트 문자열을 매번 받는다.
2. 클라이언트는 서버에게 문자열을 보낸다. ./client serverPid string
```

https://www.joinc.co.kr/w/man/2/sigaction
###  signal vs sigaction
- 이것은 일반적으로 sigaction()대신 을 사용하는 좋은 이유입니다 signal(). 그러나 의 인터페이스 sigaction()는 확실히 더 까다롭습니다.
- 이 signal()함수는 현재 핸들러가 실행되는 동안 다른 신호가 도착하는 것을 (필연적으로) 차단하지 않습니다. sigaction()현재 처리기가 반환될 때까지 다른 신호를 차단할 수 있습니다. 
- signal()신호 동작을 다시 (기본값)으로 재설정합니다 . SIG_DFL이는 signal()핸들러가 첫 번째 작업으로 자신을 다시 설치해야 함을 의미합니다. 또한 신호가 감지된 시간과 핸들러가 다시 설치되는 시간 사이에 취약성의 창을 열어 신호의 두 번째 인스턴스가 도착하면 기본 동작(보통 종료, 때로는 편견이 있음 - 일명 코어 덤프)이 발생합니다. 정확한 동작은 signal()시스템마다 다르며 표준은 이러한 변형을 허용합니다.

https://stackoverflow.com/questions/231912/what-is-the-difference-between-sigaction-and-signal
## allowd functions
### signal
```c
#include <signal.h>

void (*signal(int sig, void (*func)(int)))(int);

typedef void (*sig_t) (int);
sig_t signal(int sig, sig_t func);
```
- 신호를 사용하면 도메인 외부에서 프로세스를 조작할 수 있을 뿐만 아니라 프로세스가 자체 또는 자체 복사본(자식)을 조작할 수 있습니다.
- 신호에는 두 가지 일반적인 유형이 있습니다. 프로세스 종료를 유발하는 신호와 그렇지 않은 신호입니다.
- 프로그램을 종료시키는 신호는 복구할 수 없는 오류로 인해 발생하거나 터미널에서 사용자가 '인터럽트' 문자를 입력한 결과일 수 있습니다.
- 프로세스가 백그라운드에 있는 동안 제어 터미널에 액세스하기를 원하기 때문에 프로세스가 중지될 때 신호가 사용됩니다(tty(4) 참조).
- 프로세스가 중지된 후 재개될 때, 자식 프로세스의 상태가 변경될 때 또는 제어 터미널에서 입력이 준비될 때 신호가 선택적으로 생성됩니다.
- 조치를 취하지 않으면 대부분의 신호는 신호를 수신하는 프로세스를 종료합니다.
- 대신 일부 신호는 수신하는 프로세스를 중지시키거나 프로세스가 달리 요청하지 않은 경우 단순히 폐기됩니다.
- SIGKILL 및 SIGSTOP 신호를 제외하고, signal() 함수를 사용하면 신호를 포착하거나 무시하거나 인터럽트를 생성할 수 있습니다. 이러한 신호는 <signal.h> 파일에 정의되어 있습니다. ex) SIGUP, SIGINT, SIGILL...
- sig 인수는 수신된 신호를 지정합니다.
- func 프로시저는 신호 수신 시 사용자가 작업을 선택할 수 있도록 합니다.
- 위에 나열된 대로 신호의 기본 동작을 설정하려면 func가 SIG_DFL이어야 합니다. SIG_DFL은 기본 동작을 재설정합니다. 신호를 무시하려면 func가 SIG_IGN이어야 합니다.
- 이로 인해 신호의 후속 인스턴스가 무시되고 보류 중인 인스턴스가 삭제됩니다.
- SIG_IGN을 사용하지 않으면 신호의 추가 발생이 자동으로 차단되고 func가 호출됩니다.
- 처리된 신호는 함수가 반환될 때 차단 해제되고 신호가 발생했을 때 중단된 위치에서 프로세스가 계속됩니다. 
- 이전 신호 기능과 달리 핸들러 func()는 신호가 전달된 후에도 설치된 상태로 유지됩니다.
- 일부 시스템 호출의 경우 호출이 실행되는 동안 신호가 포착되어 호출이 조기에 종료되면 호출이 자동으로 다시 시작됩니다.
- signal(3)과 함께 설치된 모든 핸들러에는 SA_RESTART 플래그가 설정되어 있으며, 이는 다시 시작할 수 있는 시스템 호출이 신호 수신 시 반환되지 않음을 의미합니다.
- 영향을 받는 시스템 호출에는 통신 채널 read(2), write(2), sendto(2), recvfrom(2), sendmsg(2) 및 recvmsg(2), 또는 저속장치 ioctl(2), wait(2)가 포함됩니다.
- 시그널 핸들러를 설치한 프로세스가 포크하면 자식 프로세스가 시그널을 상속받는다. 포착된 모든 신호는 execve(2) 함수를 호출하여 기본 동작으로 재설정될 수 있습니다. 무시된 신호는 무시된 상태로 유지됩니다. 
- 프로세스가 SIGCHLD 신호에 대한 작업으로 SIG_IGN을 명시적으로 지정하면 시스템은 호출 프로세스의 자식이 종료될 때 좀비 프로세스를 생성하지 않습니다.
- 결과적으로 시스템은 자식 프로세스의 종료 상태를 버립니다.
- 호출 프로세스가 이후에 wait(2) 또는 이에 상응하는 호출을 실행하면 호출 프로세스의 모든 자식이 종료될 때까지 차단되고 errno가 ECHILD로 설정된 -1 값을 반환합니다. 
- 신호 처리기에서 사용하기에 안전한 것으로 간주되는 함수 목록은 sigaction(2)를 참조하십시오.

#### return value
- 호출이 성공하면 이전 작업이 반환됩니다.
- 그렇지 않으면 SIG_ERR이 반환되고 전역 변수 errno가 오류를 나타내도록 설정됩니다.

#### error
- signal() 함수는 실패하고 다음 중 하나가 발생하면 아무 작업도 수행되지 않습니다.
	- [EINVAL] sig 인수는 유효한 신호 번호가 아닙니다.
	- [EINVAL] SIGKILL 또는 SIGSTOP에 대한 처리기를 무시하거나 제공하려고 했습니다.
 
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
- 시스템은 프로세스에 전달할 수 있는 일련의 신호를 정의합니다. 신호 전달은 하드웨어 인터럽트 발생과 유사합니다. 일반적으로 신호는 더 이상 발생하지 못하도록 차단되고 현재 프로세스 컨텍스트가 저장되고 새 컨텍스트가 작성됩니다. 
- 프로세스는 신호가 전달되는 핸들러를 지정하거나 신호가 무시되도록 지정할 수 있습니다.
- 프로세스는 신호가 발생할 때 시스템이 기본 조치를 취하도록 지정할 수도 있습니다.
- 신호도 차단될 수 있으며, 이 경우 차단 해제될 때까지 전달이 연기됩니다.
- 배송 시 취해야 할 조치는 배송 시 결정됩니다.
- 일반적으로 신호 처리기는 프로세스의 현재 스택에서 실행됩니다. 이것은 신호가 특별한 신호 스택에서 취해지도록 핸들러별로 변경될 수 있습니다.
- 신호 루틴은 일반적으로 호출을 차단한 신호로 실행되지만 다른 신호가 아직 발생할 수 있습니다.
- 전역 신호 마스크는 현재 프로세스로의 전달이 차단된 신호 집합을 정의합니다.
- 프로세스의 신호 마스크는 상위(보통 비어 있음)의 신호 마스크에서 초기화됩니다.
- sigprocmask(2) 호출로 변경되거나 신호가 프로세스에 전달될 때 변경될 수 있습니다.
- 프로세스에 대해 신호 조건이 발생하면 신호가 프로세스에 대해 보류 중인 신호 세트에 추가됩니다.
- 신호가 현재 프로세스에 의해 차단되지 않은 경우 프로세스에 전달됩니다.
프로세스.
- 신호는 프로세스가 운영 체제에 진입할 때마다 전달될 수 있습니다(예: 시스템 호출, 페이지 폴트 또는 트랩, 또는 클록 인터럽트 동안).
- 여러 신호를 동시에 전달할 준비가 된 경우 트랩으로 인해 발생할 수 있는 모든 신호가 먼저 전달됩니다.
- 추가 신호는 동시에 처리될 수 있으며, 각 신호는 첫 번째 명령 이전에 이전 신호에 대한 처리기를 인터럽트하는 것으로 나타납니다.
- 보류 중인 신호 세트는 sigpending(2) 시스템 호출에 의해 반환됩니다.
- 포착된 신호가 전달되면 프로세스의 현재 상태가 저장되고 새 신호 마스크가 계산되며(아래 설명 참조) 신호 처리기가 호출됩니다.
- 핸들러에 대한 호출은 신호 처리 루틴이 정상적으로 반환되면 프로세스가 신호 전달 이전부터 컨텍스트에서 실행을 재개하도록 정렬됩니다.
- 프로세스가 다른 컨텍스트에서 재개하려면 이전 컨텍스트 자체를 복원하도록 정렬해야 합니다.
- 신호가 프로세스에 전달되면 프로세스의 신호 처리기 동안(또는 sigprocmask(2) 시스템 호출이 수행될 때까지) 새 신호 마스크가 설치됩니다.
- 이 마스크는 현재 신호 마스크 세트, 전달될 신호 및 호출할 핸들러와 관련된 신호 마스크의 합집합을 취함으로써 형성됩니다.
- sigaction() 시스템 호출은 sig로 지정된 신호에 대한 작업을 할당합니다.
- act가 0이 아니면 지정된 신호를 전달할 때 사용할 액션(SIG_DFL, SIG_IGN 또는 핸들러 루틴)과 마스크를 지정합니다.
- oact가 0이 아니면 신호에 대한 이전 처리 정보가 사용자에게 반환됩니다.
- 신호 처리기가 설치되면 일반적으로 다른 sigaction() 시스템 호출이 수행되거나 execve(2)가 수행될 때까지 설치된 상태로 유지됩니다.
- 신호별 기본 동작은 sa_handler를 SIG_DFL로 설정하여 재설정할 수 있습니다.
- 기본값은 코어 덤프가 있는 프로세스 종료입니다. 조치 없음; 프로세스 중지; 또는 프로세스를 계속합니다.
- 각 신호의 기본 동작은 아래 신호 목록을 참조하십시오.
- sa_handler가 SIG_DFL이면 신호에 대한 기본 동작은 신호를 버리는 것이고, 신호가 보류 중이면 신호가 마스킹되더라도 보류 중인 신호는 폐기됩니다.
- sa_handler가 SIG_IGN으로 설정되면 신호의 현재 및 보류 중인 인스턴스가 무시되고 폐기됩니다.
- If sa_handler is set to SIG_IGN current and pending instances of the signal are ignored and discarded.
	- SA_NOCLDSTOP : SIGCHLD 신호에 대한 잡기 기능을 설치할 때 이 비트가 설정되면 SIGCHLD 신호는 자식 프로세스가 종료될 때만 생성되고 자식 프로세스가 중지될 때는 생성되지 않습니다.
	- SA_NOCLDWAIT : SIGCHLD 신호에 대해 sigaction()을 호출할 때 이 비트가 설정되면 호출 프로세스의 자식이 종료될 때 시스템이 좀비 프로세스를 생성하지 않습니다. 호출 프로세스가 이후에 wait(2)(또는 이와 동등한 것)를 발행하면 호출 프로세스의 모든 자식 프로세스가 종료될 때까지 차단한 다음 errno가 ECHILD로 설정된 -1 값을 반환합니다. 
- 아래 나열된 시스템 호출 중에 신호가 포착되면 EINTR 오류와 함께 호출이 강제 종료될 수 있으며 요청보다 짧은 데이터 전송으로 호출이 반환되거나 호출이 다시 시작될 수 있습니다.
- 보류 중인 호출의 재시작은 sa_flags에서 SA_RESTART 비트를 설정하여 요청됩니다.
- 영향을 받는 시스템 호출에는 다음이 포함됩니다. open(2), read(2), write(2), sendto(2), recvfrom(2), sendmsg(2) 및 recvmsg(2) 통신 채널 또는 느린 장치(터미널과 같이 일반 파일) 및 wait(2) 또는 ioctl(2) 동안. 그러나 이미 커밋된 호출은 다시 시작되지 않고 대신 부분적인 성공을 반환합니다(예: 짧은 읽기 횟수). 
- fork(2) 또는 vfork(2) 모든 신호 뒤에는 신호 마스크, 신호 스택 및 재시작/인터럽트 플래그가 자식에 의해 상속됩니다.
- execve(2) 시스템 호출은 포착된 모든 신호에 대한 기본 동작을 복원하고 사용자 스택에서 포착할 모든 신호를 재설정합니다.
- 무시된 신호는 무시된 상태로 유지됩니다. 신호 마스크는 동일하게 유지됩니다. 보류 중인 시스템 호출을 다시 시작하는 신호는 계속 그렇게 합니다.
 
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
	- sigemptyset() 함수는 신호 세트를 비어 있도록 초기화합니다.
	- sigfillset() 함수는 모든 신호를 포함하도록 신호 세트를 초기화합니다.
	- sigaddset() 함수는 지정된 신호 signo를 신호 세트에 추가합니다.
	- sigdelset() 함수는 신호 세트에서 지정된 신호 signo를 삭제합니다.
	- sigismember() 함수는 지정된 신호 signo가 신호 세트에 포함되어 있는지 여부를 반환합니다.
- 이러한 기능은 포함 파일 <signal.h>에 매크로로 제공됩니다. 이름이 정의되지 않은 경우 실제 함수를 사용할 수 있습니다(#undef 이름 포함).
- sigismember() 함수는 신호가 집합의 구성원이면 1을 반환하고 그렇지 않으면 0을 반환합니다. 다른 함수는 0을 반환합니다.
#### return value
- sigismember() 함수는 신호가 집합의 구성원이면 1을 반환하고 그렇지 않으면 0을 반환합니다. 다른 함수는 0을 반환합니다.

### kill
```
kill [-s signal_name] pid ...
kill -l [exit_status]
kill -signal_name pid ...
kill -signal_number pid ...
```
- 프로세스 종료 또는 신호
- kill 유틸리티는 pid 피연산자에 의해 지정된 프로세스에 신호를 보냅니다.
- 슈퍼 사용자만이 다른 사용자의 프로세스에 신호를 보낼 수 있습니다.
- 옵션은 다음과 같습니다. 
	- -s 신호 이름: 기본 TERM 대신 보낼 신호를 지정하는 기호 신호 이름입니다.

	- -l [종료_상태]: 피연산자가 없으면 신호 이름을 나열하십시오. 그렇지 않으면 exit_status에 해당하는 신호 이름을 씁니다.
	- -signal_name
             기본 TERM 대신 보낼 신호를 지정하는 기호 신호 이름입니다. 
	- -signal_number 기본값 대신 보낼 신호를 지정하는 음이 아닌 10진수 정수
             기간. 

- 다음 PID에는 특별한 의미가 있습니다.
	- -1 수퍼유저인 경우 모든 프로세스에 신호를 브로드캐스트합니다. 그렇지 않으면 사용자에게 속한 모든 프로세스에 브로드캐스트됩니다.
 
- 더 일반적으로 사용되는 신호:
	- 1 HUP(전화 끊기)
	- 2 INT(인터럽트)
	- 3 종료(종료)
	- 6 ABRT(중단)
	- 9 KILL(잡을 수 없는, 무시할 수 없는 킬)
	- 14 ALRM(알람 시계)
	- 15 TERM(소프트웨어 종료 신호)
- 일부 쉘은 이 유틸리티와 유사하거나 동일한 내장 kill 명령을 제공할 수 있습니다.

#### exit_status
- kill 유틸리티는 성공하면 0을 종료하고 오류가 발생하면 >0을 종료합니다.

#### example
- Terminate the processes with PIDs 142 and 157:
	- kill 142 157
- Send the hangup signal (SIGHUP) to the process with PID 507:
	- kill -s HUP 507
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
- getpid() 및 getppid() 함수는 항상 성공하며 오류를 나타내기 위해 예약된 반환 값이 없습니다.

### pause
```
#include <unistd.h>

int pause(void);
```
- 일시 중지는 sigsuspend(2)에 의해 더 이상 사용되지 않습니다.
- pause() 함수는 kill(2) 함수나 간격 타이머에서 신호가 수신될 때까지 호출 스레드를 일시 중지합니다. (settimer(2)를 참조하십시오.) pause() 동안 시작된 신호 처리기가 종료되면 pause() 호출이 반환됩니다.

### sleep
- sleep 명령은 최소 초 동안 실행을 일시 중단합니다.
- sleep 명령이 신호를 받으면 표준 동작을 취합니다.
- The sleep utility exits 0 on success, and >0 if an error occurs. 

### usleep
```c
int usleep(useconds_t microseconds);
```
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

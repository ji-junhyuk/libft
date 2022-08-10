## OSI 
- 네트워크 프로토콜이 통신하는 구조를 7개의 계층으로 분리하여 나타낸 것이다.
<사진2>


## 포트
- 포트(port)는 네트워크 연결이 시작되고 끝나는 가상 공간(virtual point)을 말한다.
- 인터넷 프로토콜인 TCP/IP를 사용할 때에는 클라이언트 프로그램이 네트워크 상의 특정 서버 프로그램을 지정하는 방법으로 사용된다.
> port는 항구, port number는 선착장

### 포트포워딩
- 포트포워딩(portforwarding, 전달)이란 공유기의 포트를 통해 하나의 ip를 공유하는 여러 서버(기기) 중 특정 포트에 진입할 수 있도록 네트워크 주소를 변환시켜주는 기능을 말한다.
<사진1> 

### 포트번호
- 포트 번호는 컴퓨터에서 실행되고 있는 서버를 구분 짓기 위한 16비트의 논리적 할당으로 0~65536번이 존재한다
	- `well-known port`
		- 특정 용도를 위해 0~1023번까지의 지정되어 있는 포트를 칭한다.
	- 웹서버는 기본적으로 80번 포트를 할당받는다. 웹 서버를 하나 더 사용하고 싶은 경우 well-know port가 아닌 포트로 연결해서 사용한다. (관습적으로 8080)
	- `http://connect.com`에서 80 포트는 생략이 가능하며, 8080 포트에 연결하고 싶다면 `http://test.com:8080` 처럼 지정해주어야 한다.

### SSH 연결
#### 형식
- ssh [사용자 계정]@[원격지 ip]

#### Born2beroot
- 하나의 host OS에서 가상화된 여러개의 guest OS를 사용하는 것이다.
- host 터미널에서 guest로 접속하기 위해 포트를 열어준다.
	- HOST IP		|	HOST PORT	|	GUEST IP	|	GUSET PORT	|
	- 127.0.0.1		|	2424		|	10.0.2.15	|	4242		|  
		- (host) $ ssh junji@127.0.0.1 -port 2424
		- (host) $ ssh junji@localhost -port 2424
		- host 터미널에서 사용자 계정이 `junji`인 `원격지 ip`에 `ssh 연결을 시도`하는 것이다.
	
## 소켓(socket)
- 데이터를 주고 받을 때, 소켓에 데이터를 적어 보낸다.
- 소켓은 `protocol`, `ip`, `port number`로 구성된다.

### 텔넷(telnet)과 SSH(Secure Shell)의 차이점
- 텔넷은 정보를 byte스트림 형식으로 주고 받고, ssh는 DES, RSA등 암호화를 통해 통신을 한다.
<사진3>

### LVM
- LVM(Logical Volume Mangaer)란 논리적인 공간을 관리해주는 프로그램을 말한다.

#### LVM을 사용하는 이유
1. 여러개의 디스크 공간을 합쳐서 하나인양 사용하기 위해
2. 사용하기 애매한 공간의 디스크 파티션(짜투리)들을 활용하기 위해
3. 기존에 사용중인 디스크의 공간을 확장할 수 있기에

### su와 sudo
- su는"수퍼 사용자"를 나타내며 루트로 로그인하여 시스템에서 원하는 모든 작업을 수행할 수 있습니다. sudo는 "super user do"의 약자이며 현재 사용자 계정을 일시적으로 루트 권한으로 승격할 수 있습니다. 
- 기본적으로 Linux 커널은 보안 목적을 위해 kurnel모드와 user모드로 나눈다. 일반 사용자가 애플리케이션을 설치할 수 있도록 일시적으로 super user권한을 준다. 이를 sudo라고 한다. 


### DHCP(Dynamic Host Configuration Protocol)
- 호스트의 IP주소와 각종 TCP/IP 프로토콜의 기본 설정을 처음 부팅된 클라이언트에게 자동으로 제공해주는 프로토콜을 말한다.
- DHCP 서비스가 필요한 이유는, 통신사 입장에서 수 많은 가입자 PC마다 인터넷 주소를 개별 설정, 관리하기 어렵고, 일반 사용자에게도 인터넷 주소 설정이 까다롭기 때문이다.
 
## 참고자료
- 포트포워딩 https://lamanus.kr/59
- 소켓 https://helloworld-88.tistory.com/215
- root와 kurnel의 관계 https://unix.stackexchange.com/questions/121715/what-is-the-relationship-between-root-and-kernel 
- SSH 통신 https://limvo.tistory.com/21
- LVM https://mamu2830.blogspot.com/2019/12/lvmpv-vg-lv-pe-lvm.html
- sudo https://www.beyondtrust.com/blog/entry/unix-linux-privileged-management-should-you-sudo#:~:text=Allowing%20root%20user%20access%20using%20sudo&text=Sudo%20will%20allow%20your%20system,your%20security%20and%20compliance%20protocol.

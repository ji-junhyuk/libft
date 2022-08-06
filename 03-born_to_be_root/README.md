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

## 참고자료
- 포트포워딩 https://lamanus.kr/59
- 소켓 https://helloworld-88.tistory.com/215
- root와 kurnel의 관계 https://unix.stackexchange.com/questions/121715/what-is-the-relationship-between-root-and-kernel 
- SSH 통신 https://limvo.tistory.com/21

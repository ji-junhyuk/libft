shasum README.md | diff 123 -
diff <(cat 123) <(shasum README.md)
## 평가 때 사용해야 하는 명령어는 alias에 매핑해둬서 까먹으면 보자
# CRONTAB
```zsh
alias CRONTAB1="sudo crontab -e"
alias CRONTAB2="sudo crontab -l" 
```
# UFW
```zsh
alias UFW1="sudo ufw status verbose"
alias UFW2="sudo ufw enable"
alias UFW3="sudo ufw disable"
alias UFW4="sudo ufw default deny"
alias UFW5="sudo ufw allow 4242"
alias UFW6="sudo ufw status numbered"
alias UFW7="sudo ufw delete [number]"
```
# SSH
```zsh
alias SSH1="systemctl status ssh"
```
# OPERATING
```zsh
alias UNAME1="sudo uname -a"
```
# group
```zsh
alias GROUP1="adduser junji"
alias GROUP2="id junji"
alias GROUP3="passwd junji"
alias GROUP4="passwd -e junji"
alias GROUP5="chage -l junji"
alias GROUP6="sudo vi /etc/shadow"
alias GROUP7="usedel -f junji"
alias GROUP8="addgroup 42seoul"
alias GROUP9="addgroup -G 42seoul junji"
```
---
subject
1. 저장소에 있는 signature.txt파일과 .vdi파일과 동일한지 확인한다.

2. 가상 머신의 작동 방식
- 가상의 컴퓨터를 말한다. 이는 물리적인 컴퓨터에서 빌려온 하드웨어를(CPU, 메모리)를 소프트웨어적으로 구현하여 그 위에서 운영체제가 작동하는 방식이다. (그림 그려주기)
- 이를 명확히 이해하기 위해선 도커와의 차이점을 알면 좋다. 도커는 내가 사용하고 싶은 앱에 초점을 맞춰 그것이 필요한 종속성들을 한 컨테이너안에 넣는 방식이고, 가상머신은 하드웨어조차 소프트웨어적으로 구현하여 가상의 컴퓨터 환경을 만드는 것이다.
cf. 하이퍼바이저는 여러 개의 가상 머신 서버를 관리하는 가상머신들의 os라고 이해했다.

3. 가상 머신의 목적 
여러 가상 머신에서 여러 운영 체제를 동시에 실행할 수 있어 실제 인프라 설치 비용을 절감할 수 있다. 개발-테스트하기 쉬워진다. 독립된 환경으로 실행되기에 보안상 이점이 있다.

4. 데비안을 선택한 경우 apt와 aptitute
데비안을 선택한 이유는 처음 서버를 다루기에 비교적 쉽다고 하는 debian 운영체제를 선택했다. 
apt(advanced packaging tool)
- 소프트웨어 설치와 제거를 관리하는 소프트웨어를 말한다.
aptitute
- 사용자 인터페이스가 추가 되었다. apt보다 좀 더 똑똑하게 작동한다. (예를 들어 패키지를 삭제할 때 사용되지 않는 패키지까지 삭제하는 식이다)

5. 앱 아머란 무엇인가?
- app armor란 시스템 관리자가 프로그램 별로 기능을 제한할 수 있게 하는 보안 모듈이다. app armor는 강제적으로 접근을 통제한다(MAC, Mandatory Access Control). 접근 통제 정책은 MAC, DAC, RBAC 가 있다. MAC은 군대같고, DAC은(Discretionary Access Control) 요청하는 사용자의 신분에 기초에 접근을 제한하고 RBAC(Rule-based Accesss Control)는 역할을 기반하여 권한을 부여한다.

6. root 사용자가 아닌 것으로 ssh연결 시도.
이유 :

7. UFW 서비스가 시작되었는지 확인한다
이유 :

8. use할당하고 비밀번호 규칙이 적용되었는지 테스트해본다.
이유 :

9. evaluating 그룹 만들고, 사용자에게 할당 요청, 사용자가 evaluating에 속하는지 확인

10. 암호 정책의 장점과 구현의 장점과 단점.
- ?

### 호스트
1. 호스트 이름이 다음과 같이 올바른 형식인지 확인(..42)

2. 로그인을 바꾸어 호스트 이름을 수정한 다음 다시 시작.
$ sudo hostnamectl set-hostname [junji];

3. reboot후 호스트이름이 바뀌지 않았다면 끝

4. 호스트 이름을 다시 내것으로 수정.

5. LVM이 작동하는 방식과 LVML이 무엇인지

### 수도
1. 수도라는 프로그램 있나요?
2. sudo그룹에 새 사용자 할당해봅시다. (add group, groupdel, gorupmod, usermod, usermod -aG, usermod -g)
3. /var/log/sudo 폴더가 존재하고 하나 이상의 파일이 있는지 확인.
4. sudo 명령을 통해 update 확인

### UFW
1. 가상머신에 UFW 프로그램이 제대로 설치되어 있는지.
2. 제대로 작동하는지
3. UFW가 무엇인지, 왜 사용하는지
4. UFW의 활성 규칙 나열하기, 4242규칙이 있어

### SSH
1. SSH가 제대로 설치되어 있는지.
2. 제대로 작동하는지
3. 기본적으로 SSH가 무엇인지. 사용가치를 설명
4. 4242포트만 사용하는지 확인(SSH)
5. 새로 생성된 사용자로 로그인하기 위해 SSH를 사용하는 것을 해야 한다. (루트사용자로 로그인할 수 없는지도)

### 크론
1. 스크립트가 작동하는 방식
2. 크론이란 ?

### ftp

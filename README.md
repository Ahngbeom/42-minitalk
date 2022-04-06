# Minitalk [![bahn's 42 minitalk Score](https://badge42.vercel.app/api/v2/cl1n6fb2j003009l0lfanbfyx/project/2198518)](https://github.com/JaeSeoKim/badge42)

## <span style="color:#00AA00"/>Guacamole SSH 평가

원격으로 평가하기 위해서는 과카몰리 SSH 터미널 화면을 2개 이상으로 분리해야한다.

- brew 설치 (MacOS용 패키지 관리 애플리케이션)
```
rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
```

- tmux 패키지 설치 (터미널 세션을 생성하여 여러 개의 창 또는 틀을 생성할 수 있음)
```
brew install tmux
```

[tmux 사용법](https://velog.io/@ur-luella/tmux-%EC%82%AC%EC%9A%A9%EB%B2%95)

---

## <span style="color:#00FF00"/>Execution

1.	`make` or `make all` or `make bonus`

2.	`bash ./server`

3.	`bash ./client [SERVER PID] [SEND MESSAGE]`
---


## <span style="color:#FA5882"/>과제 요구 조건

-	클라이언트가 실행될 때에 PID를 표시해야 한다.

-	서버는 문자열이 수신되면 해당 문자열을 표시해야 한다.

-	서버와 클라이언트의 통신은 오직 UNIX signal 중 SIGUSR1과 SIGUSR2 두 신호만 사용할 수 있다.

-	서버는 문자열을 매우 빠른 속도로 표시할 수 있어야 한다.<br>
	1초 안에 100개의 문자로 이루어진 문자열을 표시할 수 있어야한다.

-	서버가 재시작할 필요없이 여러 클라이언트로부터 문자열을 연속으로 수신할 수 있어야 한다.

	Bonus

	-	소규모 수신 확인 시스템 추가 (서버/클라이언트 간의 수신 확인)<br>
		단방향 통신(Simplex)이 아닌 반이중(Half-Duplex) 통신 방식을 적용. 

	-	유니코드 문자도 지원하도록 해보세요.<br>
		🖤∑∞☞★⚝✅🔥⌚☣☮🌏📱Ⅻ🚀€🍔🍦👑⚽🎵🎧♻
---
# sigaction

- SA_SIGINFO

	sa_flags에 SA_SIGINFO 플래그를 지정하면 시그널이 발생할 원인을 알 수 있다.
	sigaction 구조체에서 시그널 핸들러를 지정할 때 sa_handler 대신 sa_sigaction을 사용한다.
	시그널 핸들러는 다음과 같이 인자 3개를 받는 형태로 정의되어진다.

	```c
	void handler(int signo, siginfo_t *siginfo, ucontext_t *context);

	// signo : 시그널 핸들러를 호출할 시그널
	// siginfo : 시그널이 발생한 원인을 담은 siginfo_t 구조체 포인터
	// context : 시그널이 전달될 때 시그널을 받는 프로세스의 내부 상태를 담은 ucontext_t 구조체 포인터
	```
---

## <span style="color:#9F81F7"/>동작흐름

### 1. 서버 실행
	
-	<span style="color:#F3F781"/>
	sigaction 구조체를 선언한다.
<br>

-	<span style="color:#F3F781"/>
	sigaction 구조체에 sa_flags 변수가 존재하는데,<br>
	시그널 처리 프로세스의 행위를 수정하는 일련의 플래그들을 명시한다.<br>sa_flags 변수에 설정 가능한 플래그는 다음과 같다.
	
	*	SA_NOCLDSTOP
	*	SA_ONESHOT / SA_RESETHAND
	*	SA_RESTART
	*	SA_NOMASK / SA_NODEFER
	*	<span style="color:red; font-weight: bold;">SA_SIGINFO

	이 과제에서는 <span style="color:red; font-weight: bold;">SA_SIGINFO</span> 플래그를 설정해줄 것이다.<br>
	<span style="color:red; font-weight: bold;">SA_SIGINFO</span>플래그는 시그널 처리기(핸들러)가 하나가 아닌 3개의 인자를 취할경우<br>
	sa_handler대신 sa_sigaction의 siginfo_t를 이용할 수 있다. <br>siginto_t는 다음과 같이 정의된 구조체이다.

	```C
	siginfo_t {
		int      si_signo;  /* 시그널 넘버 */
		int      si_errno;  /* errno 값 */
		int      si_code;   /* 시그널 코드 */
		pid_t    si_pid;    /* 프로세스 ID 보내기 */
		uid_t    si_uid;    /* 프로세스를 전송하는 실제 사용자 ID */
		int      si_status; /* Exit 값 또는 시그널 */
		clock_t  si_utime;  /* 소모된 사용자 시간 */
		clock_t  si_stime;  /* 소모된 시스템 시간 */
		sigval_t si_value;  /* 시그널 값 */
		int      si_int;    /* POSIX.1b 시그널 */
		void *   si_ptr;    /* POSIX.1b 시그널 */
		void *   si_addr;   /* 실패를 초래한 메모리 위치 */
		int      si_band;   /* 밴드 이벤트 */
		int      si_fd;     /* 파일 기술자 */
	}
	```
<br>

-	<span style="color:#F3F781"/>
	서버는 수신한 시그널에 대해 처리할 함수(핸들러)를 지정해주어야 한다.<br>sigaction 구조체에는 핸들러를 지정할 수 있는 2개의 함수 포인터가 존재한다.
	
	```c
	void (*sa_handler)(int);
	void (*sa_sigaction)(int, siginfo_t *, void *);
	```

	위에서 sa_flags 변수에 SA_SIGINFO 플래그를 지정해주었기 때문에 sa_sigaction 포인터 함수에 클라이언트 신호를 처리하기 위한 3개의 인자를 가지는 핸들러 함수를 지정해준다.<br>
<br>

-	<span style="color:#F3F781"/>
	sigaction 구조체의 sa_mask 변수도 설정해주어야 한다.<br>
	sa_mask 변수는 시그널을 처리하는 동안 블록시킬 시그널을 모아놓은 변수이다.
	
		시그널 블록이란, 운영체제에게 sa_mask에 설정된 시그널을 나중에 처리하도록 예약(?)하는 동작 방식이다.
	
	따라서 sigemptyset() 함수를 통해 sa_mask 변수안의 시그널들을 비워준다면 모든 시그널이 블록킹되지않는다.
<br>

-	<span style="color:#F3F781"/>
	설정한 sigaction 구조체를 적용시키기 위해 sigaction() 함수를 호출한다.
	sigaction() 함수의 원형은 다음과 같다.

	```c
	int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

	// signum : 발생한 시그널 번호
	// act : 시그널 발생 시 처리해주기위한 설정 값들이 존재하는 sigaction 구조체
	// act : 이전에 등록되었던 sigaction 구조체 (필요하지않다면 NULL 또는 0)
	```
<br>

-	<span style="color:#F3F781"/>
	getpid() 함수를 통해 Server PID를 터미널에 출력
<br>

-	<span style="color:#F3F781"/>
	클라이언트의 연결 신호 대기 (SIGUSR1, SIGUSR2)
<br>

### 2. 클라이언트 실행 및 서버와 연결
-	<span style="color:#F3F781"/>
	클라이언트 실행 시 2개의 인자 <span style="color:red; font-weight: bold;">[SERVER PID] [SEND MESSAGE] </span>를 입력하지 않았을 경우 예외처리
<br>

-	<span style="color:#F3F781"/>
	클라이언트도 서버와 마찬가지로 sigaction 구조체를 선언 후 시그널 처리에 필요한 설정을 해준다.
	<br>
	<span style="color:#FA8258">
	sigaction() 함수를 통한 시그널 처리 적용도 잊지 말자.
	</span>
<br>

-	<span style="color:#F3F781"/>
	getpid() 함수를 통해 Client PID를 터미널에 출력
<br>

-	<span style="color:#F3F781"/>
	g_client_data 변수는 서버와 연결하기 위해 필요한 서버 PID와 서버에게 전송할 메시지를 저장할 전역 구조체 변수이다.

	왜 전역 구조체 변수를 선언해야하는지는 다음 동작 과정에서 자세히 설명을 하겠다.
<br>

-	<span style="color:#F3F781"/>
	서버와 연결하기 위한 모든 준비 과정을 마쳤다면,<br>
	서버와 연결하기 위해 ft_connection() 함수를 호출한다.<br>
	ft_connection() 함수에서는 kill() 함수를 통해 서버에게 시그널을 전송한다. <br>kill 함수의 첫번째 매개변수로 시그널을 전송할 대상의 PID를 기입하고, 두번째 매개변수로 시그널 종류를 기입한다. <br>따라서 <span style="color:red; font-weight: bold;">서버의 PID</span>와 <span style="color:red; font-weight: bold;">SIGUSR1 시그널</span>을 전송한다.
	시그널을 보낸 후 서버의 응답 신호를 기다리기 위해 pause() 함수를 호출한다.

		pause() 함수는 시그널을 수신할 때까지 대기 상태로 전환된다.
<br>

### 3. 서버 - 클라이언트 PID 수신
-	<span style="color:#F3F781"/>
	서버는 시그널이 수신되면 hdr_client_with_connection 함수가 호출된다.<br>hdr_client_with_connection() 핸들러 함수의 2번째 매개변수인
	siginfo_t 타입 siginfo 구조체 si_pid 값을 통해<br>
	<span style="color:red; font-weight: bold;">클라이언트의 PID를 얻어낸다.</span><br>
	서버 또한 g_server_data 전역 구조체를 선언하여 클라이언트 PID를 저장할 변수와 <br>
	클라이언트가 보낸 메시지를 저장할 변수를 초기화해준다.
<br>

-	<span style="color:#F3F781"/>
	클라이언트가 보내는 신호를 통해 클라이언트가 보내고자하는 메시지를 해독하기위해 <br><span style="color:red; font-weight: bold;">sigaction 핸들러를 다시 설정해주어야한다.</span><br>
	시그널 핸들러를 hdr_receive_message() 함수로 변경을 해준 후,
	sigaction() 함수를 호출하여 시그널에 대한 처리를 재설정해준다.
<br>

-	<span style="color:#F3F781"/>
	이제 클라이언트에게 응답 시그널을 전송하여 메시지를 받을 준비가 되었다는 것을 알린다.<br>
	kill 함수를 통해 클라이언트의 PID가 저장되어있는 siginfo->si_pid 와 <br>클라이언트가 보낸 시그널이 저장되어있는 siginfo->si_signo 시그널을 그대로 보내준다.
<br>

### 4. 클라이언트 - 서버에게 메시지 전달 

-	<span style="color:#F3F781"/>
	서버로부터 응답 시그널이 발생했을 때 클라이언트는 hdr_server_with_connection() 핸들러 함수를 호출하게된다.<br>
	hdr_server_with_connection() 핸들러는 서버에게 보낸 SIGUSR1 시그널을 서버가 그대로 응답했다면<br> 서버와의 연결이 성공했다는 의미로 받아들이게된다.<br>
	클라이언트도 마찬가지로 메세지를 보낸 후 메시지 수신완료에 대한 응답시그널을 받기 위해 sigaction 핸들러 함수를 ft_send_message() 함수로 변경 및 적용시켜준다.
<br>

-	<span style="color:#F3F781"/>
	서버에게 보낼 문자열로된 메시지를 비트 단위로 보내기위해 <span style="color:red; font-weight: bold;">ft_send_message()</span> 함수를 호출한다.
<br>

-	<span style="color:#F3F781"/>
	지금부터 본격적으로 서버에게 메시지를 보내는 작업을 수행한다.<br>
	g_client_data.msg에 저장되어있는 클라이언트가 보낼 메시지를 문자 수 만큼 반복 수행하고<br>
	다시 문자를 2진수 비트 단위로 쪼개어 최상위 비트부터 비트 값에 맞추어<br>
	<span style="color:red; font-weight: bold;">
	비트 값이 1일 경우 SIGUSR1 <br>
	비트 값이 0일 경우 SIGUSR2 
	</span><br>
	신호를 보낸다.

	<mark style='background-color: #F781F3'>단, 주의할 점은 kill() 함수를 통해 서버에게 일방적으로 반복적인 신호를 전송할 것이기 때문에 약간의 딜레이가 필요하다.</mark>

		클라이언트가 서버에게 kill 함수를 통해 보내는 신호의 속도보다 
 		서버에서 signal 함수로 받는 속도가 느리기 때문에 적절한 딜레이가 필요하다.
	
	과제 요구 조건으로 100개의 문자를 보낼 때 1초 이상 소요된다면 그것은 어마어마하게 긴 시간이 소요된 것이라고 한다.

	딜레이를 주기위해 사용할 수 있는 함수는 다음 2가지 함수이다.
	```C
	unsigned int sleep (unsigned int __seconds);
	```
	```C
	int usleep (__useconds_t __useconds);
	```
	두 함수의 차이점은 sleep() 함수는 초 단위로 매개변수를 받아 해당 초 만큼 대기 상태가 된다.<br>usleep() 함수는 마이크로 초 단위로 매개변수를 받아 해당 마이크로 초 만큼 대기 상태가 된다.<br>

		1000000 µs(micro seconds) == 1.0 s (seconds)
		10000 µs(micro seconds) == 0.01 s (seconds)

	<span style="color:#B18904"/>
	1개의 문자를 전송할 때 8개의 비트를 보내야한다.
	즉, 8번의 kill() 함수를 사용하여 시그널을 전송시켜야한다.
	따라서 8번의 딜레이가 비례적으로 필요하다.
	만약 최소한 1초에 100개의 문자를 보내야한다면
	각 비트를 전송할 때마다 1250 µs 만큼의 딜레이를 준다고 가정하면

		100(character) * (1250 µs * 8(bit)) = 1000000 µs(1 s)

	100개의 모든 문자를 전송할 때까지 1초가 걸리는 셈이다.<br>
	usleep 함수를 통해 1250 µs 만큼 대기하도록 테스트해보니 <br>
	체감상 1초는 오래걸리는 것 같기는하다.

	그래서 100개의 문자를 전송할 때 0.1초 정도 걸리도록
	usleep 함수를 통해 125 µs 만큼만 대기하도록 수정해보니
	훨씬 시원하게 메시지가 출력된다.
	</span>
<br>
	
-	<span style="color:#F3F781"/>
	usleep() 함수와 함께 메세지의 구성 문자들을 모두 서버에게 전송완료했다면,<br>
	마지막으로 '\0' 널 종료문자에 대한 시그널도 서버에게 보낸다.<br>
	'\0'의 2진수는 00000000이기 때문에 SIGUSR2 시그널을 8번 반복하여 전송한다.
<br>

-	<span style="color:#F3F781"/>
	메시지가 모두 성공적으로 수신 완료되었다는 시그널을 서버로부터 받기 위해<br>
	pause() 함수를 호출하여 대기한다.
<br>

### 5. 서버 - 클라이언트 메세지 수신
-	<span style="color:#F3F781"/>
	서버는 클라이언트가 메세지에 대한 시그널을 보낼 때마다 hdr_receive_message() 함수가 호출된다.<br>
	클라이언트가 일방적이고 반복적으로 보내는 시그널을 해독하기 위해서<br>
	정적 변수를 통해 bit 수를 카운트하여 클라이언트가 보내고자하는 문자 값이 무엇인지를 알아낸다.

		핸들러 함수는 시그널이 발생할 때마다 호출되어진다.
		그말은 즉슨, 정적 변수를 사용하지않는다면 시그널이 발생할 때마다 핸들러 함수안의 변수들의 값은 유지되지않고 초기화된다.
	
	또한 8bit 만큼의 시그널을 받았다면 해당 문자 값을 저장하기위한 변수도 정적으로 선언한다.<br>

	클라이언트로부터 보내온 시그널이 SIGUSR1 이라면<br>
	ch 정적 변수에 bit 변수 값에 해당하는 비트 자리에 1을 추가한 후 비트 값을 1 감소시킨다.<br>

	반대로 클라이언트로부터 보내온 시그널이 SIGUSR2 이라면<br>
	bit 변수 값을 1 감소시키는 작업만 수행한다.<br>

	```c
	if (signo == SIGUSR1)
        ch += 1 << --bit;
    else if (signo == SIGUSR2)
        --bit;
	```

	8번의 시그널을 받은 후 bit 변수의 값이 0이 되었다면,<br>
	ch 문자 값을 g_server_data.msg 값과 병합한다.
	
	bit 변수와 ch 변수는 각각 8과 '\0'으로 다시 초기화해준다.

	```c
	if (bit == 0)
    {
        if (ch != '\0')
            g_server_data.msg = ft_charjoin(g_server_data.msg, ch);
        .
		.
		.
        bit = 8;
        ch = '\0';
    }
	```

	만약 8번의 시그널을 수신받아 bit 변수의 값이 0이 되었고, ch 값이 '\0'이라면
	<br>
	클라이언트가 보내고자하는 메세지는 모두 전송되었다는 의미로 받아들여<br>
	클라이언트와 통신 작업의 마지막 단계를 수행한다.
<br>

### 6. 통신 및 연결 종료
-	<span style="color:#F3F781"/>
	서버는 '\0' 널 종료 문자에 대한 시그널을 수신받으면<br>
	지금까지 수신받은 문자들을 조합하여 저장해놓은 g_server_data.msg 를 출력해준 후,<br>할당되었던 메모리 공간을 해제시켜준다.<br>

	sigaction 핸들러 함수도 다시 hdr_client_with_connection() 함수로 변경 및 적용하여	초기설정으로 되돌린다.<br>

	클라이언트에게 SIGUSR2 시그널을 전송하여 모든 메세지를 성공적으로 수신받았고,<br>정상적으로 출력되었다는 의미의 마지막 인사를 건넨다.
<br>

-	<span style="color:#F3F781"/>
	클라이언트는 서버로부터 수신받은 시그널이 SIGUSR2 인 것을 확인한 후,
	클라이언트 프로그램을 정상 종료한다.
<br>

### Bonus
-	<span style="color:#A9D0F5"/>
	유니코드는 어떤 방식으로 출력되는 것일까?<br><br>

	클라이언트가 서버에게 유니코드 문자 1개만을 전송한다면<br>
	클라이언트의 시그널 전송 동작은 어떻게 이루어질까?

	기존 클라이언트 파일 코드에서 일부 코드를 추가하여 kill 함수를 몇 번이나 호출하는지 확인해보자.
	```c++
	void    ft_send_message()
    {
		static  int i = 0;
		static  int bit = 8;
		static  int kill_count = 0;

		while (g_client_data.msg[i] != '\0')
		{
			while (--bit >= 0) {
				if ((g_client_data.msg[i] >> bit) & 1)
					exception_kill(kill(g_client_data.opponent_pid, SIGUSR1));
				else
					exception_kill(kill(g_client_data.opponent_pid, SIGUSR2));
				usleep(125);
				kill_count++;
			}
			bit = 8;
			i++;
		}
		ft_putnbr_fd(kill_count, 1);
		ft_putchar_fd('\n', 1);
		if (g_client_data.msg[i] == '\0')
		{
			while (bit-- > 0)
			{
				exception_kill(kill(g_client_data.opponent_pid, SIGUSR2));
				usleep(125);
			}
			pause();
		}
	}
	```

	아래 스크린샷처럼 32번의 kill 함수를 사용했다는 결과가 출력되었다.
	
	![image](https://user-images.githubusercontent.com/57256332/126058759-9342b1c9-c1ea-4349-a87e-a3f54d445ef9.png)

	ASCII 코드 경우에는 "a" 라는 메시지를 보낸다고 가정하였을 때는
	kill() 함수를 8번만 호출하여 시그널을 전송할 것이다.

	![image](https://user-images.githubusercontent.com/57256332/126059023-25e29499-e8a9-47a9-9ae4-00d0a4f78009.png)
	
	즉, 유니코드 문자는 문자 당 8Bit(1Byte) * 4 만큼 시그널이 전송되어져야 한다는 것을 알 수 있다.

	유니코드를 표현하기 위해 가변 길이 문자 인코딩 방식인 UTF-8 사용한다.<br>
	UTF-8 은 최소 1byte ~ 4byte 까지를 가변적으로 사용하게 되는 데 <br>이때 각 표현이 가능한 문자열의 크기에 따라 정해 지게 된다.<br>

	![image](https://user-images.githubusercontent.com/57256332/126059490-870e8740-6fa0-4c41-aabd-0e84c73e7fa1.png)

	| 👑 | 코드 |
	| --- | --- |
	| 유니코드 (16진수) | U+`1F451` |
	| HTML코드 (10진수) | &#`128081`; |
	
	따라서,👑 이모지의 유니코드 값이 `U+1F451` 이기 때문에 <br>출력하기위해서는 4Byte 만큼의 공간이 필요한 것이다.

	그렇기 때문에 32bit 크기 만큼의 문자를 서버로 보내기위해서는 32번의 시그널 전송이 이루어져야한다.

	[참고 - JaeSeoKim's Blog](https://jaeseokim.dev/C/C-%EC%9C%A0%EB%8B%88%EC%BD%94%EB%93%9C(unicode)%EC%97%90_%EB%8C%80%ED%95%B4_%EC%95%8C%EC%95%84%EB%B3%B4%EA%B8%B0(feat.42seoul_ft_printf)/)
<br>

---

# Text for TEST 

- Ascii

	* 100자 (100 byte)

			LoremipsumdolorsitametLoremipsumdolorsitametLoremipsumdolorsitametLoremipsumdolorsitametLoremipsumdo

	- 3,278 자 (3,278 byte)

			Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras efficitur scelerisque diam et placerat. Aenean lacinia facilisis egestas. Nulla fringilla velit sem, eu molestie odio porttitor id. Nulla et elit mollis, porta lorem at, cursus orci. Pellentesque id ultricies diam, in auctor erat. Nunc blandit lorem est, vitae pellentesque lacus tempus quis. Duis consectetur et mi in egestas. Sed vestibulum aliquet interdum. Duis quis neque vel erat placerat fermentum nec at lectus. In varius bibendum neque. Cras hendrerit mi vel tortor vestibulum finibus.

			Ut blandit lorem quam, ac interdum risus euismod ac. Pellentesque nec augue lacus. Vivamus lacus nunc, sagittis et ultrices id, tristique eu diam. Nulla quis leo ac lorem auctor placerat quis a ante. Sed mauris lorem, vestibulum ut laoreet viverra, ultricies sed dui. Donec convallis nulla nibh, eget hendrerit est luctus nec. Mauris sed turpis consectetur, varius lorem vel, lacinia erat. Donec in eleifend lectus, sed porta nibh. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur aliquam nulla at dolor placerat gravida. Duis aliquam justo nec neque auctor, eu tincidunt justo vestibulum. Mauris dapibus massa ac malesuada vestibulum. Pellentesque eu quam est. Nunc lectus ante, accumsan non sagittis at, vulputate nec neque. Donec ullamcorper erat non consequat interdum.

			Nunc luctus augue et erat vestibulum commodo. Proin cursus, lectus ut convallis lacinia, libero velit fringilla massa, eu rhoncus dui lacus id tellus. Aliquam posuere varius dapibus. Mauris congue semper dui ac mollis. Quisque accumsan aliquam augue, a ultrices odio euismod non. Duis vel justo mollis, volutpat dui fringilla, pretium metus. Donec dolor ante, congue id ullamcorper ac, maximus id justo. Mauris consequat facilisis sem in tincidunt. Maecenas vitae metus a magna congue mollis. Vivamus fringilla, metus et suscipit imperdiet, nulla dolor accumsan augue, id feugiat nisl quam ac lacus. Vestibulum lacinia ultricies fringilla. Integer est odio, imperdiet eget auctor vitae, consequat et ipsum. Praesent convallis dignissim varius. Morbi vel pulvinar arcu.

			Maecenas imperdiet nibh eget arcu eleifend, sed feugiat magna vehicula. Vivamus auctor consectetur lectus eu porttitor. Proin ac maximus dui. Duis fringilla quam euismod, sodales tellus sit amet, vestibulum leo. Curabitur sed mauris nibh. Vivamus laoreet nulla dolor, at faucibus mi blandit eu. Vivamus gravida metus justo, sit amet viverra arcu ullamcorper vitae. Nulla vel risus vel lorem dictum venenatis ut vitae eros. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec suscipit felis varius, fermentum dui eget, interdum eros.

			Suspendisse tristique arcu non egestas interdum. Aliquam vulputate efficitur tempus. Suspendisse neque mauris, vulputate non lacus sed, tristique lobortis risus. Interdum et malesuada fames ac ante ipsum primis in faucibus. Vivamus in mi placerat, vehicula dolor non, facilisis ligula. Maecenas at nisl nec arcu condimentum dictum. Nullam at ornare quam, a lobortis eros. Curabitur tincidunt, diam id ullamcorper interdum, lacus ipsum porttitor augue, condimentum ullamcorper est erat ut urna. Aenean lorem libero, pretium nec volutpat sed, faucibus sit amet arcu. Nam sit amet est sagittis eros blandit aliquet.

- Unicode

	- Emoji

			🖤∑∞☞★⚝✅🔥⌚☣☮🌏📱Ⅻ🚀€🍔🍦👑⚽🎵🎧♻

	- 200자 (400 byte)
		
			★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★

	- 500자 (1000byte)
			
			안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요

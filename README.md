
# <span style="color:yellow"/>Minitalk

## <span style="color:#00FF00"/>Execution

1.	`make` or `make all` or `make bonus`

2.	`bash ./server`

3.	`bash ./client [SERVER PID] [SEND MESSAGE]`

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

	```c
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
	sigaction 구조체에는 핸들러를 지정할 수 있는 2개의 함수 포인터가 존재한다.<br>
	
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
	서버와 연결하기 위해 ft_connection() 함수를 호출한다.
<br>

### 3. 클라이언트 PID 수신
	-	서버는 클라이언트의 PID를 저장할 변수를 선언한다.

	-	서버는 클라이언트가 보내는 신호에 따라 비트 값을 연산하여  
		클라이언트의 PID 값을 알아낸다.

			클라이언트에서 보내온 신호가 SIGUSR1 이라면 비트 값은 1.
			SIGUSR2 라면 비트 값은 0인 것으로 약속한다.
			2^0 자리부터 2^7 자리까지 신호에 따른 비트 값을 연산하여
			클라이언트의 PID 값을 알아내는 방식으로 설계해보았다.

2. ### 서버에게 메시지 전달 

	-	<span style="color:#F3F781"/>
	PID를 전달하는 과정은 서버에게 응답을 받지 않는 대신  
	usleep 함수를 통해 전송 딜레이를 발생시킨다.

		클라이언트가 서버에게 kill 함수를 통해 보내는 신호의 속도보다 
		서버에서 signal 함수로 받는 속도가 느리기 때문에 적절한 딜레이가 필요하다. 

	-	서버에게 정상적으로 PID를 전송하여 서버에서 PID 값을 정상적으로 저장을 했다면 
		같은 방식으로 Server에게 보낼 메시지의 각 문자 비트 값에 대한 신호를  
		반복적으로 보내어 서버가 메시지의 내용을 수신 및 해독할 수 있도록 한다.   

	-	클라이언트는 메시지의 각 문자의 비트 값을 보내고 pause() 함수를 통해 
		서버에서 신호가 올 때까지 대기한다.

	-	서버는 클라이언트가 보내는 각 문자의 비트 값을 정상적으로 수신하고 처리를 할 때마다   
		클라이언트에게 SIGUSR2 신호를 보낸다.

	-	클라이언트는 signal 함수를 통해 서버에서 보낸 SIGUSR2 신호를 수신하기 위해
		SIGUSR2 신호에 대한 핸들러 함수를 만들어 이에 대한 처리 과정을 할 수 있도록 한다.

			server_signal 이라는 전역 변수를 선언하여
			SIGUSR2 신호의 핸들러 함수에서 server_signal 변수 값을 조작하며
			다음 동작을 이어서 수행할 수 있도록 한다.

![image](https://user-images.githubusercontent.com/57256332/125564893-334c265e-b30b-4b9c-9b33-2418fef16f80.png)

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
# Text for TEST

- Ascii

	- 100자 (100 byte)

			LoremipsumdolorsitametLoremipsumdolorsitametLoremipsumdolorsitametLoremipsumdolorsitametLoremipsumdo

	- 3,278 자 (3,278 byte)

			Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras efficitur scelerisque diam et placerat. Aenean lacinia facilisis egestas. Nulla fringilla velit sem, eu molestie odio porttitor id. Nulla et elit mollis, porta lorem at, cursus orci. Pellentesque id ultricies diam, in auctor erat. Nunc blandit lorem est, vitae pellentesque lacus tempus quis. Duis consectetur et mi in egestas. Sed vestibulum aliquet interdum. Duis quis neque vel erat placerat fermentum nec at lectus. In varius bibendum neque. Cras hendrerit mi vel tortor vestibulum finibus.

			Ut blandit lorem quam, ac interdum risus euismod ac. Pellentesque nec augue lacus. Vivamus lacus nunc, sagittis et ultrices id, tristique eu diam. Nulla quis leo ac lorem auctor placerat quis a ante. Sed mauris lorem, vestibulum ut laoreet viverra, ultricies sed dui. Donec convallis nulla nibh, eget hendrerit est luctus nec. Mauris sed turpis consectetur, varius lorem vel, lacinia erat. Donec in eleifend lectus, sed porta nibh. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur aliquam nulla at dolor placerat gravida. Duis aliquam justo nec neque auctor, eu tincidunt justo vestibulum. Mauris dapibus massa ac malesuada vestibulum. Pellentesque eu quam est. Nunc lectus ante, accumsan non sagittis at, vulputate nec neque. Donec ullamcorper erat non consequat interdum.

			Nunc luctus augue et erat vestibulum commodo. Proin cursus, lectus ut convallis lacinia, libero velit fringilla massa, eu rhoncus dui lacus id tellus. Aliquam posuere varius dapibus. Mauris congue semper dui ac mollis. Quisque accumsan aliquam augue, a ultrices odio euismod non. Duis vel justo mollis, volutpat dui fringilla, pretium metus. Donec dolor ante, congue id ullamcorper ac, maximus id justo. Mauris consequat facilisis sem in tincidunt. Maecenas vitae metus a magna congue mollis. Vivamus fringilla, metus et suscipit imperdiet, nulla dolor accumsan augue, id feugiat nisl quam ac lacus. Vestibulum lacinia ultricies fringilla. Integer est odio, imperdiet eget auctor vitae, consequat et ipsum. Praesent convallis dignissim varius. Morbi vel pulvinar arcu.

			Maecenas imperdiet nibh eget arcu eleifend, sed feugiat magna vehicula. Vivamus auctor consectetur lectus eu porttitor. Proin ac maximus dui. Duis fringilla quam euismod, sodales tellus sit amet, vestibulum leo. Curabitur sed mauris nibh. Vivamus laoreet nulla dolor, at faucibus mi blandit eu. Vivamus gravida metus justo, sit amet viverra arcu ullamcorper vitae. Nulla vel risus vel lorem dictum venenatis ut vitae eros. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec suscipit felis varius, fermentum dui eget, interdum eros.

			Suspendisse tristique arcu non egestas interdum. Aliquam vulputate efficitur tempus. Suspendisse neque mauris, vulputate non lacus sed, tristique lobortis risus. Interdum et malesuada fames ac ante ipsum primis in faucibus. Vivamus in mi placerat, vehicula dolor non, facilisis ligula. Maecenas at nisl nec arcu condimentum dictum. Nullam at ornare quam, a lobortis eros. Curabitur tincidunt, diam id ullamcorper interdum, lacus ipsum porttitor augue, condimentum ullamcorper est erat ut urna. Aenean lorem libero, pretium nec volutpat sed, faucibus sit amet arcu. Nam sit amet est sagittis eros blandit aliquet.

- Unicode

	- 200자 (400 byte)
		
			★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★

	- 500자 (1000byte)
			
			안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요안녕하세요

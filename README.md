# Minitalk

	> make && ./server
	> ps | grep ./server | grep -v 'grep' | awk '{print $1}'

## 서버와 클라이언트 간의 통신

- ## 동작흐름 
	1. ### 서버 실행
		-	getpid() 함수를 통해 Server PID 터미널에 출력  

		-	Server 실행 & SIGNAL 대기 (SIGUSR1, SIGUSR2)

	2. ### 서버에게 현재 클라이언트 PID 전달
		-	getpid() 함수를 통해 Client PID를 얻어낸 후 
			ft_itoa() 함수를 통해 문자열로 변환
		
		-	Server PID로 문자열로 변환된 Client PID의 각 문자 비트 값에 대한 신호를   
			kill 함수를 통해 반복적으로 보내어 서버가 클라이언트의 PID 값을 수신 및 해독할 수 있도록 한다.   

		-	PID를 전달하는 과정은 서버에게 응답을 받지 않는 대신  
			usleep 함수를 통해 전송 딜레이를 발생시킨다.
		
				클라이언트가 서버에게 kill 함수를 통해 보내는 신호의 속도보다 
				서버에서 signal 함수로 받는 속도가 느리기 때문에 적절한 딜레이가 필요하다. 

	3. ### 클라이언트 PID 수신
		-	서버는 클라이언트의 PID를 저장할 변수를 선언한다.

		-	서버는 클라이언트가 보내는 신호에 따라 비트 값을 연산하여  
			클라이언트의 PID 값을 알아낸다.

				클라이언트에서 보내온 신호가 SIGUSR1 이라면 비트 값은 1.
				SIGUSR2 라면 비트 값은 0인 것으로 약속한다.
				2^0 자리부터 2^7 자리까지 신호에 따른 비트 값을 연산하여
				클라이언트의 PID 값을 알아내는 방식으로 설계해보았다.

	2. ### 서버에게 메시지 전달 
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

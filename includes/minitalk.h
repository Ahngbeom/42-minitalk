#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <unistd.h>
# include <signal.h>

struct sigaction act;

void client_with_connection(int signo, siginfo_t *siginfo, void *context);
void receive_message(int signo, siginfo_t *siginfo, void *context);

#endif
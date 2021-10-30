#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
// #include <errno.h>
#include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

static void	signal_handler(int sig)
{
	if (sig == SIGTERM)
		printf("SIGTERM captured\n");
	else if (sig == SIGQUIT)
		printf("SIGQUIT captured\n");
	else if (sig == SIGINT)
		printf("SIGINT captured\n");
	exit(1);
}


int	main(void)
{
	// signal(SIGTERM, SIG_IGN);
	//if ( )
	
	signal(SIGTERM, &printf("\n",1));
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &signal_handler);
	signal(SIGTERM, &signal_handler);
	signal(SIGQUIT, &signal_handler);
	signal(SIGINT, &signal_handler);
	//signal(SIGINT, SIG_DFL);
	while (1)
		pause();
}

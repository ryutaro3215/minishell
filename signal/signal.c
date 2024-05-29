#include "../include/signal.h"

void	interrupt_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_init(void)
{
	struct sigaction	quit_act;
	struct sigaction	interrupt_act;

	quit_act.sa_handler = SIG_IGN;
	quit_act.sa_flags = 0;
	sigemptyset(&quit_act.sa_mask);
	sigaction(SIGQUIT, &quit_act, NULL);

	interrupt_act.sa_handler = interrupt_handler;
	interrupt_act.sa_flags = 0;
	sigemptyset(&interrupt_act.sa_mask);
	sigaction(SIGINT, &interrupt_act, NULL);
}

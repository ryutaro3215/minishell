#include "../include/signal.h"

void	signal_init(void)
{
	struct sigaction	act;

	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

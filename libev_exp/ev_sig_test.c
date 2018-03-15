
#include <stdlib.h>
#include <ev.h>
#include <stdio.h>

static void
sigint_cb (struct ev_loop *loop, ev_signal *w, int revents)
{
    puts ( "signal ....." );
}

static void
exit_cb (struct ev_loop *loop, ev_signal *w, int revents)
{
    puts ( "eixt ....." );
	exit(0);
}

int main(int argc,char* argv[])
{
    struct ev_loop *loop = EV_DEFAULT;

    ev_signal signal_watcher;
    ev_signal signal_usr1;
    ev_signal_init (&signal_watcher, sigint_cb, SIGINT);
    ev_signal_start (loop, &signal_watcher);

    ev_signal_init (&signal_usr1, exit_cb, SIGQUIT);
    ev_signal_start (loop, &signal_usr1);

    ev_run (loop,0);

    return 0;
}

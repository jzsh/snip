/*	ref:
 *	http://blog.csdn.net/woxiaozhi/article/details/16963641
 */

#include <ev.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static void
sigint_cb (struct ev_loop *loop, ev_signal *w, int revents)
{
	printf("signal .....\n");
}

static void
exit_cb (struct ev_loop *loop, ev_signal *w, int revents)
{
	printf("exiting .....\n");
	sleep(2);
	exit(0);
}

// all watcher callbacks have a similar signature
// this callback is called when data is readable on stdin
static void
stdin_cb (EV_P_ ev_io *w, int revents)
{
	printf("[%d] stdin ready\n", revents);
	// for one-shot events, one must manually stop the watcher
	// with its corresponding stop function.
	ev_io_stop(EV_A_ w);

	// this causes all nested ev_run's to stop iterating
	ev_break (EV_A_ EVBREAK_ALL);
}

// another callback, this time for a time-out
static void
timeout_cb (EV_P_ ev_timer *w, int revents)
{
	printf("[%d] timeout\n", revents);
	ev_timer_stop(EV_A_ w);
	// this causes the innermost ev_run to stop iterating
	//ev_break(EV_A_ EVBREAK_ONE);
}

static void periodic_callback(struct ev_loop *loop,ev_periodic * w, int revents)
{
	printf("every 3 seconds\n");
	//ev_break(loop,EVBREAK_ALL);
}

int
main (void)
{
	// use the default event loop unless you have special needs
	struct ev_loop *loop = EV_DEFAULT;

	// every watcher type has its own typedef'd struct
	// with the name ev_TYPE
	ev_io stdin_watcher;
	ev_timer timeout_watcher;
	ev_signal signal_watcher;
	ev_signal signal_watcher2;
	ev_periodic periodic_watcher;

	// initialise an signal watcher, then start it
	// this one will watch for stdin to become readable
	ev_signal_init (&signal_watcher, sigint_cb, SIGINT); // CTRL + C
	ev_signal_start (loop, &signal_watcher);
	ev_signal_init (&signal_watcher2, exit_cb, SIGQUIT); // CTRL + 4
	ev_signal_start (loop, &signal_watcher2);

	// initialise an io watcher, then start it
	// this one will watch for stdin to become readable
	ev_io_init (&stdin_watcher, stdin_cb, /*STDIN_FILENO*/ 0, EV_READ);
	ev_io_start (loop, &stdin_watcher);

	// initialise a timer watcher, then start it
	// simple non-repeating 5.5 second timeout
	ev_timer_init (&timeout_watcher, timeout_cb, 5.5, 0.);
	ev_timer_start (loop, &timeout_watcher);

	ev_init(&periodic_watcher, periodic_callback);
	ev_periodic_set(&periodic_watcher,0,3,0);
	ev_periodic_start(loop,&periodic_watcher);

	// now wait for events to arrive
	ev_run (loop, 0);

	// break was called, so exit
	return 0;
}

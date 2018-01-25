# c

gets, fgets, scanf
Never use gets. It offers no protections against a buffer overflow vulnerability (that is, you cannot tell it how big the buffer you pass to it is, so it cannot prevent a user from entering a line larger than the buffer and clobbering memory).
Avoid using scanf. If not used carefully, it can have the same buffer overflow problems as gets. Even ignoring that, it has other problems that make it hard to use correctly.
Generally you should use fgets instead, although it's sometimes inconvenient (you have to strip the newline, you must determine a buffer size ahead of time, and then you must figure out what to do with lines that are too long–do you keep the part you read and discard the excess, discard the whole thing, dynamically grow the buffer and try again, etc.). There are some non-standard functions available that do this dynamic allocation for you (e.g. getline on POSIX systems, Chuck Falconer's public domain ggets function). Note that ggets has gets-like semantics in that it strips a trailing newline for you.

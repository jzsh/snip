
all:
	@gcc test.c
	@./a.out &
	@killall -USR1 a.out
	@killall -USR2 a.out
	@killall a.out

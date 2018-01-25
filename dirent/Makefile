all:prepare
	@gcc -g main.c
run:all
	@./a.out .
prepare:clean
	@mkdir nonempty-dir
	@cd nonempty-dir; touch a b c d
	@mkdir empty-dir
	@cd empty-dir
	@ln -sf nonempty-dir lnk_nonempty-dir
	@ln -sf empty-dir lnk_empty-dir
clean:
	@rm -rf nonempty-dir empty-dir lnk* a.out
.PHONY: clean

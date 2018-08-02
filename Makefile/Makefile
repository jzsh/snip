
world:

ifneq ($(OPENWRT_BUILD),1)
  override OPENWRT_BUILD=1
  export OPENWRT_BUILD
%::
	@echo "\033[33mfirst make world \033[0m"
	@make $@

else

world:FORCE
	@echo "\033[33msecond make world \033[0m"

.PHONY:FORCE

endif

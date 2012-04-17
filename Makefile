DIR_LIST=src/

all: Makefile.rules
	@echo -e '\e[0;34mStart building\e[0;33m\033[0m'
	@$(foreach var,$(DIR_LIST), make -C $(var) $@;)
	@echo -e '\e[0;34mDone\e[0;m'
	
clean:
	@echo -e '\e[0;32mStart cleaning\e[0;33m\033[0m'
	@$(foreach var,$(DIR_LIST), make -C $(var) $@;)
	rm -rf doc/html doc/man doc/latex
	@echo -e '\e[0;34mDone\e[0;m'
	
check: all
	cd check;./check.sh

distclean:clean
	@echo -e '\e[0;32mCleaning\e[0;33m All\e[0;m'
	@$(foreach var,$(DIR_LIST), make -C $(var) $@;)
	@rm -f Makefile.rules
	
doc: doc/Doxyfile
	@echo -e '\e[0;36mGenerating: \e[0;33m doc\e[0;m'
	@doxygen doc/Doxyfile
	@echo -e '\e[0;32mCompilation done !\033[0m'

Makefile.rules:
	@. ./configure
	
.PHONY: doc

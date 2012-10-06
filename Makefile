.PHONY: all doc clean distclean check

all:
	${MAKE} -C build/

doc:
	${MAKE} -C doc/
	${MAKE} -C doc/latex

clean:
	find . -type f -name '#*'   -exec rm -f "{}" \;
	find . -type f -name '*.o'   -exec rm -f "{}" \;
	find . -type f -name '*~'    -exec rm -f "{}" \;
	find . -type f -name '*.gch' -exec rm -f "{}" \;
	find . -type f -name '*.dot' -exec rm -f "{}" \;
	find . -type f -name '*.bz2' -exec rm -f "{}" \;
	find . -type f -name '*.gz' -exec rm -f "{}" \;
	find . -type f -name '*.aux'   -exec rm -f "{}" \;
	find . -type f -name '*.log'   -exec rm -f "{}" \;
	find . -type f -name '*.toc'   -exec rm -f "{}" \;

distclean: clean
	find . -type f -name '*.so'   -exec rm -f "{}" \;
	find . -type f -name '*.a'   -exec rm -f "{}" \;
	find . -type f -name 'CMakeCache.txt'   -exec rm -f "{}" \;
	rm -rf build/ test/build

check:
	@${MAKE} -C test/build
	@cd test/ && perl main.pl && cd ../

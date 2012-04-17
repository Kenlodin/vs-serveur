include ../Makefile.rules
include Makefile.rules

TARGET=server
TARGET_DIR=../

OBJS=$(SRCS:.cc=.o)
DEPS=$(SRCS:.cc=.d)

all:$(TARGET_DIR)$(TARGET)

$(TARGET_DIR)$(TARGET):$(OBJS)
	@echo -e '\e[0;32mStart compiling\e[0;33m $(TARGET)\e[0;m\e[0;31m'
	@echo -e '\e[0;32mLinking\e[0;33m $(TARGET)\e[0;m\e[0;31m'
	@$(CC) $(CCFLAGS) -o$(TARGET_DIR)$(TARGET) $(OBJS) $(LDFLAGS) \
	|| (echo -en '\033[0;0m' && false)
	@echo -e '\e[0;33m$(TARGET)\e[0;32m done\e[0;m'

%.o:%.cc
	@echo -e '\e[0;32mCompiling\e[0;33m $<\e[0;m \e[0;31m'
	@$(CC) $(CCFLAGS) -c -o$@ $< || (echo -en '\033[0;0m' && false)

-include $(DEPS)

clean:
	@echo -e '\e[0;32mCleaning \e[0;33m $(TARGET)\e[0;m'
	@rm -f $(OBJS) $(DEPS) $(TARGET)

distclean:
	@rm -f $(TARGET_DIR)$(TARGET) Makefile.rules

../Makefile.rules:
	@cd ../; ./configure

Makefile.rules:
	@cd ../; ./configure

#EOF

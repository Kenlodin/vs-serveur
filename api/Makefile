API_INC   =-I../include
TARGET   ?=a.so
OBJS_     =$(addprefix $M/, $(OBJS))
CPPFLAGS	= -std=c++0x
LDFLAGS  	=-fPIC -shared  -rdynamic -Wl,--export-dynamic

modules: $(OBJS_)
	g++ $(LDFLAGS) $< -o $M/$(TARGET)

%.o: %.cc
	g++ $(CPPFLAGS) $(API_INC) -c $^ -o $@

clean:
	rm -rf $M/*.o

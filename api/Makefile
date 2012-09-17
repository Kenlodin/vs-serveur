API_INC   =-I../include -DAPI__ -DMODULE__
TARGET   ?=a.so
OBJS_     =$(addprefix $M/, $(OBJS))
CPPFLAGS  =-fPIC -shared  -rdynamic -Wl,--export-dynamic

modules: $(OBJS_)
	g++ $(CPPFLAGS) $< -o $M/$(TARGET)

%.o: $M/%.c
	g++ $(API_INC) -c $^ -o $@

clean:
	rm -rf $M/*.o

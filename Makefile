OBJS := binomial_main.o binomial_slow.o binomial_fast.o
EXEC := binomial
CFLAGS := -g -Wall -Wextra

all: $(EXEC)

clean:
	$(RM) $(EXEC) $(OBJS) $(OBJS:.o=.d)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.d: %.c
	$(SHELL) -ec '$(CC) -MM $(CPPFLAGS) $< \
		| sed "s/$*\\.o/& $@/g" > $@'

include $(OBJS:.o=.d)

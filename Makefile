OBJS := binomial_main.o
EXEC := binomial
CXXFLAGS := -g -Wall -Wextra

all: $(EXEC)

clean:
	$(RM) $(EXEC) $(OBJS) $(OBJS:.o=.d)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

%.d: %.cpp
	$(SHELL) -ec '$(CXX) -MM $(CPPFLAGS) $< \
		| sed "s/$*\\.o/& $@/g" > $@'

include $(OBJS:.o=.d)

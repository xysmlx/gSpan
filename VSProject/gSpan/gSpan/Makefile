OBJS = main.o Solver.o GSPAN.o InputFilter.o Graph.o DFSCode.o
CC = g++
CFLAGS = -std=c++11 -Wall -Dxysmlx -O2 -g

gSpan: $(OBJS)
	$(CC) $(OBJS) -o gSpan

$(OBJS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	-rm gSpan $(OBJS)
CC     = gcc
OBJS   = quaternion.o main.o
LDLIBS = -lm
EXE    = main

all: $(EXE) run

run:
	./$(EXE)

%.o: %.c
	$(CC) -c $< -o $@

$(EXE): $(OBJS)
	$(CC) $(LDLIBS) $^ -o $@

clean:
	rm -f $(EXE) $(OBJS)

.PHONY: all clean

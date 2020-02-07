CC 	= gcc
CCFLAGS = -Wall -Werror
LDFLAGS	=
RM	= rm -f 
TARG 	= spiderman
SRCS 	= spiderman.c
BIN	= bin/

default: all

all: $(TARG)

$(TARG): $(SRCS)
	$(CC) -o $(BIN)$(TARG) $(SRCS) $(CCFLAGS)

clean veryclean:
	$(RM) $(BIN)$(TARG)


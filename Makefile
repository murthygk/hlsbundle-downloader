CC=g++
EXE=hlsdownloader

S_SRC= src/main.cpp
S_OBJS=	$(S_SRC:.cpp=.o)
LDFLAGS+= -lcurl

all: $(S_OBJS)
	$(CC) $(S_OBJS) $(LDFLAGS) -o $(EXE)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	find . -type f -name \*.o -exec rm {} \;
	rm -f $(EXE)

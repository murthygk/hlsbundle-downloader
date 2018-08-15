CC=g++
EXE=hlsdownloader

S_SRC= src/main.cpp src/HLSPlaylistDownloader.cpp
S_OBJS=	$(S_SRC:.cpp=.o)
CFLAGS+= -I headers --std=c++11 --stdlib=libc++
LDFLAGS+= -lcurl

all: $(S_OBJS)
	$(CC) $(S_OBJS) $(LDFLAGS) -o $(EXE)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	find . -type f -name \*.o -exec rm {} \;
	rm -f $(EXE)

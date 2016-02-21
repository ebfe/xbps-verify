CC ?= clang

CPPFLAGS ?= -D_DEFAULT_SOURCE

CFLAGS ?= -Wall -g -pipe
CFLAGS += -std=c99
CFLAGS += $(shell pkg-config libxbps --cflags)

LDFLAGS ?=

LIBS = $(shell pkg-config libxbps --libs)

xbps-verify: xbps-verify.o
	${CC} ${CPPFLAGS} ${CFLAGS} ${LDFLAGS} ${LIBS} -o $@ $^

clean:
	-@rm xbps-verify *.o

.PHONY: clean



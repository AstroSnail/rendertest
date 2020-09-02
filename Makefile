COMPILE=$(CC) -Werror=all -Wextra -Wpedantic -std=c99 -Os -D_POSIX_C_SOURCE=199309L $(NIX_CFLAGS_COMPILE) -Wl,$$(tr -s \  , <<<"$(NIX_LDFLAGS)")

all: test test2 shadertoy

install: install-test install-test2 install-shadertoy

.PHONY: all install install-test install-test2 install-shadertoy

test: test.c
	$(COMPILE) -lglfw -lGL test.c -o $@

test2: test2.c
	$(COMPILE) -lglfw test2.c -o $@

shadertoy: shadertoy.c
	$(COMPILE) -lGLEW -lglfw -lGL shadertoy.c -o $@

install-test: test
	install -D test $(out)/bin/test

install-test2: test2
	install -D test2 $(out)/bin/test2

install-shadertoy: shadertoy
	install -D shadertoy $(out)/bin/shadertoy

COMPILE=$(CC) -Werror=all -Wextra -Wpedantic -std=c99 -Os -D_POSIX_C_SOURCE=199309L $(NIX_CFLAGS_COMPILE) -Wl,$$(tr -s \  , <<<"$(NIX_LDFLAGS)")

all: test test2

install: install-test install-test2

.PHONY: all install install-test install-test2

test: test.c
	$(COMPILE) -lglfw -lGL test.c -o $@

test2: test2.c
	$(COMPILE) -lglfw test2.c -o $@

install-test: test
	install -D test $(out)/bin/test

install-test2: test2
	install -D test2 $(out)/bin/test2

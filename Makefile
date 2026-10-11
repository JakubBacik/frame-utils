CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -Iinclude -Iextern/Unity/src
SRC     = src/frame_utils.c
UNITY   = extern/Unity/src/unity.c
TESTS   = test/test_frame_utils.c

.PHONY: test clean

test: build/test_runner
	./build/test_runner

build/test_runner: $(SRC) $(UNITY) $(TESTS)
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf build
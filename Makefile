CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2

routes: routes.c
	$(CC) $(CFLAGS) routes.c -o routes

test_routes: test_routes.c routes.c
	$(CC) $(CFLAGS) -UNDEBUG test_routes.c -o test_routes

.PHONY: test clean
test: routes test_routes
	./test_routes

clean:
	rm -f routes test_routes

CC=gcc

.PHONY: clean

build: main.o conditions.o errors.o functions.o queue.o
	$(CC) main.o conditions.o errors.o functions.o queue.o -o quadtree

conditions.o: conditions.c conditions.h structs.h
	$(CC) -c conditions.c

queue.o: queue.c queue.h
	$(CC) -c queue.c

errors.o: errors.c errors.h
	$(CC) -c errors.c

functions.o: functions.c functions.h structs.h queue.h
	$(CC) -c functions.c

main.o: main.c conditions.h errors.h
	$(CC) -c main.c

verify.o: verify.c
	$(CC) -c verify.c

verify: verify.o conditions.o errors.o functions.o queue.o
	$(CC) verify.o conditions.o errors.o functions.o queue.o -o verify

run:
	./tema2

valgrind: tema2
	valgrind --leak-check=yes --show-leak-kinds=all --track-origins=yes ./tema2

tidy:
	clang-tidy *.c *.h -checks='-*,cppcoreguidelines*' --warnings-as-errors='-*,cppcoreguidelines*' -header-filter=.*

lint:
	cpplint --filter=-legal/copyright,-build/include_subdir,-readability/casting \
        --linelength=80 *.c *.h

style:
	/usr/bin/checkpatch.pl --tab-size=4 --no-tree --show-types --strict --terse \
	--ignore="SPDX_LICENSE_TAG,LEADING_SPACE,CODE_INDENT,CAMELCASE,BLOCK_COMMENT_STYLE,NEW_TYPEDEFS" -f *.c *.h

archive:
	zip -r tema2.zip \
	Makefile README \
	conditions.c conditions.h \
	errors.c errors.h \
	main.c structs.h \
	queue.h queue.c \
	errors.c errors.h \
	functions.c functions.h

remove_archive:
	rm -r tema2.zip

clean:
	rm -f tema2 main.o conditions.o errors.o
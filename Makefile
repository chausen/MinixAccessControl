SRC = src/
TEST = test/
NEWFILES =  get_tag set_tag access
CC = clang
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: $(NEWFILES) patch man

get_tag:
	cp $(SRC)get_tag.c /usr/src/lib/libc/sys-minix/

set_tag:
	cp $(SRC)set_tag.c /usr/src/lib/libc/sys-minix/

access:
	cp $(SRC)access.c /usr/src/servers/pm/

patch:
	patch -p0 < master.patch

man:
	cp man/get_tag.2 /usr/man/man2/ && cp man/set_tag.2 /usr/man/man2/

build:
	cd /usr/src/include && make dependall install \
		&& cd /usr/src/lib && make dependall install \
		&& cd /usr/src/releasetools && make install

test: gettag settag p1test

gettag: gettag.o
	$(CC) $(LFLAGS) gettag.o -o $(TEST)gettag

gettag.o: $(TEST)gettag.c $(SRC)/usr/src/include/unistd.h
	$(CC) $(CFLAGS) $(TEST)gettag.c

settag: settag.o
	$(CC) $(LFLAGS) settag.o -o $(TEST)settag

settag.o: $(TEST)settag.c $(SRC)/usr/src/include/unistd.h
	$(CC) $(CFLAGS) $(TEST)settag.c

p1test: p1test.o
	$(CC) $(LFLAGS) p1test.o -o $(TEST)p1test

p1test.o: $(TEST)p1test.c $(SRC)/usr/src/include/unistd.h
	$(CC) $(CFLAGS) $(TEST)p1test.c

tar:
	tar -cf project1_tar_clay_hausen_sp17.tar Makefile \
		man master.patch src test

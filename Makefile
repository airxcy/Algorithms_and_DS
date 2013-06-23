CC = g++ -std=c++0x
CFLAGS=-c -Wall -O0
DLDFLAGS= -L. -llkdlist -O0
SLDFLAGS= -L. -llkdlist

dynamicl: so dynamic_test 

staticl: static_test clean

so: liblkdlist.so
	sudo ldconfig
dynamic_test: test.o
	$(CC) test.o -o test $(DLDFLAGS)
static_test: test.o liblkdlist.a
	$(CC) test.o -o test $(SLDFLAGS)
test.o: test.cpp lkdlist.h
	$(CC) test.cpp $(CFLAGS)

liblkdlist.so: lkdlist.o
	$(CC) lkdlist.o -o liblkdlist.so -shared
liblkdlist.a: lkdlist.o
	ar rc liblkdlist.a lkdlist.o

lkdlist.o: lkdlist.cpp lkdlist.h
	$(CC) lkdlist.cpp $(CFLAGS) -fPIC

clean:
	rm -rf *.o

#ar rc libtest.a bar.o foo.o
#g++ -c test.cpp
#g++ test.o -L./ -ltest -o test

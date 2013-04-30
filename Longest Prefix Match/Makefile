CC=g++
OBJS=main.o ASMgr.o IPv4Trie.o IPv6Trie.o
BIN=lpm

all: $(OBJS)
	$(CC) -O3 -o $(BIN) main.cpp ASMgr.cpp IPv4Trie.cpp IPv6Trie.cpp

debug: $(OBJS)
	$(CC) -DDEBUG -o $(BIN) main.cpp ASMgr.cpp IPv4Trie.cpp IPv6Trie.cpp

run:
	./lpm -i asns.txt < ip.txt > out.txt

clean:
	rm -f $(BIN) *.o

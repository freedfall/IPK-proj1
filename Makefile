CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lm
BINDIR = bin

all: directories ipkcpc

ipkcpc: $(BINDIR)/main_logic.o $(BINDIR)/TCP_client.o $(BINDIR)/UDP_client.o
	$(CC) $(CFLAGS) -o ipkcpc $(BINDIR)/main_logic.o  $(BINDIR)/TCP_client.o $(BINDIR)/UDP_client.o $(LIBS)

$(BINDIR)/main_logic.o: main_logic/main_logic.c main_logic/main_logic.h
	$(CC) $(CFLAGS) -c main_logic/main_logic.c -o $(BINDIR)/main_logic.o

$(BINDIR)/TCP_client.o: TCP_client/TCP_client.c TCP_client/TCP_client.h
	$(CC) $(CFLAGS) -c TCP_client/TCP_client.c -o $(BINDIR)/TCP_client.o

$(BINDIR)/UDP_client.o: UDP_client/UDP_client.c UDP_client/UDP_client.h
	$(CC) $(CFLAGS) -c UDP_client/UDP_client.c -o $(BINDIR)/UDP_client.o

directories: $(BINDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -f $(BINDIR)/*.o ipkcpc
	rmdir $(BINDIR)

all: recv sender
recv.o: recv.cpp
	g++ recv.cpp -o revc.out

sender: sender.cpp
	g++ sender.cpp -o sender.out

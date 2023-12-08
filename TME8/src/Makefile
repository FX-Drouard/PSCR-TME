all: ServerSocket.o Socket.o
	g++ -o server server.cpp $^

client : ServerSocket.o Socket.o
	g++ -o client client.cpp $^
	
clean :
	rm -f *.o server

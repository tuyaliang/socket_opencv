all:server client
server:
	g++ `pkg-config opencv --cflags` SocketMatTransmissionServer.cpp Server.cpp -o server `pkg-config opencv --libs`
client:
	g++ `pkg-config opencv --cflags` SocketMatTransmissionClient.cpp Client.cpp -o client `pkg-config opencv --libs`
clean:all
	rm all

all: host client

host: host.cpp
	g++ host.cpp -o host -lX11 -lGL

client: client.cpp
	g++ client.cpp -o client -lX11 -lGL

clean:
	rm client host


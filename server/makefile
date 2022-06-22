server:server.cpp server_fun.o config.h
	g++ -w -O server.cpp server_fun.o -o server 
server_fun.o:server_fun.cpp server_fun.h
	g++ -c server_fun.cpp -o server_fun.O
clean:
	rm *.o server
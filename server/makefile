server:server.cpp server_fun.o config.h diffiehellman_work.o server.o
	g++ -w -O -pthread server.o server_fun.o diffiehellman_work.o -lcrypto -o server
server.o:server.cpp
	g++ -c server.cpp -o server.o
server_fun.o:server_fun.cpp server_fun.h config.h
	g++ -c server_fun.cpp -o server_fun.o
diffiehellman_work.o:diffiehellman_work.cpp diffiehellman_work.h config.h
	g++ -c diffiehellman_work.cpp -o diffiehellman_work.o
clean:
	rm *.o server
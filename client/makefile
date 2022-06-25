client:client.o client_fun.o config.h diffiehellman_work.o
	g++ -w -O client.o client_fun.o diffiehellman_work.o -lcrypto -o client
client.o:client.cpp
	g++ -c client.cpp -o client.o
client_fun.o:client_fun.cpp client_fun.h  config.h
	g++ -c client_fun.cpp -o client_fun.o
diffiehellman_work.o:diffiehellman_work.cpp diffiehellman_work.h config.h
	g++ -c diffiehellman_work.cpp -o diffiehellman_work.o
clean:
	rm *.o client
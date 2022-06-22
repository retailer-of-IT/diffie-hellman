client:client.cpp client_fun.o config.h
	g++ -w -O client.cpp client_fun.o -o client
client_fun.o:client_fun.cpp client_fun.h
	g++ -c client_fun.cpp -o client_fun.O
clean:
	rm *.o client
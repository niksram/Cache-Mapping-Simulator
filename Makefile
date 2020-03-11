a.out: client.o cache_mapper.o
	g++ client.o cache_mapper.o
cache_mapper.o: cache_mapper_header.h cache_mapper.cpp
	g++ -c cache_mapper_header.h cache_mapper.cpp
client.o: cache_mapper_header.h client.cpp
	g++ -c cache_mapper_header.h client.cpp
clean:
	rm -f client.o cache_mapper.o cache_mapper_header.h.gch client cache_mapper
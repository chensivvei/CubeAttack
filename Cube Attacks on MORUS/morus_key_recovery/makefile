morus_key_recovery: morus_key_recovery.o morus_encrypt.o
	g++ -o morus_key_recovery $^

morus_encrypt.o: morus_encrypt.cpp morus_cubes.h
	g++ -c morus_encrypt.cpp

morus_key_recovery.o: morus_key_recovery.cpp morus_encrypt.h morus_cubes.h
	g++ -c morus_key_recovery.cpp

.PHONY:clean
clean:
	rm *.o 

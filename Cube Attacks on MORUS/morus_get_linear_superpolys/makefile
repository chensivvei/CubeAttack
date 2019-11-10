morus_get_linear_superpolys: morus_get_linear_superpolys.o morus_encrypt.o
	g++ -o morus_get_linear_superpolys $^

morus_get_linear_superpolys.o: morus_get_linear_superpolys.cpp morus_encrypt.h morus_cube.h generate_random_value_using_AES.h
	g++ -maes -c morus_get_linear_superpolys.cpp

morus_encrypt.o: morus_encrypt.cpp morus_cube.h 
	g++ -c morus_encrypt.cpp

.PHONY:clean
clean:
	rm *.o 

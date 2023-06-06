all:
	g++ -o3 src/*.cpp lib/GLAD/src/*  -std=c++17                 \
	-ldl -lsfml-graphics -lsfml-window -lsfml-system  -lGL      \
	-Iinclude                                                   \
	-Ilib/                                                      \
	-Ilib/GLAD/include                                          \
	-Ilib/SFML/include                                          \
	-Llib/SFML/lib                                              \
	-o bin/a.out && bin/./a.out         
check:
	/home/nour/valgrind/./valgrind  ./bin/a.out        /*latest valgrind version*/                \
	# valgrind  ./bin/a.out                                /*old valgrind version*/               \
	--leak-check=full  -s    --leak-check=full --show-reachable=yes --show-leak-kinds=all         \
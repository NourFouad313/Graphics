all:
	g++ -o3 src/*.cpp -std=c++17 \
	-ldl -lSDL3 -lGLEW -lGL      \
	-Iinclude                    \
	-Llib/SDL3                   \
	-Llib/GLEW                   \
	-o bin/a.out && bin/./a.out
check:
	/home/nour/valgrind/./valgrind  ./bin/a.out        /*latest valgrind version*/                \
	# valgrind  ./bin/a.out                                /*old valgrind version*/               \
	--leak-check=full  -s    --leak-check=full --show-reachable=yes --show-leak-kinds=all         \
    --error-exitcode=1 --track-origins=yes --log-file=LOG_FILE_NAME -v EXECUTABLE_NAME         
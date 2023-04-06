linux:
	clang -v src/*.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o bin/main
	./bin/main
win:
	clang -v src/*.cpp -lraylib -lopengl32 -lgdi32 -lwinmm -o bin/main
	bin\main
clean:
	rm -rf bin/*
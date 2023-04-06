linux:
	mkdir bin
	clang -v src/*.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o bin/main
	./bin/main
win:
	mkdir bin
	clang -v src/*.cpp -lraylib -lopengl32 -lgdi32 -lwinmm -o bin/main
	bin\main
clean:
	rm -rf bin/*

all:
	@gcc -o build/out src/main.c -lm -lGL -lGLU -lglut

run:
	@./build/out

clean:
	@rm build/out

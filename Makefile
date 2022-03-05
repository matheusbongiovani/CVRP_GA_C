# valgrind --leak-check=full --track-origins=yes -v ./trab1 ./exemplos/0.txt 3 out.txt

# all: comp 
# 	./trab1 ./exemplos/0.txt 3 out.txt
	
comp:  gcc
	@echo "Compilado."

#-Wall
gcc: main.c ponto.c 
	gcc -o main main.c grafo.c leitura.c ponto.c listaPontos.c -lm -g

clean: 
	@rm -f *.o main
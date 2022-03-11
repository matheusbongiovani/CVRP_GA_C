# valgrind --leak-check=full --track-origins=yes -v ./main ./A-n32-k5.vrp 

comp:  gcc
	@echo "Compilado."

#-Wall
gcc: main.c ponto.c 
	gcc -o main main.c  leitura.c ponto.c listaPontos.c grafo.c genetics.c -g -lm 

clean: 
	@rm -f *.o main
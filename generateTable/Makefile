# valgrind --leak-check=full --track-origins=yes -v ./main ./A-n32-k5.vrp 

comp:  gcc
	@echo "Compilado."

#-Wall
gcc: main.c ponto.c 
	gcc -o main main.c  leitura.c ponto.c vetorPontos.c grafo.c genetics.c -g3 -lm 

clean: 
	@rm -f *.o main
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"
#include "grafo.h"
#include "listaPontos.h"
#include "ponto.h"


int main(int argc, char ** argv) {
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    printf("Starting of the program, start_t = %ld\n", start_t);

    FILE * file = NULL;
    file = inicializaArquivo(file, argv[1]);

    /* Declaração do buffer */
    size_t bufsize = 1;
    char * buffer = defineBuffer(file, bufsize);

    return 0;
}

char * defineBuffer (FILE * file, size_t bufsize){
    /* Lê a primeira linha do arquivo e guarda no buffer */

    char * buffer = NULL;
    buffer = (char *)malloc(bufsize * sizeof(char));
    getline(&buffer, &bufsize, file);

    return buffer;
}

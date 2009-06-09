/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#ifndef HAVE_PARSER_H
#define HAVE_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/graph_aux.h"

#define MAX_BUFFER_SIZE 255
#define INIT_IN_ZERO 1

struct request_info {
	char type; /* tipo da demanda */
	int s; /* vertice origem */
	int t; /* vertice destino */
};

struct graph {
	int v; /* n de vertices */
	int e; /* n de arestas */
	int s; /* vertice origem */
	int t; /* vertice destino */
	float **cost; /* matriz de adjacencia para custos */
};

struct request {
	int n; /* n de demandas */
	struct request_info *path;
};

struct graph_aux {
	int v; /* n de vertices */
	int e; /* n de arestas */
	struct vertex_aux *V; /* Lista de adjacencia do grafo auxiliar */
};

/* 
 * graph_parser: Guarda as informacoes do arquivo de entrada na
 * estrutura graph. 
 * Retorna 0 em caso de sucesso e 1 caso contrario.
 */
int graph_parser(const char *filename, struct graph *G);

/*
 * request_parser: Guarda as informacoes do arquivo de demanda na
 * estrutura request. 
 * Retorna 0 em caso de sucesso e 1 caso contrario.
 */
int request_parser(const char *filename, struct request *r);

/*
 * graph_aux_parser: Guarda as informacoes do grafo auxiliar na
 * estrutura graph_aux. 
 * Retorna 0 em caso de sucesso e 1 caso contrario.
 */
int graph_aux_parser(const char *filename, struct graph_aux *G);

/*
 * free_graph: Libera a memoria usada pela estrutura graph.
 */
void free_graph(struct graph G);

/*
 * free_request: Libera a memoria usada pela estrutura request.
 */
void free_request(struct request r);

/*
 * free_graph_aux: Libera a memoria usada pela estrutura request.
 */
void free_graph_aux(struct graph_aux G);

/* DEBUG FUNCTIONS */

/* 
 * print_graph: imprime as informacoes contidas na estrutura
 * graph lida.
 */
void print_graph(struct graph G);

/* 
 * print_request: imprime as informacoes contidas na estrutura
 * request lida.
 */
void print_request(struct request r);

/* 
 * print_graph_aux: imprime as informacoes contidas na estrutura
 * graph_aux lida.
 */
void print_graph_aux(struct graph_aux G);

#endif
/* ! HAVE_PARSER_H */

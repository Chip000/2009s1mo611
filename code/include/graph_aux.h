/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#ifndef HAVE_GRAPH_AUX_H
#define HAVE_GRAPH_AUX_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"
#include "../include/struct_route.h"
#include "../include/neighbor.h"

struct vertex_aux {
	int label; /* rotulo do vertice */
	int s; /* vertice origem do caminho */
	int t; /* vertice destino do caminho */
	struct route *p; /* Caminho representado */
	struct neighbor *nb; /* vizinhos do vertice atual */
	struct vertex_aux *next;
};

/*
 * create_struct_vertex_aux: Cria o no cabeca da lista de adjacencia
 */
struct vertex_aux *create_struct_vertex_aux(void);

/*
 * get_e_gaux: Retorna a quantidade de arestas na lista G
 */
int get_e_gaux(struct vertex_aux *G);

/*
 * insert_new_vertex_aux: Insere um novo vertice em G
 * retorna 0 se ocorreu a insercao e 1 cc
 */
int insert_new_vertex_aux(struct vertex_aux *G, struct route *p, 
			  int s, int t);

/*
 * insert_new_edge_gaux: Insere uma nova aresta em G
 * retorna 0 se ocorreu a insercao e 1 cc
 */
int insert_new_edge_gaux(struct vertex_aux *G, int i, int j);

/*
 * update_vertex_aux_path: Atualiza o path representado pelo vertice
 * retorna 1 se atualizou e 0 cc
 */
int update_vertex_aux_path(struct vertex_aux *G, int u, struct route *p);

/*
 * update_vertex_aux_label: Atualiza os labels de todos os vertices do grafo
 * auxiliar
 */
void update_vertex_aux_label(struct vertex_aux *G);

/*
 * remove_vertex_aux: Remove o vertice u da struct vertex_aux
 * retorna 0 se ocorreu a remocao e 1 cc
 */
int remove_vertex_aux(struct vertex_aux *G, int u);

/*
 * remove_edge_gaux: Remove uma aresta em G
 * retorna 0 se ocorreu a remocao e 1 cc
 */
int remove_edge_gaux(struct vertex_aux *G, int i, int j);

/*
 * free_vertex_aux: Libera a memoria da estrutura vertex_aux.
 */
void free_vertex_aux(struct vertex_aux *G);

/* Funcoes de escrita em arquivo */
/*
 * print2file_vertex_aux: Imprime em um arquivo as informacoes da 
 * struct vertex_aux
 */
void print2file_vertex_aux(FILE *f, struct vertex_aux *G);

#endif
/* ! HAVE_GRAPH_AUX_H */

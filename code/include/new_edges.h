/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#ifndef HAVE_NEW_EDGES_H
#define HAVE_NEW_EDGES_H

#include <stdio.h>
#include <stdlib.h>

struct new_edges {
	int u;
	int v;
	struct new_edges *next;
};

/* 
 * create_struct_new_edges: Cria o no cabeca da lista new_edges 
 */
struct new_edges *create_struct_new_edges(void);

/*
 * insert: Insere a aresta na estrutura
 * retorna 0 se ocorreu a insercao e 1 cc
 */
int insert(struct new_edges *e, int i, int j);

/*
 * free_struct_new_edges: Libera a memoria usada pela estrutura new_edges
 */
void free_struct_new_edges(struct new_edges *e);

/*
 * print2file_struct_new_edges: Imprime a rota de s a t no arquivo 
 * especificado para o grafo auxiliar.
 * retorna 1 se ocorreu a impressao, 0 se a rota e vazia e -1 cc
 */
int print2file_struct_new_edges(FILE *f, struct new_edges *e);

#endif

/* ! HAVE_NEW_EDGES_H */

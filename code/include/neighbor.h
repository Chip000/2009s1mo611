/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#ifndef HAVE_NEIGHBOR_H
#define HAVE_NEIGHBOR_H

#include <stdio.h>
#include <stdlib.h>

struct neighbor {
	int label; /* rotulo do vertice */
	struct neighbor *next;
};

/*
 * create_neighbor: Cria o no cabeca da lista
 */
struct neighbor *create_neighbor(void);

/*
 * insert_new_neighbor: Insere um novo vizinho em u
 * retorna 0 se ocorreu a insercao e 1 cc
 */
int insert_new_neighbor(struct neighbor *u, int v);

/*
 * update_neighbor: Atualiza o rotulo do vertice olabel para nlabel na
 * vizinhanca
 * retorna 0 se ocorreu a atualizacao e 1 cc
 */
int update_neighbor(struct neighbor *u, int olabel, int nlabel);

/*
 * remove_neighbor: Remove o vizinho v de u
 * retorna 0 se ocorreu a remocao e 1 cc
 */
int remove_neighbor(struct neighbor *u, int v);

/*
 * free_neighbor: Libera memoria alocada pela struct neighbor
 */
void free_neighbor(struct neighbor *nb);

/*
 * print2file_neighbor: Imprime a vizinhanca de u.
 */
void print2file_neighbor(FILE *f, int u, struct neighbor *nb);

#endif
/* ! HAVE_NEIGHBOR_H */

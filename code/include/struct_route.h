/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#ifndef HAVE_STRUCT_ROUTE_H
#define HAVE_STRUCT_ROUTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

/* Estrutura que armazena as info de uma aresta */
struct edge {
	int i;
	int j;
	float cost;
};

/* Estrutura que guarda uma rota */
struct route {
	struct edge e;
	struct route *next;
};

/* 
 * create_struct_route: Cria o no cabeca da lista route 
 */
struct route *create_struct_route(void);

/*
 * insert_new_edge: Insere a aresta na rota P
 * retorna 0 se ocorreu a insercao e 1 cc
 */
int insert_new_edge(struct route *P, int i, int j, float c);

/*
 * remove_edge: Remove a aresta (u, v) da rota P
 * retorna 0 se ocorreu a remocao e 1 cc
 */
int remove_edge(struct route *P, int u, int v);

/*
 * in_path: Verifica se o vertice u ja esta no caminho
 * retorna 0 caso u nao esta no caminho e 1 cc
 */
int in_path(struct route *P, int u);

/*
 * edge_in_path: Verifica se a aresta (u,v) ja esta no caminho
 * retorna 0 caso u nao esta no caminho e 1 cc
 */
int edge_in_path(struct route *P, int u,int v);

/*
 * route_len: Calcula o tamanho da rota
 */
int route_len(struct route *P);

/*
 * cpyroute: copia a rota src para a rota dest
 */
void cpyroute(struct route *dest, struct route *src);

/*
 * print_route_path: Imprime a rota de s a t no arquivo especificado
 * retorna 1 se ocorreu a impressao, 0 se a rota e vazia e -1 cc
 */
int print_route_path(FILE *f, struct route *P);

/*
 * print2file_struct_route: Imprime a rota de s a t no arquivo especificado
 * para o grafo auxiliar.
 * retorna 1 se ocorreu a impressao, 0 se a rota e vazia e -1 cc
 */
int print2file_struct_route(FILE *f, struct route *P);

/*
 * free_struct_route: Libera a memoria usada pela estrutura route
 */
void free_struct_route(struct route *P);

#endif 
/* ! HAVE_STRUCT_ROUTE_H */

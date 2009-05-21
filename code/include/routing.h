/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#ifndef HAVE_ROUTING_H
#define HAVE_ROUTING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "../include/shortest_path.h"
#include "../include/struct_route.h"

/* Estrutura que guarda a melhor solucao */
struct best {
	float cost;
	struct route *p;
};

/*
 * min_route_aux: Algoritmo de branch-and-bound para encontrar a rota
 * minima com penalizacao.
 * Entrada:
 *   - Matriz com as distancias das arestas de G
 *   - Numero de vertices
 *   - Vertice origem
 *   - Vertice destino
 *   - Custo do caminho atual
 *   - Penalizacao
 *   - Numero de arestas criadas na triangulacao
 * Saida:
 *   - Conjunto solução
 *   - Custo do caminho
 */
void min_route_aux(struct best *b, float **G, int n, int s, int t, 
		   float w, float a, int T);

/*
 * min_route: encontra a rota minima de s para t
 * para o grafo dado.
 * Entrada:
 *   - Matriz com as distancias das arestas de G
 *   - Numero de vertices
 *   - Vertice origem
 *   - Vertice destino
 *   - Penalizacao
 *   - Numero de arestas criadas na triangulacao
 * Saida:
 *   - Conjunto solução
 *   - Custo do caminho
 */
void min_route(struct best *b, float **G, int n, int s, int t, 
	       float a, int T);

#endif 
/* ! HAVE_ROUTING_H */

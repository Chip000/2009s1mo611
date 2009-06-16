/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#ifndef HAVE_CHORDAL_H
#define HAVE_CHORDAL_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/neighbor.h"
#include "../include/graph_aux.h"
#include "../include/parser.h"
#include "../include/routing.h"

/*
 * graph_aux_shortest_path: Determina o caminho mais curto do
 * vertice u para o vertice v em G.
 * Entrada:
 *   - Grafo auxiliar
 *   - Vertice origem
 * Saida:
 *   - Lista de predecessores
 *   - Vetor com as distancias
 */
void graph_aux_shortest_path(struct graph_aux *G, int s,
			     float **dist, int **prev);

/*
 * triangulation: Retorna o numero de arestas necessarias para
 * tornar o grafo G cordal com a adicao do vertice new
 */
int triangulation(struct graph_aux *G, int new, int s, int t, 
		  int *prev);

/*
 * gen_graph_aux: Gera o grafo auxiliar (cordal) a partir das 
 * info contidas na struct request
 * Entrada:
 *   - Grafo auxiliar
 *   - Topolagia da rede
 *   - Info de demanda
 *   - Penalizacao
 * Saida:
 *   - Grafo auxiliar
 *   - 0 em caso de sucesso das operacoes e 1 cc
 */
int gen_graph_aux(struct graph_aux *G, struct graph R,
		  struct request req, float a, const char *fname);

#endif
/* ! HAVE_CHORDAL_H */

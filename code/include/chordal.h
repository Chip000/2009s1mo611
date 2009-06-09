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

#endif
/* ! HAVE_CHORDAL_H */

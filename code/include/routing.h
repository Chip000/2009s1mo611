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

#define INF FLT_MAX

/*
 * shortest_path: Utiliza o algoritmo de Dijkstra para encontrar 
 * o caminho mais curto de s a t em um grafo G.
 * Entradas: 
 *   - Matriz de adjacencia contendo as distancias das arestas
 *   - Numero de vertices do grafo.
 *   - Vertice origem
 *   - Vertice destino
 * Saidas:
 *   - Conjunto solucao
 *   - Custo do caminho mais curto
 */
float shortest_path(float **G, int n, int s, int t, int ***x);


/* DEBUG FUNCTIONS */

/*
 * print_shortest_path: Imprime o custo e o caminho mais curto 
 * da solucao dada.
 */
void print_shortest_path(int **x, int n, int s, int t, float cost);

#endif 
/* ! HAVE_ROUTING_H */

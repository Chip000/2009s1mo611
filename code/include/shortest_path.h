/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#ifndef HAVE_SHORTEST_PATH_H
#define HAVE_SHORTEST_PATH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define INF FLT_MAX

/*
 * shortest_path: Utiliza o algoritmo de Dijkstra para encontrar o 
 * caminho mais curto de s a todos os outros vértices em um grafo G.
 * Entrada: 
 *   - Matriz de adjacencia contendo as distancias das arestas
 *   - Numero de vertices do grafo.
 *   - Vertice origem
 * Saida:
 *   - Vetor com as distancias
 */
void shortest_path(float **G, int n, int s, float **dist);

/* DEBUG FUNCTIONS */

/*
 * print_shortest_path: Imprime o custo e o caminho mais curto 
 * da solucao dada.
 */
void print_shortest_path(int **x, int n, int s, int t, float cost);

#endif 
/* ! HAVE_SHORTEST_PATH_H */

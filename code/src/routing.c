/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include "../include/routing.h"

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
		   float w, float a, int T)
{

	int u;
	float cost;
	float *dist;
	
	/* Inicializacao */
	dist = (float *) malloc(n * sizeof(float));

	cost = 0;

	for (u = 0; u < n; u ++) {
		if ((G[s][u] != 0) && (in_path(b->p, u) == 0))  {
			/* bem incompleto*/
			cost = w + G[s][u]; 
			if ((u == t) && ((cost + a * T) < b->cost)) {
				b->cost = cost;
				insert_new_edge(b->p, s, u, G[s][u]);
			}
			else {
				shortest_path(G, n, u, &dist);
				if ((cost + dist[t]) < b->cost) {
					min_route_aux(b, G, n, u, t,
						      cost, a, T);
				}
			}
		}
	}

	return;

} /* min_route_aux */

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
	       float a, int T)
{

	b->cost = INF;
	b->p = create_struct_route();

        min_route_aux(b, G, n, s, t, 0, a, T);

	return;

} /* min_route */

/* EOF */

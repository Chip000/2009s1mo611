/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include "../include/shortest_path.h"

/* 
 * init_int_array: Cria um vetor do tipo int de tamanho n, inicializado
 * com valor v.
 */
static int *init_int_array(int n, int v)
{
	int *t = (int *) malloc(n * sizeof(int));
	int i;

	for (i = 0; i < n; i++) {
		t[i] = v;
	}

	return t;

} /* init_int_array */

/*
 * min_dist_vertex: retorna o vertice que possui a menor distancia.
 */
static int min_dist_vertex(float *dist, int n, int *visited)
{
	int i;
	int min_vertex;

	float min_dist;

	min_dist = INF;
	min_vertex = -1;

	for (i = 0; i < n; i++) {
		if ((visited[i] == 0) && (dist[i] <= min_dist)) {
			min_dist = dist[i];
			min_vertex = i;
		}
	}

	return min_vertex;

} /* min_dist_vertex */

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
void shortest_path(float **G, int n, int s, float **dist)
{
	int i;
	int u;
	int S;

	float tmp;
	float cost;

	int *visited;
	int *prev;

	/* Inicializacao */
	cost = 0;
	prev = init_int_array(n, -1);
	visited = init_int_array(n, 0);

	for (i = 0; i < n; i++) {
		(*dist)[i] = INF;
	}

	S = n;

	/* Valores para o vertice origem */
	(*dist)[s] = 0;
	prev[s] = -1;

	while (S != 0) {
		/* Escolhe o elemento de menor (*dist)ancia */
		u = min_dist_vertex((*dist), n, visited);
		
		visited[u] = 1;
		S --;
		/* Percorre os vizinhos de u */
		for (i = 0; i < n; i++) {
			if (G[u][i] != 0) {
				tmp = (*dist)[u] + G[u][i];
				
				/* Relaxa a aresta (u, i) */
				if (tmp < (*dist)[i]) {
					(*dist)[i] = tmp;
					prev[i] = u;
				}
			}
		}
	}

	/* Liberando memoria */
	free(prev);
	free(visited);

	return;

} /* shortest_path */

/* DEBUG FUNCTIONS */

/*
 * print_shortest_path: Imprime o custo e o caminho mais curto da 
 * solucao dada.
 */
void print_shortest_path(int **x, int n, int s, int t, float cost)
{
	
	int i;
	int u;

	fprintf(stdout, "\n>>>DEBUG:\n");
	fprintf(stdout, "Custo: %f\n\n", cost);
	fprintf(stdout, "Vertices do Caminho:\n");

	i = 0;
	u = s;
	fprintf(stdout, "%d ", u);
	while (u != t) {
		if (x[u][i] != 0) {
			fprintf(stderr, "%d ", i);
			u = i;
			i = -1;
		}
		i++;
	}
	fprintf(stdout, "%d ", t);

	fprintf(stderr, "\n");

	return;
} /* print_shortest_path */

/* EOF */

/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include "../include/chordal.h"

/*
 * list2matrix: Transforma a lista de adjacencia para uma 
 * matriz de adjacencia
 */
static void list2matrix(struct graph_aux *Gaux, float ***G)
{

	int i;
	int j;
	struct vertex_aux *V;
	struct neighbor *nb;

	/* inicializacao */
	(*G) = (float **) malloc(G->v * sizeof(float *));
	for (i = 0; i < G->v; i++) {
		(*G)[i] = (float *) malloc(G->v * sizeof(float));
	}

	for (i = 0; i < G->v; i++) {
		for (j = 0; j < G->v; j++) {
			(*G)[i][j] = 0;
		}
	}

	/* Criando G */
	V = Gaux->V;
	while (V->next != NULL) {
		V = V->next;
		nb = V->nb;
		i = V->label;
		while (nb->next != NULL) {
			nb = nb->next;
			j = nb->label;
			(*G)[i][j] = 1.0;
		}
	}

	return;

} /* list2matrix */

/*
 * free_matrix_gaux: Libera a memoria usada pela matrix G
 */
static void free_matrix_gaux(float **G, int n)
{

	int i;

	for (i = 0; i < n; i++) {
		free(G[i]);
	}

	free(G);

	return;

} /* free_matrix_gaux */

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
			     float **dist, int **prev)
{

	float **M;

	list2matrix(G, &M);

	shortest_path(M, G->v, s, dist, prev);

	free_matrix_gaux(M, G->v);

	return;

} /* graph_aux_shortest_path */



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
		   struct request req, float a)
{

	int r;

	for (r = 0; r < req.n; r++){
		if (req.path[r].type == "") {
			/* TODO: o grafo deve continuar cordal */
		}
		else if (req.path[r].type == "r") {
			/* o grafo G nao deixa de ser cordal
			   quando se remove uma aresta */
			if (remove_edge_aux(G->v, req.path[r].s,
					    req.path[r].t) != 0) {
				/* problema na remocao da aresta */
				return 1;
			}
		}
	}

	return 0;

} /* gen_graph_aux */

/* EOF */

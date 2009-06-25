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
	(*G) = (float **) malloc(Gaux->v * sizeof(float *));
	for (i = 0; i < Gaux->v; i++) {
		(*G)[i] = (float *) malloc(Gaux->v * sizeof(float));
	}

	for (i = 0; i < Gaux->v; i++) {
		for (j = 0; j < Gaux->v; j++) {
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

/* /\* */
/*  * get_min_inpath: pega o vertice que possui a menor distancia  */
/*  * para o vertice t' */
/*  *\/ */
/* static int get_min_inpath(struct graph_aux *G, int s, int t,  */
/* 			  float *d) */
/* { */

/* 	int min; */
/* 	int i; */
/* 	int *prev; */
/* 	float *dist; */

/* 	min = 0; */

/* 	if (s == -1) { */
/* 		return t; */
/* 	} */
	
/* 	if (t == -1) { */
/* 		return s; */
/* 	} */

/* 	prev = (int *) malloc(G->v * sizeof(int)); */
/* 	dist = (float *) malloc(G->v * sizeof(float)); */

/* 	graph_aux_shortest_path(G, s, &dist, &prev); */

/* 	i = t; */
/* 	while (i != -1) { */
/* 		if (d[i] < d[min]) { */
/* 			min = i; */
/* 		} */

/* 		i = prev[i]; */
/* 	} */

/* 	free(dist); */
/* 	free(prev); */
/* 	return min; */

/* } /\* get_min_inpath *\/ */



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
 * triangulation: Retorna o numero de arestas necessarias para
 * tornar o grafo G cordal com a adicao do vertice new
 */
int triangulation(struct graph_aux *G, int new, int s, int t, 
		  int *prev)
{

	int T;
	int i;
	int ret;

	T = 0;

	i = t;
	while (i != -1) {
		/* caso possua buracos adiciona uma aresta a 
		   cada elemento que pertence ao buraco */
		if ((ret = add_new_edge_in_gaux(G, new, i)) == 0) {
			T++;
			if (insert(MOD.e, new, i) == 0) {
				MOD.n++;
			}
		}

		i = prev[i];
	}

	return T;

} /* triangulation */



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
		  struct request req, float a, const char *fname,
		  const char *modfile)
{

	int u;
	int v;
	int new;
	int r;
	int ext_e;

	int *prev;
	float *dist;

	struct best b;
	int *vertex;

	FILE *f;
	FILE *fmod;

	if ((f = fopen(fname, "w")) == NULL) {
		return 1;
	}

	/* inicializando as info do modulador */
	MOD.n = 0;
	MOD.e = create_struct_new_edges();

	if ((fmod = fopen(modfile, "w")) == NULL) {
		return 1;
	}

	/* numero de demandas */
	fprintf(f, "%d\n", req.n);

	for (r = 0; r < req.n; r++) {
		ext_e = 0;
		if (req.path[r].type == 'p') {
			/* o grafo deve continuar cordal */

			min_route(&b, R.cost, R.v, req.path[r].s, 
				  req.path[r].t, a, ext_e);

			vertex = have_path(G, b.p);

			free_struct_route(b.p);

			new = add_new_vertex_in_gaux(G, NULL, 
						     req.path[r].s,
						     req.path[r].t);

			prev = (int *) malloc(G->v * sizeof(int));
			dist = (float *) malloc(G->v * sizeof(float));

			for (u = 0; u < G->v - 1; u ++) {
				if (vertex[u] != 0) {
					add_new_edge_in_gaux(G, new, u);
					for (v = u + 1; v < G->v - 1; v++) {
						if (vertex[v] != 0) {
							add_new_edge_in_gaux(G, new, v);

							graph_aux_shortest_path(G, req.path[r].s, &dist, &prev);

							/* encontra o valor de T */
							ext_e += triangulation(G, new, u, v, prev);
						}
					}
					
				}
			}

			free(vertex);
			free(prev);
			free(dist);

			min_route(&b, R.cost, R.v, req.path[r].s, 
				  req.path[r].t, a, ext_e);

			update_vertex_aux_path(G->V, new, b.p);

			print_route_path(f, b.p);

			free_struct_route(b.p);

		}
		else if (req.path[r].type == 'r') {
			/* o grafo G nao deixa de ser cordal
			   quando se remove uma aresta */
			if (del_edge_in_gaux(G, req.path[r].s,
					    req.path[r].t) != 0) {
				/* problema na remocao da aresta */
				return 1;
			}
		}
	}

	fprintf(fmod, "%d\n", MOD.n);
	print2file_struct_new_edges(fmod, MOD.e);

	free_struct_new_edges(MOD.e);

	fclose(fmod);
	fclose(f);

	return 0;

} /* gen_graph_aux */

/* EOF */

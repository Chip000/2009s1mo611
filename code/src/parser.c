/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include "../include/parser.h"

/*
 * graph_parser: Guarda as informacoes do arquivo de topologia na
 * estrutura graph. 
 * Retorna 0 em caso de sucesso e 1 caso contrario.
 */
int graph_parser(const char *filename, struct graph *G)
{

	int i = 0;
	int j = 0;
	int u = 0;
	int v = 0;
	float c = 0;

	FILE *file;

	if ((file = fopen(filename, "r")) == NULL) {
		return 1;
	}

	/* Pegando a quantidade de vertices */
	fscanf(file, "n %d\n", &(G->v));
		
	/* Pegando a quantidade de arestas */
	fscanf(file, "m %d\n", &(G->e));
		
	/* Pegando o vertice de origem */
	if ((fscanf(file, "s %d\n", &(G->s))) != EOF) {
		/* Pegando o vertice de destino */
		fscanf(file, "t %d\n", &(G->t));
	}
	
	/* Alocando espaco para a matriz de custo das arestas */
	G->cost = (float **) malloc(G->v * sizeof(float *));
	for (i = 0; i < G->v; i++) {
		G->cost[i] = (float *) malloc(G->v * sizeof(float));
	}

	/* Armazenando os valores de custos das arestas
	 * OBS: o grafo	e' nao-orientado */
	while ((fscanf(file, "a %d %d %f\n", &i, &j, &c)) > 0) {
		u = i - INIT_IN_ZERO;
		v = j - INIT_IN_ZERO;
		G->cost[u][v] = c;
	}
	
	fclose(file);

	return 0;

} /* graph_parser */

/*
 * request_parser: Guarda as informacoes do arquivo de demanda na
 * estrutura request. 
 * Retorna 0 em caso de sucesso e 1 caso contrario.
 */
int request_parser(const char *filename, struct request *r)
{

	int i = 0;
	int j = 0;
	int s = 0;
	int t = 0;
	int n = 0;
	char type;
	
	FILE *file;

	if ((file = fopen(filename, "r")) == NULL) {
		return 1;
	}
	
	/* Pegando o numero de demandas a ser analisadas */
	n = 0;

	while ((fscanf(file, "%c %d %d\n", &type, &i, &j)) > 0) {
		n = n + 1;
	}
       
	rewind(file);

	/* Preenchendo a estrutura request */
	r->n = n;

	r->path = malloc(n * sizeof(struct request_info));

	n = 0;

	while ((fscanf(file, "%c %d %d\n", &type, &i, &j)) > 0) {
		s = i - INIT_IN_ZERO;
		t = j - INIT_IN_ZERO;
		(r->path)[n].type = type;
		(r->path)[n].s = s;
		(r->path)[n].t = t;
		n = n + 1;
	}

	fclose(file);

	return 0;

} /* request_parser */

/*
 * graph_aux_parser: Guarda as informacoes do grafo auxiliar na
 * estrutura graph_aux. 
 * Retorna 0 em caso de sucesso e 1 caso o arquivo nao existe e
 * -1 cc.
 */
int graph_aux_parser(const char *filename, struct graph_aux *G)
{

	int i = 0;
	int j = 0;
	int s = 0;
	int t = 0;
	int u = 0;
	int v = 0;
	int n = 0;
	int label = 0;
	struct route *p;
	float c = 0;

	FILE *file;

	/* inicializacao */
	G->v = 0;
	G->e = 0;

	/* Criando a lista de adjacencia */
	G->V = create_struct_vertex_aux();

	if ((file = fopen(filename, "r")) == NULL) {
		return 1;
	}

	/* Pegando a quantidade de vertices */
	fscanf(file, "n %d\n", &(G->v));
		
	/* Pegando a quantidade de arestas */
	fscanf(file, "m %d\n", &(G->e));

	/* Lendo as info dos vertices */
	for (i = 0; i < G->v; i++) {
		fscanf(file, "v %d s %d t %d n %d\n", 
		       &label, &s, &t, &n);

		/* criando a rota */
		p = create_struct_route();

		for (j = 0; j < n; j++) {
			fscanf(file, "a %d %d %f\n", &u, &v, &c);
			if (insert_new_edge(p, u, v, c) != 0) {
				return -1;
			}
		}

		insert_new_vertex_aux(G->V, p, s, t);
	}

	/* Lendo as arestas */
	for (i = 0; i < G->e; i++) {
		fscanf(file, "a %d %d %f\n", &u, &v, &c);
		if (insert_new_edge_gaux(G->V, u, v) != 0) {
			return -1;
		}
	}
		
	fclose(file);

	return 0;

} /* graph_aux_parser */



/*
 * free_graph: Libera a memoria usada pela estrutura graph.
 */
void free_graph(struct graph G)
{
	
	int i;

	for (i = 0; i < G.v; i++) {
		free(G.cost[i]);
	}
	
	free(G.cost);

	return;

} /* free_graph */

/*
 * free_request: Libera a memoria usada pela estrutura request.
 */
void free_request(struct request r)
{
	
	free(r.path);

	return;

} /* free_request */

/*
 * free_graph_aux: Libera a memoria usada pela estrutura request.
 */
void free_graph_aux(struct graph_aux G)
{

	free_vertex_aux(G.V);

	return;

} /* free_graph_aux */



/*
 * add_new_vertex_in_gaux: Insere um novo vertice em gaux
 * retorna o label do vertice inserido se ocorreu a insercao e -1 cc
 */
int add_new_vertex_in_gaux(struct graph_aux *G, struct route *p, 
			  int s, int t)
{

	if (insert_new_vertex_aux(G->V, p, s, t) != 0) {
		return -1;
	}

	G->v++;

	return G->v - 1;

} /* add_new_vertex_in_gaux */

/*
 * add_new_edge_in_gaux: Insere uma nova aresta em gaux
 * retorna 0 se ocorreu a insercao e 1 cc
 */
int add_new_edge_in_gaux(struct graph_aux *G, int u, int v)
{

	int ret1;
	int ret2;

	int h1;
	int h2;

	if ((h1 = has_edge_gaux(G->V, u, v)) != 0) {
		ret1 = insert_new_edge_gaux(G->V, u, v);
	}
	
	if ((h2 = has_edge_gaux(G->V, v, u)) != 0) {
		ret2 = insert_new_edge_gaux(G->V, v, u);
	}

	if (((h1 != 0) && (ret1 != 0)) || 
	    ((h2 != 0) && (ret2 != 0))) {
		return 1;
	}

	if (h1 != 0) {
		G->e ++;
	}
	if (h2 != 0) {
		G->e ++;
	}

	return (!((h1 != 0) && (h2 != 0)));

} /* add_new_edge_in_gaux */

/*
 * del_vertex_in_gaux: Remove o vertice u do grafo gaux
 * retorna 0 se ocorreu a remocao e 1 cc
 */
int del_vertex_in_gaux(struct graph_aux *G, int u)
{

	if (remove_vertex_aux(G->V, u) != 0) {
		return 1;
	}

	G->v --;
	G->e = get_e_gaux(G->V);

	return 0;

} /* del_vertex_in_gaux */

/*
 * del_edge_in_gaux: Remove uma aresta em gaux
 * retorna 0 se ocorreu a remocao e 1 cc
 */
int del_edge_in_gaux(struct graph_aux *G, int u, int v)
{

	int ret1;
	int ret2;

	ret1 = remove_edge_gaux(G->V, u, v);
	ret2 = remove_edge_gaux(G->V, v, u);

	if ((ret1 != 0) || (ret2 != 0)) {
		return 1;
	}

	G->e -= 2;

	return 0;

} /* del_edge_in_gaux */

/*
 * vertex_in_gaux: Verifica se o vertice pertence a algum no do grafo
 * auxiliar
 * retorna o label do no se v pertence a ele e -1 cc
 */
int vertex_in_gaux(struct graph_aux *gaux, int v)
{

	struct vertex_aux *G;

	G = gaux->V;

	while (G->next != NULL) {
		G = G->next;

		if ((v == G->s) || (v == G->t) ||
		    (in_path(G->p, v) != 0)) {
			return G->label;
		}
	}

	return -1;

} /* vertex_in_gaux */



/*
 * have_path: Verifica quais vertices do grafo auxiliar possui
 * uma aresta em comum com p
 */
int *have_path(struct graph_aux *Gaux, struct route *p)
{

	struct vertex_aux *V;
	struct route *paux;
	int *res;

	int i;

	res = (int *) malloc(Gaux->v * sizeof(int));

	for (i = 0; i < Gaux->v; i++) {
		res[i] = 0;
	}

	if ((Gaux->V != NULL) && (p != NULL)) {
		V = Gaux->V->next;

		while (V != NULL) {
			paux = p->next;
			while (paux != NULL) {
				if (edge_in_path(V->p, 
						 paux->e.i, 
						 paux->e.j) != 0) {
					res[V->label] = 1;
				}
				paux = paux->next;
			}
			V = V->next;
		}
	}

	return res;

} /* have_path */

/* DEBUG FUNCTIONS */

/* 
 * print_graph: imprime as informacoes contidas na estrutura
 * graph lida.
 */
void print_graph(struct graph G)
{
	int i, j;
	
	fprintf(stdout, "\n>>>DEBUG: \n");

	fprintf(stdout, "n %d\n", G.v);
	fprintf(stdout, "m %d\n", G.e);
	fprintf(stdout, "s %d\n", G.s);
	fprintf(stdout, "t %d\n", G.t);

	for (i = 0; i < G.v; i++) {
		for (j = 0; j < G.v; j ++) {
			if (G.cost[i][j] != 0) {
				fprintf(stdout, "a %d %d %.f\n",
					i + INIT_IN_ZERO, 
					j + INIT_IN_ZERO, 
					G.cost[i][j]);
			}
		}
	} 

	return;

} /* print_graph */

/* 
 * print_request: imprime as informacoes contidas na estrutura
 * request lida.
 */
void print_request(struct request r)
{
	int i;
	
	fprintf(stdout, "\n>>>DEBUG: \n");

	fprintf(stdout, "N. de demandas %d\n", r.n);

	for (i = 0; i < r.n; i++) {
		fprintf(stdout, "p %d %d\n",
			r.path[i].s + INIT_IN_ZERO, 
			r.path[i].t + INIT_IN_ZERO);
	} 

	return;

} /* print_request */

/* 
 * print_graph_aux: imprime as informacoes contidas na estrutura
 * graph_aux lida.
 */
void print_graph_aux(const char *fname, struct graph_aux G)
{

	FILE *f;

	if ((f = fopen(fname, "w")) == NULL) {
		fprintf(stderr, ">>>ERROR: Arquivo de topologia invalido\n");
		exit(1);
	}

	fprintf(f, "n %d\n", G.v);
	fprintf(f, "m %d\n", G.e);

	print2file_vertex_aux(f, G.V);

	fclose(f);

	return;

} /* print_graph_aux */

/* EOF */

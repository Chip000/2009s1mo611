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
	
	FILE *file;

	if ((file = fopen(filename, "r")) == NULL) {
		return 1;
	}
	
	/* Pegando o numero de demandas a ser analisadas */
	n = 0;

	while ((fscanf(file, "p %d %d\n", &i, &j)) > 0) {
		n = n + 1;
	}
       
	rewind(file);

	/* Preenchendo a estrutura request */
	r->n = n;

	r->path = (struct pair *) malloc(n * sizeof(struct pair));

	n = 0;

	while ((fscanf(file, "p %d %d\n", &i, &j)) > 0) {
		s = i - INIT_IN_ZERO;
		t = j - INIT_IN_ZERO;
		(r->path)[n].s = s;
		(r->path)[n].t = t;
		n = n + 1;
	}

	fclose(file);

	return 0;

} /* request_parser */

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

/* EOF */

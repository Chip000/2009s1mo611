/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include "../include/graph_aux.h"

/*
 * insert_new_vertex_aux_aux: Insere o vertice apos o elemento 
 * apontado por G
 */
static void insert_new_vertex_aux_aux(struct vertex_aux *G,
				      struct route *p, 
				      int label,
				      int s, int t)
{

	struct vertex_aux *new;

	new = (struct vertex_aux *) malloc(sizeof(struct vertex_aux));

	new->label = label;
	new->s = s;
	new->t = t;
	new->p = p;
	new->nb = create_neighbor();
	new->next = NULL;

	G->next = new;

	return;

} /* insert_new_vertex_aux_aux */



/*
 * update_vertex_aux_label_aux: Atualiza a vizinhanca do vertice u para
 * seu novo rotulo label
 */
static void update_vertex_aux_label_aux(struct vertex_aux *G,
					struct neighbor *nb,
					int u,
					int label)
{

	struct vertex_aux *tmp;

	/* o vertice nao tem vizinhos */
	if (nb == NULL) {
		return;
	}

	tmp = G;
	/* encontra o vizinho */
	while ((tmp->next != NULL) && (tmp->label != nb->label)) {
		tmp = tmp->next;
	}

	/* se encontrou entao atualiza a vizinhanca */
	if (tmp->label == nb->label) {
		update_neighbor(tmp->nb->next, u, label);
	}

	update_vertex_aux_label_aux(G, nb->next, u, label);

	return;

} /* update_vertex_aux_label_aux */



/*
 * remove_vertex_neighbor: Remove o vertice v do vertices pertencentes
 * a sua vizinhanca.
 */
static void remove_vertex_neighbor(struct vertex_aux *G, 
				   struct neighbor *u,
				   int v)
{

	struct vertex_aux *tmp;

	if (u == NULL) {
		return;
	}

	tmp = G;
	while (tmp->next != NULL) {
		if (tmp->label == u->label) {
			remove_neighbor(tmp->nb, v);
			break;
		}
		tmp = tmp->next;
	}

	remove_vertex_neighbor(G, u->next, v);

	return;

} /* remove_vertex_neighbor */



/*
 * print2file_vertex_info: Imprime as informacoes rotulo, origem, 
 * destino, qtde de arestas do path e o caminho que representa
 * o vertice.
 */
static void print2file_vertex_info(FILE *f, struct vertex_aux *G)
{

	int n;

	if (G == NULL) {
		return;
	}

	n = route_len(G->p);

	fprintf(f, "v %d s %d t %d n %d\n", G->label, G->s, G->t, n);
	
	print2file_struct_route(f, G->p);

	print2file_vertex_info(f, G->next);

	return;

} /* printf2file_vertex_info */

/*
 * print2file_edge_gaux: Imprime as arestas do grafo auxiliar
 */
static void print2file_edge_gaux(FILE *f, struct vertex_aux *G)
{

	if (G == NULL) {
		return;
	}

	print2file_neighbor(f, G->label, G->nb->next);

	print2file_edge_gaux(f, G->next);

	return;

} /* print2file_edge_gaux */



/*
 * create_struct_vertex_aux: Cria o no cabeca da lista de adjacencia
 */
struct vertex_aux *create_struct_vertex_aux(void)
{

	struct vertex_aux *r;

	r = (struct vertex_aux *) malloc(sizeof(struct vertex_aux));

	r->label = -1;
	r->s = -1;
	r->t = -1;
	r->p = NULL;
	r->nb = NULL;
	r->next = NULL;

	return r;

} /* create_struct_vertex_aux */



/*
 * insert_new_vertex_aux: Insere um novo vertice em G
 * retorna 0 se ocorreu a insercao e 1 cc
 */
int insert_new_vertex_aux(struct vertex_aux *G, struct route *p, 
			  int s, int t)
{

	int n;

	if (G == NULL) {
		return 1;
	}

	n = 0;
	while (G->next != NULL) {
		n = n + 1;
		G = G->next;
	}

	insert_new_vertex_aux_aux(G, p, n, s, t);

	return 0;
	
} /* insert_new_vertex_aux */

/*
 * insert_new_edge_gaux: Insere uma nova aresta em G
 * retorna 0 se ocorreu a insercao e 1 cc
 */
int insert_new_edge_gaux(struct vertex_aux *G, int i, int j)
{

	int u;
	int v;

	struct neighbor *u_nb;

	if (G == NULL) {
		return 1;
	}
	
	if (G->next == NULL) {
		return 1;
	}

	u = i;
	v = j;

	/* Encontrando o vertice u */
	while ((G != NULL) && (G->label != u)) {
		G = G->next;
	}

	if (G == NULL) {
		return 1;
	}

	u_nb = G->nb;

	insert_new_neighbor(u_nb, v);

	return 0;

} /* insert_new_edge_gaux */



/*
 * update_vertex_aux_path: Atualiza o path representado pelo vertice
 * retorna 1 se atualizou e 0 cc
 */
int update_vertex_aux_path(struct vertex_aux *G, int u, struct route *p)
{

	if (G == NULL) {
		return 0;
	}

	while (G->next != NULL) {
		if (G->label == u) {
			G->p = p;
			return 1;
		}
		G = G->next;
	}

	return 0;

} /* update_vertex_aux_path */

/*
 * update_vertex_aux_label: Atualiza os labels de todos os vertices do grafo
 * auxiliar
 */
void update_vertex_aux_label(struct vertex_aux *G)
{

	struct vertex_aux *tmp;
	int i;

	if (G == NULL) {
		return;
	}

	i = 0;
	tmp = G;
	while (tmp != NULL) {
		if (tmp->label != i) {
			update_vertex_aux_label_aux(G, tmp->nb->next, 
						    tmp->label, i);
			tmp->label = i;
		}
		i++;
		tmp = tmp->next;
	}

	return;

} /* update_vertex_aux_label */



/*
 * remove_vertex_aux: Remove o vertice u da struct vertex_aux
 * retorna 0 se ocorreu a remocao e 1 cc
 */
int remove_vertex_aux(struct vertex_aux *G, int u)
{

	struct vertex_aux *rem;
	struct vertex_aux *prev;

	if (G == NULL) {
		return 1;
	}
	
	if (G->next == NULL) {
		return 1;
	}

	rem = G;
	prev = G;

	/* Encontrando o vertice u */
	while ((rem->next != NULL) && (rem->label != u)) {
		prev = rem;
		rem = rem->next;
	}

	/* Nao encontrou */
	if (rem->label != u) {
		return 1;
	}

	remove_vertex_neighbor(G, rem->nb->next, u);

	prev->next = rem->next;
	free_neighbor(rem->nb);
	free_struct_route(rem->p);
	free(rem);

	update_vertex_aux_label(G->next);

	return 0;

} /* remove_vertex_aux */

/*
 * remove_edge_gaux: Remove uma aresta em G
 * retorna 0 se ocorreu a remocao e 1 cc
 */
int remove_edge_gaux(struct vertex_aux *G, int i, int j)
{

	int u;
	int v;

	struct neighbor *u_nb;
	struct neighbor *v_nb;

	if (G == NULL) {
		return 1;
	}
	
	if (G->next == NULL) {
		return 1;
	}

	u = i;
	v = j;

	if (i > j) {
		u = j;
		v = i;
	}

	/* Encontrando o vertice u */
	while ((G != NULL) && (G->label != u)) {
		G = G->next;
	}

	if (G == NULL) {
		return 1;
	}

	u_nb = G->nb;

	/* Encontrando o vertice v */
	while ((G != NULL) && (G->label != v)) {
		G = G->next;
	}

	if (G == NULL) {
		return 1;
	}

	v_nb = G->nb;

	remove_neighbor(u_nb, v);
	remove_neighbor(v_nb, u);

	return 0;

} /* remove_edge_gaux */

/*
 * free_vertex_aux: Libera a memoria da estrutura vertex_aux.
 */
void free_vertex_aux(struct vertex_aux *G)
{

	if (G != NULL) {
		free_vertex_aux(G->next);
		free_neighbor(G->nb);
		free_struct_route(G->p);
		free(G);
	}

	return;

} /* free_vertex_aux */

/* Funcoes de escrita em arquivo */
/*
 * print2file_vertex_aux: Imprime em um arquivo as informacoes da 
 * struct vertex_aux
 */
void print2file_vertex_aux(FILE *f, struct vertex_aux *G)
{

	if (G == NULL) {
		return;
	}

	G = G->next;
	if (G == NULL) {
		return;
	}

	print2file_vertex_info(f, G->next);

	print2file_edge_gaux(f, G->next);

} /* print2file_vertex_aux */

/* EOF */

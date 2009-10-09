/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include "../include/struct_route.h"

/*
 * insert_new_edge_aux: Insere a aresta apos o elemento apontado por P
 */
static void insert_new_edge_aux(struct route *P, int i, int j, float c)
{

	struct route *new;

	new = (struct route *) malloc(sizeof(struct route));

	new->e.i = i;
	new->e.j = j;
	new->e.cost = c;
	new->next = NULL;

	P->next = new;

	return;

} /* insert_new_edge_aux */



/* 
 * create_struct_route: Cria o no cabeca da lista route 
 */
struct route *create_struct_route(void)
{

	struct route *r;

	r = (struct route *) malloc(sizeof(struct route));
	
	r->e.i = -1;
	r->e.j = -1;
	r->e.cost = -1;
	r->next = NULL;

	return r;

} /* create_struct_route */



/*
 * insert_new_edge: Insere a aresta na rota P
 * retorna 0 se ocorreu a insercao e 1 cc
 */
int insert_new_edge(struct route *P, int i, int j, float c)
{

	if (P == NULL) {
		return 1;
	}

	while (P->next != NULL) {
		P = P->next;
	}

	insert_new_edge_aux(P, i, j, c);

	return 0;
	
} /* insert_new_edge */

/*
 * remove_edge: Remove a aresta (u, v) da rota P
 * retorna 0 se ocorreu a remocao e 1 cc
 */
int remove_edge(struct route *P, int u, int v)
{

	struct route *rem;

	if (P == NULL) {
		return 1;
	}

	rem = P->next;
	while (rem != NULL) {
		if ((rem->e.i == u) && (rem->e.j == v)) {
			P->next = rem->next;
			free(rem);
			return 0;
		}

		rem = rem->next;
		P = P->next;
	}

	return 1;
	
} /* remove_edge */



/*
 * in_path: Verifica se o vertice u ja esta no caminho
 * retorna 0 caso u nao esta no caminho e 1 cc
 */
int in_path(struct route *P, int u)
{

	if (P == NULL) {
		return 0;
	}

	if ((P->e.i == u) || (P->e.j == u)) {
		return 1;
	}

	return in_path(P->next, u);

} /* in_path */ 

/*
 * edge_in_path: Verifica se a aresta (u,v) ja esta no caminho
 * retorna 0 caso u nao esta no caminho e 1 cc
 */
int edge_in_path(struct route *P, int u,int v)
{

	if (P == NULL) {
		return 0;
	}

	if (((P->e.i == u) && (P->e.j == v)) || 
	    ((P->e.i == v) && (P->e.j == u))) {
		return 1;
	}

	return edge_in_path(P->next, u, v);

} /* edge_in_path */ 



/*
 * route_len: Calcula o tamanho da rota
 */
int route_len(struct route *P)
{

	if (P == NULL) {
		return -1;
	}

	if (P->next == NULL) {
		return 0;
	}

	return (route_len(P->next) + 1);

} /* route_len */



/*
 * cpyroute: copia a rota src para a rota dest
 */
void cpyroute(struct route *dest, struct route *src)
{
	
	while (src->next != NULL) {
		src = src->next;

		insert_new_edge_aux(dest, src->e.i, src->e.j, 
				    src->e.cost);

		dest = dest->next;
	}

	return;

} /* cpyroute */



/*
 * free_struct_route: Libera a memoria usada pela estrutura route
 */
void free_struct_route(struct route *P)
{

	if (P != NULL) {
		if (P->next != NULL) {
			free_struct_route(P->next);
		}

		free(P);
	}

	return;

} /* free_struct_route */



/*
 * print_route_path: Imprime a rota de s a t no arquivo especificado
 * retorna 1 se ocorreu a impressao, 0 se a rota e vazia e -1 cc
 */
int print_route_path(FILE *f, struct route *P)
{

	if (P == NULL) {
		return -1;
	}

	P = P->next;
	if (P == NULL) {
		return 0;
	}

	fprintf(f, "%d", P->e.i + INIT_IN_ZERO);

	while (P != NULL) {
		fprintf(f, " %d", P->e.j + INIT_IN_ZERO);
		P = P->next;
	}
	
	fprintf(f, "\n");

	return 1;

} /* print_route_path */

/*
 * print2file_struct_route: Imprime a rota de s a t no arquivo especificado
 * para o grafo auxiliar.
 * retorna 1 se ocorreu a impressao, 0 se a rota e vazia e -1 cc
 */
int print2file_struct_route(FILE *f, struct route *P)
{

	if (P == NULL) {
		return -1;
	}

	P = P->next;
	if (P == NULL) {
		return 0;
	}

	while (P != NULL) {
		fprintf(f, "a %d %d %.2f\n", P->e.i, 
			P->e.j, P->e.cost);
		P = P->next;
	}
	
	return 1;

} /* print2file_struct_route */

/* EOF */

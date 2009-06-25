/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include "../include/new_edges.h"

/*
 * insert_aux: Insere a aresta apos o elemento apontado por e
 */
static void insert_aux(struct new_edges *e, int i, int j)
{

	struct new_edges *new;

	new = (struct new_edges *) malloc(sizeof(struct new_edges));

	new->u = i;
	new->v = j;
	new->next = NULL;

	e->next = new;

	return;

} /* insert_aux */



/* 
 * create_struct_new_edges: Cria o no cabeca da lista new_edges 
 */
struct new_edges *create_struct_new_edges(void)
{

	struct new_edges *r;

	r = (struct new_edges *) malloc(sizeof(struct new_edges));
	
	r->u = -1;
	r->v = -1;
	r->next = NULL;

	return r;

} /* create_struct_new_edges */

/*
 * insert: Insere a aresta na estrutura
 * retorna 0 se ocorreu a insercao e 1 cc
 */
int insert(struct new_edges *e, int i, int j)
{

	if (e == NULL) {
		return 1;
	}

	while (e->next != NULL) {
		if ((e->u == i) && (e->v == j)) {
			return 1;
		}
		e = e->next;
	}

	if ((e->u == i) && (e->v == j)) {
		return 1;
	}

	insert_aux(e, i, j);

	return 0;
	
} /* insert */

/*
 * free_struct_new_edges: Libera a memoria usada pela estrutura new_edges
 */
void free_struct_new_edges(struct new_edges *e)
{

	if (e != NULL) {
		if (e->next != NULL) {
			free_struct_new_edges(e->next);
		}

		free(e);
	}

	return;

} /* free_struct_new_edges */


/*
 * print2file_struct_new_edges: Imprime a rota de s a t no arquivo 
 * especificado para o grafo auxiliar.
 * retorna 1 se ocorreu a impressao, 0 se a rota e vazia e -1 cc
 */
int print2file_struct_new_edges(FILE *f, struct new_edges *e)
{

	if (e == NULL) {
		return -1;
	}

	e = e->next;
	if (e == NULL) {
		return 0;
	}

	while (e != NULL) {
		fprintf(f, "%d %d\n", e->u, e->v);
		e = e->next;
	}
	
	return 1;

} /* print2file_struct_new_edges */

/* EOF */

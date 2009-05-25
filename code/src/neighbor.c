/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include "../include/neighbor.h"

/*
 * insert_new_neighbor_aux: Insere um novo vizinho apos a posicao
 * apontada por u
 */
static void insert_new_neighbor_aux(struct neighbor *u, int v)
{

	struct neighbor *new;

	new = (struct neighbor *) malloc(sizeof(struct neighbor));

	new->label = label;
	new->next = NULL;

	u->next = new;

	return;

} /* insert_new_neighbor_aux */



/*
 * create_neighbor: Cria o no cabeca da lista
 */
struct neighbor *create_neighbor(void)
{

	struct neighbor *r;

	r = (struct neighbor *) malloc(sizeof(struct neighbor));

	r->label = -1;
	r->next = NULL;

	return r;

} /* create_neighbor */



/*
 * insert_new_neighbor: Insere um novo vizinho em u
 * retorna 0 se ocorreu a insercao e 1 cc
 */
int insert_new_neighbor(struct neighbor *u, int v)
{

	if (u == NULL) {
		return 1;
	}

	while (u->next != NULL) {
		u = u->next;
	}

	insert_new_neighbor_aux(u, v);

	return 0;

} /* insert_new_neighbor */



/*
 * update_neighbor: Atualiza o rotulo do vertice olabel para nlabel na
 * vizinhanca
 * retorna 0 se ocorreu a atualizacao e 1 cc
 */
int update_neighbor(struct neighbor *u, int olabel, int nlabel)
{

	int i;

	if (u == NULL) {
		return 1;
	}

	while (u->next != NULL) {
		if (u->label == olabel) {
			u->label = nlabel;
			return 0;
		}
		u = u->next;
	}

	return 1;

} /* update_neighbor */



/*
 * remove_neighbor: Remove o vizinho v de u
 * retorna 0 se ocorreu a remocao e 1 cc
 */
int remove_neighbor(struct neighbor *u, int v)
{

	struct neighbor *rem;

	if (u == NULL) {
		return 1;
	}

	rem = u;

	while ((rem->next != NULL) && (rem->label != v)) {
		u = rem;
		rem = rem->next;
	}

	if ((rem->next == NULL) || (rem->label != v)) {
		return 1;
	}

	u->next = rem->next;
	free(rem);

	return 0;

} /* remove_neighbor */



/*
 * free_neighbor: Libera memoria alocada pela struct neighbor
 */
void free_neighbor(struct neighbor *nb)
{

	if (nb->next == NULL) {
		free_neighbor(nb->next);
	}

	free(nb);

	return;

}/* free_neighbor */



/* Funcoes de escrita em arquivo */
/*
 * print2file_neighbor: Imprime a vizinhanca de u.
 */
void print2file_neighbor(FILE *f, int u, struct neighbor *nb)
{

	if (nb == NULL) {
		return;
	}

	fprintf(f, "a %d %d\n", u, nb->label);

	print2file(f, u, nb->next);

	return;

} /* print2file_neighbor */

/* EOF */
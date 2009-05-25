/* 
 * Trabalho de MO611 2009s1
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#ifndef HAVE_GRAPH_AUX_H
#define HAVE_GRAPH_AUX_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/struct_route.h"
#include "../include/neighbor.h"

struct vertex_aux {
	int label; /* rotulo do vertice */
	int s; /* vertice origem do caminho */
	int t; /* vertice destino do caminho */
	struct route *p; /* Caminho representado */
	struct neighbor *nb; /* vizinhos do vertice atual */
	struct vertex_aux *next;
};



#endif
/* ! HAVE_GRAPH_AUX_H */

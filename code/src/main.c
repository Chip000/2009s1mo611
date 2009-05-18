/* 
 * Trabalho de MO420 - Programacao Linear Inteira
 * 2009s1 - Prof. Cid
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "../include/parser.h"
#include "../include/routing.h"

#define DEBUG 1
#define TARGET "main"

void display_help(void)
{
	fprintf(stderr, 
		"USAGE: ./%s (topologia) (demanda) \n",
		TARGET);
	fprintf(stderr, "topologia: Arquivo de topologia da rede");
	fprintf(stderr, " a ser analisado\n");
	fprintf(stderr, "demanda: caminhos que serao gerados\n");
 
	return;
}

int main(int argc, char **argv) {

	struct graph G;
	struct request req;

	char *file_top;
	char *file_req;

	if (argc < 2) {
		fprintf(stderr, ">>>ERROR: ");
		fprintf(stderr, "Numero de parametros invalido!!\n");
		display_help();
		return 1;
	}

	file_top = argv[1];
	file_req = argv[2];

	/* Carregando a topologia na memoria */
	if (graph_parser(file_top, &G) != 0) {
		fprintf(stderr, ">>>ERROR: ");
		fprintf(stderr, "Arquivo de topologia invalido!!\n");
		return 1;
	}

	if (DEBUG == 1) {
		print_graph(G);
	}

	if (request_parser(file_req, &req) != 0) {
		fprintf(stderr, ">>>ERROR: ");
		fprintf(stderr, "Arquivo de demanda invalido!!\n");
		return 1;
	}

	if (DEBUG == 1) {
		print_request(req);
	}

	/* Liberando memoria */
	free_graph(G);
	free_request(req);

	return 0;

}

/* EOF */

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
#include "../include/graph_aux.h"
#include "../include/chordal.h"

#define DEBUG 0
#define TARGET "main"

void display_help(void)
{
	fprintf(stderr, 
		"USAGE: ./%s (penalidade) (topologia) (demanda)",
		TARGET);
	fprintf(stderr, " (grafo_aux) (output)\n");
	fprintf(stderr, "penalidade: multiplicador que ira penalizar");
	fprintf(stderr, " a rota de acordo com a qtde de arestas");
	fprintf(stderr, " usadas na triangulação\n");
	fprintf(stderr, "topologia: Arquivo de topologia da rede");
	fprintf(stderr, " a ser analisado\n");
	fprintf(stderr, "demanda: caminhos que serao gerados\n");
	fprintf(stderr, "grafo_aux: Arquivo que contem o grafo");
	fprintf(stderr, " auxiliar para a topologia dada\n");
	fprintf(stderr, "output: Arquivo de saida contendo os lpaths");
	fprintf(stderr, "\n");
 
	return;
}

int main(int argc, char **argv) {

	struct graph G;
	struct request req;
	struct graph_aux G_aux;

	char *file_top;
	char *file_req;
	char *file_gaux;
	char *file_out;

	float a;

	if (argc < 5) {
		fprintf(stderr, ">>>ERROR: ");
		fprintf(stderr, "Numero de parametros invalido!!\n");
		display_help();
		return 1;
	}

	a = (float) atof(argv[1]);
	file_top = argv[2];
	file_req = argv[3];
	file_gaux = argv[4];
	file_out = argv[5];

	/* Carregando a topologia na memoria */
	if (graph_parser(file_top, &G) != 0) {
		fprintf(stderr, ">>>ERROR: ");
		fprintf(stderr, "Arquivo de topologia invalido!!\n");
		return 1;
	}

	if (DEBUG == 1) {
		print_graph(G);
	}

	/* Carregando as demandas na memoria */
	if (request_parser(file_req, &req) != 0) {
		fprintf(stderr, ">>>ERROR: ");
		fprintf(stderr, "Arquivo de demanda invalido!!\n");
		return 1;
	}

	if (DEBUG == 1) {
		print_request(req);
	}

	/* Carregando o grafo auxiliar na memoria */
	if (graph_aux_parser(file_gaux, &G_aux) < 0) {
		fprintf(stderr, ">>>ERROR: ");
		fprintf(stderr, "Arquivo do grafo auxiliar invalido!!\n");
		return 1;
	}

	if (gen_graph_aux(&G_aux, G, req, a, file_out) != 0) {
		fprintf(stderr, ">>>ERROR: ");
		fprintf(stderr, "Erro ao gerar o grafo auxiliar!!\n");
		return 1;
	}

	print_graph_aux(file_gaux, G_aux);

	/* Liberando memoria */
	free_graph(G);
	free_request(req);
	free_graph_aux(G_aux);

	return 0;

}

/* EOF */

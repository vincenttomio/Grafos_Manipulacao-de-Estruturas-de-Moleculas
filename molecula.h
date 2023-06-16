/*******************************************
 * Biblioteca para manipulação de moléculas.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#ifndef _MOLECULA_
#define _MOLECULA_

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// le informações de uma molécula no formato .mol
// cria um grafo correspondente e o retorna
grafo le_molecula(FILE *f, int id);

// le valores das energias de ligacao e atribui esses
// valores como pesos às arestas do grafo G
void atribui_energia_ligacao(FILE *f, grafo G);

// remove arestas de menor peso nos caminhos minimos entre u e v
// [ver enunciado do Trabalho 1 para detalhes]
void quebra_molecula(grafo G, vertice u, vertice v);

#endif

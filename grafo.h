/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#ifndef _GRAFO_
#define _GRAFO_

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // INT_MAX

#define ABERTO 1
#define PROCESSADO 2
#define FECHADO 3

typedef struct t_vertice *vertice;
typedef struct t_aresta *aresta;
typedef struct t_grafo *grafo;

typedef struct t_vertice {
  int id;
  char rotulo[10];
  int custo;        // para algoritmos de busca
  int estado;
  vertice pai;
  lista fronteira;
} t_vertice;

typedef struct t_aresta {
  int id;
  char rotulo[10];
  int peso;
  vertice u, v;
} t_aresta;

typedef struct t_grafo {
  int id;
  lista vertices;
  lista arestas;
} t_grafo ;

//---------------------------------------------------------
// getters:

int vertice_id(vertice v);
char* vertice_rotulo(vertice v);
int custo(vertice v);
int estado(vertice v);
vertice pai(vertice v);
lista fronteira(vertice v);
int aresta_id(aresta e);
char *aresta_rotulo(aresta e);
int peso(aresta e);
vertice vertice_u(aresta e);
vertice vertice_v(aresta e);
int grafo_id(grafo G);
lista vertices(grafo G);
lista arestas(grafo G);

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo(int id);

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G);

// cria novo vertice com id <id> rotulo <rotulo> e adiciona ao grafo G
void adiciona_vertice(int id, char *rotulo, grafo G);

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G);

// cria aresta com id <id>, rotulo <rotulo> e peso <peso>,
// incidente a vertices com ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, char *rotulo, int peso, int u_id, int v_id, grafo G);

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G);

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau(vertice v);

// imprime o grafo G
void imprime_grafo(grafo G);

// imprime o vertice v
void imprime_vertice(vertice v);

// imprime a aresta e
void imprime_aresta(aresta e);

// imprime apenas a estrutura da aresta e
void imprime_estrutura_aresta(aresta e);
  
// devolve a aresta do grafo com vertices u e v
// se a aresta nao existe, devolve NULL
aresta aresta_com_vertices(vertice u, vertice v);

// cria e devolve a componente do grafo G que contem o vertice v
// [a compoente é devolvida como um novo grafo com id <id>, copiando
// todos os vertices e arestas de tal modo que se G for destruido
// o componente continua existindo integralmente]
grafo componente_conexa(grafo G, vertice v, int id);

// aplica o algoritmo de dijkstra para encontrar o menor caminho de u para
// todos os vertices do grafo G. Ao final, os atributos custo e pai de cada vertice
// estarão preenchidos adequadamente
// [a constante INT_MAX deve ser usada como valor de custo infinito.
//  ATENÇÃO: não dem ser somados valores em INT_MAX (comportamento diferente de INF)]
void dijkstra(grafo G, vertice u);

//cria uma lista com o caminho minimo de u a v
lista caminho_minimo(vertice u, vertice v, grafo G);

#endif

/*******************************************
 * Biblioteca para manipulação de moléculas.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include "molecula.h"
#include <stdio.h>
#include <stdlib.h>

// le informações de uma molécula no formato .mol
// cria um grafo correspondente e o retorna
grafo le_molecula(FILE *f, int id)
{
  // cria grafo vazio
  grafo G = cria_grafo(id);

  // LEITURA
  size_t st = 1024;
  char *s = (char *)malloc(sizeof(char) * st);

  // cabeçalhos
  getline(&s, &st, f);
  getline(&s, &st, f);
  getline(&s, &st, f);

  // numero de vertices e arestas
  int n, m;
  getline(&s, &st, f);
  sscanf(s, "%d %d", &n, &m);

  // vertices
  for (int i = 1; i <= n; ++i)
  {
    float x, y, z;
    char rotulo[10];
    getline(&s, &st, f);
    sscanf(s, "%f %f %f %s", &x, &y, &z, rotulo);
    adiciona_vertice(i, rotulo, G);
  }

  // arestas
  for (int i = 1; i <= m; ++i)
  {
    int u, v;
    char rotulo[10];
    getline(&s, &st, f);
    sscanf(s, "%d %d %s ", &u, &v, rotulo);
    adiciona_aresta(i, rotulo, 1, u, v, G);
  }
  return G;
}

// le valores das energias de ligacao e atribui esses
// valores como pesos às arestas do grafo G
void atribui_energia_ligacao(FILE *f, grafo G)
{
  int peso1, peso2, peso3;
  char u[10], v[10];

  lista arestas = G->arestas;

  while (fscanf(f, "%s %s %d %d %d", u, v, &peso1, &peso2, &peso3) == 5)
  {

    no atual = arestas->primeiro_no;
    while (atual != NULL)
    {
      aresta a = (aresta)atual->conteudo;

      if (strcmp(vertice_rotulo(a->u), u) == 0 && strcmp(vertice_rotulo(a->v), v) == 0)
      {
        if (strcmp(a->rotulo, "1") == 0)
          a->peso = peso1;
        else if (strcmp(a->rotulo, "2") == 0)
          a->peso = peso2;
        else if (strcmp(a->rotulo, "3") == 0)
          a->peso = peso3;
      }
      else if (strcmp(vertice_rotulo(a->u), v) == 0 && strcmp(vertice_rotulo(a->v), u) == 0)
      {

        if (strcmp(a->rotulo, "1") == 0)
          a->peso = peso1;
        else if (strcmp(a->rotulo, "2") == 0)
          a->peso = peso2;
        else if (strcmp(a->rotulo, "3") == 0)
          a->peso = peso3;
      }

      atual = atual->proximo;
    }
  }
}

// remove arestas de menor peso nos caminhos minimos entre u e v
// [ver enunciado do Trabalho 1 para detalhes]
void quebra_molecula(grafo G, vertice u, vertice v)
{

  lista caminho = caminho_minimo(u, v, G);
  aresta aresta_min = NULL;
  int tem_aresta = 0;

  if (caminho)
  {
    vertice vertice_u, vertice_v;
    int tam_lista = tamanho_lista(caminho);
    for (int i = 0; i <= tam_lista; i++)
    {

      vertice_u = desempilha(caminho);
      vertice_v = topo(caminho);

      lista arestas = G->arestas;

      no atual = arestas->primeiro_no;
      while (atual != NULL)
      {
        aresta a = (aresta)atual->conteudo;

        if ((a->u == vertice_u && a->v == vertice_v) || (a->u == vertice_v && a->v == vertice_u))
        {
          if (!tem_aresta || a->peso <= aresta_min->peso)
          {
            aresta_min = a;
          }
          tem_aresta = 1;
          break;
        }
        else if (a->v == vertice_u && a->u == vertice_v)
        {
          if (!tem_aresta || a->peso <= aresta_min->peso)
          {
            aresta_min = a;
          }
          tem_aresta = 1;
          break;
        }
        atual = atual->proximo;
      }
    }
    if (tem_aresta)
    {
      printf("Ligação removida:\n");
      imprime_aresta(aresta_min);
      puts("");
    }
  }
  remove_aresta(aresta_min->id, G);

  if (tamanho_lista(caminho_minimo(u, v, G)) > 1)
  {
    quebra_molecula(G, u, v); // chamada recursiva
  }
}
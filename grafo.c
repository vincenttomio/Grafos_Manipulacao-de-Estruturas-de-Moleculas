/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------
// getters:

int vertice_id(vertice v) {
  return v->id;
};
char* vertice_rotulo(vertice v) {
  return v->rotulo;
};
int custo(vertice v) {
  return v->custo;
};
int estado(vertice v) {
  return v->estado;
};
vertice pai(vertice v) {
  return v->pai;
};
lista fronteira(vertice v) {
  return v->fronteira;
};
int aresta_id(aresta e) {
  return e->id;
};
char *aresta_rotulo(aresta e) {
  return e->rotulo;
};
int peso(aresta e) {
  return e->peso;
};
vertice vertice_u(aresta e) {
  return e->u;
};
vertice vertice_v(aresta e) {
  return e->v;
};
int grafo_id(grafo G) {
  return G->id;
}
lista vertices(grafo G) {
  return G->vertices;
};
lista arestas(grafo G) {
  return G->arestas;
};

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo(int id) {
  grafo G = (grafo) malloc(sizeof(t_grafo));
  if (!G)
    exit(_ERRO_MALLOC_);
  G->id = id;
  G->vertices = cria_lista();
  G->arestas = cria_lista();
  return G;
}

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G) {
  // desalocar os vertices
  lista lv = vertices(G);
  for (no n = primeiro_no(lv); n; n = proximo(n)) {
    vertice v = conteudo(n);
    free(v);
  }

  // desalocar as arestas
  lista la = arestas(G);
  for (no n = primeiro_no(la); n; n = proximo(n)) {
    aresta a = conteudo(n);
    free(a);
  }
  free(G);
}

// cria novo vertice com id <id> rotulo <rotulo> e adiciona ao grafo G
void adiciona_vertice(int id, char *rotulo, grafo G) {
  vertice v = (vertice) malloc(sizeof(t_vertice));
  if (!v)
    exit(_ERRO_MALLOC_);
  v->id = id;
  strcpy(v->rotulo, rotulo);
  v->fronteira = cria_lista();
  empilha(v, vertices(G));
}

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {
  // Busca o vértice com o id passado como parâmetro
  vertice v = busca_chave(id, vertices(G), (int_f_obj) vertice_id);
  
  if (!v)
    return;

  // Remove todas as arestas incidentes ao vértice e as destroi
  while (!vazio(fronteira(v))) {
    aresta e = desempilha(fronteira(v));
    if (vertice_u(e) != v) {
      remove_chave(aresta_id(e), fronteira(vertice_u(e)), (int_f_obj)aresta_id);
    }
    else {
      remove_chave(aresta_id(e), fronteira(vertice_v(e)), (int_f_obj)aresta_id);
    }
    remove_chave(aresta_id(e), arestas(G), (int_f_obj) aresta_id);
    free(e);
  }

  // Remove o vértice da lista de vértices do grafo e o destroi
  remove_chave(id, vertices(G), (int_f_obj) vertice_id);
  free(v);
}

// cria aresta com id <id>, rotulo <rotulo> e peso <peso>,
// incidente a vertices com ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, char *rotulo, int peso, int u_id, int v_id, grafo G) {
  // cria vértices u e v correspondentes aos ids passados como parâmetros
  vertice u = busca_chave(u_id, vertices(G), (int_f_obj)vertice_id);
  vertice v = busca_chave(v_id, vertices(G), (int_f_obj)vertice_id);

  // cria a aresta com id passado como parâmetro e os vértices u e v
  aresta e = (aresta) malloc(sizeof(t_aresta));
  if (!e)
    exit(_ERRO_MALLOC_);
  e->id = id;
  strcpy(e->rotulo, rotulo);
  e->peso = peso;
  e->u = u;
  e->v = v;

  // adiciona a aresta na lista de arestas do grafo
  empilha(e, arestas(G));

  // adiciona a aresta nas listas de fronteiras dos vértices u e v
  empilha(e, fronteira(u));
  empilha(e, fronteira(v));
}

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G) {
  aresta e = busca_chave(id, arestas(G), (int_f_obj)aresta_id);

  if (!e)
    return;

  // remove a aresta da lista de fronteiras dos vértices u e v
  remove_chave(id, fronteira(vertice_u(e)), (int_f_obj)aresta_id);
  remove_chave(id, fronteira(vertice_v(e)), (int_f_obj)aresta_id);

  // remove a aresta da lista de arestas do grafo
  remove_chave(id, arestas(G), (int_f_obj)aresta_id);
  
  // desaloca memória da aresta
  free(e);
}

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}

// imprime o grafo G
void imprime_grafo(grafo G) {
  printf("Molécula ");
  printf("%d\n", grafo_id(G));
  printf("\nEstrutura: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_estrutura_aresta);
  printf("\nVertices: ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n\n===================\n");
}

// imprime o grafo G ponderado
void imprime_grafo_ponderado(grafo G) {
  printf("\nVertices: <id> - [grau]( <fronteira> )");
  printf("\nVertices: ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: <id>:{u,v}<w>");
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n");
}

// imprime o vertice v
void imprime_vertice(vertice v) {
  printf("(id:%d, rotulo:%s, grau:%d, fronteira:{ ", vertice_id(v), vertice_rotulo(v), grau(v));
  imprime_lista(fronteira(v), (void_f_obj) imprime_aresta);
  printf("})");
}

// imprime a aresta e
void imprime_aresta(aresta e) {
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("(id:%d, rotulo:%s, peso:%d, {%d,%d})", aresta_id(e), aresta_rotulo(e), peso(e), u_id, v_id);
}

// imprime apenas a estrutura da aresta e
void imprime_estrutura_aresta(aresta e) {
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("{%d,%d}", u_id, v_id);
}

// devolve a aresta do grafo com vertices u e v
// se a aresta nao existe, devolve NULL
aresta aresta_com_vertices(vertice u, vertice v) {
  for (no n = primeiro_no(fronteira(u)); n; n = proximo(n)) {
    aresta e = conteudo(n);
    if ((vertice_u(e) == u && vertice_v(e) == v) ||
        (vertice_u(e) == v && vertice_v(e) == u))
      return e;
  }
  return NULL;
}

grafo componente_conexa(grafo G, vertice v, int id) {
  // Cria um novo grafo para armazenar a componente conexa
  grafo componente = cria_grafo(id);
  
  // Cria uma pilha para realizar a Busca em profundidade
  lista pilha = cria_lista();
  
  // Marca todos os vértices como não v_visitados
  for (no n = primeiro_no(vertices(G)); n; n = proximo(n)) {
    vertice u = conteudo(n);
    u->estado = 0;
  }
  
  // Empilha o vértice inicial e marca como visitado
  empilha(v, pilha);
  v->estado = 1;
  
  // Adiciona o vértice inicial ao grafo da componente conexa
  adiciona_vertice(v->id, v->rotulo, componente);
  
  // Enquanto houver vértices na pilha
  while (!vazio(pilha)) {
    // Desempilha o próximo vértice a ser visitado
    vertice u = desempilha(pilha);
    
    // Percorre as arestas incidentes ao vértice u
    for (no n = primeiro_no(fronteira(u)); n; n = proximo(n)) {
      aresta e = conteudo(n);
      vertice w;
      if (vertice_u(e) == u)
        w = vertice_v(e);
      else
        w = vertice_u(e);
      
      // Se w ainda não foi visitado, marca como visitado e empilha
      if (w->estado == 0) {
        w->estado = 1;
        empilha(w, pilha);
        
        // Adiciona o vértice w ao grafo da componente conexa
        adiciona_vertice(w->id, w->rotulo, componente);
      }
      
      // Adiciona a aresta ao grafo da componente conexa, caso ela ainda não tenha sido adicionada
      if (!busca_chave(aresta_id(e), componente->arestas, (int_f_obj)aresta_id)) {
        adiciona_aresta(e->id, e->rotulo, e->peso, vertice_id(vertice_u(e)), vertice_id(vertice_v(e)), componente);
      }
    }
  }
  return componente;
}

// aplica o algoritmo de dijkstra para encontrar o menor caminho de u para
// todos os vertices do grafo G. Ao final, os atributos custo e pai de cada vertice
// estarão preenchidos adequadamente
// [a contante INT_MAX é usada como valor de custo infinito]
void dijkstra(grafo G, vertice u) {
  // Armazena os vertices visitados numa lista
  lista visitados = cria_lista();

  // Inicializa os atributos de custo e pai de todos os vértices
  for (no n = primeiro_no(vertices(G)); n; n = proximo(n)) {
    vertice v = conteudo(n);
    v->custo = INT_MAX;
    v->pai = NULL;
  }

  //vertice inicial terá custo 0
  u->custo = 0;

  while (!vazio(vertices(G))) {
    // Encontra o vértice não visitado de menor custo
    vertice v_min = NULL;
    int menor_custo = INT_MAX;
    for (no n = primeiro_no(vertices(G)); n; n = proximo(n)) {
      vertice v = conteudo(n);
      if (v->custo < menor_custo && !busca_chave(v->id, visitados, (int_f_obj)vertice_id)) {
        menor_custo = v->custo;
        v_min = v;
      }
    }

    // Se não há mais vértices não visitados, encerra o algoritmo
    if (!v_min) {
      break;
    }

    // Adiciona o vértice atual à lista de visitados
    empilha(v_min, visitados);

    // Percorre as arestas incidentes ao vértice atual
    for (no n = primeiro_no(fronteira(v_min)); n; n = proximo(n)) {
      aresta e = conteudo(n);
      vertice v;
      if (vertice_u(e) == v_min)
        v = vertice_v(e);
      else
        v = vertice_u(e);
        
      int custo_alternativo = v_min->custo + peso(e);

      // Atualiza o custo do vértice v, caso seja menor que o custo atual
      if (custo_alternativo < v->custo) {
        v->custo = custo_alternativo;
        v->pai = v_min;
      }
    }
  }


  // Libera a memória utilizada pela lista de vértices visitados
  free(visitados);
}

// Gera o caminho minímo de u até v
lista caminho_minimo(vertice u, vertice v, grafo G) {
  //Encontra o menor caminho de um vértice inicial u
  dijkstra(G,u); 
  lista caminho = cria_lista();
  vertice v_min = v;

  // Constrói o caminho mínimo através dos pais
  while (v_min) {
    empilha(v_min, caminho);
    v_min = v_min->pai;
  }

  return caminho;
}
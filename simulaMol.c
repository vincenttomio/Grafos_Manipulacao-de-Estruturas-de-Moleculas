/*******************************************
 * Manipulação de Moléculas - Trabalho 1
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include "molecula.h"
#include <stdio.h>
#include <stdlib.h>

// ./simulaMol arq.mol energias.dat < vertices.in
int main(int argc, char *argv[])
{

  // Lidando com possiveis erros de entrada de dados
  if (argc != 3)
  {
    printf("Uso correto: %s arquivo_mol arquivo_dat\n", argv[0]);
    return 1;
  }

  // le arquivo .mol e cria molecula inicial
  FILE *mol_file = fopen(argv[1], "r");
  if (mol_file == NULL)
  {
    printf("Erro ao abrir arquivo %s\n", argv[1]);
    return 1;
  }

  grafo G = le_molecula(mol_file, 1);

  fclose(mol_file);

  // le arquivo .dat e atribui energias de ligação à molécula inicial
  FILE *dat_file = fopen(argv[2], "r");
  if (dat_file == NULL)
  {
    printf("\nErro ao abrir arquivo %s\n", argv[2]);
    return 1;
  }

  atribui_energia_ligacao(dat_file, G);

  fclose(dat_file);

  // processamento inicial e imprimir molécula
  imprime_grafo(G);

  lista grafos = cria_lista();
  empilha(G, grafos);

  // laço principal de leitura
  int entrada_u, entrada_v, i = 1;
  scanf("%d %d", &entrada_u, &entrada_v);

  while (entrada_u || entrada_v)
  {
    int listaTam = tamanho_lista(grafos);
    int j = 1;
    no n = primeiro_no(grafos);

    while (1)
    {
      grafo GX = conteudo(n);
      vertice u = busca_chave(entrada_u, vertices(GX), (int_f_obj)vertice_id);
      vertice v = busca_chave(entrada_v, vertices(GX), (int_f_obj)vertice_id);

      if (u && v)
      {
        printf("Átomos %d e %d da molécula %d, iniciando quebra:\n", entrada_u, entrada_v, GX->id);

        quebra_molecula(GX, u, v);

        grafo G_u = componente_conexa(GX, u, G->id + i);
        i++;
        grafo G_v = componente_conexa(GX, v, G->id + i);

        remove_chave(grafo_id(GX), grafos, (int_f_obj)grafo_id);

        empilha(G_u, grafos);
        empilha(G_v, grafos);
        break;
      }

      if (j == listaTam)
      {
        puts("Átomos não encontrados ou de moléculas diferentes");
        break;
      }
      else
      {
        n = proximo(n);
        j++;
      }
    }

    imprime_lista(grafos, (void_f_obj)imprime_grafo);

    scanf("%d %d", &entrada_u, &entrada_v);
    i++;
  }

  destroi_grafo(G);
  return 0;
}
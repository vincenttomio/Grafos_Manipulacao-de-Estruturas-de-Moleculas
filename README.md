# Trabalho 1 - Manipulação de Estruturas de Moléculas

Este projeto foi realizado em dupla pelos alunos:
```
 Vincent Van Santen Von Biveniczko Tomio - GRR20206365
 Yan Oliveira da Costa - GRR20204095
```
Como parte da disciplina de CI1054 - Algoritmos em Grafos e Otimização, o objetivo do trabalho foi desenvolver um programa capaz de manipular estruturas moleculares em arquivos, permitindo ao usuário adicionar uma molécula e cortar as ligações, criando assim uma molécula k-partida, ou k-moléculas. 

O projeto foi bastante desafiador, exigindo dos alunos o domínio de conceitos em grafos e programação. 
No entanto, apesar dos desafios enfrentados, a conclusão do projeto foi extremamente gratificante, pois permitiu aos alunos aplicar seus conhecimentos teóricos em um problema real e desenvolver habilidades práticas de programação e análise de dados.

# Tópicos

O projeto foi dividido em:

  - Adequação das bibliotecas Grafo.c e Molecula.C
  - Implementação do algoritmo principal


# Adequação da biblioteca grafo.C

## Funções para manipulação dos Grafos

### Foi implementando um conjunto de funções que tem como objetivo auxiliar na construção, manipulação e destruição dos grafos, sendo elas:

A função `destroi_grafo` recebe um ponteiro para um grafo G e desaloca toda a memória alocada para ele. Isso inclui, além do próprio grafo, todos os seus vértices e arestas.

A função `adiciona_vertice` cria um novo vértice com o identificador id, rótulo rotulo e o adiciona ao grafo G. A função aloca memória suficiente para armazenar o vértice e seu rótulo.

A função `remove_vertice` faz a remoção do vértice com identificador id do grafo G e também todas as arestas incidentes a ele. Ela percorre a lista de fronteiras do vértice, removendo as arestas da lista de arestas do grafo e desalocando a memória alocada para elas.

A função `adiciona_aresta` cria uma nova aresta com identificador id, com o rótulo, peso e a adiciona ao grafo G. Para isso, ela busca pelos vértices com identificadores u_id e v_id e atribui-os à aresta. Em seguida, a função adiciona a aresta às listas de fronteira dos vértices u_id e v_id.

A função `remove_aresta` faz a remoção da aresta com identificador id do grafo G. Ela busca pela aresta na lista de arestas do grafo e a remove da lista de fronteira dos vértices incidentes a ela. Em seguida, a função desaloca a memória alocada para a aresta.

## Algoritmos implementados

### Componente Conexo

A função `componente_conexa` implementa um algoritmo para encontrar a componente conexa de um grafo G a partir de um vértice inicial com identificador id. A componente conexa de um grafo é definida como o conjunto de todos os vértices e arestas que são alcançáveis a partir de um dado vértice.

### Implementação
A função começa criando um novo grafo vazio chamado componente com o identificador fornecido como parâmetro. Em seguida, cria-se uma lista vazia para armazenar os vértices a serem visitados. Após isso é marcado todos os vértices do grafo original como não visitados, percorrendo a lista de vértices do grafo original e atualizando o estado de cada vértice para 0.

```
grafo componente = cria_grafo(id);
  
lista pilha = cria_lista();
  
for (no n = primeiro_no(vertices(G)); n; n = proximo(n)) {
  vertice u = conteudo(n);
  u->estado = 0;
}

```

A seguir, o vértice inicial v é empilhado na pilha e marcado como visitado (estado 1). Além disso, é adicionado ao grafo da componente conexa componente como um novo vértice.

O algoritmo continua enquanto houver vértices na pilha. Em cada iteração do loop, o próximo vértice a ser visitado é desempilhado da pilha e armazenado em u. Depois, são percorridas todas as arestas incidentes ao vértice u, obtidas por meio da lista de adjacências do vértice.

Para cada vértice adjacente w, se ele ainda não foi visitado, é empilhado na pilha, marcado como visitado (estado 1) e adicionado ao grafo da componente conexa componente. Além disso, se a aresta que liga u e w ainda não foi adicionada ao grafo componente, ela é adicionada.

```
  while (!vazio(pilha)) {
    vertice u = desempilha(pilha);
    
    for (no n = primeiro_no(fronteira(u)); n; n = proximo(n)) {
      aresta e = conteudo(n);
      vertice w;
      if (vertice_u(e) == u)
        w = vertice_v(e);
      else
        w = vertice_u(e);
      
      if (w->estado == 0) {
        w->estado = 1;
        empilha(w, pilha);
        adiciona_vertice(w->id, w->rotulo, componente);
      }

      if (!busca_chave(aresta_id(e), componente->arestas, (int_f_obj)aresta_id)) {
        adiciona_aresta(e->id, e->rotulo, e->peso, vertice_id(vertice_u(e)), vertice_id(vertice_v(e)), componente);
      }
    }
  }

```

Por fim, quando a lista estiver vazia, o algoritmo retorna o grafo da componente conexa encontrado a partir do vértice inicial.

## Algoritmo de Dijkstra

A função `dijkstra` implementa o algoritmo de Djikstra que recebe o grafo G, onde vai encontrar o menor caminho de um vértice inicial u para todos os outros vértices em um grafo ponderado. O resultado do algoritmo é armazenado nos atributos custo (v->custo) e pai (v->pai) de cada vértice do grafo. O valor INT_MAX é utilizado como custo infinito.

### Implementação

Inicialmente, é criado uma lista vazia de vértices visitados e os atributos custo e pai de todos os vértices são inicializados. O custo é definido como INT_MAX, que representa um valor infinito. O vértice u é o vértice inicial e seu custo é definido como 0.

```
  lista visitados = cria_lista();

  // Inicializa os atributos de custo e pai de todos os vértices
  for (no n = primeiro_no(vertices(G)); n; n = proximo(n)) {
    vertice v = conteudo(n);
    v->custo = INT_MAX;
    v->pai = NULL;
  }

  //vertice inicial terá custo 0
  u->custo = 0;
```

#### Em seguida, a função entra em um loop que segue as seguintes etapas:

1. Encontra o vértice não visitado de menor custo.
2. Adiciona o vértice atual à lista de visitados.
3. Percorre as arestas incidentes ao vértice atual e atualiza o custo e o pai dos vértices adjacentes, caso seja necessário.
O loop continua até que todos os vértices tenham sido visitados ou não haja mais vértices não visitados.

```
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

    if (!v_min) {
      break;
    }

    empilha(v_min, visitados);

    for (no n = primeiro_no(fronteira(v_min)); n; n = proximo(n)) {
      aresta e = conteudo(n);
      vertice v;
      if (vertice_u(e) == v_min)
        v = vertice_v(e);
      else
        v = vertice_u(e);
        
      int custo_alternativo = v_min->custo + peso(e);

      if (custo_alternativo < v->custo) {
        v->custo = custo_alternativo;
        v->pai = v_min;
      }
    }
  }
  ```
  Por fim, libera a memória utilizada pela lista de vértices visitados.

### Caminho Mínimo

A função `caminho_minimo` foi uma função auxiliar criada que recebe dois vértices u e v e um grafo G, e retorna uma lista contendo o caminho mínimo de u até v no grafo G. Essa função utiliza a função dijkstra para calcular os valores de custo e pai dos vértices, e então percorre os pais a partir de v até u para construir a lista com o caminho mínimo. Foi muito importante implementação de uma das principais funções do trabalho, a função `quebra_molecula`.

# Adequação da biblioteca molécula.C

## Atribuição de Energia de Ligação

O código em C apresentado tem como objetivo a atribuição de energia de ligação em um grafo. Para isso, é necessário ter um arquivo com informações sobre as ligações entre os vértices do grafo e seus respectivos pesos.

### Funcionamento

A função `atribui_energia_ligacao` é responsável por receber um arquivo `f` contendo as informações das ligações e os pesos correspondentes e também recebe o grafo `G` ao qual serão atribuídas as energias de ligação. 

No início da função, são declaradas as variáveis `peso1`, `peso2`, `peso3` para armazenar os valores dos pesos de cada tipo de ligação e os arrays `u` e `v` para armazenar os rótulos dos vértices que compõem a aresta. 

Em seguida, é acessada a lista de arestas do grafo `G`. Através de um loop while, a função lê as informações do arquivo de entrada e, enquanto for possível ler 5 valores, ou seja, os rótulos dos vértices e os três tipos de peso, a função entra em outro loop while que percorre a lista de arestas do grafo. 

Para cada aresta, é verificado se seus vértices correspondem aos rótulos lidos no arquivo através da função `strcmp` (que compara duas strings). Caso haja correspondência, a energia de ligação da aresta é atualizada de acordo com o tipo de peso correspondente.

Por fim, a função percorre todas as arestas do grafo e atualiza as energias de ligação conforme a leitura do arquivo.

## Quebra de Molécula

O código em C apresentado tem como objetivo quebrar uma molécula a partir da remoção da aresta de menor peso entre dois vértices. Para isso, é necessário ter um grafo já criado e passar dois dos seus vértices.

### Funcionamento

A função `quebra-molecula` recebe o grafo `G` e os vértices `u` e `v` que representam a extremidade da ligação que deverá ser removida.

Inicialmente, a função chama a função `caminho_minimo` para encontrar o caminho mínimo entre os dois vértices passados. Caso exista um caminho, a função entra em um loop for que percorre todos os vértices do caminho encontrado.

Dentro do loop, a função verifica se existe uma aresta que conecta o vértice atual com o próximo vértice no caminho. Em caso afirmativo, a função compara o peso dessa aresta com a menor aresta encontrada anteriormente. Se essa aresta tiver peso menor ou se for a primeira aresta encontrada, a variável `aresta_min` receberá essa aresta.

Após percorrer todo o caminho e encontrar a aresta de menor peso, a função remove essa aresta do grafo e faz uma chamada recursiva da função `quebra_molecula` se ainda houver caminhos mínimos entre os vértices `u` e `v`.

# Implementação do algoritmo principal simulaMol.C

## Explicação
Este é um programa em C que lida com a manipulação de moléculas e realiza a quebra de ligações entre átomos. O programa lê arquivos de entrada em formato .mol e .dat, cria uma estrutura de grafo para representar a molécula e executa a quebra de ligações conforme as entradas fornecidas.

## Uso
```
./simulaMol.c arquivo.mol arquivo.dat < .in > .out
```

## Código

Verificação de argumentos de linha de comando:

```
if (argc != 3)
{
  printf("Uso correto: %s arquivo_mol arquivo_dat\n", argv[0]);
  return 1;
}

```
O programa verifica se o número correto de argumentos de linha de comando foi fornecido. Caso contrário, exibe uma mensagem de uso correto e retorna um código de erro.

Leitura do arquivo `.mol` e criação da molécula inicial:

```
FILE *mol_file = fopen(argv[1], "r");
if (mol_file == NULL)
{
  printf("Erro ao abrir arquivo %s\n", argv[1]);
  return 1;
}

grafo G = le_molecula(mol_file, 1);

fclose(mol_file);
```

O programa abre o arquivo `.mol` fornecido e cria uma molécula inicial representada por um grafo.

Leitura do arquivo `.dat` e atribuição de energias de ligação à molécula inicial:


```
FILE *dat_file = fopen(argv[2], "r");
if (dat_file == NULL)
{
  printf("\nErro ao abrir arquivo %s\n", argv[2]);
  return 1;
}

atribui_energia_ligacao(dat_file, G);

fclose(dat_file);
```

O programa abre o arquivo `.dat` fornecido e atribui as energias de ligação à molécula inicial.

Processamento inicial e impressão da molécula:


```
imprime_grafo(G);
```

O programa imprime a representação do grafo da molécula inicial.

## Parte principal
### Criação da lista `grafos` e empilhamento do grafo inicial

```c
lista grafos = cria_lista();
empilha(G, grafos);
```

Nessa parte do código, é criada uma lista chamada `grafos` usando a função `cria_lista()`. Essa lista será usada para armazenar os grafos resultantes da quebra de ligações.

Em seguida, o grafo inicial `G` é empilhado na lista `grafos` usando a função `empilha(G, grafos)`. Isso significa que o grafo inicial será o primeiro elemento da lista.

### Laço principal de leitura

```c
int entrada_u, entrada_v, i = 1;
scanf("%d %d", &entrada_u, &entrada_v);

while (entrada_u || entrada_v)
{
  // ...
}
```

Nessa parte do código, é iniciado um laço principal de leitura que será executado enquanto o usuário fornecer valores diferentes de zero para `entrada_u` e `entrada_v`. Os valores são lidos do usuário usando a função `scanf`.

### Iteração na lista de grafos

```c
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
    // Quebra de ligação e criação de novos grafos
    // ...
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
```

Nessa parte do código, é realizada uma iteração na lista de grafos `grafos` para encontrar o grafo que contém os átomos fornecidos pelo usuário.

A variável `listaTam` guarda o tamanho da lista de grafos, enquanto `j` é um contador usado para percorrer a lista. A variável `n` é um nó que aponta para o primeiro nó da lista, obtido através da função `primeiro_no(grafos)`.

Dentro do laço `while(1)`, o programa verifica se os átomos `u` e `v` existem no grafo atual `GX` usando a função `busca_chave()`. Se os átomos forem encontrados, significa que a ligação pode ser quebrada nesse grafo.

### Quebra de ligação e criação de novos grafos

```c
printf("Átomos %d e %d da molécula %d, iniciando quebra:\n", entrada_u, entrada_v, GX->id);

quebra_molecula(GX, u, v);

grafo G_u = componente_conexa(GX, u, G->id + i);
i++;
grafo G_v = componente_conexa(GX, v, G->id + i);

remove_chave(grafo_id(GX), grafos, (int_f_obj)grafo_id);

empilha(G_u, grafos);
empilha(G_v, grafos);


break;
```

Nessa parte do código, ocorre a quebra da ligação entre os átomos `u` e `v` no grafo `GX` usando a função `quebra_molecula()`. Em seguida, são criados dois novos grafos, `G_u` e `G_v`, que representam as componentes conexas resultantes da quebra.

Após a quebra da ligação, o grafo `GX` é removido da lista de grafos `grafos` usando a função `remove_chave()`, que remove o grafo com base no seu identificador.

Os grafos `G_u` e `G_v` são empilhados na lista `grafos` usando a função `empilha()`, tornando-os os próximos grafos a serem processados.

### Impressão da lista de grafos e leitura dos próximos valores

```c
imprime_lista(grafos, (void_f_obj)imprime_grafo);

scanf("%d %d", &entrada_u, &entrada_v);
i++;
```

Nessa parte do código, a lista de grafos `grafos` é impressa na tela usando a função `imprime_lista()`, que recebe como parâmetro a função `imprime_grafo` para imprimir cada grafo da lista.

Em seguida, são lidos os próximos valores de `entrada_u` e `entrada_v` usando a função `scanf`. O contador `i` é incrementado para garantir a criação de identificadores únicos para os próximos grafos a serem processados.

### Destruir o grafo inicial e encerrar o programa

```c
destroi_grafo(G);
return 0;
```

Nessa parte final do código, o grafo inicial `G` é destruído usando a função `destroi_grafo()`, que libera a memória alocada para o grafo e seus elementos.

Em seguida, o programa retorna 0 para indicar que a execução ocorreu sem erros.

Essa é uma visão geral do código e como ele funciona. Cada parte desempenha um papel importante na manipulação de moléculas e na quebra de ligações entre átomos.
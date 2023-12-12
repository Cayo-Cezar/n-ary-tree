#include <stdio.h>
#include <stdlib.h>

typedef struct nohArvore {
  int info;
  struct nohArvore *primeiroFilho;
  struct nohArvore *proximoIrmao;
} NohArvore;

typedef struct dArvore {
  int grauMaximo;
  NohArvore *raiz;
} DArvore;

typedef NohArvore *pNohArvore;
typedef DArvore *pDArvore;

pDArvore criarArvore(int grauMaximo) {
  pDArvore novaArvore = (pDArvore)malloc(sizeof(DArvore));
  novaArvore->grauMaximo = grauMaximo;
  novaArvore->raiz = NULL;
  return novaArvore;
}

void incluirInfo(pDArvore arvore, int info) {
  NohArvore *novoNoh = (NohArvore *)malloc(sizeof(NohArvore));
  novoNoh->info = info;
  novoNoh->primeiroFilho = NULL;
  novoNoh->proximoIrmao = NULL;

  if (arvore->raiz == NULL) {
    arvore->raiz = novoNoh;
  } else {
    NohArvore *ultimoFilho = arvore->raiz->primeiroFilho;
    if (ultimoFilho == NULL) {
      arvore->raiz->primeiroFilho = novoNoh;
    } else {
      while (ultimoFilho->proximoIrmao != NULL) {
        ultimoFilho = ultimoFilho->proximoIrmao;
      }
      ultimoFilho->proximoIrmao = novoNoh;
    }
  }
}

int excluirInfo(pDArvore arvore, int info) {
  if (arvore == NULL || arvore->raiz == NULL) {
    return 0;
  }

  NohArvore *atual = arvore->raiz;
  NohArvore *anterior = NULL;

  while (atual != NULL && atual->info != info) {
    anterior = atual;
    atual = atual->proximoIrmao;
  }

  if (atual == NULL) {
    return 0;
  }

  if (anterior != NULL) {
    anterior->proximoIrmao = atual->proximoIrmao;
  } else {
    arvore->raiz = atual->proximoIrmao;
  }

  free(atual);
  return 1;
}

int excluirInfoComFilhosRecursivo(NohArvore *raiz, int info) {
  if (raiz == NULL) {
    return 0;
  }

  if (raiz->info == info) {
    free(raiz);
    return 1;
  }

  int excluido = excluirInfoComFilhosRecursivo(raiz->primeiroFilho, info);
  if (excluido) {
    return 1;
  }

  excluido = excluirInfoComFilhosRecursivo(raiz->proximoIrmao, info);

  return excluido;
}

int excluirInfoComFilhos(pDArvore arvore, int info) {
  if (arvore == NULL || arvore->raiz == NULL) {
    return 0;
  }

  if (arvore->raiz->info == info) {
    free(arvore->raiz);
    arvore->raiz = NULL;
    return 1;
  }

  return excluirInfoComFilhosRecursivo(arvore->raiz->primeiroFilho, info);
}

pNohArvore buscarInfoRecursivo(NohArvore *raiz, int info) {
  if (raiz == NULL) {
    return NULL;
  }

  if (raiz->info == info) {
    return raiz;
  }

  pNohArvore resultadoFilhos = buscarInfoRecursivo(raiz->primeiroFilho, info);
  if (resultadoFilhos != NULL) {
    return resultadoFilhos;
  }

  return buscarInfoRecursivo(raiz->proximoIrmao, info);
}

pNohArvore buscarInfo(pDArvore arvore, int info) {
  if (arvore == NULL || arvore->raiz == NULL) {
    return NULL;
  }

  return buscarInfoRecursivo(arvore->raiz, info);
}

int quantidadeFolhasRecursivo(NohArvore *raiz) {
  if (raiz == NULL) {
    return 0;
  }

  if (raiz->primeiroFilho == NULL) {
    return 1;
  }

  int folhasFilho = quantidadeFolhasRecursivo(raiz->primeiroFilho);
  int folhasIrmao = quantidadeFolhasRecursivo(raiz->proximoIrmao);

  return folhasFilho + folhasIrmao;
}

int quantidadeFolhas(pDArvore arvore) {
  if (arvore == NULL || arvore->raiz == NULL) {
    return 0;
  }

  return quantidadeFolhasRecursivo(arvore->raiz);
}

int quantidadeNohsRecursivo(NohArvore *raiz) {
  if (raiz == NULL) {
    return 0;
  }

  int nohsFilho = quantidadeNohsRecursivo(raiz->primeiroFilho);
  int nohsIrmao = quantidadeNohsRecursivo(raiz->proximoIrmao);

  return nohsFilho + nohsIrmao + 1;
}

int quantidadeNohs(pDArvore arvore) {
  if (arvore == NULL || arvore->raiz == NULL) {
    return 0;
  }

  return quantidadeNohsRecursivo(arvore->raiz);
}

int ehFolha(pDArvore arvore, int info) {
  pNohArvore noh = buscarInfo(arvore, info);

  if (noh != NULL && noh->primeiroFilho == NULL) {
    return 1;
  }

  return 0;
}

void imprimirArvoreRecursivo(NohArvore *raiz, int nivel) {
  if (raiz == NULL) {
    return;
  }

  for (int i = 0; i < nivel; i++) {
    printf("  ");
  }
  printf("%d\n", raiz->info);

  imprimirArvoreRecursivo(raiz->primeiroFilho, nivel + 1);
  imprimirArvoreRecursivo(raiz->proximoIrmao, nivel);
}

void imprimirArvore(pDArvore arvore) {
  printf("Árvore:\n");
  imprimirArvoreRecursivo(arvore->raiz, 0);
}

int naoEhFolha(pDArvore arvore, int info) { return !ehFolha(arvore, info); }

int main() {
  pDArvore minhaArvore = criarArvore(3);

  // Teste de inclusão de informações
  incluirInfo(minhaArvore, 1);
  incluirInfo(minhaArvore, 2);
  incluirInfo(minhaArvore, 3);
  incluirInfo(minhaArvore, 4);
  incluirInfo(minhaArvore, 5);

  // Teste de contagem de folhas
  int folhas = quantidadeFolhas(minhaArvore);
  printf("\nQuantidade de folhas na árvore: %d\n", folhas);

  // Teste de contagem de nós
  int nohs = quantidadeNohs(minhaArvore);
  printf("\nQuantidade de nós na árvore: %d\n", nohs);

  // Teste de verificação se é folha
  int folhaInfo = 5;
  if (ehFolha(minhaArvore, folhaInfo)) {
    printf("\n%d é uma folha na árvore.\n", folhaInfo);
  } else {
    printf("\n%d não é uma folha na árvore ou não foi encontrado.\n",
           folhaInfo);
  }

  // Teste de verificação se não é folha
  int naoFolhaInfo = 3;
  if (naoEhFolha(minhaArvore, naoFolhaInfo)) {
    printf("\n%d não é uma folha na árvore.\n", naoFolhaInfo);
  } else {
    printf("\n%d é uma folha na árvore ou não foi encontrado.\n", naoFolhaInfo);
  }

  printf("Árvore inicial:\n");
  imprimirArvore(minhaArvore);

  // Teste de exclusão de informação preservando filhos
  excluirInfo(minhaArvore, 3);
  printf("\nApós excluir 3 (preservando filhos):\n");
  imprimirArvore(minhaArvore);

  // Teste de exclusão de informação com filhos
  excluirInfoComFilhos(minhaArvore, 2);
  printf("\nApós excluir 2 (com filhos):\n");
  imprimirArvore(minhaArvore);

  // Teste de busca de informação
  int buscaInfo = 4;
  pNohArvore nohBusca = buscarInfo(minhaArvore, buscaInfo);
  if (nohBusca != NULL) {
    printf("\nEncontrado %d na árvore.\n", buscaInfo);
  } else {
    printf("\n%d não encontrado na árvore.\n", buscaInfo);
  }
}

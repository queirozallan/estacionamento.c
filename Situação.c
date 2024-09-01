#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARROS 10
#define MAX_ESPERA 10

typedef struct {
    int placa;
    int manobras;
    int ficouNaFila;
} Carro;

typedef struct {
    Carro carros[MAX_CARROS];
    int topo;
} Beco;

typedef struct {
    Carro carros[MAX_ESPERA];
    int frente;
    int traseira;
    int contador;
} FilaEspera;

// Função para criar um beco
Beco* criarBeco() {
    Beco* beco = (Beco*)malloc(sizeof(Beco));
    beco->topo = -1;
    return beco;
}

// Função para criar uma fila de espera
FilaEspera* criarFilaEspera() {
    FilaEspera* fila = (FilaEspera*)malloc(sizeof(FilaEspera));
    fila->frente = 0;
    fila->traseira = -1;
    fila->contador = 0;
    return fila;
}

// Funções para verificar se o beco ou a fila estão cheios ou vazios
int isBecoCheio(Beco* beco) {
    return beco->topo == MAX_CARROS - 1;
}

int isBecoVazio(Beco* beco) {
    return beco->topo == -1;
}

int isFilaCheia(FilaEspera* fila) {
    return fila->contador == MAX_ESPERA;
}

int isFilaVazia(FilaEspera* fila) {
    return fila->contador == 0;
}

// Função para adicionar um carro ao beco
void entrarCarroBeco(Beco* beco, int placa, int ficouNaFila) {
    if (isBecoCheio(beco)) {
        printf("O beco está cheio. Carro com placa %d não pode entrar.\n", placa);
        return;
    }
    beco->carros[++beco->topo].placa = placa;
    beco->carros[beco->topo].manobras = 0;
    beco->carros[beco->topo].ficouNaFila = ficouNaFila;
    printf("Carro com placa %d entrou no beco.\n", placa);
}

// Função para remover um carro do beco
void sairCarroBeco(Beco* beco, int placa) {
    if (isBecoVazio(beco)) {
        printf("O beco está vazio. Nenhum carro para sair.\n");
        return;
    }

    Beco* temp = criarBeco();
    int found = 0;
    Carro carroRemovido;

    while (!isBecoVazio(beco)) {
        Carro carro = beco->carros[beco->topo--];
        carro.manobras++;

        if (carro.placa == placa) {
            carroRemovido = carro;
            printf("Carro com placa %d saiu do beco após %d manobras.\n", carro.placa, carro.manobras);
            if (carro.ficouNaFila) {
                printf("Este carro ficou na fila de espera.\n");
            }
            found = 1;
            break;
        } else {
            temp->carros[++temp->topo] = carro;
        }
    }

    while (!isBecoVazio(temp)) {
        beco->carros[++beco->topo] = temp->carros[temp->topo--];
    }

    if (!found) {
        printf("Carro com placa %d não encontrado no beco.\n", placa);
    }

    free(temp);
}

// Função para adicionar um carro à fila de espera
void adicionarCarroFila(FilaEspera* fila, int placa) {
    if (isFilaCheia(fila)) {
        printf("A fila de espera está cheia. Carro com placa %d não pode ser adicionado.\n", placa);
        return;
    }

    if (fila->traseira == MAX_ESPERA - 1) {
        fila->traseira = -1;
    }
    fila->carros[++fila->traseira].placa = placa;
    fila->carros[fila->traseira].manobras = 0;
    fila->carros[fila->traseira].ficouNaFila = 1;
    fila->contador++;
    printf("Carro com placa %d foi adicionado à fila de espera.\n", placa);
}

// Função para remover um carro da fila de espera e adicioná-lo a um beco
void removerCarroFila(FilaEspera* fila, Beco* beco1, Beco* beco2) {
    if (isFilaVazia(fila)) {
        printf("A fila de espera está vazia.\n");
        return;
    }

    Carro carro = fila->carros[fila->frente++];
    if (fila->frente == MAX_ESPERA) {
        fila->frente = 0;
    }
    fila->contador--;

    if (!isBecoCheio(beco1)) {
        entrarCarroBeco(beco1, carro.placa, carro.ficouNaFila);
    } else if (!isBecoCheio(beco2)) {
        entrarCarroBeco(beco2, carro.placa, carro.ficouNaFila);
    } else {
        adicionarCarroFila(fila, carro.placa);
    }
}

// Função para alocar carros da fila de espera se houver vaga em algum dos becos
void alocarCarroNaFilaSeTiverVaga(FilaEspera* fila, Beco* beco1, Beco* beco2) {
    if (!isFilaVazia(fila)) {
        removerCarroFila(fila, beco1, beco2);
    }
}

// Função para exibir o estado atual do estacionamento
void exibirEstadoEstacionamento(Beco* beco1, Beco* beco2, FilaEspera* fila) {
    printf("\nEstado atual do estacionamento:\n");

    printf("Beco 1 (%d carros): ", beco1->topo + 1);
    for (int i = 0; i <= beco1->topo; i++) {
        printf("%d ", beco1->carros[i].placa);
    }
    printf("\n");

    printf("Beco 2 (%d carros): ", beco2->topo + 1);
    for (int i = 0; i <= beco2->topo; i++) {
        printf("%d ", beco2->carros[i].placa);
    }
    printf("\n");

    printf("Fila de Espera (%d carros): ", fila->contador);
    int index = fila->frente;
    for (int i = 0; i < fila->contador; i++) {
        printf("%d ", fila->carros[index].placa);
        index = (index + 1) % MAX_ESPERA;
    }
    printf("\n");
}

// Função principal
int main() {
    Beco* beco1 = criarBeco();
    Beco* beco2 = criarBeco();
    FilaEspera* fila = criarFilaEspera();

    int opcao, placa;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Adicionar carro\n");
        printf("2. Remover carro\n");
        printf("3. Exibir estado do estacionamento\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a placa do carro: ");
                scanf("%d", &placa);

                if (!isBecoCheio(beco1)) {
                    printf("Vaga disponível no Beco 1.\n");
                    entrarCarroBeco(beco1, placa, 0);
                } else if (!isBecoCheio(beco2)) {
                    printf("Vaga disponível no Beco 2.\n");
                    entrarCarroBeco(beco2, placa, 0);
                } else {
                    printf("Não há vagas disponíveis. Deseja entrar na fila de espera? (1 - Sim, 0 - Não): ");
                    int desejaFila;
                    scanf("%d", &desejaFila);
                    if (desejaFila) {
                        adicionarCarroFila(fila, placa);
                    }
                }
                break;

            case 2:
                printf("Digite a placa do carro para remover: ");
                scanf("%d", &placa);

                sairCarroBeco(beco1, placa);
                sairCarroBeco(beco2, placa);

                alocarCarroNaFilaSeTiverVaga(fila, beco1, beco2);
                break;

            case 3:
                exibirEstadoEstacionamento(beco1, beco2, fila);
                break;

            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 4);

    free(beco1);
    free(beco2);
    free(fila);

    return 0;
}

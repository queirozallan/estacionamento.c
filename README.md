# estacionamento.c
Situação 2: Situação 2: Um estacionamento é composto por dois becos que guarda até 10 carros cada. Existe apenas uma
entrada/saída para acessar cada beco. Se chegar um cliente para retirar um carro que não seja o que está na
saída, todos os carros bloqueando seu caminho sairão do estacionamento, o carro é removido, e os outros
carros voltam para mesma sequência. O programa deverá informar toda vez que um carro entrar ou sair.
Quando um carro chegar, o programa deverá informar se tem ou não vaga e em qual beco. Se não houver
vaga, o usuário pode escolher se quer ou não ficar numa fila de espera. Quando abrir vaga, os carros que estão
na fila, serão alocados no beco que houver vaga. Quando o carro sair, o programa deverá informar quantas
vezes o carro foi manobrado, se ele ficou na fila de espera.





# Estacionamento e Fila de Espera

Este projeto é um sistema para gerenciar um estacionamento com dois becos e uma fila de espera. O sistema permite adicionar e remover carros dos becos, gerenciar a fila de espera e exibir o estado atual do estacionamento.

## Descrição

O programa gerencia um estacionamento dividido em dois becos, cada um com capacidade para 10 carros. Quando um carro é removido e não está no beco de saída, todos os carros que bloqueiam seu caminho são removidos temporariamente. Os carros que ficam na fila de espera são alocados aos becos quando uma vaga se torna disponível.

### Funcionalidades

- **Adicionar Carro**: Adiciona um carro a um dos becos ou à fila de espera se ambos os becos estiverem cheios.
- **Remover Carro**: Remove um carro de um dos becos e, se necessário, manobra os carros que bloqueiam seu caminho.
- **Exibir Estado do Estacionamento**: Mostra a situação atual dos becos e da fila de espera.
- **Gerenciamento da Fila de Espera**: Carros na fila de espera são alocados aos becos quando vagas se tornam disponíveis.

## Como Usar

1. **Compilar o Programa**

   Para compilar o código, utilize um compilador C como o `gcc`. Execute o comando:

   ```bash
   gcc -o estacionamento principal.c


Executar o Programa

Após compilar, execute o programa com o comando:

./estacionamento

Interagir com o Menu

O programa exibirá um menu com as seguintes opções:

1. Adicionar carro: Digite a placa do carro para adicioná-lo ao estacionamento ou à fila de espera.
2. Remover carro: Digite a placa do carro que deseja remover do estacionamento.
3. Exibir estado do estacionamento: Mostra o estado atual dos becos e da fila de espera.
4. Sair: Encerra o programa.

Estrutura do Código
Beco: Estrutura que representa um beco do estacionamento.
FilaEspera: Estrutura que representa a fila de espera para os carros.
Carro: Estrutura que representa um carro, incluindo sua placa, número de manobras e se ficou na fila.
Funções principais:
criarBeco(): Cria um novo beco.
criarFilaEspera(): Cria uma nova fila de espera.
entrarCarroBeco(): Adiciona um carro a um beco.
sairCarroBeco(): Remove um carro de um beco.
adicionarCarroFila(): Adiciona um carro à fila de espera.
removerCarroFila(): Remove um carro da fila de espera e tenta alocá-lo a um beco.
alocarCarroNaFilaSeTiverVaga(): Aloca carros da fila de espera se houver vagas disponíveis.
exibirEstadoEstacionamento(): Exibe o estado atual do estacionamento.

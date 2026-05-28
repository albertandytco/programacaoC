//==========================================================================
// PRÁTICA: SISTEMA DE BIBLIOTECA - PARTE 2
//
// OBJETIVO DESTA PARTE: 
// Adicionar a funcionalidade de empréstimo e intriduzir alocação dinâmica.
// - Os arrays de livros e empréstimos são alocados com malloc/calloc.
// - Nova strut para Empréstimo.
// - Liberação de memória com free. 
//==========================================================================

#include <stdio.h> 
#include <stdlib.h> //
#include <string.h> // Para strcspn ()

// --- Constantes Globais ---
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100 // Definimos uma capacidade para empréstimos. 
#define TAM_STRING 100

// --- Definição das Estruturas ---
// Struct Livro agora tem um campo 'disponível' para controlar o status. 
struct Livro{
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 1 para sim, 0 para não (bool)
};

// Nova struct para armazenar informações do empréstimo. 
struct Emprestimo {
    int indiceLivro; // Para saber qual livro do array 'biblioteca' foi empresata.
    char nomeUsuario[TAM_STRING];
};

// --- Função para limpar o buffer de entrada --- 
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal (main) ---
int main () {
    // 1. ALOCAÇÃO DINÂMICA DE MEMÓRIA
    // Agora, em vez de arrays estáticos, usamos ponteiros. 
    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;

    // Usamos calloc para o array de livros. calloc(num_elementos, tamanho_de_cada_elemento)
    // Vantagem: inicializa toda a memória com zeros. Isso significa que 'disponivel' já começa com todo o valor zerado.
    biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));

    // Usamos malloc para o array de empréstimos. malloc(tamanho_total_em_bytes)
    emprestimos = (struct Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    // VERIFICAÇÃO: É crucial verificar se a alocação de memória deu certo.
    if (biblioteca == NULL || emprestimos == NULL){
        printf("Erro: Falha ao alocar memoria. \n");
        return 1; // Retorna 1 para indicar um erro. 
    }

    int totalLivros = 0;
    int totalEmprestimos = 0; 
    int opcao;

    do {
        printf("=============================================\n");
        printf("       BIBLIOTECA - PARTE 2 \n");
        printf("=============================================\n");
        printf("1 - Cadastrar novo livro \n"); 
        printf("2 - Listar todos os livros \n");
        printf("3 - Realizar emprestimo\n");
        printf("4 - Listar emprestimos\n");
        printf("0 - Sair\n"); 
        printf("---------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1: // CADASTRO DE LIVRO
                printf("--- Cadastro de Novo Livro --- \n\n");
                if (totalLivros < MAX_LIVROS) {
                    // O acesso aos campos é igual ao do array estático.
                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                    // ... (demais leituras são iguais à parte 1) ...
                    printf("Digite o autor ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

                    printf("Digite a editora: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

                    printf("Digite a edicao: "); 
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparBufferEntrada();

                    // Ao cadastrar. o livro automaticamente se torna disponivel. 
                    biblioteca[totalLivros].disponivel = 1; 
                    totalLivros++;
                    printf("\nLivro cadastrado com sucesso!\n");
                } else {
                    printf("Biblioteca cheia!\n");
                }
                printf("\nPresisone Enter para continuar...");
                getchar();
                break;

                case 2: // LISTAGEM DE LIVROS
                    printf("--- Lista de Livros Cadastrados ---\n\n");
                    if (totalLivros == 0) {
                        printf("Nenhum livro cadastrado ainda. \n");
                    } else {
                        for (int i = 0; i < totalLivros; i++) {
                            printf("-----------------------------------\n");
                            printf("LIVRO %d \n\n", i + 1);
                            printf("Nome: %s \n", biblioteca[i].nome);
                            printf("Autor: %s \n", biblioteca[i].autor);
                            // Mostra o status de disponibilidade.
                            printf("Status: %s\n", biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
                        }
                        printf("-----------------------------------\n");
                    }
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    break;

                case 3: // REALIZAR EMPRÉSTIMO
                    printf("--- Realizar Emprestimo ---\n\n");

                    if (totalEmprestimos >= MAX_EMPRESTIMOS) {
                        printf("Limite de emprestimos atingido!\n");
                    } else {
                        printf("Livros disponiveis:\n");
                        int disponiveis = 0;
                        for (int i =0; i < totalLivros; i++) {
                            if (biblioteca[i].disponivel) {
                                printf("%d - %s\n", i + 1, biblioteca[i].nome);
                                disponiveis++;
                            }
                        }

                        if (disponiveis == 0) {
                            printf("Nenhum livro disponivel para emprestimo. \n");
                        } else {
                            printf("\nDigite o numero do livro que deseja emprestar: ");
                            int numLivro;
                            scanf("%d", &numLivro);
                            limparBufferEntrada();

                            int indice = numLivro - 1; // Converte para o indice do array (0 a N-1).

                            // Validação da escolha do usuário. 
                            if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                                printf("Digite o nome do usuario que esta pegando o livro: ");
                                fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                                emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = '\0';
                                
                                // Registra o empréstimo.
                                emprestimos[totalEmprestimos].indiceLivro = indice;

                                // Atualiza o status do livro para indisponível.
                                biblioteca[indice].disponivel = 0;

                                totalEmprestimos++;
                                printf("\nEmprestimo realizado com sucesso!\n");
                            } else {
                                printf("Escolha invalida ou livro indisponivel.\n");
                            }
                        }
                    }
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    break;

                case 4: // LISTAR EMPRÉSTIMOS
                    printf("--- Lista de Emprestimos ---\n\n");
                    if (totalEmprestimos == 0) {
                        printf("Nenhum emprestimo registrado ainda.\n");
                    } else {
                        for (int i = 0; i < totalEmprestimos; i++) {
                            // Usa o indice do livro armazenado no empréstimo para acessar os detalhes do livro emprestado.
                            int indiceLivro = emprestimos[i].indiceLivro;
                            printf("-----------------------------------\n");
                            printf("EMPRESTIMO %d \n\n", i + 1);
                            printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                            printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
                        }
                        printf("-----------------------------------\n");
                    }
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    break;

                case 0:
                    printf("Saindo do sistema...\n");
                    break;
                default:
                    printf("Opcao invalida! Tente novamente.\n");
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    break;
        }
    } while (opcao != 0);

    // 2. LIBERAÇÃO DE MEMÓRIA
    // Antes de terminar, é ESSENCIAL liberar a memória que foi alocada dinamicamente. 
    // Isso evita "memory leaks" (vazamentos de memória) e é uma boa prática de programação.
    free(biblioteca); // Libera o array de livros.
    free(emprestimos); // Libera o array de empréstimos.

    printf("Memoria liberada. Programa encerrado.\n");

    return 0; // Fim do programa.

}

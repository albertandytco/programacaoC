#include <stdio.h>
#include <stdlib.h>

// o código abaixo se refere a um problema onde a saída deve apontar o vencedor numa disputa de impar ou par, 

int main() {

	int bino_mao, cino_mao;

    // Entrada dos dedos de Bino
    
    printf("Digite a quantidade de dedos que Bino mostrou (0 a 10): ");
    scanf("%d", &bino_mao);

     // Validação da entrada de Bino

    if (bino_mao < 0 || bino_mao > 10) {
        printf("Entrada inválida para Bino. Envie um número entre 0 e 10.\n");
        return 1;  // Encerra o programa com erro
    }

    // Entrada dos dedos de Cino
    printf("Digite a quantidade de dedos que Cino mostrou (0 a 10): ");
    scanf("%d", &cino_mao); 

    // Validação da entrada de cino 
    if (cino_mao < 0 || cino_mao > 10) {
        printf("Entrada inválida para Cino. Envie um número entre 0 e 10.\n"); 
        return 1; //Encerra o programa com erro 
    }

    // Verificando o vencedor
    if ((bino_mao+cino_mao) % 2 == 0) {
        printf("Bino\n");
    }
    else {printf("Cino\n"); 
         }
    return 0;
}



// o código abaixo é especificamente para definir se um número é par ou não.  

#include <stdio.h>

int main() {
    int A, B;

    // Entrada dos dois números
    scanf("%d", &A);
    scanf("%d", &B);

    // Verifica se a soma é par ou ímpar
    if ((A + B) % 2 == 0) {
        printf("Par\n");
    } else {
        printf("Impar\n");
    }

    return 0;

}


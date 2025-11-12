#include <stdio.h>
#include <string.h>

// 1. Definição da struct Territorio
struct Territorio
{
    char nome[30];
    char cor[10];
    int tropas;

};

// funçao para limpara o buffer de entrada ==
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

};

int main(){
    // 2. Criação do vetor estático de 5 elementos
    struct Territorio territorios[5];
    int i;

    printf(" === Cadastro de territorios(war) === \n");
    printf("Cadastre  apenas 5 territorios. \n");

    // --- 3. CADASTRO DOS TERRITÓRIOS ---
    for (i = 0; i < 5; i++) {
        printf("\n----Territorios %d -------\n", i + 1);

        printf("Digite o nome: \n");
        scanf("%s",territorios[i].nome);
        // Leitura da COR
        printf("Digite a cor do exército: \n");
        scanf("%s", territorios[i].cor);
        
        printf("Digite a quantidade de tropas: \n");
        scanf("%d", &territorios[i].tropas);


    }
    // --- 3. EXIBIÇÃO DOS DADOS ---
    printf("\n\n=== Territórios Cadastrados ===\n");

    // Loop 'for' que executa 5 vezes para mostrar os dados
    for (i = 0; i < 5; i++) {
        printf("\n--- Dados do Território %d ---\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
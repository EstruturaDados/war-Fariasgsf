#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos
void cadastrarTerritorios(Territorio* mapa, int qtd);
void exibirTerritorios(Territorio* mapa, int qtd);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
void limparBuffer();

int main() {
    srand(time(NULL));

    int qtd;
    Territorio* mapa = NULL;

    printf("=== SIMULADOR DE BATALHA TERRITORIAL ===\n");
    
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);
    limparBuffer();

    mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    
    if (mapa == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    int op = 1;
    while (op != 0) {
        exibirTerritorios(mapa, qtd);

        int idAtk, idDef;
        
        printf("\n--- Fase de Ataque ---\n");
        // MUDANÇA AQUI: Orientamos o usuário de 1 até qtd
        printf("Digite o ID do territorio ATACANTE (1 a %d): ", qtd);
        scanf("%d", &idAtk);
        
        printf("Digite o ID do territorio DEFENSOR (1 a %d): ", qtd);
        scanf("%d", &idDef);

        // MUDANÇA AQUI: Validamos se está entre 1 e qtd
        if (idAtk >= 1 && idAtk <= qtd && idDef >= 1 && idDef <= qtd) {
            
            // MUDANÇA CRUCIAL: Subtraímos 1 para acessar o vetor corretamente (índice 0)
            int indiceAtk = idAtk - 1;
            int indiceDef = idDef - 1;

            if (strcmp(mapa[indiceAtk].cor, mapa[indiceDef].cor) == 0) {
                printf("\n[!] Erro: Voce nao pode atacar um territorio aliado (mesma cor)!\n");
            } else {
                atacar(&mapa[indiceAtk], &mapa[indiceDef]);
            }
        } else {
            printf("\n[!] Erro: ID de territorio invalido (Use numeros de 1 a %d).\n", qtd);
        }

        printf("\nDeseja realizar outro ataque? (1-Sim, 0-Nao): ");
        scanf("%d", &op);
    }

    liberarMemoria(mapa);
    printf("Simulacao encerrada.\n");

    return 0;
}

// --- FUNÇÕES ---

void cadastrarTerritorios(Territorio* mapa, int qtd) {
    printf("\n--- Cadastro de Territorios ---\n");
    for (int i = 0; i < qtd; i++) {
        // MUDANÇA AQUI: Exibe (i + 1) para o usuário ver "Territorio #1"
        printf("Territorio #%d:\n", i + 1);
        
        printf(" Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0; 
        
        printf(" Cor do Exercito: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf(" Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();
    }
}

void exibirTerritorios(Territorio* mapa, int qtd) {
    printf("\nEstado Atual do Mapa:\n");
    printf("ID | %-20s | %-10s | Tropas\n", "Nome", "Cor");
    printf("------------------------------------------------\n");
    for (int i = 0; i < qtd; i++) {
        // MUDANÇA AQUI: Exibe (i + 1) na tabela
        printf("%02d | %-20s | %-10s | %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n>>> BATALHA INICIADA: %s (Atq) vs %s (Def) <<<\n", atacante->nome, defensor->nome);

    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("Rolagem de dados -> Atacante: %d | Defensor: %d\n", dadoAtk, dadoDef);

    if (dadoAtk > dadoDef) {
        printf("Resultado: VITORIA DO ATACANTE!\n");
        printf("O territorio %s foi conquistado pelo exercito %s.\n", defensor->nome, atacante->cor);

        strcpy(defensor->cor, atacante->cor);

        int tropasMovidas = atacante->tropas / 2;
        if (tropasMovidas < 1 && atacante->tropas > 1) tropasMovidas = 1;

        defensor->tropas = tropasMovidas;
        atacante->tropas -= tropasMovidas;

    } else {
        printf("Resultado: DEFESA BEM SUCEDIDA!\n");
        printf("O atacante perdeu 1 tropa.\n");

        if (atacante->tropas > 0) {
            atacante->tropas -= 1;
        }
    }
}

void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
    }
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
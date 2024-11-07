#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura da pilha
struct Pilha {
    char dado;
    struct Pilha* prox;
};

// Fun��o para inicializar a pilha
struct Pilha* inicializa() {
    return NULL;
}

// Fun��o para empilhar um valor
void push(struct Pilha** topo, char valor) {
    struct Pilha* novo = (struct Pilha*) malloc(sizeof(struct Pilha));
    if (!novo) { 
        printf("Erro de alocacao\n");
        exit(1); // C�digo de erro de aloca��o, pode ser tratado de forma mais flex�vel
    }
    novo->dado = valor;
    novo->prox = *topo;
    *topo = novo;
}

// Fun��o para desempilhar um valor
void pop(struct Pilha** topo) {
    if (*topo != NULL) {
        struct Pilha* temp = *topo;
        *topo = (*topo)->prox;
        free(temp);
    }
}

// Fun��o para comparar os caracteres de abertura e fechamento
int comparar(struct Pilha* topo, char fechamento) {
    if (topo == NULL) return 0; // Garantir que a pilha n�o esteja vazia
    char abertura = topo->dado;
    return (abertura == '(' && fechamento == ')') ||
           (abertura == '[' && fechamento == ']') ||
           (abertura == '{' && fechamento == '}');
}

// Fun��o para verificar se o caractere � de abertura ou fechamento
int avaliar(char c) {
    if (c == '(' || c == '[' || c == '{') return 1; // Abertura
    if (c == ')' || c == ']' || c == '}') return 2; // Fechamento
    return 0; // N�o � um caractere de par�nteses
}

// Fun��o para validar a express�o balanceada
int validar(char* exp) {
    struct Pilha* pilha = inicializa();
    
    for (int i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];
        
        if (avaliar(c) == 1) { // Se for um caractere de abertura
            push(&pilha, c); // Empilha
        } else if (avaliar(c) == 2) { // Se for um caractere de fechamento
            if (!comparar(pilha, c)) { // Verifica se corresponde ao topo da pilha
                return 0; // Express�o inv�lida
            }
            pop(&pilha); // Desempilha
        }
    }
    
    // A express�o � v�lida se a pilha estiver vazia no final
    int resultado = (pilha == NULL);

    // Liberando a mem�ria restante
    while (pilha != NULL) {
        pop(&pilha);
    }
    
    return resultado;
}

int main() {
    char expressao[100];
    
    // Solicita ao usu�rio a express�o
    printf("Digite a expressao desejada: ");
    if (scanf("%99s", expressao) != 1) { // Verifica se a entrada foi bem-sucedida
        printf("Erro ao ler a entrada\n");
        return 1;
    }
    
    // Valida a express�o
    if (validar(expressao)) {
        printf("Expressao valida\n");
    } else {
        printf("Expressao incorreta\n");
    }
    
    return 0;
}


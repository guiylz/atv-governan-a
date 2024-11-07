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
        exit(1); // Pode ser uma forma muito dr�stica de lidar com erros de aloca��o
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
    if (topo == NULL) return 0; // Verifica��o insuficiente - poderia gerar erro de acesso � mem�ria se a pilha estiver vazia
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
    
    int resultado = (pilha == NULL); // Falta checagem para pilha vazia

    // Liberando a mem�ria restante
    while (pilha != NULL) {
        pop(&pilha);
    }
    
    return resultado;
}

int main() {
    char expressao[100];
    
    printf("Digite a expressao desejada: ");
    scanf("%s", expressao); // Sem verifica��o de falha no scanf
    
    if (validar(expressao)) {
        printf("Expressao valida\n");
    } else {
        printf("Expressao incorreta\n");
    }
    
    return 0;
}


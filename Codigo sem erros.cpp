#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura da pilha
struct Pilha {
    char dado;
    struct Pilha* prox;
};

// Função para inicializar a pilha
struct Pilha* inicializa() {
    return NULL;
}

// Função para empilhar um valor
void push(struct Pilha** topo, char valor) {
    struct Pilha* novo = (struct Pilha*) malloc(sizeof(struct Pilha));
    if (!novo) { 
        printf("Erro de alocacao\n");
        exit(1); // Código de erro de alocação, pode ser tratado de forma mais flexível
    }
    novo->dado = valor;
    novo->prox = *topo;
    *topo = novo;
}

// Função para desempilhar um valor
void pop(struct Pilha** topo) {
    if (*topo != NULL) {
        struct Pilha* temp = *topo;
        *topo = (*topo)->prox;
        free(temp);
    }
}

// Função para comparar os caracteres de abertura e fechamento
int comparar(struct Pilha* topo, char fechamento) {
    if (topo == NULL) return 0; // Garantir que a pilha não esteja vazia
    char abertura = topo->dado;
    return (abertura == '(' && fechamento == ')') ||
           (abertura == '[' && fechamento == ']') ||
           (abertura == '{' && fechamento == '}');
}

// Função para verificar se o caractere é de abertura ou fechamento
int avaliar(char c) {
    if (c == '(' || c == '[' || c == '{') return 1; // Abertura
    if (c == ')' || c == ']' || c == '}') return 2; // Fechamento
    return 0; // Não é um caractere de parênteses
}

// Função para validar a expressão balanceada
int validar(char* exp) {
    struct Pilha* pilha = inicializa();
    
    for (int i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];
        
        if (avaliar(c) == 1) { // Se for um caractere de abertura
            push(&pilha, c); // Empilha
        } else if (avaliar(c) == 2) { // Se for um caractere de fechamento
            if (!comparar(pilha, c)) { // Verifica se corresponde ao topo da pilha
                return 0; // Expressão inválida
            }
            pop(&pilha); // Desempilha
        }
    }
    
    // A expressão é válida se a pilha estiver vazia no final
    int resultado = (pilha == NULL);

    // Liberando a memória restante
    while (pilha != NULL) {
        pop(&pilha);
    }
    
    return resultado;
}

int main() {
    char expressao[100];
    
    // Solicita ao usuário a expressão
    printf("Digite a expressao desejada: ");
    if (scanf("%99s", expressao) != 1) { // Verifica se a entrada foi bem-sucedida
        printf("Erro ao ler a entrada\n");
        return 1;
    }
    
    // Valida a expressão
    if (validar(expressao)) {
        printf("Expressao valida\n");
    } else {
        printf("Expressao incorreta\n");
    }
    
    return 0;
}


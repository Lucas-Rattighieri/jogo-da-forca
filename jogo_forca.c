# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>


# define TOTAL_ERROS 5 // Tente escolher multiplos de 5

// Variáveis globais
char palavra[10], espacos[10];
char chute;
int len_palavra;
int acertos = 0, erros = 0;



void linha(char caractere, int n) {
    for (int i = 0; i < n; i++) {
        printf("%c", caractere);
    } 
    printf("\n");
}

void cabecalho(char * titulo) {
    int n = strlen(titulo);

    printf("\n\n");

    linha('*', n+6);

    printf("*  %s  *\n", titulo);

    linha('*', n+6);

}


void escolher_palavra_secreta() {

    int num_palavras_secretas;
    int num_randomico;

    FILE * lista_palavras;

    lista_palavras = fopen("palavras.txt", "r");

    if (lista_palavras == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fscanf(lista_palavras, "%d", &num_palavras_secretas);

    srand(time(0));
    num_randomico = rand() % num_palavras_secretas;

    for (int i = 0; i <= num_randomico; i++) {
        fscanf(lista_palavras, "%s", palavra);
    }

    len_palavra = strlen(palavra);



    for (int i = 0; i < len_palavra; i++) {
        espacos[i] = '_';
    }

    fclose(lista_palavras);

}

void mostrar_espacos() {
    printf("\n");
    for (int i = 0; i < len_palavra; i++) {

        printf("%c ", espacos[i]);
    }
    printf("\n\n");
}

void chutar() {
        printf("Faca um chute: ");
        scanf(" %c", &chute);

}

void verificar_chute() {
    int chute_errado = 1;

    for (int i = 0; i < len_palavra; i++) {
        if (('A' - palavra[i]) == ('A' - chute) || ('A' - palavra[i]) == ('a' - chute)) {
            espacos[i] = palavra[i];
            acertos ++;
            chute_errado = 0;
        }
    }
    if (chute_errado) {
        erros++;
    }
}


int ganhou() {
    return acertos == len_palavra;
}


int enforcou() {
    return erros == TOTAL_ERROS;
}

void mostrar_trofeu() {
    FILE * trofeu;
    char linha[100];
    int fim;

    trofeu = fopen("trofeu.txt", "r");

    if (trofeu == NULL) 
        return;

    fim = 0;
    while (!fim) {
        fgets(linha, 99, trofeu);
        printf("%s", linha);
        fim = feof(trofeu);
    }

    printf("\n\n");

    fclose(trofeu);
}


void mostrar_caveira() {
    FILE * caveira;
    char linha[100];
    int fim;

    caveira = fopen("caveira.txt", "r");

    if (caveira == NULL) 
        return;

    fim = 0;
    while (!fim) {
        fgets(linha, 99, caveira);
        printf("%s", linha);
        fim = feof(caveira);
    }

    printf("\n\n");

    fclose(caveira);
}

void mostrar_forca() {

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >= (TOTAL_ERROS / 5) ? '(':' '), (erros >= (TOTAL_ERROS / 5)?'_':' '), (erros >= (TOTAL_ERROS / 5)?')':' '));
    printf(" |      %c%c%c  \n", (erros >= 3 * (TOTAL_ERROS / 5) ? '\\':' '), (erros >= 2 * (TOTAL_ERROS / 5)?'|':' '), (erros >= 3 * (TOTAL_ERROS / 5)?'/': ' '));
    printf(" |       %c     \n", (erros >= 2 * (TOTAL_ERROS / 5) ? '|':' '));
    printf(" |      %c %c   \n", (erros >= 4 * (TOTAL_ERROS / 5) ? '/':' '), (erros >= TOTAL_ERROS?'\\':' '));
    printf(" |              \n");
    printf("_|__ ");
    printf("\n");

}


int main() {

    
    escolher_palavra_secreta();

    cabecalho("Jogo da Forca");

    mostrar_forca();
    mostrar_espacos();


    do {

        chutar();

        verificar_chute();

        mostrar_forca();
        mostrar_espacos();
         
    } while (!ganhou() && !enforcou());

    if (ganhou()) {
        mostrar_trofeu();
    }
    else {
        mostrar_caveira();
    }


    return 0;
}
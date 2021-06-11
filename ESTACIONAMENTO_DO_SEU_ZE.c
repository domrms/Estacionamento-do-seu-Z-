#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "textos.h"

typedef struct CAD_ENTRADA{
    char placa[7], tipo[10], modelo[10], cor[10];
    int  hora, min;
}CAD_ENTRADA;

void cadastrar_entrada_veiculo(void);
void cadastrar_saida_veiculo(void);
void log_de_entrada(void);
void log_de_saida(void);
void delete_registros_de_entrada(void);

int main(){
    int opcao_escolhida;

    inicio:
    system("cls");
    mensagem_de_inicio();
    scanf("%d", &opcao_escolhida);

    switch (opcao_escolhida){
    case 1:
        system("cls");
        cadastrar_entrada_veiculo();
        goto inicio;

    case 2: 
        system("cls");
        cadastrar_saida_veiculo();
        goto inicio;

    case 3:
        system("cls");
        log_de_entrada();
        goto inicio;

    case 4:
        system("cls");
        log_de_saida();
        goto inicio;

    case 5:
        system("cls");
        delete_registros_de_entrada();
        goto inicio;
    
    case 6:
        system("cls");
        mensagem_de_encarramento();
        sleep(2);
        return 0;
            
    default:
        printf("OPCAO INVALIDA! TENTE NOVAMENTE...\n");
        sleep(2);
        goto inicio;

    }
    return 0;
}

void cadastrar_entrada_veiculo(void){

    time_t seconds;
    time(&seconds);
    struct tm * P; 

    FILE *cadastro;
    CAD_ENTRADA * C;
    P = localtime(&seconds);
    C = malloc(sizeof(struct CAD_ENTRADA));
    cadastro = fopen("LOG_DE_ENTRADA.txt", "ab");

    int tamanho_placa;

    mensagem_cadastro_de_entrada();

    //RECEBE INFORMAÇÃO DA PLACA
    printf("DIGITE A PLACA (SOMENTE NUMEROS E LETRAS!): ");
    scanf("%s", C->placa);
    tamanho_placa=strlen(C->placa);
    if (tamanho_placa != 7){
        printf("PLACA INVALIDA! TENTE NOVAMENTE...\n");
        sleep(1);
        return 1;
    } else
    strupr(C->placa); //DEIXA TUDO EM CAIXA ALTA
    fprintf(cadastro, "%s\n", C->placa);
    fflush(stdin);

    printf("DIGITE O TIPO: ");
    scanf("%s", C->tipo);
    strupr(C->tipo);
    fprintf(cadastro, "%s\n", C->tipo);
    fflush(stdin);

    printf("DIGITE O MODELO: ");
    scanf("%s", C->modelo);
    strupr(C->modelo);
    fprintf(cadastro, "%s\n", C->modelo);
    fflush(stdin);

    printf("DIGITE A COR: ");
    scanf("%s", C->cor);
    strupr(C->cor);
    fprintf(cadastro, "%s\n", C->cor);
    fflush(stdin);

    //AJUSTA O VALOR DA HORA PARA ACRESCENTAR O ZERO EM CASO DE HORA OU MIN < 10. (INT)
    if (P->tm_hour < 10 && P->tm_min > 9){
        fprintf(cadastro, "0%d:%d\n\n", P->tm_hour, P->tm_min);
        fflush(stdin);
    } else if (P->tm_hour > 9 && P->tm_min < 10){
        fprintf(cadastro, "%d:0%d\n\n", P->tm_hour, P->tm_min);
        fflush(stdin);
    } else if (P->tm_hour < 10 && P->tm_min < 10){
        fprintf(cadastro, "0%d:0%d\n\n", P->tm_hour, P->tm_min);
        fflush(stdin);
    } else
    fprintf(cadastro, "%d:%d\n\n", P->tm_hour, P->tm_min);
    fflush(stdin);

    fclose(cadastro);
    free(C);

    printf("\nCADASTRO REALIZADO COM SUCESSO!\n");
    sleep(2);
}

void cadastrar_saida_veiculo(void){
    mensagem_cadastro_de_saida();
    
    time_t seconds;
    time(&seconds);
    struct tm * P;
    P = localtime(&seconds);

    FILE *cadastro;
    FILE *log;
    cadastro = fopen("LOG_DE_ENTRADA.txt", "rw");
    log = fopen("LOG_DE_SAIDA", "ab");

    CAD_ENTRADA * C;
    C = malloc(sizeof(struct CAD_ENTRADA));

    char placa[7];
    int tempo_entrada, tempo_saida;
    double total, min_perrmanencia;
    int pagamento, digito;

    placa:
    printf("DIGITE A PLACA DO VEICULO (SOMENTE LETRAS E NUMEROS): ");
    scanf("%s", placa);
    strupr(placa);

    while(!feof(cadastro)){
        fscanf(cadastro, "%s\n", C->placa);
        if(strcmp(placa, C->placa)==0){
            printf("PLACA: %s\n", C->placa);
            fscanf(cadastro, "%s\n", C->tipo);
            printf("TIPO: %s\n", C->tipo);
            fscanf(cadastro, "%s\n", C->modelo);
            printf("MODELO: %s\n", C->modelo);
            fscanf(cadastro, "%s\n", C->cor);
            printf("COR: %s\n", C->cor);
            fscanf(cadastro, "%d:%d\n", &C->hora, &C->min);
            printf("HORA DE ENTRADA: %d:%d\n", C->hora, C->min);
            break;
        } 
    
    }

    printf("HORA DE SAIDA: %d:%d\n", P->tm_hour, P->tm_min);

    //CONVERTE A HORA PARA MINUTOS E SOMA COM OS MINUTOS
    tempo_entrada=(P->tm_hour*60)+P->tm_min;
    tempo_saida=(C->hora*60)+C->min;
    min_perrmanencia=(double)tempo_entrada-(double)tempo_saida;

    //TAXAMENTO DE ACORDO COM OS MINUTOS DE PERMANENCIA DO ESTACIONAMENTO
    if (min_perrmanencia<=15){
        total=0;
        printf("TOTAL A PAGAR: GRATUITO. PERMANENCIA DE ATE 15 MINUTOS!\n\n");
        system("pause");
        goto registro;
    } else if (min_perrmanencia<=60){
        total=5;
        printf("TOTAL A PAGAR: R$ 5.00\n");
    } else if (min_perrmanencia<=120){
        total=10;
        printf("TOTAL A PAGAR: R$ 10.00\n");
    } else if (min_perrmanencia<=180){
        total=15;
        printf("TOTAL A PAGAR: R$ 15.00\n");
    } else if (min_perrmanencia>180 && min_perrmanencia<=300){
        total=28;
        printf("TOTAL A PAGAR: R$ 28.00\n");
    } else if (min_perrmanencia>300){
        total=50;
        printf("TOTAL A PAGAR: R$ 50.00\n");
    }

    //RECEBE FORMA DE PAGAMENTO
    printf("\nFORMA DE PAGAMENTOS:\n1 - DINHEIRO\n2 CARTAO DE CREDITO / DEBITO\n3 - VOUCHER\n");
    printf("\nDIGITE O METODO DE PAGAMENTO: ");
    scanf("%d", &pagamento);
    
    //OPÇÕES DE PAGAMENTO
    digito:
    switch (pagamento){
    case 1:
        printf("DIGITE 1 PARA CONFIRMAR O PAGAMENTO: ");
        scanf("%d", &digito);
        if (digito!=1){
            printf("OPCAO INVALIDA! TENTE NOVAMENTE...\n");
            sleep(1);
            goto digito;
        }
        break;

    case 2: 
        printf("DIGITE 1 PARA CONFIRMAR O PAGAMENTO: ");
        scanf("%d", &digito);
        if (digito!=1){
            printf("OPCAO INVALIDA! TENTE NOVAMENTE...\n");
            sleep(1);
            goto digito;
        }
        break;

    case 3: 
        printf("DIGITE 1 PARA CONFIRMAR O PAGAMENTO: ");
        scanf("%d", &digito);
        if (digito!=1){
            printf("OPCAO INVALIDA! TENTE NOVAMENTE...\n");
            sleep(1);
            goto digito;
        }
        break;
    
    default:
        printf("OPCAO INVALIDA. TENTE NOVAMENTE...\n");
        break;
    }

    printf("\nPAGAMENTO CONFIRMADO COM SUCESSO!\n");
    sleep(3);

    //REGISTRO DO VEICULO NO LOG DE SAIDA DO ESTACIONAMENTO
    registro:
    fprintf(log, "PLACA: %s\n", placa);
    fprintf(log, "TIPO: %s\n", C->tipo);
    fprintf(log, "MODELO: %s\n", C->modelo);
    fprintf(log, "COR: %s\n", C->cor);
    fprintf(log, "ENTRADA: %d:%d\n", C->hora, C->min);
    fprintf(log, "SAIDA: %d:%d\n", P->tm_hour, P->tm_min);
    fprintf(log, "TOTAL PAGO: R$%.2f\n", total);
    if (pagamento==1){
        fprintf(log, "METODO DE PAGAMENTO: DINHEIRO\n\n");
    }else if (pagamento==2){
        fprintf(log, "METODO DE PAGAMENTO: CARTAO DE CREDITO/DEBITO\n\n");
    } else if (pagamento==3){
        fprintf(log, "METODO DE PAGAMENTO: VOUCHER\n\n");
    } else if (total==0){
        fprintf(log, "METODO DE PAGAMENTO: GRATIS (ATE 15 MIN)\n\n");
    }

    free(C);
    fclose(log);
    fclose(cadastro);
}

//MOSTRA TODOS OS VEICULOS QUE ENTRARAM NO ESTACIONAMENTO
void log_de_entrada(void){
    mensagem_entrada();
    FILE *cadastro;
    cadastro = fopen("LOG_DE_ENTRADA.txt", "r");
    if (cadastro==NULL){
        printf("\nNAO EXISTEM REGISTROS DE ENTRADA!\n\n");
        system("pause");
        return 1;
    }

    int c;

    c = fgetc(cadastro);
    while(!feof(cadastro)){
        putchar(c);
        c = fgetc(cadastro);
    }

    fclose(cadastro);
    system("pause");

}

//MOSTRA TODOS OS VEICULOS QUE SAIRAM DO ESTACIONAMENTO
void log_de_saida(void){
    mensagem_saida();
    FILE *log;
    log = fopen("LOG_DE_SAIDA", "r");
    if (log==NULL){
        log = fopen("LOG_DE_SAIDA", "w");
    }

    int c;

    c = fgetc(log);
    while(!feof(log)){
        putchar(c);
        c = fgetc(log);
    }

    fclose(log);
    system("pause");
}

//APAGA O ARQUIVO LOG_DE_ENTRADA.txt
void delete_registros_de_entrada(void){
    mensagem_delete();
    FILE *cadastro;
    cadastro = fopen("LOG_DE_ENTRADA.txt", "r");
    fclose(cadastro);
    rename("LOG_DE_ENTRADA.txt", "trash.txt");
    printf("OPERACAO REALIZADA COM SUCESSO. VOCE APAGOU TODOS OS DADOS DE ENTRADA!\n");
    printf("TODOS OS DADOS ESTAO SALVOS NOS REGISTROS DE SAIDA!\n\n");
    system("pause");
}


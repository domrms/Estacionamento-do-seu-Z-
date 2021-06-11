#ifndef TEXTOSDETELA_H
#define TEXTOSDETELA_H

#include <stdio.h>

//TEXTO DAS INTERFACES: 

void mensagem_de_inicio(void){
    printf("\n====================================================================\n");
    printf("\n   BEM-VINDO(A) AO SISTEMA DE ESTACIONAMENTO DO SEU ZE\n");
    printf("\n====================================================================\n");
    printf("\nDIGITE UMA OPCAO PARA CONTINUAR:\n");
    printf("\n1 - CADASTRAR ENTRADA DE VEICULO\n2 - INFORMAR SAIDA DE VEICULO\n3 - EXIBIR REGISTROS DE ENTRADA\n4 - EXIBIR REGISTROS DE SAIDA\n5 - LIMPAR REGISTROS DE ENTRADA\n6 - FINALIZAR PROGRAMA\n");
    printf("\nOPCAO ESCOLHIDA: ");

}

void mensagem_de_encarramento(void){
        printf("\n====================================================================\n");
        printf("\n          SISTEMA DE ESTACIONAMENTO DO SEU ZE\n");
        printf("\n====================================================================\n");
        printf("\nDESENVOLVIDO POR: DOMINGOS ALVES.\n\n");
}

void mensagem_cadastro_de_entrada(void){
        printf("\n====================================================================\n");
        printf("\n                    REGISTRAR DE ENTRADA\n");
        printf("\n====================================================================\n\n");
}

void mensagem_saida(void){
        printf("\n====================================================================\n");
        printf("\n                    LOG DE SAIDA DE VEICULOS\n");
        printf("\n====================================================================\n\n");
}

void mensagem_cadastro_de_saida(void){
        printf("\n====================================================================\n");
        printf("\n                    REGISTRAR DE SAIDA\n");
        printf("\n====================================================================\n\n");
}

void mensagem_entrada(void){
         printf("\n====================================================================\n");
        printf("\n                 REGISTROS DE ENTRADA DE VEICULOS\n");
        printf("\n====================================================================\n\n");
}

void mensagem_delete(void){
         printf("\n====================================================================\n");
        printf("\n                    DELETAR REGISTROS DE ENTRADA\n");
        printf("\n====================================================================\n\n");
}


#endif TEXTOSDETELA_H
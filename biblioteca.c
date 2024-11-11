#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void Carregar_Memoria_Instrucoes_Dados(struct instrucao *inst_name) { //carrega mem�ria de instru��es

setlocale(LC_ALL, "Portuguese");

    char nomefile[100];
    printf("\tDigite o nome do arquivo .mem: ");
    printf("\n\t");
    scanf("%s", nomefile);
    printf("\n");

// Abre o arquivo para leitura
    FILE *file = fopen(nomefile, "r");
    if (file == NULL) {
        printf("\tErro ao abrir o arquivo.\n");
    }
    else{
        printf("\tMemoria de instrucoes carregada!\n");
    }

    // Inicializa todos os 256 opcodes como -1, serve para sinalizar que o espa�o est� vazio, sem instru��es
    for (int i = 0; i < 256; i++) {
        inst_name[i].opcode = -1;
    }

    int posicao = 0;

    // L� cada linha do arquivo
    while (fgets(inst_name[posicao].inst_char, sizeof(inst_name[posicao].inst_char), file)) {
        // Remove o caractere de nova linha, se presente
        inst_name[posicao].inst_char[strcspn(inst_name[posicao].inst_char, "\n")] = '\0';

        size_t tamanho_linha = strlen(inst_name[posicao].inst_char);

        if (tamanho_linha == 16) {
        // Separa o opcode (4 primeiros bits)
        char opcode[5] = {0}; // 4 bits + 1 para o caractere nulo
        strncpy(opcode, inst_name[posicao].inst_char, 4); // Copia os 4 primeiros bits para o opcode

        // Converte o opcode para n�mero inteiro
        unsigned int opcode_num = (unsigned int)strtol(opcode, NULL, 2);

        // Verifica o tipo de instru��o para armazenar os dados nas vari�veis corretas
        if (opcode_num == 4) {
            // Instru��o tipo I (ADDI)
            char opcode[5] = {0};// 4 bits + 1 para nulo
            char rs[4] = {0};   // 3 bits + 1 para nulo
            char rt[4] = {0};   // 3 bits + 1 para nulo
            char imm[7] = {0};  // 6 bits + 1 para nulo

            // Copia os bits correspondentes para os campos
            strncpy(opcode, inst_name[posicao].inst_char, 4);   // Bits 1 a 4 (opcode)
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);   // Bits 5 a 7 (rs)
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);   // Bits 8 a 10 (rt)
            strncpy(imm, inst_name[posicao].inst_char + 10, 6); // Bits 11 a 16 (imm)

        //Verificar se o valor do imm � positivo ou negativo, se for negativo, desfazer a opera��o de complemento de 2.
        if (imm[0] == '1'){ // Se for 1 � negativo, invertemos os bits.
            imm[0] = '0';
            for(int i=1; i<=5; i++){
                if(imm[i] == '1'){
                    imm[i] = '0';
                }else{
                    imm[i] = '1';
                }
            }
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2); //converte p/ inteiro
            inst_name[posicao].imm = inst_name[posicao].imm +1; //add +1 no valor convertido
            inst_name[posicao].imm = inst_name[posicao].imm*(-1); //inverte o sinal
        }

        else{
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2); //converte p/ inteiro
        }

            // Converte os campos para inteiros e armazena na estrutura
            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);


        } else if (opcode_num == 11) {
            // Instru��o tipo I (LW)
            char opcode[5] = {0};
            char rs[4] = {0};
            char rt[4] = {0};
            char imm[7] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);
            strncpy(imm, inst_name[posicao].inst_char + 10, 6);

            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2);

        } else if (opcode_num == 15) {
            // Instru��o tipo I (SW)
            char opcode[5] = {0};
            char rs[4] = {0};
            char rt[4] = {0};
            char imm[7] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);
            strncpy(imm, inst_name[posicao].inst_char + 10, 6);

            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2);

        } else if (opcode_num == 8) {
            // Instru��o tipo I (BEQ)
            char opcode[5] = {0};// 4 bits + 1 para nulo
            char rs[4] = {0};
            char rt[4] = {0};
            char imm[7] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);
            strncpy(imm, inst_name[posicao].inst_char + 10, 6);

        //Verificar se o valor do imm � positivo ou negativo, se for negativo, desfazer a opera��o de complemento de 2.
        if (imm[0] == '1'){ // Se for 1 � negativo, invertemos os bits.
            imm[0] = '0';
            for(int i=1; i<=5; i++){
                if(imm[i] == '1'){
                    imm[i] = '0';
                }else{
                    imm[i] = '1';
                }
            }
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2); //converte p/ inteiro
            inst_name[posicao].imm = inst_name[posicao].imm +1; //add +1 no valor convertido
            inst_name[posicao].imm = inst_name[posicao].imm*(-1); //inverte o sinal
        }

        else{
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2); //converte p/ inteiro
        }

            // Converte os campos para inteiros e armazena na estrutura
            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);

        } else if (opcode_num == 2) {
            // Instru��o tipo J
            char opcode[5] = {0};
            char addr[8] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(addr, inst_name[posicao].inst_char + 9, 7);

            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].addr = (int)strtol(addr, NULL, 2);

        } else if (opcode_num == 0) {
            // Instru��o tipo R
            char opcode[5] = {0};
            char rs[4] = {0};
            char rt[4] = {0};
            char rd[4] = {0};
            char funct[4] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);
            strncpy(rd, inst_name[posicao].inst_char + 10, 3);
            strncpy(funct, inst_name[posicao].inst_char + 13, 3);

            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);
            inst_name[posicao].rd = (int)strtol(rd, NULL, 2);
            inst_name[posicao].funct = (int)strtol(funct, NULL, 2);

        } else {
            printf("Tipo de instrucao nao identificada.\n");
        }

        posicao++;

        if (posicao >= 256) {
            printf("\tLimite maximo de instrucoes atingido.\n");
            break;
            }
        } else if (tamanho_linha == 8) {
        // Separa os bits do dado (8 primeiros bits)
        char dado[9] = {0}; // 8 bits + 1 para o caractere nulo
        strcpy(inst_name[posicao].dado_char, inst_name[posicao].inst_char);
        strcpy(dado, inst_name[posicao].inst_char); // Copia os 8 bits para o dado

        //Verificar se o valor � positivo ou negativo, se for negativo, desfazer a opera��o de complemento de 2.
        if (dado[0] == '1'){ // Se for 1 � negativo, invertemos os bits.
            dado[0] = '0';
            for(int i=1; i<=7; i++){
                if(dado[i] == '1'){
                    dado[i] = '0';
                }else{
                    dado[i] = '1';
                }
            }
            inst_name[posicao].dado = (int)strtol(dado, NULL, 2); //converte p/ inteiro
            inst_name[posicao].dado = inst_name[posicao].dado +1; //add +1 no valor convertido
            inst_name[posicao].dado = inst_name[posicao].dado*(-1); //inverte o sinal
        }
        else{
            inst_name[posicao].dado = (int)strtol(dado, NULL, 2); //converte p/ inteiro
        }
            posicao++;
        }
    }

    fclose(file);
}

void Imprimir_Memorias_Instrucoes(int tamanho, struct instrucao *inst_name) { //Imprime as mem�ria de instru��es

    for(int i=0; i<256; i++) {

        if (inst_name[i].opcode == -1) {
        }
        else if (inst_name[i].opcode == 0) {
            tamanho ++;
            printf("\tMem[%d]: Tipo R - opcode: %d, rs: %d, rt: %d, rd: %d, funct: %d\n",i ,  inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].rd, inst_name[i].funct);
        }
        else if(inst_name[i].opcode == 2) {
            tamanho ++;
            printf("\tMem[%d]: Tipo J - opcode: %d, addr: %d\n",i , inst_name[i].opcode, inst_name[i].addr);
        }
        else if(inst_name[i].opcode == 8) {
            tamanho ++;
            printf("\tMem[%d]: Tipo BEQ - opcode: %d, rs: %d, rt: %d, imm: %d\n",i , inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
        }
        else if(inst_name[i].opcode == 15) {
            tamanho ++;
            printf("\tMem[%d]: Tipo SW - opcode: %d, rs: %d, rt: %d, imm: %d\n",i , inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
        }
        else if(inst_name[i].opcode == 11) {
                tamanho ++;
                printf("\tMem[%d]: Tipo LW - opcode: %d, rs: %d, rt: %d, imm: %d\n",i , inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
        }
        else if(inst_name[i].opcode == 4) {
                tamanho ++;
                printf("\tMem[%d]: Tipo ADDI - opcode: %d, rs: %d, rt: %d, imm: %d\n",i , inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
        }
        else{
            printf("Tipo de instrucao invalida!\n");
        }
    }
    printf("\n");

    printf("\t********Memoria de Dados********\n\n");

    for (int x = 0; x < 16; x++) {
        for(int y = 0; y < 16; y++) {
            int mem = tamanho + x * 16 + y;
            if (mem < 256 + tamanho) {
                printf("Mem[%d] %d\t", mem, inst_name[mem].dado);
                }
            }
            printf("\n");
    }
}

//**Modelagem do banco de registradores**//

void Escrever_Registrador(int *banco_de_registradores, int indice, int valor) {     //salva valores nos registradores

    if(indice >= 0 && indice < 8) {
        banco_de_registradores[indice] = valor;
    }
    else {
        printf("\tindice de registrador nao encontrado!\n");
    }

}

int Ler_Registrador(int *banco_de_registradores, int indice) {          //l� valores armazenados nos registradores

    if(indice >= 0 && indice < 8) {
        return banco_de_registradores[indice];
    }
    else{
        printf("\tindice de registrador nao encontrado!\n");
    }
}

void Imprimir_BancoRG(int *banco_de_registradores) {                   //imprime os valores armazenados no banco de registradores
    printf("\t********Banco de Registradores********\n");
    printf("\n");
    for(int x=0; x<8; x++) {
        printf("\tRG[%d] = %d\n", x, banco_de_registradores[x]);
    }
    printf("\n");
}

int Ler_Memoria_Dados(int endereco, struct instrucao *inst_name){
    if (endereco < 0 || endereco >= 256) {
        printf("\tEndereco invalido.\n");
    }
    return inst_name[endereco].dado; // Retorna o dado no endere�o
}

void Escrever_Memoria_Dados(int endereco, int valor, struct instrucao *inst_name){
    if (endereco < 0 || endereco >= 256) {
        printf("\tEndereco invalido.\n");
    }
    inst_name[endereco].dado = valor; // Armazena o valor no endere�o
}

void Salva_Memoria(struct instrucao *inst_name, int *tamanho){
        printf("\n\n");

        char nomearq[100];
        *tamanho=256;
        printf("\tDigite o nome do arquivo .dat: ");
        scanf("%s", nomearq);
        printf("\n");

        FILE *file = fopen(nomearq, "w");
        if (file == NULL) {
        printf("\tErro ao abrir o arquivo");
        }
        for(int x = 0; x<*tamanho; x++){
            if(inst_name[x].opcode != -1){
                fprintf(file,"%s\n", inst_name[x].inst_char);
                }
        }

        int bin[8], num;
        for(int x = 0; x<*tamanho; x++){
            num=0;
            num = inst_name[x].dado;
            for(int i=0; i<8; i++){
                bin[i] = 0;}
                if(num<0){
                    num = num * -1;
                    num = num -1;
                    for(int i=0; i<8; i++){
                        if((num%2)==0){
                            bin[7-i] = 0;
                            num=num/2;
                        }else{
                            bin[7-i] = 1;
                            num=num/2;
                            }
                    }
                    for(int i=0; i<=8; i++){
                        if(bin[i] == 0){
                            bin[i] = 1;
                        }else{
                            bin[i] = 0;
                        }
                    }
                }else if(num>=0){
                    for(int i=0; i<8; i++){
                        if((num%2)==0){
                            bin[7-i] = 0;
                            num=num/2;
                        }else{
                            bin[7-i] = 1;
                            num=num/2;
                        }
                    }
                }
                for(int i=0; i<=6; i++){
                    fprintf(file,"%d", bin[i]);
                }
                    fprintf(file,"%d\n",bin[7]);
        }

        fclose(file);
}

 void Salva_Asm(struct instrucao *inst_name){
        char nomearq[100];

        printf("\tDigite o nome do arquivo .asm: ");
        scanf("%s", nomearq);
        printf("\n");

        FILE *arq2 = fopen(nomearq, "w");
        if (arq2 == NULL) {
        printf("\tErro ao abrir o arquivo");
        }

        for(int i=0; i < 256; i++){
            if(inst_name[i].opcode == 0){
                if(inst_name[i].funct == 0){
                    fprintf(arq2,"ADD $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 2){
                    fprintf(arq2,"SUB $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 4){
                    fprintf(arq2,"AND $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 5){
                    fprintf(arq2,"OR $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
            }
            else if(inst_name[i].opcode == 4){
                    fprintf(arq2,"ADDI $t%d, $t%d, %d\n", inst_name[i].rt, inst_name[i].rs, inst_name[i].imm);
            }else if(inst_name[i].opcode == 11){
                    fprintf(arq2,"LW $t%d, %d($t%d)\n", inst_name[i].rt,inst_name[i].imm, inst_name[i].rs);
            }else if(inst_name[i].opcode == 15){
                    fprintf(arq2,"SW $t%d, %d($t%d)\n", inst_name[i].rt, inst_name[i].imm, inst_name[i].rs);
            }else if(inst_name[i].opcode == 8){
                    fprintf(arq2,"BEQ $t%d, $t%d, %d\n", inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
            }else if(inst_name[i].opcode == 2){
                    fprintf(arq2,"J %d\n", inst_name[i].addr);
            }
            if(inst_name[i].opcode == 0){
                if(inst_name[i].funct == 0){
                    printf("ADD $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 2){
                    printf("SUB $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 4){
                    printf("AND $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 5){
                    printf("OR $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
            }
            else if(inst_name[i].opcode == 4){
                    printf("ADDI $t%d, $t%d, %d\n", inst_name[i].rt, inst_name[i].rs, inst_name[i].imm);
            }else if(inst_name[i].opcode == 11){
                    printf("LW $t%d, %d($t%d)\n", inst_name[i].rt,inst_name[i].imm, inst_name[i].rs);
            }else if(inst_name[i].opcode == 15){
                    printf("SW $t%d, %d($t%d)\n", inst_name[i].rt, inst_name[i].imm, inst_name[i].rs);
            }else if(inst_name[i].opcode == 8){
                    printf("BEQ $t%d, $t%d, %d\n", inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
            }else if(inst_name[i].opcode == 2){
                    printf("J %d\n", inst_name[i].addr);
            }
        }

        fclose(arq2);
 }

void imprime_simulador(int *reg_dado, struct ULA_saida *saida, int *reg_A, int *reg_B, int *estado_c, struct instrucao *RI){
            printf("\topcode: %d, rs: %d, rt: %d, rd: %d, funct: %d, imm: %d, addr: %d\n", RI->opcode, RI->rs, RI->rt, RI->rd, RI->funct, RI->imm, RI->addr);
            printf("\tRegistrador de dados [%d]\n", *reg_dado);
            printf("\tRegistrador A $t%d[%d]\n", RI->rs, *reg_A);
            printf("\tRegistrador B $t%d[%d]\n", RI->rt,*reg_B);
            printf("\tRegistrador da ULA [%d]\n", saida->reg_ULA);
            printf("\tRegistrador da ULA_Flag [%d]\n", saida->flag);
            printf("\tEstado atual [%d]\n\n", *estado_c);
}

void Executar_Instrucao_M(int *reg_A, int *reg_B, int *estado_c, int *PC, struct instrucao *RI, struct ULA_saida *saida) {   //Executa as instru��es
    if(RI->opcode == 2) {
         printf("\tInstrucao nao gerou valor de resultado.\n\n");
    }
    else if(RI->opcode == -1) {                                            // se o opcode estiver como -1, indica que n�o h� mais instru��es v�lidas
            printf("\tPC esta apontando para um campo vazio!\n\n");
    }
    else{
            Calculos_ULA_M(reg_A, reg_B, estado_c, PC, RI, saida);
        }
}

void Ciclo(int *reg_dado, struct ULA_saida *saida, int *reg_A, int *reg_B, int *estado_c, int *PC, struct instrucao *RI, struct instrucao *inst_name,  int *banco_de_registradores){

    if(*estado_c == 0){
        if(inst_name[*PC].opcode != -1){
        *RI = inst_name[*PC];
}
    }
    if(*estado_c == 1){
        *reg_A = Ler_Registrador(banco_de_registradores, RI->rs);
        *reg_B = Ler_Registrador(banco_de_registradores, RI->rt);
        saida->reg_ULA = Calculos_ULA_M(reg_A, reg_B, estado_c, PC, RI, saida);
    }if(*estado_c == 2){
        saida->reg_ULA = Calculos_ULA_M(reg_A, reg_B, estado_c, PC, RI, saida);
    }
    if(*estado_c == 3){
        *reg_dado = Ler_Memoria_Dados(saida->reg_ULA, inst_name);
    }
    if(*estado_c == 4){
       Escrever_Registrador(banco_de_registradores, RI->rt, *reg_dado);
    }
    if(*estado_c == 5){
        Escrever_Memoria_Dados(saida->reg_ULA, *reg_B, inst_name);
        *reg_dado = Ler_Memoria_Dados(saida->reg_ULA, inst_name);
    }
    if(*estado_c == 6){
		Escrever_Registrador(banco_de_registradores, RI->rt , saida->reg_ULA);
	}
    if(*estado_c == 7){
        saida->reg_ULA = Calculos_ULA_M(reg_A, reg_B, estado_c, PC, RI, saida);
    }
    if(*estado_c == 8){
        Escrever_Registrador(banco_de_registradores, RI->rd, saida->reg_ULA);
    }
    if(*estado_c == 9){
        Calculos_ULA_M(reg_A, reg_B, estado_c, PC, RI, saida);
        if(saida->flag == 1){
            *PC = saida->reg_ULA;
        }
    }
    if(*estado_c == 10){
        *PC = RI->addr;
    }
}

void estado_M(int *estado_c, struct instrucao *RI){
    switch(*estado_c) {
        case 0:
            *estado_c = 1;
            break;

        case 1:
            if(RI->opcode == 0) {
                *estado_c = 7;
            }
            else if(RI->opcode == 15 || RI->opcode == 11 || RI->opcode == 4) {
                *estado_c = 2;
            }
            if(RI->opcode == 8) {
                *estado_c = 9;
            }
            if(RI->opcode == 2) {
                *estado_c = 10;
            }

            break;

        case 2:
            if(RI->opcode == 15) {
                *estado_c = 5;
            }else if(RI->opcode == 11) {
                *estado_c = 3;
            }else if(RI->opcode == 4) {
                *estado_c = 6;
            }
            break;
        case 3:
            *estado_c = 4;

            break;
        case 4:
            *estado_c = 0;

            break;

        case 5:
            *estado_c = 0;

            break;
		case 6:
            *estado_c = 0;

            break;
        case 7:
            *estado_c = 8;
            break;

        case 8:
            *estado_c = 0;
            break;
        case 9:
            *estado_c = 0;
            break;
        case 10:
            *estado_c = 0;
            break;


        default:
            printf("Estado desconhecido!\n");
            break;
    }
}

void Visualizar_Instrucao_Atual(struct instrucao *RI){

            if(RI->opcode == 0){
                if(RI->funct == 0){
                    printf("\tADD $t%d, $t%d, $t%d\n", RI->rd, RI->rs, RI->rt);
                }
                else if(RI->funct == 2){
                    printf("\tSUB $t%d, $t%d, $t%d\n", RI->rd, RI->rs, RI->rt);
                }
                else if(RI->funct == 4){
                    printf("\tAND $t%d, $t%d, $t%d\n", RI->rd, RI->rs, RI->rt);
                }
                else if(RI->funct == 5){
                    printf("\tOR $t%d, $t%d, $t%d\n", RI->rd, RI->rs, RI->rt);
                }
            }
            else if(RI->opcode == 4){
                    printf("\tADDI $t%d, $t%d, %d\n", RI->rt, RI->rs, RI->imm);
            }else if(RI->opcode == 11){
                    printf("\tLW $t%d, %d($t%d)\n", RI->rt,RI->imm, RI->rs);
            }else if(RI->opcode == 15){
                    printf("\tSW $t%d, %d($t%d)\n", RI->rt, RI->imm, RI->rs);
            }else if(RI->opcode == 8){
                    printf("\tBEQ $t%d, $t%d, %d\n", RI->rs, RI->rt, RI->imm);
            }else if(RI->opcode == 2){
                    printf("\tJ %d\n", RI->addr);
            }
        printf("\n");
}
void imprime_estado(int *reg_dado, struct ULA_saida *saida, int *reg_A, int *reg_B, int *estado_c, struct instrucao *RI, int *banco_de_registradores){
        if(*estado_c == 0){
            printf("\t********ESTADO ATUAL [%d]********\n\n", *estado_c);
            if (RI->opcode == -1) {}
            else if (RI->opcode == 0) {
                printf("\tTipo R - opcode: %d, rs: %d, rt: %d, rd: %d, funct: %d\n", RI->opcode, RI->rs, RI->rt, RI->rd, RI->funct);
            }
            else if(RI->opcode == 2) {
                printf("\tTipo J - opcode: %d, addr: %d\n", RI->opcode, RI->addr);
            }
            else if(RI->opcode == 8) {
                printf("\tTipo BEQ - opcode: %d, rs: %d, rt: %d, imm: %d\n", RI->opcode, RI->rs, RI->rt, RI->imm);
            }
            else if(RI->opcode == 15) {
                printf("\tTipo SW - opcode: %d, rs: %d, rt: %d, imm: %d\n", RI->opcode, RI->rs, RI->rt, RI->imm);
            }
            else if(RI->opcode == 11) {
                    printf("\tTipo LW - opcode: %d, rs: %d, rt: %d, imm: %d\n", RI->opcode, RI->rs, RI->rt, RI->imm);
            }
            else if(RI->opcode == 4) {
                    printf("\tTipo ADDI - opcode: %d, rs: %d, rt: %d, imm: %d\n", RI->opcode, RI->rs, RI->rt, RI->imm);
            }
            else{
                printf("Tipo de instrucao invalida!\n");
            }

        }else if(*estado_c == 1){
            printf("\t********ESTADO ATUAL [%d]********\n\n", *estado_c);
            Visualizar_Instrucao_Atual(RI);
            printf("\tRegistrador A $t%d[%d]\n",RI->rs, *reg_A);
            printf("\tRegistrador B $t%d[%d]\n", RI->rt,*reg_B);
            printf("\tRegistrador da ULA [%d]\n", saida->reg_ULA);
        }else if(*estado_c == 2){
            printf("\t********ESTADO ATUAL [%d]********\n\n", *estado_c);
            Visualizar_Instrucao_Atual(RI);
            printf("\tRegistrador A $t%d[%d]\n",RI->rs, *reg_A);
            printf("\tRegistrador B $t%d[%d]\n", RI->rt,*reg_B);
            printf("\tRegistrador da ULA [%d]\n", saida->reg_ULA);
        }else if(*estado_c == 3){
            printf("\t********ESTADO ATUAL [%d]********\n\n", *estado_c);
            Visualizar_Instrucao_Atual(RI);
            printf("\tRegistrador de dados [%d]\n", *reg_dado);
        }else if(*estado_c == 4){
            printf("\t********ESTADO ATUAL [%d]********\n\n", *estado_c);
            Visualizar_Instrucao_Atual(RI);
            Imprimir_BancoRG(banco_de_registradores);
        }else if(*estado_c == 5){
            printf("\t********ESTADO ATUAL [%d]********\n\n", *estado_c);
            Visualizar_Instrucao_Atual(RI);
            Imprimir_BancoRG(banco_de_registradores);
            printf("\tDado escrito [%d]\n", *reg_dado);
            printf("\tRegistrador da ULA [%d]\n", saida->reg_ULA);
        }else if(*estado_c == 6){
            printf("\t********ESTADO ATUAL [%d]********\n\n", *estado_c);
            Visualizar_Instrucao_Atual(RI);
            Imprimir_BancoRG(banco_de_registradores);
            printf("\tDado escrito [%d]\n", saida->reg_ULA);
            printf("\tRegistrador da ULA [%d]\n", saida->reg_ULA);
        }else if(*estado_c == 7){
            printf("\t********ESTADO ATUAL [%d]********\n\n", *estado_c);
            Visualizar_Instrucao_Atual(RI);
            printf("\tRegistrador da ULA [%d]\n", saida->reg_ULA);
        }else if(*estado_c == 8){
            printf("\t********ESTADO ATUAL [%d]********\n\n", *estado_c);
            Visualizar_Instrucao_Atual(RI);
            Imprimir_BancoRG(banco_de_registradores);
        }else if(*estado_c == 9){
            printf("\t********ESTADO ATUAL [%d]********\n\n", *estado_c);
            Visualizar_Instrucao_Atual(RI);
            printf("\tsaida flag [%d]\n", saida->flag);
        }else if(*estado_c == 10){
            printf("\t********ESTADO ATUAL [%d]********\n\n", *estado_c);
            Visualizar_Instrucao_Atual(RI);
        }

}

int Calculos_ULA_M(int *reg_A, int *reg_B, int *estado_c, int *PC, struct instrucao *RI, struct ULA_saida *saida) { //Executa os c�lculos

    int resultado = 0;

    if(*estado_c == 0){
        (*PC)++;
        resultado = *PC;
    }
    if(*estado_c == 1){
		if(RI->opcode==0){
			RI->imm=0;
			}
        resultado = *PC + RI->imm;
    }

    if(*estado_c == 7){
        if(RI->opcode == 0) { //Tipo R
            switch(RI->funct) {                                                                                                        // faz a verifica��o do campo funct para informar qual opera��o realizar
        case 0:     //soma
            resultado = *reg_A + *reg_B; //faz a soma dos valores armazenados em rs e rt
                if(resultado >127 || resultado <-128){
                printf("\tOverflow. O resultado nao foi armazenado!\n");
            }
            break;

        case 2:     //sub
            resultado = *reg_A - *reg_B;
                if(resultado >127 || resultado <-128){
                printf("\tOverflow. O resultado nao foi armazenado!\n");
            }
            break;
        case 4:     //and
            resultado = *reg_A & *reg_B;
                if(resultado >127 || resultado <-128){
                printf("\tOverflow. O resultado nao foi armazenado!\n");
            }
            break;

        case 5:     //or
            resultado = *reg_A | *reg_B;
                if(resultado >127 || resultado <-128){
                printf("\tOverflow. O resultado nao foi armazenado!\n");
            }
            break;
                }
            }
     }
     else if(*estado_c == 2){  // estado para tipo SW, LW e ADDI
        resultado = *reg_A + RI->imm; // endere�o = rs + imm. L� da mem�ria e armazena no registrador
        if(resultado >127 || resultado <-128){
            printf("\tEndereco de memoria invalido!\n");
        }
    }else if(*estado_c == 9){
        if(*reg_A == *reg_B){
            saida->flag = 1;
        }else{
            saida->flag = 0;
        }
    }

    return resultado;
}

void Salva_Estado(int *PC, struct instrucao *inst_name, struct estado_salvo *estado,
                  int *banco_de_registradores, int *reg_dado, int *reg_A, int *reg_B, int *estado_c,
                  struct instrucao *RI,  struct instrucao *copia_RI, struct ULA_saida *saida, struct ULA_saida *copia_saida) {

    estado->copia_PC = *PC;
    estado->copia_RGdados = *reg_dado;
    estado->copia_RGa = *reg_A;
    estado->copia_RGb = *reg_B;
    estado->copia_estado_c = *estado_c;

    // Salvar o estado dos registradores
    for (int i = 0; i < 8; i++) {
        estado->copia_banco_de_registradores[i] = banco_de_registradores[i];
    }

    // Salvar o estado da memoria
    for (int i = 0; i < 256; i++) {
        estado->copia_memoria[i] = inst_name[i];
    }

    memcpy(copia_RI, RI, sizeof(struct instrucao)); // Copia todos os bytes da estrutura instrucao, os dados de RI são passados para copia_RI
    memcpy(copia_saida, saida, sizeof(struct ULA_saida));

}

void Restaurar_Estado(struct estado_salvo *estado, int *PC, int *reg_dado, int *reg_A, int *reg_B, int *estado_c,
                      int *banco_de_registradores, struct instrucao *inst_name,
                      struct instrucao *copia_RI, struct ULA_saida *copia_saida) {

    *PC = estado->copia_PC;
    *reg_dado = estado->copia_RGdados;
    *reg_A = estado->copia_RGa;
    *reg_B = estado->copia_RGb;
    *estado_c = estado->copia_estado_c;

    // Restaurar o estado dos registradores
    for (int i = 0; i < 8; i++) {
        banco_de_registradores[i] = estado->copia_banco_de_registradores[i];
    }

    // Restaurar a memória
    for (int i = 0; i < 256; i++) {
        inst_name[i] = estado->copia_memoria[i];
    }

    // Restaurar o registrador de instruções (RI)
    memcpy(copia_RI, &estado->copia_RI, sizeof(struct instrucao));

    // Restaurar o resultado da ULA
    memcpy(copia_saida, &estado->copia_saida, sizeof(struct ULA_saida));
}

void Inicializar_Pilha(struct Pilha *pilha) {
    pilha->topo = NULL;
}

void Inserir_No(struct Pilha *pilha, int *PC, struct instrucao *inst_name, int *banco_de_registradores,
          int *reg_dado, int *reg_A, int *reg_B, int *estado_c, struct instrucao *RI,
          struct instrucao *copia_RI, struct ULA_saida *saida, struct ULA_saida *copia_saida) {

    struct Nodo *novo_nodo = malloc(sizeof(struct Nodo));

    Salva_Estado(PC, inst_name, &novo_nodo->estado, banco_de_registradores, reg_dado, reg_A, reg_B, estado_c, RI, copia_RI, saida, copia_saida);

    novo_nodo->proximo = pilha->topo; //proximo armazena o ponteiro que referência o próximo nó na pilha
    pilha->topo = novo_nodo; //o topo da pilha passa a ser o novo_nodo
}

void Remover_No(struct Pilha *pilha, int *PC, int *reg_dado, int *reg_A, int *reg_B, int *estado_c,
         int *banco_de_registradores, struct instrucao *inst_name,
         struct instrucao *copia_RI, struct ULA_saida *copia_saida) {

    struct Nodo *nodo_a_remover = pilha->topo; // atribuindo o topo da pilha a nodo_a_remover
    Restaurar_Estado(&nodo_a_remover->estado, PC, reg_dado, reg_A, reg_B, estado_c, banco_de_registradores, inst_name, copia_RI, copia_saida);

    pilha->topo = nodo_a_remover->proximo;
    free(nodo_a_remover);
}

void Liberar_Pilha(struct Pilha *pilha) {
    while (pilha->topo != NULL) {
        struct Nodo *nodo_atual = pilha->topo;
        pilha->topo = pilha->topo->proximo; // Vai para o próximo nó
        free(nodo_atual);
    }
}

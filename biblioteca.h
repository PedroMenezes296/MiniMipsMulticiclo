#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

struct instrucao {
    char dado_char[9];
    char inst_char[17];
    int opcode;
    int rs;
    int rt;
    int rd;
    int funct;
    int imm;
    int addr;
    int dado;
};

struct ULA_saida {
    int reg_ULA;
    int flag;
};

struct estado_salvo {
    int copia_PC;
    int copia_RGdados;
    int copia_RGa;
    int copia_RGb;
    int copia_estado_c;
    int copia_banco_de_registradores[8];
    struct instrucao copia_memoria[256];
    struct ULA_saida copia_saida;
    struct instrucao copia_RI;
};

void Carregar_Memoria_Instrucoes_Dados(struct instrucao *inst_name);

void Imprimir_Memorias_Instrucoes(struct instrucao *inst_name);

void ImprimirMemorias_d(struct instrucao *inst_name);

void Escrever_Registrador(int *banco_de_registradores, int indice, int valor);

int Ler_Registrador(int *banco_de_registradores, int indice);

void Imprimir_BancoRG(int *banco_de_registradores);

int Ler_Memoria_Dados(int endereco, struct instrucao *inst_name);

void Escrever_Memoria_Dados(int endereco, int valor, struct instrucao *inst_name);

void Salva_Memoria(struct instrucao *inst_name, int *tamanho);

void Salva_Asm(struct instrucao *inst_name);

void imprime_simulador(int *reg_dado, struct ULA_saida *saida, int *reg_A, int *reg_B, int *estado_c, struct instrucao *RI);

void Visualizar_Instrucao_Atual(int *PC, struct instrucao *inst_name);

void Executar_Instrucao_M(int *reg_A, int *reg_B, int *estado_c, int *PC, struct instrucao *RI, struct ULA_saida *saida);

void Ciclo(int *reg_dado, struct ULA_saida *saida, int *reg_A, int *reg_B, int *estado_c, int *PC, struct instrucao *RI, struct instrucao *inst_name,  int *banco_de_registradores);

void estado_M(int *estado_c, struct instrucao *inst_M);

void imprime_estado(int *reg_dado, struct ULA_saida *saida, int *reg_A, int *reg_B, int *estado_c, struct instrucao *RI, int *banco_de_registradores, int *PC);

int Calculos_ULA_M(int *reg_A, int *reg_B, int *estado_c, int *PC, struct instrucao *RI, struct ULA_saida *saida);

void Restaurar_Estado(struct estado_salvo *estado, int *PC, int *reg_dado, int *reg_A, int *reg_B, int *estado_c,
                      int *banco_de_registradores, struct instrucao *inst_name,
                      struct instrucao *copia_RI, struct ULA_saida *copia_saida);

void Salva_Estado(int *PC, struct instrucao *inst_name, struct estado_salvo *estado,
                  int *banco_de_registradores, int *reg_dado, int *reg_A, int *reg_B, int *estado_c,
                  struct instrucao *RI,  struct instrucao *copia_RI, struct ULA_saida *saida, struct ULA_saida *copia_saida);

#endif // BIBLIOTECA_H_INCLUDED

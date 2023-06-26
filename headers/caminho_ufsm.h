typedef struct _caminho_ufsm{
    char* inicio;
    char* fim;
}caminho_ufsm;

caminho_ufsm *caminho_ufsm_cria(char* inicio, char* fim);
void caminho_ufsm_destroi(caminho_ufsm* c);


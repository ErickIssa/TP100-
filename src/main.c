#include "ListaSondas/ListaSondas.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {

    char operacao;
    srand(time(NULL));
    listaSonda sondasL;
    iniciaListaSonda(&sondasL);

    FILE *arq = NULL;
    arq = fopen("teste.txt", "r");
    if(arq == NULL){
        printf("falha leitura");
        exit(0);
    }
    int N_Sondas; 
    float lat_i,lon_i,c_i,v_i,nc_i;
    fscanf(arq, "%d", &N_Sondas);

    for(int i = 0; i<N_Sondas;i++){
        SondaMarte sonda1;
        fscanf(arq,"%f %f %f %f %f", &lat_i,&lon_i,&c_i,&v_i,&nc_i);
        insereSonda(&sondasL, inicializaSondaTexto(&sonda1,lat_i,lon_i,c_i,v_i,nc_i));
    }
    int qntdOperacoes;
    fscanf(arq,"%d", &qntdOperacoes);

    for (int i = 0; i < qntdOperacoes; i++) {
        printf("Selecione a operacao: (R, I, E)\n");
        scanf(" %c", &operacao);
        TRocha novarocha;

        switch (operacao) {
            case 'R': {
                printf("Digite a latitude, longitude, peso e minerais\n");
                float lat, long_i, peso;
                char minerais[100];
                scanf("%f %f %f", &lat, &long_i, &peso);
                getchar();

                fgets(minerais, sizeof(minerais), stdin);
                minerais[strcspn(minerais, "\n")] = '\0';

                const char delim[2] = " ";
                char *parte = strtok(minerais, delim);

                TMineral x;
                TListaMineral listaM;
                
                FLVaziaM(&listaM);
                while (parte != NULL) {
                    strcpy(x.nomeM, parte);
                    LInsereM(&listaM, x);
                    parte = strtok(NULL, delim);
                    // vai me da uma categoria, eu tenho que inserir em um mineral 
                    // e dps colocar na lista mineral da rocha 
                }
                novarocha = preenche_rocha(&novarocha, lat, long_i, peso, &listaM);
                
                // vamos colocar essa rocha em um compartimento
                operacaoR(&sondasL, &novarocha);
                
                break;
            }
            case 'E':{
                pontoComumSondas(&sondasL);
                operacao_E(&sondasL);
                break;
            }
            case 'I':{
                Imprime_I_Lista(&sondasL);
            }
            default: {
                break;
            }
        }
    }
    ImprimeListaSondas(&sondasL);

    return 0;
}
#include "invaders.h"
#include <stdio.h>

int pega_recorde(FILE **arq, int *recorde)
{

    *arq = fopen("record.txt", "r");

    if (*arq != NULL)
    {
        if (fscanf(*arq, "%d", recorde) != 1)
        {
            printf("Erro ao ler o número do arquivo.\n");
            fclose(*arq);
            return 0;
        }

        else
        {
            return 1;
            fclose(*arq);
        }
    }
    else
    {
        printf("\nerro ao abrir o arquivo");
        return 0;
    }
}

int adiciona_recorde(FILE **arq, int *recorde, int *pontuacao)
{
    if (*pontuacao > *recorde)
    {
        *arq = fopen("record.txt", "w");
        if (*arq != NULL)
        {
            int writen_chars = fprintf(*arq, "%d", *pontuacao);
            if (writen_chars < 0)
            {
                printf("Erro durante a escrita com fprintf.\n");
                fclose(*arq);
                return 0;
            }
            else
            {
                return 1;
                fclose(*arq);
            }
        }
    }
    else
    {
        return 0;
    }
}
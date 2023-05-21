// TODO: eliberare memorie

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

#define MAX_WORDS 5002
#define MAX_LENGTH 22

int main()
{
    int n = 0, corespunde, steluta;
    char cuvant[MAX_LENGTH], cuvbun[MAX_LENGTH], text[MAX_WORDS], *aux, line[MAX_LENGTH + 3];
    char *priority;
    struct dictionary_entry *intrare;
    FILE *fr, *fw;
    tQueue queue;

    fr = fopen("input.in", "r");
    fw = fopen("output.out", "w");

    queue = initQueue(queue);

    fgets(text, MAX_WORDS, fr);
    text[strlen(text) - 1] = '\0';

    aux = strtok(text, " ");
    while (aux != NULL)
    {
        queue = addQueue(queue, aux);
        //puts(aux);
        aux = strtok(NULL, " ");
    }

    intrare = malloc(sizeof(struct dictionary_entry));

    fgets(line, MAX_LENGTH+3, fr);
    line[strlen(line) - 1] = '\0';
    while (strcmp(line, "complete"))
    {
        aux = strtok(line, " ");
        priority = strtok(NULL, " ");
        adaugacuvant(&intrare, &n, aux, atoi(priority));

        fgets(line, MAX_LENGTH+3, fr);
        line[strlen(line) - 1] = '\0';
    }

    // parcurge cuvintele introduse de utilizator
    while (!isEmptyQueue(queue))
    {
        queue = delQueue(queue, cuvant);

        // verifică dacă are * la final
        steluta = 0;
        if (cuvant[strlen(cuvant) - 1] == '*')
        {
            steluta = 1;
            cuvant[strlen(cuvant) - 1] = '\0';
        }

        // dacă nu este semn de punctuație
        if (trbcautat(cuvant))
        {
            // verifică dacă corespunde măcar unui cuvânt din dicționar
            corespunde = cautare(intrare, cuvant, n);

            // dacă nu corespunde niciunuia și nu are * la final
            if (!corespunde && !steluta)
            {
                adaugacuvant(&intrare, &n, cuvant, 1);

                // este afișat așa cum e
                fprintf(fw, "%s ", cuvant);
            }

            // dacă are * la final
            if (steluta)
            {
                // dacă nu există deja în dicționar
                if (!exista(&intrare, cuvant, &n))
                {
                    adaugacuvant(&intrare, &n, cuvant, 1);
                }

                // este afișat așa cum e
                fprintf(fw, "%s ", cuvant);
            }

            // dacă corespunde măcar unui cuvânt
            // din dicționar și nu are * la final
            if (corespunde && !steluta)
            {
                potrivire(&intrare, cuvant, n, cuvbun);

                // este afișat cuvântul din dicționar cel mai potrivit
                fprintf(fw, "%s ", cuvbun);
            }
        }
        // dacă e semn de punctuație
        else
        {
            // este afișat așa cum e
            fprintf(fw, "%s ", cuvant);
        }
    }

    fclose(fr);
    fclose(fw);

    return 0;
}
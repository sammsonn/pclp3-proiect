// TODO - eliberare memorie, coada, headere, makefile

/* exemplu de input

his inv w di in* an interv , it was rather interes .
add_word arrow
add_word discussed
add_word hi
del_word hi
show_dict
priority_word arrow 6
show_dict
exit

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

#define MAX_WORDS 5002
#define MAX_LENGTH 22

void citeste(char **cuvant);
int cautare(struct dictionary_entry *intrare, char *decautat, int n);
int trbcautat(char *cuvant);
void adaugacuvant(struct dictionary_entry **intrare, int *marime, char *cuvant);
int exista(struct dictionary_entry **intrare, char *decautat, int *marime);
void potrivire(struct dictionary_entry **intrare,
               char *decautat, int n, char *cuvbun);

int main()
{
    int n, m, i, corespunde, steluta;
    char cuvant[MAX_WORDS][MAX_LENGTH], cuvbun[MAX_LENGTH];
    struct dictionary_entry *intrare;

    // citește numărul de cuvinte din dicționarul inițial
    scanf("%d", &n);
    getchar();

    intrare = malloc(n * sizeof(struct dictionary_entry));

    // citește cuvintele din dicționarul inițial
    for (i = 0; i < n; i++)
    {
        citeste(&intrare[i].word);
        intrare[i].priority = 0;
    }

    // citește numărul de cuvinte introduse de utilizator
    scanf("%d", &m);
    getchar();

    // citește cuvintele introduse de utilizator
    for (i = 0; i < m; i++)
    {
        scanf("%s", cuvant[i]);
        getchar();
    }

    // parcurge cuvintele introduse de utilizator
    for (i = 0; i < m; i++)
    {
        // verifică dacă are * la final
        steluta = 0;
        if (cuvant[i][strlen(cuvant[i]) - 1] == '*')
        {
            steluta = 1;
            cuvant[i][strlen(cuvant[i]) - 1] = '\0';
        }

        // dacă nu este semn de punctuație
        if (trbcautat(cuvant[i]))
        {
            // verifică dacă corespunde măcar unui cuvânt din dicționar
            corespunde = cautare(intrare, cuvant[i], n);

            // dacă nu corespunde niciunuia și nu are * la final
            if (!corespunde && !steluta)
            {
                adaugacuvant(&intrare, &n, cuvant[i]);

                // este afișat așa cum e
                printf("%s ", cuvant[i]);
            }

            // dacă are * la final
            if (steluta)
            {
                // dacă nu există deja în dicționar
                if (!exista(&intrare, cuvant[i], &n))
                {
                    adaugacuvant(&intrare, &n, cuvant[i]);
                }

                // este afișat așa cum e
                printf("%s ", cuvant[i]);
            }

            // dacă corespunde măcar unui cuvânt
            // din dicționar și nu are * la final
            if (corespunde && !steluta)
            {
                potrivire(&intrare, cuvant[i], n, cuvbun);

                // este afișat cuvântul din dicționar cel mai potrivit
                printf("%s ", cuvbun);
            }
        }
        // dacă e semn de punctuație
        else
        {
            // este afișat așa cum e
            printf("%s ", cuvant[i]);
        }
    }

    return 0;
}
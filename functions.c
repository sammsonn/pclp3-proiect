#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#define MAX_WORDS 5002
#define MAX_LENGTH 22

tQueue initQueue() // initializare coada
{
    tQueue q;
    q.front = q.rear = NULL;
    return q;
}

int isEmptyQueue(tQueue q) // verificare coada goala
{
    if (q.front == NULL)
    {
        return 1;
    }

    return 0;
}

tQueue addQueue(tQueue q, char *op) // adaugare celula in coada
{
    pQueueCell p = (pQueueCell)malloc(sizeof(queueCell));

    strcpy(p->word, op);
    p->next = NULL;

    if (q.front == NULL)
        q.front = q.rear = p;
    else
    {
        q.rear->next = p;
        q.rear = p;
    }

    return q;
}

tQueue delQueue(tQueue q, char op[MAX_LENGTH]) // scoatere celula din coada
{
    pQueueCell p;

    strcpy(op, q.front->word);

    if (q.front == q.rear)
    {
        free(q.front);
        q.front = q.rear = NULL;
    }
    else
    {
        p = q.front;
        q.front = q.front->next;
        free(p);
    }

    return q;
}

void freeQueue(tQueue q) // eliberare memorie coada
{
    pQueueCell p, aux;

    p = q.front;

    while (p != NULL)
    {
        aux = p;
        p = p->next;
        free(aux);
    }
}

/* citește fiecare cuvânt */
void citeste(char **cuvant)
{
    char aux[MAX_LENGTH];

    scanf("%s", aux);
    *cuvant = malloc(strlen(aux) + 1);
    strcpy(*cuvant, aux);
}

/* caută dacă cuvântul corespunde unui cuvânt
din dicționar și returnează 0 sau 1 */
int cautare(struct dictionary_entry *intrare, char *decautat, int n)
{
    if (n == 0)
    {
        return 0;
    }

    if (strstr(intrare[n - 1].word, decautat) == intrare[n - 1].word)
    {
        return 1;
    }

    return cautare(intrare, decautat, n - 1);
}

/* verifică dacă cuvântul nu este un semn de punctuație și returnează 0 sau 1 */
int trbcautat(char *cuvant)
{
    unsigned int semne = 0;

    // setează biți în variabila semne pentru a reprezenta fiecare semn de punctuație
    semne |= ((unsigned long long)1 << ',');
    semne |= ((unsigned long long)1 << '.');
    semne |= ((unsigned long long)1 << ':');
    semne |= ((unsigned long long)1 << '!');
    semne |= ((unsigned long long)1 << '?');
    semne |= ((unsigned long long)1 << ';');

    for (int i = 0; i < strlen(cuvant); i++)
    {
        // verifică dacă caracterul i al cuvântului este un semn de punctuație
        if (semne & (1 << cuvant[i]))
        {
            return 0;
        }
    }

    return 1;
}

/* adaugă un cuvânt nou in dicționar */
void adaugacuvant(struct dictionary_entry **intrare, int *marime, char *cuvant, int priority)
{
    struct dictionary_entry nou;

    nou.word = malloc(strlen(cuvant) + 1);
    strcpy(nou.word, cuvant);
    nou.priority = priority;

    *marime = *marime + 1;
    *intrare = realloc(*intrare, *marime * sizeof(struct dictionary_entry));

    (*intrare)[*marime - 1] = nou;
}

/* verifică dacă cuvântul există deja în dicționar și returnează 0 sau 1*/
int exista(struct dictionary_entry **intrare, char *decautat, int *marime)
{
    int i;

    for (i = 0; i < *marime; i++)
    {
        if (!strcmp((*intrare)[i].word, decautat))
        {
            // dacă există deja îi crește prioritatea
            (*intrare)[i].priority = (*intrare)[i].priority + 1;
            return 1;
        }
    }

    return 0;
}

/* găsește cuvântul cel mai potrivit din dicționar pentru cuvântul dat */
void potrivire(struct dictionary_entry **intrare,
               char *decautat, int n, char *cuvbun)
{
    char potrivit[MAX_WORDS][MAX_LENGTH], minpotrivit[MAX_LENGTH], bun[MAX_WORDS][MAX_LENGTH];
    int prioritatepotrivit[MAX_WORDS] = {0}, i, k = 0, maxprioritate, j = 0;

    // parcurge toate cuvintele din dicționar și
    // le păstrează pe cele cu care se potrivește
    for (i = 0; i < n; i++)
    {
        if (strstr((*intrare)[i].word, decautat) == (*intrare)[i].word)
        {
            strcpy(potrivit[k], (*intrare)[i].word);
            prioritatepotrivit[k] = (*intrare)[i].priority;
            k++;
        }
    }

    // parcurge cuvintele ce se potrivesc și află cea mai mare prioritate
    maxprioritate = prioritatepotrivit[0];
    for (i = 1; i < k; i++)
    {
        if (prioritatepotrivit[i] > maxprioritate)
        {
            maxprioritate = prioritatepotrivit[i];
        }
    }

    // parcurge cuvintele ce se potrivesc și le
    // salvează pe cele care au cea mai mare prioritate
    for (i = 0; i < k; i++)
    {
        if (prioritatepotrivit[i] == maxprioritate)
        {
            strcpy(bun[j], potrivit[i]);
            j++;
        }
    }

    // parcurge cuvintele cu prioritate maximă ce se potrivesc
    strcpy(minpotrivit, bun[0]);
    for (i = 1; i < j; i++)
    {
        if (strcmp(bun[i], minpotrivit) < 0)
        {
            // îl păstrează pe cel mai mic lexicografic
            strcpy(minpotrivit, bun[i]);
        }
    }

    strcpy(cuvbun, minpotrivit);

    // crește prioritatea cuvântului găsit
    for (i = 0; i < n; i++)
    {
        if (!strcmp((*intrare)[i].word, minpotrivit))
        {
            (*intrare)[i].priority = (*intrare)[i].priority + 1;
        }
    }
}
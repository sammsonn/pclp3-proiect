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

tQueue addQueue(tQueue q, char *word) // adaugare celula in coada
{
    pQueueCell p = (pQueueCell)malloc(sizeof(queueCell));

    strcpy(p->word, word);
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

tQueue delQueue(tQueue q, char word[MAX_LENGTH]) // scoatere celula din coada
{
    pQueueCell p;

    strcpy(word, q.front->word);

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

/* caută dacă cuvântul corespunde unui cuvânt
din dicționar și returnează 0 sau 1 */
int search(dictionaryEntry *entry, char *searchedWord, int dictSize)
{
    if (dictSize == 0)
    {
        return 0;
    }

    if (strstr(entry[dictSize - 1].word, searchedWord) ==
        entry[dictSize - 1].word)
    {
        return 1;
    }

    return search(entry, searchedWord, dictSize - 1);
}

/* verifică dacă cuvântul nu este un semn de punctuație și returnează 0 sau 1 */
int mustSearch(char *word)
{
    unsigned int signs = 0;

    // setează biți în variabila signs pentru a
    // reprezenta fiecare semn de punctuație
    signs |= ((unsigned long long)1 << ',');
    signs |= ((unsigned long long)1 << '.');
    signs |= ((unsigned long long)1 << ':');
    signs |= ((unsigned long long)1 << '!');
    signs |= ((unsigned long long)1 << '?');
    signs |= ((unsigned long long)1 << ';');

    for (int i = 0; i < strlen(word); i++)
    {
        // verifică dacă caracterul i al cuvântului este un semn de punctuație
        if (signs & (1 << word[i]))
        {
            return 0;
        }
    }

    return 1;
}

/* adaugă un cuvânt nou in dicționar */
void addWord(dictionaryEntry **entry, int *dictSize, char *word, int priority)
{
    dictionaryEntry nou;

    nou.word = malloc(strlen(word) + 1);
    strcpy(nou.word, word);
    nou.priority = priority;

    *dictSize = *dictSize + 1;
    *entry = realloc(*entry, *dictSize * sizeof(dictionaryEntry));

    (*entry)[*dictSize - 1] = nou;
}

/* verifică dacă cuvântul există deja în dicționar și returnează 0 sau 1*/
int exists(dictionaryEntry **entry, char *searchedWord, int *dictSize)
{
    int i;

    for (i = 0; i < *dictSize; i++)
    {
        if (!strcmp((*entry)[i].word, searchedWord))
        {
            // dacă există deja îi crește prioritatea
            (*entry)[i].priority = (*entry)[i].priority + 1;
            return 1;
        }
    }

    return 0;
}

/* găsește cuvântul cel mai match din dicționar pentru cuvântul dat */
void match(dictionaryEntry **entry,
           char *searchedWord, int n, char *rightWord)
{
    char match[MAX_WORDS][MAX_LENGTH], minMatch[MAX_LENGTH],
        right[MAX_WORDS][MAX_LENGTH];
    int matchPriority[MAX_WORDS] = {0}, i, k = 0, priorityMax, j = 0;

    // parcurge toate cuvintele din dicționar și
    // le păstrează pe cele cu care se potrivește
    for (i = 0; i < n; i++)
    {
        if (strstr((*entry)[i].word, searchedWord) == (*entry)[i].word)
        {
            strcpy(match[k], (*entry)[i].word);
            matchPriority[k] = (*entry)[i].priority;
            k++;
        }
    }

    // parcurge cuvintele ce se potrivesc și află cea mai mare prioritate
    priorityMax = matchPriority[0];
    for (i = 1; i < k; i++)
    {
        if (matchPriority[i] > priorityMax)
        {
            priorityMax = matchPriority[i];
        }
    }

    // parcurge cuvintele ce se potrivesc și le
    // salvează pe cele care au cea mai mare prioritate
    for (i = 0; i < k; i++)
    {
        if (matchPriority[i] == priorityMax)
        {
            strcpy(right[j], match[i]);
            j++;
        }
    }

    // parcurge cuvintele cu prioritate maximă ce se potrivesc
    strcpy(minMatch, right[0]);
    for (i = 1; i < j; i++)
    {
        if (strcmp(right[i], minMatch) < 0)
        {
            // îl păstrează pe cel mai mic lexicografic
            strcpy(minMatch, right[i]);
        }
    }

    strcpy(rightWord, minMatch);

    // crește prioritatea cuvântului găsit
    for (i = 0; i < n; i++)
    {
        if (!strcmp((*entry)[i].word, minMatch))
        {
            (*entry)[i].priority = (*entry)[i].priority + 1;
        }
    }
}

void freeDict(dictionaryEntry *entry, int dictSize)
{
    for (int i = 0; i < dictSize; i++)
    {
        free(entry[i].word);
    }

    free(entry);
}

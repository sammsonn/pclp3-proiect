#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#define MAX_WORDS 5002
#define MAX_LENGTH 22

int main()
{
    int dictSize = 0, corresponds, star;
    char word[MAX_LENGTH], rightWord[MAX_LENGTH], text[MAX_WORDS],
        line[MAX_LENGTH + 3], *priority, *aux;
    dictionaryEntry *entry;
    FILE *fr, *fw;
    tQueue queue;

    fr = fopen("input.in", "r");
    fw = fopen("output.out", "w");

    queue = initQueue(queue);

    // citește textul de completat
    fgets(text, MAX_WORDS, fr);
    text[strlen(text) - 1] = '\0';

    // adaugă fiecare cuvânt din text într-o coadă
    aux = strtok(text, " ");
    while (aux != NULL)
    {
        queue = addQueue(queue, aux);
        aux = strtok(NULL, " ");
    }

    entry = malloc(sizeof(dictionaryEntry));

    // citește cuvintele din dicționar și prioritatea lor
    fgets(line, MAX_LENGTH + 3, fr);
    line[strlen(line) - 1] = '\0';
    while (strcmp(line, "complete"))
    {
        aux = strtok(line, " ");
        priority = strtok(NULL, " ");
        // adaugă cuvântul și prioritatea curentă în dicționar
        addWord(&entry, &dictSize, aux, atoi(priority));

        fgets(line, MAX_LENGTH + 3, fr);
        line[strlen(line) - 1] = '\0';
    }

    // parcurge cuvintele din text
    while (!isEmptyQueue(queue))
    {
        queue = delQueue(queue, word);

        // verifică dacă are * la final
        star = 0;
        if (word[strlen(word) - 1] == '*')
        {
            star = 1;
            word[strlen(word) - 1] = '\0';
        }

        // dacă nu este semn de punctuație
        if (mustSearch(word))
        {
            // verifică dacă corespunde măcar unui cuvânt din dicționar
            corresponds = search(entry, word, dictSize);

            // dacă nu corresponds niciunuia și nu are * la final
            if (!corresponds && !star)
            {
                addWord(&entry, &dictSize, word, 1);

                // este afișat așa cum e
                fprintf(fw, "%s ", word);
            }

            // dacă are * la final
            if (star)
            {
                // dacă nu există deja în dicționar
                if (!exists(&entry, word, &dictSize))
                {
                    addWord(&entry, &dictSize, word, 1);
                }

                // este afișat așa cum e
                fprintf(fw, "%s ", word);
            }

            // dacă corespunde măcar unui cuvânt
            // din dicționar și nu are * la final
            if (corresponds && !star)
            {
                match(&entry, word, dictSize, rightWord);

                // este afișat cuvântul din dicționar cel mai potrivit
                fprintf(fw, "%s ", rightWord);
            }
        }
        // dacă e semn de punctuație
        else
        {
            // este afișat așa cum e
            fprintf(fw, "%s ", word);
        }
    }

    // se eliberează memoria
    freeDict(entry, dictSize);
    freeQueue(queue);

    fclose(fr);
    fclose(fw);

    return 0;
}

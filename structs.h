#define MAX_LENGTH 22

typedef struct dictionaryEntry
{
    char *word;
    int priority;
} dictionaryEntry;

typedef struct queueCell // celula din coada
{
    char word[MAX_LENGTH];  // cuvantul continut
    struct queueCell *next; // adresa celulei urmatoare
} queueCell, *pQueueCell;

typedef struct queue // coada
{
    pQueueCell front, rear; // adresa fetei si a spatelui
} tQueue;

int search(dictionaryEntry *entry, char *searchedWord, int dictSize);
int mustSearch(char *word);
int exists(dictionaryEntry **entry, char *searchedWord, int *dictSize);
int isEmptyQueue(tQueue q);
void match(dictionaryEntry **entry,
           char *searchedWord, int n, char *rightWord);
void addWord(dictionaryEntry **entry, int *dictSize, char *word, int priority);
void freeQueue(tQueue q);
void freeDict(dictionaryEntry *intrare, int size);
tQueue initQueue();
tQueue addQueue(tQueue q, char *op);
tQueue delQueue(tQueue q, char op[MAX_LENGTH]);

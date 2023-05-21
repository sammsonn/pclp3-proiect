#define MAX_LENGTH 22

struct dictionary_entry
{
    char *word;
    int priority;
};

typedef struct queueCell // celula din coada
{
    char word[MAX_LENGTH];  // cuvantul continut
    struct queueCell *next; // adresa celulei urmatoare
} queueCell, *pQueueCell;

typedef struct queue // coada
{
    pQueueCell front, rear; // adresa fetei si a spatelui
} tQueue;

int cautare(struct dictionary_entry *intrare, char *decautat, int n);
int trbcautat(char *cuvant);
int exista(struct dictionary_entry **intrare, char *decautat, int *marime);
int isEmptyQueue(tQueue q);
void potrivire(struct dictionary_entry **intrare,
               char *decautat, int n, char *cuvbun);
void citeste(char **cuvant);
void adaugacuvant(struct dictionary_entry **intrare, int *marime, char *cuvant, int priority);
void freeQueue(tQueue q);
tQueue initQueue();
tQueue addQueue(tQueue q, char *op);
tQueue delQueue(tQueue q, char op[MAX_LENGTH]);

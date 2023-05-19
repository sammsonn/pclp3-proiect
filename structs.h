struct dictionary_entry
{
    char *word;
    int priority;
};

typedef struct queueCell // celula din coada
{
    char op[20];            // operatia continuta
    struct queueCell *next; // adresa celulei urmatoare
} queueCell, *pQueueCell;

typedef struct queue // coada
{
    pQueueCell front, rear; // adresa fetei si a spatelui
} tQueue;

void citeste(char **cuvant);
int cautare(struct dictionary_entry *intrare, char *decautat, int n);
int trbcautat(char *cuvant);
void adaugacuvant(struct dictionary_entry **intrare, int *marime, char *cuvant);
int exista(struct dictionary_entry **intrare, char *decautat, int *marime);
void potrivire(struct dictionary_entry **intrare,
               char *decautat, int n, char *cuvbun);
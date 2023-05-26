/* Lívia Lutz dos Santos - 2211055 
Luiza Marcondes Paes Leme - 2210275
*/

typedef struct no No; 

void imprimeArray(int ocorrencias[], int tam);

No* insereLista(No* lista, char c, int quant);

No* formaLista(int ocorrencias[], int tam);

void arvImprime(No* a);

void imprimeLista(No* l);

No* montaArv(No* lista);

No* montaArvzinha(No** plista);

No* insereArvLista(No* lista, No* arv);

void comprime(No* arv, FILE* f);

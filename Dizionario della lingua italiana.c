/*                              Progetto n°2
                    Dizionario della lingua italiana (significati)
Questo programma simula la gestione di un dizionario.
Il dizionario è indicizzato tramite le lettere dell'alfabeto (lettere straniere
incluse). Ogni parola di questo dizionario, contiene un suo significato.
All'avvio l'utente inserisce un numero per eseguire la ricerca della parola
L'algoritmo che ho creato, mi permette, di ricercare una parola e ricevere il suo significato digitando il tasto 1,
Il tasto 2 permette di uscire dal programma.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definiamo il Min e il Max

#define Min 50
#define Max 500

// Definiamo la struct composta da 4 campi "lettera, nome, significato e sinonimi"

typedef struct {
	char lettera;
	char nome[Min];
	char significato[Max];
} Dizionario;

// Prototipi funzioni

int ricerca_binaria(Dizionario *a, int primo, int ultimo, char chiave[]); //compie la ricerca binaria ricorsiva
void riempi_dizionario(Dizionario *a); //riempie il dizionario applicando tutte le parole con i sinonimi, attraverso le strcpy
void compilazione_dizionaro(Dizionario *a , int dim_array); //permette di aggiornare il dizionario cambiando la parola precedente e i suoi sinonimi, con una scelta dall'utente e i suoi sinonimi.

int main ()
{                                                   // Parte dichiarativa
    Dizionario a[120];
    int indice_ricerca, primo=0;
    int dim_array=25, ultimo=25;
    int scelta_caso;
    char chiave [25];
    riempi_dizionario(a);                           // Procedura che permette di riempire il dizionario

    do
    {
    printf("\n Selezionare una delle seguenti scelte:");
    printf("\n\n 1 Se si vuole ricercare una parola \n 2 per uscire dal programma: ");
    scanf("%d", &scelta_caso);
    if (scelta_caso == 1)      // Costrutto di selezione permette di selezionare la prima scelta del menù
    {
        fflush(stdin);
        printf("\n Inserire la parola da ricercare: ");
        gets(chiave);    // Acquisizione chiave
        fflush(stdin);
        indice_ricerca=ricerca_binaria(a, primo, ultimo, chiave);  // Chiamata algoritmo di ricerca binaria ricorsiva
        if (indice_ricerca>=0)        // Se la ricerca fornisce esito positivo allora si procede con quanto segue
            {
                printf("\n\nPer %s intendiamo:\n%s\n", a[indice_ricerca].nome, a[indice_ricerca].significato);
            }
        else                          // altrimenti viene selezionata la seguente opzione
            {
                printf("\a\n La parola non e\' stata trovata nel dizionario\n\n ");
            }
    }

    if (scelta_caso == 1)

    {
        sleep(3);
        system("CLS");

    }

    }while (scelta_caso != 2); //quando scelta_caso diventa 2 allora procede alla chiusura del programma.

    printf("\nAdesso il programma si chiudera'\n\n");
    sleep (1);

    return 0;

}

void riempi_dizionario(Dizionario *a)   // Inizializzazione della struct dizionario
{
    a[0].lettera='a';
    strcpy (a[0].nome, "antico");
    strcpy (a[0].significato, "un modo come un altro per definire un qualcosa vecchio");

    a[1].lettera='b';
    strcpy (a[1].nome, "banca");
    strcpy (a[1].significato, "istituto di credito che fa circolare il denaro");

    a[2].lettera='c';
    strcpy (a[2].nome, "conchiglia");
    strcpy (a[2].significato, "involucro calcareo che ricopre il corpo di molti molluschi");

    a[3].lettera='d';
    strcpy (a[3].nome, "dizionario");
    strcpy (a[3].significato, "libro contenente varie parole con i propri significati");

    a[4].lettera='e';
    strcpy (a[4].nome, "enoteca");
    strcpy (a[4].significato, "Collezione di vini pregiati in bottiglia.");

    a[5].lettera='f';
    strcpy (a[5].nome, "ferro");
    strcpy (a[5].significato, "minerale raccolto dal sottosuolo terrestre");

    a[6].lettera='g';
    strcpy (a[6].nome, "golfo");
    strcpy (a[6].significato, "concavità bagnata dal mare");

    a[7].lettera='h';
    strcpy (a[7].nome, "hotel");
    strcpy (a[7].significato, "struttura che accoglie gli ospiti spesso di altri luoghi, per motivi di business o leisure");

    a[8].lettera='i';
    strcpy (a[8].nome, "isole");
    strcpy (a[8].significato, "terreno circondato dal mare");

    a[9].lettera='j';
    strcpy (a[9].nome, "jogging");
    strcpy (a[9].significato, "mini corsetta di campagna");

    a[10].lettera='k';
    strcpy (a[10].nome, "koala");
    strcpy (a[10].significato, "un animale grigio");

    a[11].lettera='l';
    strcpy (a[11].nome, "libro");
    strcpy (a[11].significato, "Serie continua di fogli stampati della stessa misura, cuciti insieme e forniti di copertina o rilegatura");

    a[12].lettera='m';
    strcpy (a[12].nome, "monologo");
    strcpy (a[12].significato, "discorso che avviene tra sè, a volte anche ad alta voce");

    a[13].lettera='n';
    strcpy (a[13].nome, "noleggiare");
    strcpy (a[13].significato, "effettuare un contratto di affitto per breve periodo, spesso utilizzato per i film o le auto");

    a[14].lettera='o';
    strcpy (a[14].nome, "oroscopo");
    strcpy (a[14].significato, "la previsione circa il destino di una persona attraverso la data, l'ora e il luogo della sua nascita");

    a[15].lettera='p';
    strcpy (a[15].nome, "pelle");
    strcpy (a[15].significato, "superficie che riveste il corpo umano");

    a[16].lettera='q';
    strcpy (a[16].nome, "quadro");
    strcpy (a[16].significato, "un abbellimento per la casa");

    a[17].lettera='r';
    strcpy (a[17].nome, "ragno");
    strcpy (a[17].significato, "un animale con 8 zampe");

    a[18].lettera='s';
    strcpy (a[18].nome, "salario");
    strcpy (a[18].significato, "quello che tutti desiderano ma pochi hanno");

    a[19].lettera='t';
    strcpy (a[19].nome, "terreno");
    strcpy (a[19].significato, "una zona che appartiene alla terra");

    a[20].lettera='u';
    strcpy (a[20].nome, "ulivo");
    strcpy (a[20].significato, "albero di olive");

    a[21].lettera='v';
    strcpy (a[21].nome, "vigneto");
    strcpy (a[21].significato, "terreno, per lo più di notevole estensione, coltivato a viti.");

    a[22].lettera='w';
    strcpy (a[22].nome, "wafer");
    strcpy (a[22].significato, "biscotto croccante");

    a[23].lettera='x';
    strcpy (a[23].nome, "xilofono");
    strcpy (a[23].significato, "uno strumento con note molto stridule");

    a[24].lettera='y';
    strcpy (a[24].nome, "yacht");
    strcpy (a[24].significato, "imbarcazione spesso di lusso");

    a[25].lettera='z';
    strcpy (a[25].nome, "zebra");
    strcpy (a[25].significato, "un animale con strisce bianche e nere");
}
int ricerca_binaria(Dizionario *a, int primo, int ultimo, char chiave[]) // Algoritmo ricerca binaria ricorsiva
{                                                                     // Ha come parametri in ingresso Array in cui cercare
    int med;                                                          // Indice primo da cui partire, inizializzato nel main
    if (primo > ultimo)                                                 // Indice ultimo a cui fermarsi nella ricerca, anch'esso inizializzato nel main
      return -1;                                                      // Chiave ovvero l'elemento da cercare
    else
    {
      med = (primo + ultimo) / 2;
    if (strcmpi(chiave,a[med].nome)==0)                               // I valori in uscita sono
      return med;                                                     // Successo della ricerca ed posizione dell'elemento nell'array
    else if (strcmpi(chiave,a[med].nome)>0)                           // Un numero negativo può essere considerato un insucesso
      return ricerca_binaria(a, med+1, ultimo, chiave);
    else
      return ricerca_binaria(a, primo, med-1, chiave);
    }
}

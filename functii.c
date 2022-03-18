/* ORZATA Gabriel-Nicusor-313 */
#include "trie.h"



Arb_Trie_autor* search_autor(Arb_Trie_autor* autori, char* autor)
{
    int i, nr, index;
    for(i = 0; autor[i]!='\0'; i++){
        nr = (int)autor[i];
        index = determinare_index(nr);
        if(autori->copil[index] == NULL){
            return NULL;
        }
        autori = autori->copil[index];  
    }
    if(autori != NULL && autori->frunza == 0){
        return NULL;
    }
    if(autori != NULL && autori->frunza == 1){
        return autori;
    }
    return 0;
}


void add_book(Arb_Trie* titluri, Arb_Trie_autor *autori, char **v)
{
    // Construiesc doua structuri de tip Carte in care pun datele cartii
    // si le adaug in T1 si T2.
    Carte* carte = malloc(sizeof(Carte));
    carte->titlu = malloc(50 * sizeof(char));
    strcpy(carte->titlu, v[1]);
    carte->autor = malloc(50 * sizeof(char));
    strcpy(carte->autor, v[2]);
    carte->rating = atoi(v[3]);
    carte->nr_pagini = atoi(v[4]);

    Carte* carte_autor = malloc(sizeof(Carte));
    carte_autor->titlu = malloc(50 * sizeof(char));
    strcpy(carte_autor->titlu, v[1]);
    carte_autor->autor = malloc(50 * sizeof(char));
    strcpy(carte_autor->autor, v[2]);
    carte_autor->rating = atoi(v[3]);
    carte_autor->nr_pagini = atoi(v[4]);
    titluri = insert_trie(titluri, carte);
    Arb_Trie_autor* aux = search_autor(autori, v[2]);
    if(aux != NULL){
        // Daca autorul exista deja introduc inca o carte in trie-ul sau de carti.
        aux->carti = insert_trie(aux->carti, carte_autor);
    }else{
        // Daca autorul nu exista, mai intai creez trie-ul sau de carti,
        // iar apoi il introduc in T2. 
        Arb_Trie* carti_autor = make_Arb_Trie('\0');
        carti_autor = insert_trie(carti_autor, carte_autor);
        autori = insert_trie_autor(autori, carti_autor, v[2]);
    }
}

int search_book(Arb_Trie* titluri, char* titlu, FILE* out, int x)
{
    int i, nr, index;
    // Parcurg fiecare litera din titlul cartii si verfic daca exista
    // fiecare in trie. Daca nu sunt toate, inseamna ca nu exista. 
    for(i = 0; titlu[i]!='\0'; i++){
        nr = (int)titlu[i];
        index = determinare_index(nr);
        if(titluri->copil[index] == NULL){
            fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", titlu);
            return -1;
        }
        titluri = titluri->copil[index];  
    }
    // In cazul in care titlul reprezinta o parte dintr-un titlu deja existent
    // acesta nu are campul frunza egal cu 1, deci cartea nu exista in trie.
    if(titluri != NULL && titluri->frunza == 0){
        fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", titlu);
        return -1;
    }
    if(titluri != NULL && titluri->frunza == 1){
        Carte* carte = (Carte*)titluri->carte;
        if(x == 1){
            fprintf(out, "Informatii recomandare: %s, %s, %d, %d\n", 
            carte->titlu, carte->autor, carte->rating, carte->nr_pagini);
        }
        return 1;
    }


    return 0;
}

void parcurgere_trie(Arb_Trie* arb, FILE* out)
{
    // Trec prin toate cartile autorului pe rand, acestea fiind
    // introduce initial dupa ordinea lexicografica.
    if(!arb)
        return;
    int i;
    if(arb->frunza == 1){
        Carte* carte = (Carte*)arb->carte;
        fprintf(out, "%s\n", carte->titlu);
    }
    for(i = 0; i < N; i++){
        parcurgere_trie(arb->copil[i], out); 
    }
}

void list_author(Arb_Trie_autor* autori, char* nume, FILE* out)
{
    int i, nr, index;
    for(i = 0; nume[i]!='\0'; i++){
        // Acelasi proces ca la search_book.
        nr = (int)nume[i];
        index = determinare_index(nr);
        if(autori->copil[index] == NULL){
            fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n", nume);
            return;
        }
        autori = autori->copil[index];  
    }

    if(autori != NULL && autori->frunza == 0){
        fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n", nume);
        return;
    }
    
    if(autori != NULL && autori->frunza == 1){
        Arb_Trie* lista_carti = (Arb_Trie*)autori->carti;
        parcurgere_trie(lista_carti, out);
        return;
    }
    return;
}

void search_by_author(Arb_Trie_autor* autori, char* autor, char* titlu, FILE* out)
{
    int i, nr, index;
    // Prima data verific daca autorul exista in T2.
    // Apoi folosesc functia search_book ca sa gasesc cartea.
    for(i = 0; autor[i]!='\0'; i++){
        nr = (int)autor[i];
        index = determinare_index(nr);
        if(autori->copil[index] == NULL){
            fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n", autor);
            return;
        }
        autori = autori->copil[index];  
    }

    if(autori != NULL && autori->frunza == 0){
        fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n", autor);
        return;
    }
    if(autori != NULL && autori->frunza == 1){
        Arb_Trie* lista_carti = (Arb_Trie*)autori->carti;
        search_book(lista_carti, titlu, out, 1);
        return;
    }
    return;
}

void parcurgere_trie_auto(Arb_Trie* arb, FILE* out, int* x)
{
    // La fel ca la parcurgere_trie numai ca ma opresc daca am afisat
    // 3 carti.
    if(*x == 3 || !arb){
        return;
    }
    int i;
    if(arb->frunza == 1){
        Carte* carte = (Carte*)arb->carte;
        fprintf(out, "%s\n", carte->titlu);
        *x += 1;
    }
    for(i = 0; i < N; i++){
        parcurgere_trie_auto(arb->copil[i], out, x);
    }
}

void search_book_auto(Arb_Trie* titluri, char* prefix, FILE* out)
{
    // La fel ca la search_book, numai ca difera conditiile pentru care
    // o carte nu exista.
    int i, nr, index;
    for(i = 0; prefix[i]!='\0'; i++){
        nr = (int)prefix[i];
        index = determinare_index(nr);
        if(titluri->copil[index] == NULL){
            fprintf(out, "Nicio carte gasita.\n");
            return;
        }
        titluri = titluri->copil[index];  
    }

    
    if(titluri != NULL){
        int *x = calloc(1,sizeof(int));
        parcurgere_trie_auto(titluri, out, x);
        free(x);
        return;
    }


    return;
}



void parcurgere_trie_autori_auto(Arb_Trie_autor* arb, FILE* out, int* x)
{
    // La fel ca celelalte functii de parcurgere.
    if(*x == 3 || !arb){
        return;
    }
    int i;
    if(arb->frunza == 1){
        fprintf(out, "%s\n", arb->autor);
        *x += 1;
    }
    for(i = 0; i < N; i++){

        parcurgere_trie_autori_auto(arb->copil[i], out, x);

    }
}

void list_author_auto(Arb_Trie_autor* autori, char* prefix, FILE* out)
{
    // La fel ca la list_author.
    // Functie speciala pentru cazul in care se cauta o carte a unui autor.
    int i, nr, index;
    for(i = 0; prefix[i]!='\0'; i++){
        nr = (int)prefix[i];
        index = determinare_index(nr);
        if(autori->copil[index] == NULL){
            fprintf(out, "Niciun autor gasit.\n");
            return;
        }
        autori = autori->copil[index];  
    }
    
    if(autori != NULL){
        int *x = calloc(1,sizeof(int));
        parcurgere_trie_autori_auto(autori, out, x);
        free(x);
        return;
    }
    return;
}

void search_by_author_auto_1(Arb_Trie_autor* autori, char* autor,
    char* prefix, FILE* out)
{
    // Functie speciala pentru cazul in care se cauta doar autorul.
    int i, nr, index;
    for(i = 0; autor[i]!='\0'; i++){
        nr = (int)autor[i];
        index = determinare_index(nr);
        if(autori->copil[index] == NULL){
            fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n"
                , autor);
            return;
        }
        autori = autori->copil[index];  
    }

    if(autori != NULL){
        Arb_Trie* lista_carti = (Arb_Trie*)autori->carti;
        search_book_auto(lista_carti, prefix, out);
        return;
    }
    return;
}


void determinare_autor(Arb_Trie* titluri, char* titlu, char* autor)
{
    // Determin numele autorului in functie de titlul cartii.
    int i = 0, nr, index;
    for(i = 0; titlu[i] != '\0'; i++){
        nr = (int)titlu[i];
        index = determinare_index(nr);
        if(titluri->copil[index] == NULL){
            return;
        }

        titluri = titluri->copil[index];

        if(titluri->frunza == 1){
            Carte* carte = (Carte*)titluri->carte;
            strcpy(autor, carte->autor);
            return;
        }
    }
    return;
}


void delete_autor(Arb_Trie_autor* autori, char* autor)
{
    int i, j, nr, index, nr_litera, flag = 0, contor = 0, flag2 = 0;
    Arb_Trie_autor *anterior = NULL, *ultima_frunza = NULL,
                    *A = autori, *Inc = autori, *ultimul_nod; 


    for(i = 0; autor[i] != '\0'; i++){
        nr = (int)autor[i];
        index = determinare_index(nr);
        if(A->copil[index] == NULL){
            return;
        }
        if(A->copil[index]->frunza == 1){
            if(ultima_frunza != NULL){
                anterior = ultima_frunza;
            }
            if(autor[i+1] != '\0'){
                nr_litera = i;   
            }
            ultima_frunza = A->copil[index];
        }
        A = A->copil[index];
    }

    
    for(i = 0; i < N; i++){
        if(A->copil[i] != NULL && A->frunza == 1 && anterior == NULL){
            flag = 1;
            A->frunza = 0;
            free_Arb_Trie_Autor(&anterior->copil[index]);
            return;
        }
    }

    if(anterior == NULL && flag == 0){
        nr = (int)autor[0];
        index = determinare_index(nr);
        autori = autori->copil[index];
        Inc = Inc->copil[index];

        for(i = 1; autor[i] != '\0'; i++){
            nr = (int)autor[i];
            index = determinare_index(nr);
            for(j = 0; j < N; j++){
                if(autori->copil[j] != NULL){
                    contor++;
                }
            }
            if(contor >= 2){
                ultimul_nod = autori->copil[index];
                contor = 0;
                flag2 = 1;
            } else{
                contor = 0;
            }
            autori = autori->copil[index];
        }
        if(flag2 == 1){
            free_Arb_Trie_Autor(&ultimul_nod);
        }
        if(flag2 == 0){
            free_Arb_Trie_Autor(&Inc);
        }
    }

    if(anterior != NULL){
        nr = (int)autor[nr_litera + 1];
        index = determinare_index(nr);
        free_Arb_Trie_Autor(&anterior->copil[index]);
    }
    
}

void delete_book(Arb_Trie *titluri, Arb_Trie_autor *autori, char* titlu,
                 FILE* out, int stop)
{
    int i, j, nr, index, nr_litera, flag = 0, contor = 0, flag2 = 0;
    Arb_Trie *anterior = NULL, *ultima_frunza = NULL,
             *T = titluri, *Inc = titluri, *ultimul_nod; 
    char *autor = malloc(40 * sizeof(int));

    if(stop == 0){
        determinare_autor(titluri, titlu, autor);
    }

    for(i = 0; titlu[i] != '\0'; i++){
        nr = (int)titlu[i];
        index = determinare_index(nr);
        if(T->copil[index] == NULL){
            if(stop == 0){
                fprintf(out, "Cartea %s nu exista in recomandarile tale.\n",
                        titlu);
            }
            return;
        }
        if(T->copil[index]->frunza == 1){
            if(ultima_frunza != NULL){
                anterior = ultima_frunza;
            }
            if(titlu[i+1] != '\0'){
                nr_litera = i;   
            }
            ultima_frunza = T->copil[index];

        }
        T = T->copil[index];
    }

    if(T != NULL && T->frunza == 0){
        fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", titlu);
        return;
    }

    for(i = 0; i < N; i++){
        if(T->copil[i] != NULL && T->frunza == 1 && anterior == NULL){
            flag = 1;
            T->frunza = 0;
            free_Arb_Trie(&anterior->copil[index]);
            return;
        }
    }

    if(anterior == NULL && flag == 0){
        nr = (int)titlu[0];
        index = determinare_index(nr);
        titluri = titluri->copil[index];
        Inc = Inc->copil[index];

        for(i = 1; titlu[i] != '\0'; i++){
            nr = (int)titlu[i];
            index = determinare_index(nr);
            for(j = 0; j < N; j++){
                if(titluri->copil[j] != NULL){
                    contor++;
                }
            }
            if(contor >= 2){
                ultimul_nod = titluri->copil[index];
                contor = 0;
                flag2 = 1;
            } else{
                contor = 0;
            }
            titluri = titluri->copil[index];
        }
        if(flag2 == 1){
            free_Arb_Trie(&ultimul_nod);
        }
        if(flag2 == 0){
            free_Arb_Trie(&Inc);
        }
    }

    if(anterior != NULL){
        nr = (int)titlu[nr_litera + 1];
        index = determinare_index(nr);
        free_Arb_Trie(&anterior->copil[index]);
    }

    if(stop == 0){
        Arb_Trie_autor* A = autori;
        for(i = 0; autor[i]!='\0'; i++){
            nr = (int)autor[i];
            index = determinare_index(nr);
            autori = autori->copil[index];  
        }
        Arb_Trie *lista_carti = ((Arb_Trie*)autori->carti);
        delete_book(lista_carti, autori, titlu, out, 1);
        contor = 0;
        for(i = 0; i < N; i++){
            if(lista_carti->copil[i] != NULL){
                contor++;
            }
        }
        if(contor == 1){
            for(i = 0; i < N; i++){
                lista_carti->copil[i] = NULL;
            }
            nr = (int)autor[0];
            index = determinare_index(nr);
            delete_autor(A, autor);
        }
    }
    return;
}
/* ORZATA Gabriel-Nicusor-313 */
#include "trie.h"

int determinare_index(int nr)
{
    // In functie de carcaterul dat determin indexul lui in arbore.
    int index;
    if(97 <= nr && nr <= 122){
        index = nr - 'a';
    } else if(65 <= nr && nr <= 90){
        index = nr - 39;
    }else if(48 <= nr && nr <= 57){
        index = nr + 4;
    } else if(nr == 46){
        index = 62;
    } else if(nr == 45){
        index = 63;
    } else if(nr == 39){
        index = 64;
    }else if(nr == 63){
        index = 65;
    }else if(nr == 33){
        index = 66;
    }else if(nr == 32){
        index = 67;
    }
    return index;
}
 
Arb_Trie* make_Arb_Trie(char litera)
{
    // Creez un nod cu litera data si ii initializez copiii.
    Arb_Trie* node = (Arb_Trie*)malloc(sizeof(Arb_Trie));
    int i;
    for(i = 0; i < N; i++){
        node->copil[i] = NULL;
    }
    node->frunza = 0;
    node->c = litera;
    node->carte = NULL;
    return node;
}


Arb_Trie_autor* make_Arb_Trie_autor(char litera)
{
    // Acelasi lucru ca mai sus.
    Arb_Trie_autor* node = (Arb_Trie_autor*)malloc(sizeof(Arb_Trie_autor));
    int i;
    for(i = 0; i < N; i++){
        node->copil[i] = NULL;
    }
    node->frunza = 0;
    node->c = litera;
    node->autor = NULL;
    node->carti = NULL;
    return node;
}


void free_Arb_Trie(Arb_Trie** node)
{
    if(*node == NULL){
        return;
    }
    int i, contor = 0;
    for(i = 0; i < N; i++){
        if((*node)->copil[i] != NULL){
            // Iterez prin totate caracterele pana ajung la ultimul.
            free_Arb_Trie(&(*node)->copil[i]);
        }
    }
    for(i = 0; i < N; i++){
        if((*node)->copil[i] != NULL){
            contor++;
        }
        if(contor == 2){
            // Daca nodul are mai mult de un copil, inseamna ca mai exista
            // un titlu de carte cu acelasi prefix, asa ca nu il sterg.
            return;
        }
    }
    if((*node)->carte != NULL){
        Carte* carte = (Carte*)(*node)->carte;
        free(carte->autor);
        free(carte->titlu);
        free(carte);
        carte = NULL;
    }
    for(i = 0; i < N; i++){
        (*node)->copil[i] = NULL;
    }
    // Eliberez memoria si o fac NULL.
    (*node)->c = 0;
    free((*node));
    (*node) = NULL;
}


void free_Arb_Trie_Autor(Arb_Trie_autor** node)
{
    // La fel ca mai sus.
    if(*node == NULL){
        return;
    }
    int i, contor = 0;
    for(i = 0; i < N; i++){
        if((*node)->copil[i] != NULL){
            free_Arb_Trie_Autor(&(*node)->copil[i]);
        }
        else{
            continue;
        }
    }
    for(i = 0; i < N; i++){
        if((*node)->copil[i] != NULL){
            contor++;
        }
        if(contor == 2){
            return;
        }
    }
    if((*node)->carti != NULL){
        Arb_Trie *lista = (Arb_Trie*)(*node)->carti;
        free(lista);
        lista = NULL;
    }
    for(i = 0; i < N; i++){
        (*node)->copil[i] = NULL;
    }
    (*node)->frunza = 0;
    (*node)->c = 0;
    (*node) = NULL;
}


Arb_Trie* insert_trie(Arb_Trie* root, Carte* carte)
{
    Arb_Trie* temp = root;
    int i, index, nr;
    char* word = carte->titlu;
    // Iau titlul din structura carte.
    for(i = 0; word[i] != '\0'; i++){
        nr = (int)word[i];
        index = determinare_index(nr);
        // Adaug in T1 fiecare litera din el,  daca nu exista deja.
        // Introducerea se face dupa ordinea lexicografica.
        if(temp->copil[index] == NULL){
            temp->copil[index] = make_Arb_Trie(word[i]);
        }
        else{
        }
        temp = temp->copil[index];
    }
    temp->frunza = 1;
    temp->carte = carte;
    return root;
}

Arb_Trie_autor* insert_trie_autor(Arb_Trie_autor* root, Arb_Trie* carti_autor, char* nume)
{
    // Acelasi lucru ca mai sus, numia ca in loc de strcutra de date carte
    // acum introduc un T1 in arbore.
    Arb_Trie_autor* temp = root;
    int i, index, nr;
    for(i = 0; nume[i] != '\0'; i++){
        nr = (int)nume[i];
        index = determinare_index(nr);

        if(temp->copil[index] == NULL){
            temp->copil[index] = make_Arb_Trie_autor(nume[i]);
        }
        temp = temp->copil[index];
    }
    temp->frunza = 1;
    temp->carti = carti_autor;
    temp->autor = malloc(50 * sizeof(char));
    strcpy(temp->autor, nume);
    return root;
}


/* ORZATA Gabriel-Nicusor-313 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 68
 
typedef struct Arb_Trie Arb_Trie;
typedef struct Arb_Trie_autor Arb_Trie_autor;

typedef struct carte{
    int nr_pagini, rating;
    char *titlu, *autor;
} Carte;

struct Arb_Trie {
    Carte* carte;
    char c;
    Arb_Trie* copil[N];
    int frunza;
};

struct Arb_Trie_autor {
    char c, *autor;
    Arb_Trie_autor* copil[N];
    int frunza;
    Arb_Trie* carti;
};

int determinare_index(int nr);
Arb_Trie* make_Arb_Trie(char litera);
Arb_Trie_autor* make_Arb_Trie_autor(char litera);
void free_Arb_Trie(Arb_Trie** node);
void free_Arb_Trie_Autor(Arb_Trie_autor** node);
Arb_Trie* insert_trie(Arb_Trie* root, Carte* carte);
Arb_Trie_autor* insert_trie_autor(Arb_Trie_autor* root,
    Arb_Trie* carti_autor, char* nume);
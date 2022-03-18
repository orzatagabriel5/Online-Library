/* ORZATA Gabriel-Nicusor-313 */
#include "trie.h"


void add_book(Arb_Trie* titluri, Arb_Trie_autor *autori, char **v);
int search_book(Arb_Trie* titluri, char* titlu, FILE* out, int x);
void list_author(Arb_Trie_autor* autori, char* nume, FILE* out);
void list_author_auto(Arb_Trie_autor* autori, char* nume, FILE* out);
void search_by_author(Arb_Trie_autor* autori, char* autor, 
                     char* titlu, FILE* out);
void search_by_author_auto_1(Arb_Trie_autor* autori, char* autor, 
                             char* prefix, FILE* out);
void search_book_auto(Arb_Trie* titluri, char* prefix, FILE* out);
void delete_book(Arb_Trie *titluri, Arb_Trie_autor *autori, char* titlu,
                 FILE* out, int stop);


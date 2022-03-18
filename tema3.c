/* ORZATA Gabriel-Nicusor-313 */
#include "functii.h"
#include<stdio.h>


int main (int argc, char* argv[])
{
    FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[2], "w");

    Arb_Trie *titluri = make_Arb_Trie('\0');
    Arb_Trie_autor *autori = make_Arb_Trie_autor('\0');

    int i, line=1, flag;
    char **v, str[200], *p;
    v = malloc(100 * sizeof(char*));

    for(i = 0; i < 20; i++){
        v[i] = malloc(50 * sizeof(char));
    }
    while(fgets(str, 200, in)){
        i = 0;
        flag = 0;
        if(str[strlen(str) - 1] == '\n'){
			str[strlen(str) - 1] = 0;
		}
        p = strtok(str, " ");
        while(p != NULL){
            strcpy(v[i], p);
            p = strtok(NULL, ":");
			i++;
        }
        
        if(strcmp(v[0], "add_book") == 0){
            add_book(titluri, autori, v);
        }
        if(strcmp(v[0], "search_book") == 0){
            for(i = 0; i < strlen(v[1]); i++){
                if(v[1][i] == '~'){
                    v[1][i] = 0;
                    search_book_auto(titluri, v[1], out);
                    flag = 1;
                }
            }
            if(flag == 0){
                search_book(titluri, v[1], out, 1);
            }
        }
        if(strcmp(v[0], "list_author") == 0){
            for(i = 0; i < strlen(v[1]); i++){
                if(v[1][i] == '~'){
                    v[1][i] = 0;
                    list_author_auto(autori, v[1], out);
                    flag = 1;
                }
            }
            if(flag == 0){
                list_author(autori, v[1], out);
            }
        }
        if(strcmp(v[0], "search_by_author") == 0){
            if(strcmp(v[2], "0") != 0){
                for(i = 0; i < strlen(v[2]); i++){
                    if(v[2][i] == '~'){
                        v[2][i] = 0;
                        search_by_author_auto_1(autori, v[1], v[2], out);
                        flag = 1;
                    }
                }
                if(flag == 0){
                    search_by_author(autori, v[1], v[2], out);
                }
            }else{
                i = strlen(v[1]) - 1;
                v[1][i] = 0;
                list_author_auto(autori, v[1], out);
            }
        }

        if(strcmp(v[0], "delete_book") == 0){
            delete_book(titluri, autori, v[1], out, 0);
        }
        line++;

        for(i = 0; i < 20; i++){
            strcpy(v[i],"0");
        }
    }
    fclose(in);
    fclose(out);
    return 1;
}
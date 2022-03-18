Tema 3.
Structura de trie contine litera corespunzatoare din stringul care trebuie
introdus in arbore, un vectori de arbori care reprezinta urmatoarele litere
din string care urmeaza sa fie adaugate, variabila frunza care indica daca
nodul este sau nu sfarsitul unui string si o structura carte sau inca una
de tip trie, dac arborele este T1, respectiv T2.

add_book:
	Construiesc doua structuri Carte pe care le adaug in T1 si T2 folosind
	functia insert_trie; in aceasta functie iau fiecare litera din titlul
	cartii si o introduc in arborele de tip T1.
	Daca autorul cartii exista deja in T2, adaug in lista sa de carti noua
	carte, iar daca nu exista, creez o lista de carti (T1) si adaug autorul
	in T2, impreuna cu prima sa carte.

search_book:
	Prima data verific daca exista cartea parcurgand T1 si verficand daca
	exista un copil la fiecare nod corespunzator literelor din titlul cartii.
	Daca titlul cautat este un prefix al altei carti din T1, la iesirea din
	for frunza ultimei sale litere o sa fie 0, ceea ce inseamna ca nu exista
	in arbore.
	Daca frunza este 1, printez informatiile din structura carte in output.

search_book_auto:
	search_book, numai ca atunci cand gasesc prefixul in arbore, retin nodul
	unde se alfa si il dau ca parametru functiei parcurgere_trie_auto:
	aici parcurg arborele incepand de la nodul dat si cand am gasit 3 frunze
	ma opresc din printat.

list_author:
	Fac acelasi lucru ca la search_book, dar atunci cand gasesc autorul in
	T2 folosesc functia parcurgere_trie ca sa printez cartile sale:
	functia primeste ca paramentru lista de cartia a autorului pe care o
	parcurg integral, iar atunci cand ajung la finalul unui titlu, printez
	informatiile din structura Carte.

list_author_auto:
	Este pentru cazul in care se cauta o carte a unui autor.
	Folosesc o parcurgere asemanatoare cu celelalte, pentru a printa cartile
	gasite.

list_author_auto1:
	Este pentru cazul in care se cauta un autor.
	
search_by_auhtor:
	Prima data verific daca autorul exista in T2, apoi folosesc functia
	search_book ca sa gasesc cartea.

delete_book:
	Prima data verific daca cartea se afla in T1 si in acelsi timp verific
	daca mai exista carti care reprezinta un prefix din titlul cartii care
	trebuie stearsa (cu ultima_frunza si anterior) si retin litera unde se
	afla ultima frunza pentru cazul in care trebuie sa sterg de la o frunza
	a altui titlu prefix pana la frunza titlului care trebuie sters.
	In functie de cazul in care ma aflu apelez functia free_Arb_Trie:
	Este o functie recursiva care itereaza prin toate nodurile, incepand
	cu cel dat ca paramentru, apoi verfica daca nodurile nu fac parte si
	din alte titluri din arbore si elibereaza memoria acelora.
	Apoi folosesc acelasi tip de functii pentru a elibera carte si din lista
	de carti a autorului si numele lui din T2, daca nu mai exista nicio carte
	in lista sa.
	
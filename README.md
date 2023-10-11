# image-compression
Image compression and decompression algorithm that utilizes a quaternary tree data structure.

# Cerinta 2: Compresie cu arbore cuaternar
Am facut o fucntie care sa printeze un arbore pe nivele si am printat elementele din arbore intr-un fisier binar.

# Cerinta 3: Decompresie
Am citit informatiile din fisierul binar, le-am trecut intr-o matrice de pixeli si am printat matricea intr-un fisier binar (.ppm)

# Acestea sunt functiile/structurile pe care le-am utilizat:

# In fisierul "structs.h" sunt definite structurile pe care le-am folosit

    - structura *RGB* pentru un pixel care retine cele 3 valori pentru rosu, verde si albastru
    - structura *Grid* pentru o matrice cu pixeli si dimensiunea acesteia
    - structura *Square* pentru un patrat. practic retine dimensiunea unui bloc si coordonatele coltului din stanga sus (x pentru rand si y pentru coloana)
    - structura *Tree* pentru un arbore cuaternar. retine tipul nodului, pointeri la nodurile din stanga sus, drepata sus, dreapta jos si stanga jos si un pixel RGB
    - enumeratia *options* pentru optiunile alese la rulare. am ales sac le folosesc asa pentru a avea un cod mai usor de inteles
    - structura *cerinta1* retine informatiile aferente primei cerinte: dimensiunea blocului maxim care nu a fost spart, numarul de blocuri si inaltimea arborelui. am ales sa folosesc o structura pentru a retine aceste informatii deoarece ele sunt calculate in acelasi timp in care este realizat arborele si mi-a fost mai usor sa le manipulez/returnez asa din functii.
    - structura *que_node* este o structura pentru o un nod dintr-o coada care va contine ca element un nod din quadtree
    - structura *queue* este o structura pentru o coada "clasica". are un field pentru un pointer la primul element, un pointer la ultimul element si un field pentru dimensiunea (lungimea) cozii

# Fisierele principale sunt main.c si functions.c in care e implementata tema. Celelalte fisiere contin functii ajutatoare pentru a avea un cod mai aerat

# In fisierul queue.c sunt implementate operatiile pe o coada, iar in fisierul queue.h se afla antetele acestor functii.

    - functia *create_queue* creeaza o coada (ii aloca memorie) si o initializeaza. returneaza coada creata
    - functia *init_node* creeaza un nod (ii aloca memorie) si il initializeaza cu nodul din quadtree primit ca parametru. returneaza nodul de coada creat
    - functia *empty_queue* verifica daca o coada est e goala (size=0). daca e goala returneaza 1, altfel returneaza 0
    - functia *enqueue* adauga un nou element in coada la final
    - functia *dequeue* elimina primul element din coada
    - functia *free_queue* elibereaza memoria pentru o coada

# In fisierul errors.c sunt implementate modurile in care sunt tratate erorile (ce mesaje se afiseaza), iar in fisierul errors.h se afla antetele acestor functii.

    - functia *error_f_in* cand fisierul de input nu se poate deschide
    - functia *error_f_out* cand fisierul de output nu se poate deschide
    - functia *error_invalid_option* cand optiunea la rulare nu este c1, c2 sau d
    - functia *error_factor* cand factorul e necorespunzator (negativ)
    - functia *error_arguments* cand s-a oferit un numar incorect de argumente (mai putin de 4 argumente sau mai mult de 5)
    - functia *error_ppm_type* cand fisierul ppm nu este de tip P6
    - functia *error_size* cand imaginea nu e patratica sau dimensiunea ei nu e putere a lui 2
    - functia *error_color* cand valoarea maxima pentru culoare nu este 255
    - functia *error_alocare_memorie* cand nu s-a putut aloca memorie
    - functia *error_fread* cand fisierul binar nu a fost creat corepsunzator

# In fisierul conditions.c sunt implementate conditii folosite in fisierul functions.c pe care am ales sa le implementez separat pentru a nu incurca codul. In fisierul conditions.h se afal antetele acestor functii

    - functia *options* coreleaza argumentul primit cu tipul de optiune. daca opiunea e valida returneaza optiunea, altfel returneaza -1
    - functia *ppm_type* verifica daca tipul fisierului ppm e P6. returneaza 0 si -1 altfel
    - functia *check_power_2* (folosita pentru dimensiunea imaginii) verifica daca un numar este puetere a lui 2. daca da returneaza 1, altfel returneaza 0;

# In fisierul functions.c sunt implementate functiile folosite pentru a realiza cerintele. In fisierul functions.h se afla antetele acestor functii

## Functiile pentru cerinta 2

    - functia *close_files* e folosita pentru a inchide toate fisierele deschise: input si output (nu returneaza nimic)
    - functia *create_image_matrix* aloca memorie pentru o matrice de pixeli de dimensiune size (primit ca argument, unsigned int). returneaza matricea creata
    - functia *free_image_matrix* elibereaza emmoria pentru o matrice iamgine creata (primita ca arguement). Nu returneaza nimic
    - functia *create_tree* creeaza un arbore cuaternar. Initializeaza primul nod cu un nod de tip frunza. Valorile pentru pixel-ul nodului sunt cele primite ca argument.
    - functia *mean_color* calculeaza culoarea medie dintr-un bloc al amtricei imagine. Blocul e reprezentat prin coordonatele coltului din stanga sus si dimensiunea acestuia. Primeste ca argumente o matrice imagine si un bloc si returneaza un pixel cu valorile medii ale culorilor
    - functia *similarity_score* calculeaza scorul de similaritate dintr-un bloc. Primeste ca argumente matricea imagine, blocul in care se calculeaza scorul si pixel-ul cu valorile medii ale culorilor. Calculeaza scorul si il returneaza. 
    - functiile split despart un bloc in 4 blocuri dupa cum urmeaza (toate primesc ca parametru un bloc orginal si returneaza blocul rezultat dupa divizare):
        - *split_left_up* returneaza blocul din stanga sus (coordonatele colutlui din stanga sus si dimensiunea)
        - *split_right_up* returneaza blocul din dreapta sus (coordonatele colutlui din stanga sus si dimensiunea)
        - *split_right_down* returneaza blocul din dreapta jos (coordonatele colutlui din stanga sus si dimensiunea)
        - *split_left_down* returneaza blocul din stanga jos (coordonatele colutlui din stanga sus si dimensiunea)
    - functia *construct_tree* contruieste un arbore de compresie si preia informatiile necesare pentru prima cerinta (este o functie recursiva). Primeste ca parametrii: radacina arborelui cuaternar (sau nodul pentru care se fac calculele), matricea imagine, blocul actual pentru care se fac calculele, o variabila check pentru erori (daca check nu e 0 la final inseamna ca s-au intampinat erori), o structura info cu informatiile aferente primei cerinte si factorul. Daca scorul de similitudine este corespunzator, se mareste numarul de frunze si se verifica daca blocul actual este mai mare decat blocul de dimensiune maxima retinut pana la momentul respectiv. Daca scorul nu e corespunzator, se divizeaza blocul actula in 4 blocuri cu functiile split si se foloseste functia *construct_tree* pentru acelea
    - functia *free_tree* elibereaza memroia (recursiv) alocata pentru un arbore cuaternar (primit ca argument). Nu returneaza nimic
    - functia *initiate_c1_info* initializeaza valorile din structura cu informatiile aferente pentru prima cerinta (toate sunt 0). Nu reeturneaza nimic
    - functia *make_compression_tree* se foloseste de functia construct_tree pentru a realiza arborele cuaternar. Primeste ca parametrii o matrice imagine, adresa structurii cu informatiile pentru prima cerinta si factorul. Returneaza arborele creat.
    - functia *maximum* returneaza maximul dintre doua numere primite ca parametru
    - functia *tree_depth* calculeaza ianltimea arborelui cuaternar (recursiv)
    - functia *print_node* printeaza un nod (primit ca argument) in fisierul binar primit ca argument. Nu returneaza nimic
    - functia *print_current_level* primeste ca parametrii fisierul de output, arborele si nivelul care se doreste a fi printat si printeaza nodurile de pe acel nivel in ordine. Nu returneaza nimic
    - functia *print_in_level_order* priemeste ca parametru un fisier de output si arborele cuaternar si printeaza nodurile din arbore in ordinea nivelelor. Nu returneaz nimic

## Functiile pentru cerinta 3

    - functia *insert_node* se foloseste de o coada pentru a insera nodurile citite din fisierul binar in arborele cuaternar. Primeste ca parametrii arborele, nodul care se doreste a fi inserat, coada cu nodurile care asteapta sa fie introduse si un contor check pentru erori. Returneaza arborele cu noul nod inserat
    Mica explicatie pentru cum am folosit coada:
    Cand se adauga un nod in tree acesta este adaugat automat in coada. Daca coada are deja un nod se verfiica daca nodurile stanga sus, dreapta sus, drepata jos, stanga jso sunt goale sau nu. Daca nodurile respective sunt goale, se adauga nodul acolo. Odata ce s-au ocupat toate cele 4 noduri fii pentru nodul curent, acesta se scoate din coada. Orice nou nod adaugat in tree este adaugat la finalul cozii.
    - functia *read_and_make_tree* citeste arborele printat la cerinta 2 in fisierul binar si il reface cu ajutorul functiei descrise anterior. Primeste ca argumente fisierul binar cu arborele si un contor check pentru erori. Returneaza arborele
    - functia *put_block_in_matrix* insereaza un bloc de culaore in amtricea imagine cu valorile de la nodul corespunztor bloculuui. Primeste ca argumente matrice imagine, nodul si blocul si nu returneaza nimic.
    - functia *decompression* trasnforma arborele cuaternar in mtricea imagine. Primeste ca argumente matricea imagine, arborele si un bloc si introduce recursiv blocurile corespunzatoare nodurilor in matrice. Nu returneaza nimic
    - functia *make_matrix_from_tree* sef oloseste de functia recursiva decompression pentru a realiza matricea imagine 

# In fisierul main.c este implementata tema

    - Daca sunt 5 argumente inseaman ca este vorba despre cerintele 1 si 2 si se preiau argumentele pentru f_in si f_out (arg 3 si 4) si factor (arg 2). Daca sunt 4 argumente este vorba despre cerinta 3 si se preiau argumentele pentru f_in si f_out (arg 2 si 3). Daca nu se respecta numarul de argumente se afiseaza eroare.
    - Daca optiunea nu e -c1 , -c2 sau -d se afiseaza eroare

### Cerinta 2:

    - Se printeaza dimensiunea imaginii in fisierul binar ssi apoi se printeaza si arborele in ordinea nivelelor

### Cerinta 3:

    - Se citeste dimensiunea imaginii, apoi se citeste si se realizeaza arborele
    - Se creeaza si matricea imagine cu ajutorul arborelui
    - Se printeaza specificatiile necesare pentru fisierul .ppm, iar apoi se printeaza si pixelii din matricea imagine

    Se elibereaza memoria si se iese din program

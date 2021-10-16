CIUREA Robert-Mihai - 313CBb
87/135

                            Tema2-SD (Netflix)

Scopul temei il constituie implementarea functionalitatilor de baza alei
platformei Netflix. Astfel pentru inceput au necesare implementarea mai multor
structuri de date precum vectorul de liste in care fiecare lista retinea
serialele dintr-o categorie de seriale, pentru ca mai apoi sa avem coada de
watch_later, stiva de currently watching si stiva history. Un serial era compus
din nume, rating, durata totala a unui serial, numar de sezoane si coada de
sezoane in care fiecare sezon era compus din numaru de episoada si coada care
retinea durata fiecarui episod. Inainte de a se putea incepe lucrul efectiv la
program, au fost necesare anumite implementari de baza, si anume functii ce permit
efectuarea de operatii pentru liste, cozi si stive. Astfel au fost implementate
functii de initializare de lista, creare de nod, adaugare de elemente in lista,
aflarea pozitiei unui anumit nod ce reprezeinta un seria, aflarea dimensiunii unei
liste si eliminarea primului nod dintr-o lista. Legat de stive si cozi, rolurile
functiilor sunt destul de similare, astfel avem initializarea unei astfel de
structuri de date, introducere de element nou, eliminare de element, mutare element
dintr-o structura de date in alta de acelas tip, afisare de structura de date.
In plus la stive fata de cozi exista o functie care determina dimensiunea unui stack.

Legat de implementarea efectiva a programului, in main.c are au loc citirile
necesare din fisier pentru realizarea tuturor task-urilor aferente temei, si
in functie de primul cuvant citit de pe fiecare linie din input se decide ce
functie urmeaza a fi apelata pentru a permite realizarea operatiilor pe
structurile de date necesare indeplinirii obiectivului.

Pentru adaugarea de serial in categoria sa aferenta, se citeste id-ul serialului
pentru a se accesa lista aferenta categoriei din care trebuie sa faca pentru si
dupa ulterior se apeleaza functia create_serial prin intermediul careia sunt
citite toate datele ce corespund unui anumit serial pentru ca ulterior sa se
creeze nodul ce va retine toata informatia unui serial pentru ca ulterior sa se
introduca corespunzator in categoria de seriale, tinandu-se cont ca fiecare
categorie, in afara de top10 trebuie sa fie sortata descrescator dupa rating,
iar in caz de egalitate de rating, alfabetic dupa nume.

Functia add_top este functia creata exclusiv pentru adaugarea serialelor in
categoria top10. Astfel ca se acceseaza pozitia unde urmeaza sa fie introdus
noul serial, si in cazul in care deja exista un serial acolo, toate serialele
de la acel nod in jos sunt mutate cu cate un nod la dreapta, iar in cazul in
care categoria top10 este deja plina si un serial nu mai are loc in categorie,
intreaga memorie legata de acel serial este eliberata intrucat nu mai este
necesara retinerea informatiilor legate de acel serial.

Functia ce adauga un sezon nou pentru inceput apeleaza functia create_season
ce citeste toate datele aferente unui sezon, dupa care acceseaza toate
categoriile de seriale pentru a identifica nodul in care se afla serialul
caruia i-a mai aparut un sezon pentru a-l adauga in structura. La final se
incrementeaza variabila all_time ce retine durata totala a unui sezon.

Functia later citeste numele serialului ce urmeaza a fi introdus in coada
watch_later cauta in toate categoriile de seriale numele serialuli cautat
astfel incat sa se dea enqueue informatieie din nodul gasit si eliminarea
nodului din lista, fara a aduce alte modificari la continutul listei. In
plus se si elibereaza memoria nodului ce candva retinea informatiile
legate de serial. Insa, daca se face discutie legata de categoria top10,
daca acolo se regaseste serialul ce urmeaza a fi introdus in coada
watch_later, atunci nu se mai elibereaza memoria nodului si in plus,
toate serialele de sub serialul ce a fost adaugat in coada respectiva
sunt urcate un nivel mai sus categoria top10.

Functia show citeste numele structurii de date ce urmeaza a fi afisata
in fisierul de output, pentru ca ulterior sa se parcurga intreaga
structura de date, din care se acceseaza numele serialului si rating-ul
acestuia pentru a fi afisate in fisierul de output. Daca structura de
date respectiva este goala, atunci se afiseaza un output aferent ce
surprinda caracteristica de structura fara date.

Functia watch chiar daca nu este functionala, urmeza sa descriu care
a fost gandirea din spatele a ceea ce am incercat sa fie functie ce
suprindea vizionarea partiala sau totala a unui serial. Pentru inceput
se citesc numele serialului, respectiv durata in timp pentru care urma
sa aiba loc vizionarea. Dupa care pentru inceput cautam in toate
categoriile de seriale serialul ce urmeaza a fi vizionat. Daca acesta
este gasit, acesta este introdus in stack-ul currently_watching pentru
ca ulterior sa aiba loc vizionarea serialului. Insa, daca serialul nu a
fost gasit, se cauta mai departe in categoria watch_later. Daca se
gaseste aici serialul dorit, acesta este introdus in stiva
currently_watching si se elimina din coada din care a facut inainte parte.
De aici, stim sigur ca serialul dorit se afla in stack-ul
currently_watching asa ca incercam sa-l identificam in stiva si odata ce
a fost gasit, se scade durata acestuia decrementand variabila all_time cu
un numar de unitati egal cu durata citita initial ca data de intrare,
odata ce a avut loc decrementarea, se verifica daca durata nu a ajuns
valoare negativa, iar in caz afirmativa se muta serialul in stiva history
si se afiseaza in fisierul de output faptul ca serialul s-a terminat de
vizionat. Daca serialul nu a fost gasit ca fiind cel mai de sus element al
stivei, atunci aducem serialul deasupra tuturor celorlalte elemente din stiva.
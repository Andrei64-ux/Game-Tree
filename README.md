Pentru implementarea acestei teme mi-am creat mai multe biblioteci ajutatoare si , de altfel , mai multe surse . Atat sursele "DoublyLinkedList.c" si "Node.c" , cat si head-urile "DoublyLinkedList.h" si "Node.h" au fost preluate din implementarea temei 1. In acestea am ales sa pastrez structura de lista si cateva din functiile caracteristice lor , pe care le-am folosit la task-ul 3 . Pe langa acestea , am implementat si un header "tree.h" unde pastrez structura de arbore . In "tree.c" am functia de initializare , cea de adaugare fii la arbore si cea de eliberare memorie . Am creat o biblioteca "tasks.h" unde pastrez structura pentru jocul de "X si O" cat si pentru "Minimax" , dar si antetele a 3 functii din "tasks.c" , functii in care se ajunge la rezolvarea celor 3 task-uri . 
    
Am creat o functie care schimba jucatorul in functie de cel care deja se afla in postura de jucator care trebuie sa faca o "mutare" . Urmeaza o functie care verifica momentul in care jocul este gata , atunci cand unul dintre jucatori castiga si cand se realizeaza conditia de victorie din joc . In functia "create_states" imi creez o stare de joc , verifica daca jocul s-a terminat care ar fi castigatorul in cazul acesta . Daca se gaseste caracterul '-' pe tabla de joc , se schimba playerul , se creste adancimea si se adauga un nou fiu. Daca radacina nu are niciun fiu se considera ca joc pierdut . Am mai facut 2 functii pentru a printa o stare si apoi pentru mai multe stari .

La task-ul 2 m-am folosit de functia "create_states" si am mai facut 2 functii care face printare doar pentru o valoare si apoi pentru toate valorile de T/F. In functie de jucatorul care se afla in starea respectiva am facut fie un sau logic , "|=" , fie un si logic , "&=" intre fiii din stare . Pentru task-ul 3 am creat o functie care verifica urmatorul caracter ; daca se gaseste '[' inseamna ca este un nod frunza care pastreaza adancimea si numarul de fii este 0 , iar daca se gaseste '(' citim numarul de fii , pastram adancimea , iar valoarea din nod nu este semnificativa . Pentru a crea jocul "Minimax" am folosit o coada si oarecum am facut o parcurgere pe latime prin fiii radacinei . In final , pentru task-ul 3 am creat functii care rezolva jocul si printeza rezultatul in fisier. Am mai creat 2 functii auxiliare min si max care in functie de paritatea adancimii din stare calculeaza noua valoare pentru starea data .

In main am deschis si inchis fisierele si am apelat functiile , in functie de comanda primita ca argument in linia de comanda . 
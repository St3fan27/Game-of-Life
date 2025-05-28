Game of Life – Proiect PA

STRUCTURĂ FIȘIERE:
- main.c               – Fișierul principal (funcția main), citește inputul și rulează task-urile.
- task1.c / task1.h    – Regulile standard Game of Life.
- task2.c / task2.h    – Salvarea diferențelor între generații (stivă) + operația bonus de revenire.
- task3.c / task3.h    – Arbore binar al generațiilor (regulă alternativă la stânga, regula standard la dreapta).
- task4.c / task4.h    – Calcularea celui mai lung lanț Hamiltonian în componentele de celule vii.
- Makefile             – Script de compilare.
- input.txt            – Fișier de intrare.
- output.txt           – Fișier de ieșire generat.

DESCRIERE TASK-URI:
TASK 1 – Generarea regulilor standard (Conway)
- Aplică regulile clasice:
    Celulă vie cu 2 sau 3 vecini rămâne vie.
    Celulă moartă cu exact 3 vecini devine vie.
    În rest, celula devine sau rămâne moartă.

TASK 2 – Salvarea diferențelor + bonus (revers)
- Salvează doar celulele care își schimbă starea între generații.
- Se folosește o stivă (`Node`) pentru urmărirea modificărilor.
- Bonus: se pot inversa pașii înapoi pentru a reveni la o stare anterioară.

TASK 3 – Arbore binar de generații
- Se construiește un arbore binar în care:
    Stânga: generație după regulă alternativă.
    Dreapta: generație după regulile clasice.
- Arborele se parcurge în preordine și se salvează în output.txt.

TASK 4 – Lanț Hamiltonian
- Se identifică componentele conexe de celule vii (vecini direcți/diagonali).
- Pentru fiecare componentă mică (≤ 16 celule), se caută un lanț Hamiltonian folosind DFS.
- Dacă se găsește, se afișează lungimea și traseul:
    Exemplu:
    4
    (1,1) (1,2) (1,3) (1,4) (1,5)
- Dacă nu există un lanț valid, se scrie: -1

STRUCTURI DE DATE FOLOSITE:
- Coord      – stochează coordonatele unei celule (rând, coloană).
- Node       – nod din stivă pentru salvarea diferențelor.
- TreeNode   – nod pentru arborele binar al generațiilor.
- Matrice adjacenta, vectori vizitat/path – pentru DFS în Task 4.


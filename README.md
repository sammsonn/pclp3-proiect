# Proiect PCLP3 - Autocomplete

## Descriere

- Pentru acest proiect am folosit 5 funcții principale, prima pentru căutare, a
  doua pentru a verifica dacă trebuie căutat, a treia pentru adăugare de cuvânt,
  a patra pentru a verifica existența, iar a cincea pentru a găsi cuvântul
  potrivit din dicționar.

- Funcția de căutare parcurge dicționarul pentru a verifica dacă cuvântul
  aparține măcar unui cuvânt din dicționar.

- Funcția de verificare vede dacă cuvântul este sau nu un semn de punctuație.

- Funcția de adăugare cuvânt adaugă un cuvânt nou în dicționar.

- Funcția de existență verifică dacă cuvântul apare deja în dicționar în forma
  sa, și dacă apare deja îi crește prioritatea.

- Funcția de potrivire parcurge dicționarul pentru a găsi cel mai potrivit
  cuvânt.

- În funcția main se citesc datele de intrare, se parcurg cuvintele introduse de
  utilizator și în funcție de forma lor sunt apelate funcțiile corespunzătoare.
  Se verifică dacă au '*' la final, dacă sunt semne de punctuație, dacă
  corespund unui cuvânt din dicționar etc și pentru fiecare cuvânt ori este
  afișat cuvântul în sine, ori cel mai potrivit cuvânt din dicționar.

## Comentarii asupra proiectului

- Implementarea mi se pare destul de bună, am reușit să nu am leak-uri de
  memorie, dar sigur era posibil să fie și mai eficientă sau mai scurtă. Totuși
  sunt mulțumit cu această rezolvare.

- Proiectul acesta mi-a aprofundat cunoștințele în limbajul C, încercând să
  acopăr cât mai mult concepte predate la curs.

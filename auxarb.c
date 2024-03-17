/* SIMION GEORGE-VLAD 312CB */
/*--- auxarb.c --- functii de afisare si constructie arbore */
#include <stdarg.h>
#include <time.h>

#include "tarb.h"

TArb_director ROOT() { /* functie de creare a root-ului */
  TArb_director root = malloc(sizeof(TNod_director));
  if (!root) {
    DistrFinala_d(&root);
    return NULL;
  }
  root->nume = strdup("root");
  root->st = NULL;
  root->dr = NULL;
  root->directories = NULL;
  root->fisier = NULL;
  return root;
}

int Inserare_ABC_f(TArb_fisier* c_fisiere, char* nume, TArb_director* curent,
                   TArb_director c_directoare) {
  TArb_fisier aux, p, n;

  while (c_directoare) { /* verific daca exista un director cu numele dat */
    if (strcmp(nume, c_directoare->nume) == 0) {
      printf("Directory %s already exists!\n", nume);
      return 0;
    }
    if (strcmp(nume, c_directoare->nume) <
        0) { /* aleg eficient unde ma duc mai departe */
      c_directoare = c_directoare->st;
    } else {
      c_directoare = c_directoare->dr;
    }
  }

  if (*c_fisiere == NULL) { /* daca directorul in care ma aflu nu are fisiere,
                               creez radacina */
    *c_fisiere = ConstrFr_f(nume, curent);
    if (!*c_fisiere) return 0;
    return 1;
  }

  n = *c_fisiere;

  while (n) { /* verific daca exista un fisier cu numele dat */
    p = n;
    if (strcmp(nume, n->nume) == 0) {
      printf("File %s already exists!\n", nume);
      return 0;
    }
    if (strcmp(nume, n->nume) < 0) { /* aleg eficient unde ma duc mai departe */
      n = n->st;
    } else {
      n = n->dr;
    }
  }

  aux = ConstrFr_f(nume, curent); /* construiesc fisierul */
  if (!aux) return 0;

  if (strcmp(nume, p->nume) <
      0) { /* aleg corespunzator in ce zona va fi plasat fisierul */
    p->st = aux;
  } else {
    p->dr = aux;
  }
  return 1;
}

int Inserare_ABC_d(TArb_director* c_directoare, char* nume,
                   TArb_director* curent, TArb_fisier c_fisiere) {
  TArb_director aux, p, n;

  while (c_fisiere) { /* verific daca exista un fisier cu numele dat */
    if (strcmp(nume, c_fisiere->nume) == 0) {
      printf("File %s already exists!\n", nume);
      return 0;
    }
    if (strcmp(nume, c_fisiere->nume) <
        0) { /* aleg eficient unde ma duc mai departe */
      c_fisiere = c_fisiere->st;
    } else {
      c_fisiere = c_fisiere->dr;
    }
  }

  if (*c_directoare == NULL) { /* daca directorul in care ma aflu nu are
                                  directoare, creez radacina */
    *c_directoare = ConstrFr_d(nume, curent);
    if (!*c_directoare) return 0;
    return 1;
  }

  n = *c_directoare;
  while (n) { /* verific daca exista un director cu numele dat */
    p = n;
    if (strcmp(nume, n->nume) == 0) {
      printf("Directory %s already exists!\n", nume);
      return 0;
    }
    if (strcmp(nume, n->nume) < 0) { /* aleg eficient unde ma duc mai departe */
      n = n->st;
    } else {
      n = n->dr;
    }
  }

  aux = ConstrFr_d(nume, curent); /* construiesc directorul */
  if (!aux) return 0;

  if (strcmp(nume, p->nume) <
      0) /* aleg corespunzator in ce zona va fi plasat fisierul */
    p->st = aux;
  else
    p->dr = aux;
  return 1;
}

int touch(TArb_director* director,
          char* nume) { /* functie de creare a unui fisier */
  Inserare_ABC_f(&((*director)->fisier), nume, &(*director),
                 (*director)->directories);
  return 1;
}

int mkdir(TArb_director* director,
          char* nume) { /* functie de creare a unui director */
  Inserare_ABC_d(&(*director)->directories, nume, &(*director),
                 (*director)->fisier);
  return 1;
}

void AfiArb_d(
    TArb_director r) /* afiseaza arborele de directoare r (parcurgere SRD) */
{
  if (r != NULL) {
    AfiArb_d(r->st);
    printf("%s ", r->nume);
    AfiArb_d(r->dr);
  }
}

void AfiArb_f(
    TArb_fisier r) /*- afiseaza arborele de fisiere r (parcurgere SRD) */
{
  if (r != NULL) {
    AfiArb_f(r->st);
    printf("%s ", r->nume);
    AfiArb_f(r->dr);
  }
}

TArb_fisier minim_lexicografic_f(
    TArb_fisier fisier) { /* cautarea fisierului cel mai mic din punct de vedere
                             lexicografic */
  if (fisier == NULL) {
    return fisier;
  }
  while (fisier) { /* parcurg pana la frunza cea mai din stanga */
    if (fisier->st == NULL) {
      return fisier;
    }
    fisier = fisier->st;
  }
  return fisier;
}

TArb_director minim_lexicografic_d(
    TArb_director fisier) { /* cautarea directorului cel mai mic din punct de
                               vedere lexicografic */
  if (fisier == NULL) {
    return fisier;
  }
  while (fisier) { /* parcurg pana la frunza cea mai din stanga */
    if (fisier->st == NULL) {
      return fisier;
    }
    fisier = fisier->st;
  }
  return fisier;
}

TArb_fisier rm(TArb_fisier* fisiere,
               char* nume) { /* functie de stergere a unui fisier */
  if (*fisiere == NULL) {    /* caz in care comanda nu e buna */
    printf("File %s doesn't exist!\n", nume);
    return *fisiere;
  } else if (strcmp(nume, (*fisiere)->nume) <
             0) { /* ma uit eficient in care zona a arborelui caut fisierul */
    rm(&(*fisiere)->st, nume);
  } else if (strcmp(nume, (*fisiere)->nume) > 0) {
    rm(&(*fisiere)->dr, nume);
  } else { /* am gasit fisierul si acum verific de ce tip este */
    if ((*fisiere)->st == NULL &&
        (*fisiere)->dr == NULL) { /* frunza sau radacina fara copii */
      DistrFinala_f(&(*fisiere));
      return *fisiere;
    }
    if ((*fisiere)->st != NULL &&
        (*fisiere)->dr == NULL) { /* caz cand are un copil la stanga */
      TArb_fisier aux = *fisiere;
      *fisiere = (*fisiere)->st;
      DistrFinala_f(&(aux));
      return *fisiere;
    }
    if ((*fisiere)->st == NULL &&
        (*fisiere)->dr != NULL) { /* caz cand are un copil la dreapta */
      TArb_fisier aux = *fisiere; /* preiau informatia pentru a o distruge */
      *fisiere =
          (*fisiere)->dr;    /* nodul va prelua informatia copilului drept */
      DistrFinala_f(&(aux)); /* distrug fostul nod/fisierul */
      return *fisiere;
    }
    if ((*fisiere)->st != NULL &&
        (*fisiere)->dr != NULL) { /* caz cand are doi copii */
      TArb_fisier aux = minim_lexicografic_f(
          (*fisiere)->dr); /* caut in subarborele respectiv frunza din stanga */
      strcpy((*fisiere)->nume,
             aux->nume); /* preia doar numele pastrand stanga si dreapta */
      rm(&((*fisiere)->dr), aux->nume); /* cauta elementul de unde am preluat
                                           numele pentru a il sterge */
    }
  }
  return *fisiere;
}

TArb_director rmdir(TArb_director* director,
                    char* nume) { /* functie de stergere a unui director, analog
                                     cu functia rm cu un detaliu diferit */
  if (*director == NULL) {
    printf("Directory %s doesn't exist!\n", nume);
    return *director;
  } else if (strcmp(nume, (*director)->nume) < 0) {
    rmdir(&(*director)->st, nume);
  } else if (strcmp(nume, (*director)->nume) > 0) {
    rmdir(&(*director)->dr, nume);
  } else {
    if ((*director)->st == NULL && (*director)->dr == NULL) {
      DistrFinala_d(&(*director));
      return *director;
    }
    if ((*director)->st != NULL && (*director)->dr == NULL) {
      TArb_director aux = *director;
      *director = (*director)->st;
      DistrFinala_d(&(aux));
      return *director;
    }
    if ((*director)->st == NULL && (*director)->dr != NULL) {
      TArb_director aux = *director;
      *director = (*director)->dr;
      DistrFinala_d(&(aux));
      return *director;
    }
    if ((*director)->st != NULL && (*director)->dr != NULL) {
      TArb_director aux = minim_lexicografic_d((*director)->dr);
      strcpy((*director)->nume, aux->nume);
      (*director)->fisier =
          aux->fisier; /* mut arborele de fisiere in cel corespunzator */
      (*director)->directories = aux->directories; /* mut arborele de directoare
                                                      in cel corespunzator */
      rmdir(&((*director)->dr), aux->nume);
    }
  }
  return *director;
}

int CD(TArb_director curent_r, TArb_director root, TArb_director* curent,
       char* nume, int ok) { /* functie de schimbare a directorului curent */
  if (strcmp(nume, "..") ==
      0) { /* tratez cazul de a ma intoarce la folderul parinte */
    if (strcmp((*curent)->nume, root->nume) !=
        0) { /* daca nu ma aflu in root, cazul este valid */
      *curent = (*curent)->parinte; /* ma intorc la parinte */
      ok = 1; /* ok are rolul de a imi confirma ca s-a produs operatia de
                 schimbare */
      return 1;
    } else
      return 2; /* ma aflu in root deci raman in root */
  }

  if (curent_r != NULL &&
      ok == 0) { /* daca inca nu am gasit si arborele nu este null */
    if (strcmp(curent_r->nume, nume) ==
        0) { /* verific in nodul in care ma aflu daca are numele coresp. */
      *curent = curent_r;
      ok = 1;
      return 1;
    }

    if (strcmp(curent_r->nume, nume) >
        0) { /* aleg in ce zona a arborelui/subarborelui ma indrept folosind
                functia in mod recursiv */
      return CD(curent_r->st, root, &(*curent), nume, ok);
    } else {
      return CD(curent_r->dr, root, &(*curent), nume, ok);
    }
  }

  return 0;
}

void PWD(TArb_director root,
         TArb_director curent) { /* functie de afisare pentru calea absoluta */
  char** cale =
      malloc(1000 * sizeof(char*)); /* creez un vector de string-uri */

  int index, contor = 0;

  if (curent->parinte) {
    do {
      index = contor;
      cale[index] =
          malloc(sizeof(char) *
                 strlen(curent->nume)); /* aloc spatiu necesar elementului */
      strcpy(cale[index], curent->nume);
      curent = curent->parinte; /* trec la urmatorul parinte/trec la urmatorul
                                   element din vector daca mai exista */
      contor++;
    } while (root != curent);
    printf("/%s", root->nume);
    for (index = contor - 1; index >= 0;
         index--) { /* parcurg descrescator pentru am stocat parintii de la
                       curent pana la root */
      printf("/%s", cale[index]);
    }
  } else { /* daca ma aflu in root */
    printf("/%s", root->nume);
  }
  free(cale);
  printf("\n");
}
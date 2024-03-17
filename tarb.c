/* SIMION GEORGE-VLAD 312CB */
/*--- tarb.c --- operatii cu arbori binari --*/
#include "tarb.h"

TArb_director ConstrFr_d(
    char* nume,
    TArb_director* parinte) { /* functia efectiva de creare a unui director */
  TArb_director aux = (TArb_director)malloc(sizeof(TNod_director));
  if (!aux) {
    DistrFinala_d(&aux);
    return NULL;
  }
  aux->nume = strdup(nume); /* copiez informatia */
  aux->st = aux->dr = NULL;
  aux->directories = NULL;
  aux->parinte = *parinte; /* ii setez parintele */
  aux->fisier = NULL;

  return aux;
}

TArb_fisier ConstrFr_f(
    char* nume,
    TArb_director* parinte) /* functia efectiva de creare a unui fisier */
{
  TArb_fisier aux = malloc(sizeof(TNod_fisier));
  if (!aux) {
    DistrFinala_f(&aux);
    return NULL;
  }

  aux->nume = strdup(nume); /* copiez informatia */
  aux->st = aux->dr = NULL;
  aux->parinte = *parinte; /* ii setez parintele */

  return aux;
}

void distruge_d(TArb_director r) /* functie de distrugere a unui director */
{
  if (!r) return;
  free(r->nume);
  free(r->fisier);
  free(r); /* distruge nodul radacina */
}

void distruge_f(TArb_fisier r) /* functie de distrugere a unui fisier */
{
  if (!r) return;
  free(r->nume);
  free(r);
}

void DistrFinala_d(
    TArb_director* a) /* functie care apeleaza distrugerea unui director */
{
  if (!(*a)) return; /* nod deja vid */
  distruge_d(*a);    /* distruge informatia nodului */
  *a = NULL;         /* nodul este vid */
}

void DistrFinala_f(
    TArb_fisier* a) /* functie care apeleaza distrugerea unui fisier */
{
  if (!(*a)) return; /* nod deja vid */
  distruge_f(*a);    /* distruge informatia nodului */
  *a = NULL;         /* nodul este vid */
}
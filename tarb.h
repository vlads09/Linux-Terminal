/*--- tarb.h ---*/
/* SIMION GEORGE-VLAD 312CB */
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef ARBORE_BINAR
#define ARBORE_BINAR

typedef struct nod_director {
  char* nume;
  struct nod_fisier* fisier;
  struct nod_director* parinte;
  struct nod_director* directories;
  struct nod_director *st, *dr;
} TNod_director, *TArb_director, **AArb_director;

typedef struct nod_fisier {
  char* nume;
  struct nod_director* parinte;
  struct nod_fisier *st, *dr;
} TNod_fisier, *TArb_fisier, **AArb_fisier;

TArb_director ConstrFr_d(char*, TArb_director*);
TArb_fisier ConstrFr_f(char*, TArb_director*);
void DistrFinala_d(AArb_director);
void DistrFinala_f(AArb_fisier);

TArb_director ROOT();
int touch(TArb_director*, char*);
int mkdir(TArb_director*, char*);

void AfiArb_d(TArb_director);
void AfiArb_f(TArb_fisier);

TArb_fisier rm(TArb_fisier*, char*);
TArb_director rmdir(TArb_director*, char*);

int CD(TArb_director, TArb_director, TArb_director*, char*, int);
void PWD(TArb_director, TArb_director);

#endif

#ifndef _random_
#define _random_
#define random(n) (rand() % (n))
#define randomize() (srand((unsigned int)time(NULL)))
#endif

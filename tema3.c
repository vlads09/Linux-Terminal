/* SIMION GEORGE-VLAD 312CB */
#include "tarb.h"

int main() {
  TArb_director arbore_root = ROOT();
  TArb_director director_curent;

  size_t len = 0;
  char* line = NULL;
  int while_quit = 0;
  char* instructiune = NULL;

  director_curent = arbore_root;

  while (while_quit == 0 && getline(&line, &len, stdin) != -1) {
    instructiune = strtok(line, " \n");

    if (strcmp(instructiune, "touch") == 0) {
      char* nume_fisier = strtok(NULL, " \n");
      /* apel functie touch */
      touch(&director_curent, nume_fisier);
    }

    if (strcmp(instructiune, "mkdir") == 0) {
      char* nume_director = strtok(NULL, " \n");
      /* apel functie mkdir */
      mkdir(&director_curent, nume_director);
    }

    if (strcmp(instructiune, "ls") == 0) {
      /* apel functie ls */
      AfiArb_d(director_curent->directories);
      AfiArb_f(director_curent->fisier);
      printf("\n");
    }

    if (strcmp(instructiune, "rm") == 0) {
      char* nume_fisier = strtok(NULL, " \n");
      /* apel functie rm */
      rm(&(director_curent->fisier), nume_fisier);
    }

    if (strcmp(instructiune, "rmdir") == 0) {
      char* nume_director = strtok(NULL, " \n");
      /* apel functie rmdir */
      rmdir(&(director_curent->directories), nume_director);
    }

    if (strcmp(instructiune, "cd") == 0) {
      char* nume_director = strtok(NULL, " \n");
      /* apel functie cd */
      int ok = CD(director_curent->directories, arbore_root, &director_curent,
                  nume_director, 0);
      if (ok == 0) {
        printf("Directory not found!\n");
      }
    }

    if (strcmp(instructiune, "pwd") == 0) {
      /* apel functie pwd */
      PWD(arbore_root, director_curent);
    }

    if (strcmp(instructiune, "find") == 0) {
      continue;
    }

    if (strcmp(instructiune, "quit") == 0) {
      while_quit = 1;
      DistrFinala_f(&arbore_root->fisier);
      DistrFinala_d(&arbore_root);
    }
  }
  free(line);
  return 0;
}
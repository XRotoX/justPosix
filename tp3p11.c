#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


//La fonction du thread
void* lire_entier(void *arg) {
  int un_entier;
  int val_arg = (int) arg;
  printf("Bienvenue chez le thread ayant comme argument %d\n", val_arg);
  printf("Priere de saisir un entier: ");
  scanf("%d", &un_entier);
  pthread_exit((void *) un_entier); 
}//fin lire_entier

void* printDecValue(void *arg){
    printf("[I] Vous avez lu une valeur decimale egale a: %d\n", (int) arg);
    pthread_exit((void *)0);
}


void* printHexaValue(void *arg){
    printf("[I] Vous avez lu une valeur hexadecimale egale a: %x\n", (int) arg);
    pthread_exit((void *)0);
}

void* printOctalValue(void *arg){
    printf("[I] Vous avez lu une valeur octale egale a: %o\n", (int) arg);
    pthread_exit((void *)0);
}

int main(void) {
  clock_t begin_execution = clock();

  int i, val_retour;
  pthread_t thread0, thread1, thread2, thread3;
  srand(time(NULL));
  i = 1 + rand() % 100;

  clock_t begin_reading = clock();

  int read_success = pthread_create(&thread1, NULL, lire_entier, (void *) i);

  if (read_success) {
    fprintf(stderr, "[E] Erreur de creation du thread de lecture.");
    exit(0);
  }
   
  //Attente du thread de lecture
  pthread_join(thread1, (void *)&val_retour); 
  
  clock_t end_reading = clock();

  clock_t begin_printing = clock();
   
  int decSuccess = pthread_create(&thread1, NULL, printDecValue, (void *) val_retour);
  int octSuccess = pthread_create(&thread2, NULL, printHexaValue, (void *) val_retour);
  int hexadecSuccess = pthread_create(&thread3, NULL, printOctalValue, (void *) val_retour);
  
  if (decSuccess != 0 && octSuccess !=0 && hexadecSuccess != 0) {
    fprintf(stderr, "[E] Erreur de creation d'un thread d'affichage.");
    exit(0);
  }//fin if (succes != 0)

  //Attente des threads d'affichage
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL); 

  clock_t end_printing = clock();
  
  clock_t end_execution = clock();
  
  printf("[I] Function execution finished successfully.\n");
  double time_spent_execution = (double)(end_execution - begin_execution) / CLOCKS_PER_SEC;
  double time_spent_reading = (double)(end_reading - begin_reading) / CLOCKS_PER_SEC;
  double time_spent_printing = (double)(end_printing - begin_printing) / CLOCKS_PER_SEC;
  printf("[I] Execution time info:\n");
  printf("[-] Execution elapsed time: %f second.\n", time_spent_execution);
  printf("[-] Reading elapsed time: %f second.\n", time_spent_reading);
  printf("[-] Printing elapsed time: %f second.\n", time_spent_printing);
  return 0;
}//fin main()

/* // */
/* // lab 2 */
/* // winter 2023 */
/* // name: Benjamin Banh */
/* // */
/* //  includes	 */

/* #include <stdio.h> */
/* #include <string.h> */

/* int main (void); */
/* void insert(); */
/* void list(); */
/* void list_hour(); */
/* char tasks[10][10]; */
/* int hours[10]; */
/* int counter = 0; */

/* int main (void){ */
/* 	int option; */
/* 	while (1){ */
/* 		printf ("Enter option\n"); */
/* 		if (scanf ("%d", &option) != 1){ */
/* 			printf ("error\n"); */
/* 			return 0; */
/* 		} */

/* 		switch (option){ */
			
/* 			//insert */
/* 			case 1: */
/* 			    insert(); */
/* 			    break; */
/* 			//list */
/* 			case 2:		 */
/* 			    list(); */
/* 			    break; */
/* 			//list_hour */
/* 			case 3: */
/* 			    list_hour();   */
/* 			    break; */
/* 			case 0: */
/* 			    printf ("exit\n"); */
/* 			    return 0; */
/* 			default: */
/* 				printf ("wrong option\n"); */
/* 		} */
/* 	} */
/* } */

/* void insert(void){ */
/* 	char nTask[20]; */
/*         int nHour; */
        
/* 	printf("Enter task:\n"); */
/*         printf("    "); */
/*         __fpurge(stdin);        //scanner for task */
/*         scanf("%[^'\n']", nTask); */
        
/* 	printf("Enter time:\n"); */
/*         printf("    "); */
/*         scanf("%d", &nHour); */
       
/* 	if(nHour > 23){ */
/* 	  printf("Not valid time\n"); */
/* 	  return; */
/* 	} */
       
/* 	strcpy(tasks[counter],nTask);       */
/* 	hours[counter] = nHour; */
/*         counter++; */
/* } */

/* void list(void){ */
/*   int i; */
/*   printf("List of Tasks:\n"); */
/*   for(i=0; i < counter; i++){ */
/*     printf("	"); */
/*     printf("%d", hours[i]); */
/*     printf("	"); */
/*     printf("%s", tasks[i]); */
/*     printf("\n"); */
/*   } */
/* } */

/* void list_hour(void){ */
/*   int hour; */
/*   int i; */
/*   printf("%s","Enter Hour:\n"); */
/*   printf("%s","	"); */
/*   scanf("%d", &hour); */

/*   for(i=0; i < counter; i++){ */
/*     if(hours[i] == hour){ */
/*       printf("%s","  Task:"); */
/*       printf("%s",tasks[i]); */
/*       printf("\n"); */
/*     } */
/*   } */
/* } */

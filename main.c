#include <stdio.h>
#include <stdlib.h>
#include "Student.h"
#include "Book.h"
#include "Reservation.h"
void printMenu(){          //printing the interface
    printf("1- Add Book\n");
    printf("2- Add Student\n");
    printf("3- Modify Book\n");
    printf("4- Modify Student\n");
    printf("5- Delete Book\n");
    printf("6- Delete Student\n");
    printf("7- Issue Book\n");
    printf("8- Return Book\n");
    printf("9- Display Data\n");
    printf("10- Save and Exit\n\n");
    printf("Choose what to do:");
}

void DisplayData(List L1, List2 L2, List3 L3){ //display all data
        FILE *out;
        out = fopen("Data.dat","w");
        printf("\n");
        printf("\n");
        printf("Books Records:\n");
        fprintf(out,"Books Records:\n");
        printBooks(L2,out);
        printf("\n");
        fprintf(out,"\n");
        printf("Students Records:\n");
        fprintf(out,"Students Records:\n");
        printList(L1,out);
        printf("\n");
        fprintf(out,"\n");
        printf("Reservations Records:\n");
        fprintf(out,"Reservations Records:\n");
        printBorrowed(L3,out);
        printf("\n");
        fprintf(out,"\n");
        fclose(out);
    }

int main(){
    int x;
    printMenu();
    List L1;
    List2 L2;
    List3 L3;
    L1 = MakeEmpty(NULL);     //initialization
    L2 = MakeEmpty2(NULL);
    L3 = MakeEmpty3(NULL);
    scanf("%d", &x);
    while(1){      //switch functions
        switch(x){
        case 1: InsertBook(L2); break;
        case 2: Insert(L1); break;
        case 3: UpdateBook(L2); break;
        case 4: Update(L1); break;
        case 5: DeleteBook(L2); break;
        case 6: Delete(L1); break;
        case 7: Issue(L3,L1,L2); break;
        case 8: Return(L1,L2,L3); break;
        case 9: DisplayData(L1,L2,L3); break;
        case 10:return 0; break;
        default: printf("\n\nInvalid Input\n\n"); break;
        }
        printMenu();
        scanf("%d", &x);
        printf("\n");
    }
}

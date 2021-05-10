#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"Book.h"
typedef struct Node * ptr;
typedef ptr List;
typedef ptr Pos;
struct Node{
    char name[20];
    char address[20];
    char dateOfBirth[15];
    int rollNum;
    int reservations;           //shows how many books every student is borrowing
    List2 BooksBorrowed;        //A list to insert borrowed books in
    Pos2 NextBorrowed;
    Pos Next;
};

void DeleteList(List L){      //Delete the whole list
    Pos p, temp;
    p = L ->Next;
    L -> Next = NULL;
    while(p != NULL){
        temp = p ->Next;
        free(p);
        p = temp;
    }
}

List MakeEmpty(List L){     //Initialize List
    if( L != NULL)
        DeleteList(L);
    L =(struct Node*)malloc(sizeof(struct Node));
    if(L == NULL)
        printf("Out of memory!!\n");
    else
        L ->Next = NULL;
    return L;
}

void Insert(List L){         //Insert data from file into list
    FILE *in;
    Pos p;
    char name[10], address[10], dateOfBirth[10];
    int rollNum, reservations;
    List2 BooksBorrowed = 0;
    BooksBorrowed = MakeEmpty2(BooksBorrowed);
    in = fopen("Students.dat","r");
    while(fscanf(in,"%d %s %s %s %d", &rollNum, name, address, dateOfBirth, &reservations) != 1){
         if((feof(in)))   //to stop reading data when it reaches the end of the file
           break;
    else
        p = malloc(sizeof(struct Node));
    if(p == NULL)
        printf("Out of memory!!");
    else{
        p ->reservations = reservations;
        p ->rollNum = rollNum;
        p ->BooksBorrowed = BooksBorrowed;
        strcpy(p->name, name);
        strcpy(p->address, address);
        strcpy(p->dateOfBirth, dateOfBirth);
        Pos t = L;
        while(t ->Next != NULL && t != NULL)
              t = t ->Next;
        t -> Next = p;
        p ->Next = NULL;
    }
    }
    printf("Students Added!\n\n");
    fclose(in);
}

int IsEmpty(List L){
    return L ->Next == NULL;
}

int IsLast(Pos p, List L){
    return L ->Next == NULL;
}

Pos FindPrevious(int x, List L){      //finds the previous position of a node
    Pos p;
    p = L;
    while(p != NULL && p ->Next ->rollNum != x)
        p = p ->Next;
    return p;
}

void Delete(List L){   //Delete a specified node
    int x;
    printf("\nEnter the Id of the Student you want to Delete:");
    scanf("%d",&x);
    Pos p, temp;
    p = L ->Next;
    while(p != NULL && p ->rollNum != x)
        p = p ->Next;
    if(p == NULL || p->reservations != 0){
        printf("Not Available to Delete!\n");
    }
    else{
    p = FindPrevious(x, L);
       if(!IsLast(p, L)){
           temp = p ->Next;
           p ->Next = temp ->Next;
           free(temp);
           printf("Deleted!\n");
       }
    }
}

void printList(List L, FILE *out){   //prints all data on screen and on a file
    Pos p = L ->Next;
    if(p == NULL){
        printf("No Students to Display!\n");
        fprintf(out,"No Students to Display!\n");
    }

    else{
        while(p != NULL){
        printf("Roll Num:[%d] ,Name:[%s] ,Address:[%s] ,Date of Birth:[%s] , Num of Reservations:[%d]\n",
                p->rollNum ,p ->name, p ->address, p->dateOfBirth, p->reservations);
        fprintf(out,"Roll Num:[%d] ,Name:[%s] ,Address:[%s] ,Date of Birth:[%s] , Num of Reservations:[%d]\n",
                p->rollNum ,p ->name, p ->address, p->dateOfBirth, p->reservations);
        p = p ->Next;
    }
    }
}

Pos Find(List L){      //returns the position of a specified node
    Pos p;
    printf("\nEnter the Id of the Student you want to find: ");
    int x;
    scanf("%d",&x);
    p = L ->Next;
    while(p != NULL && p ->rollNum != x)
        p = p ->Next;
    if(p == NULL || p ->rollNum != x){
        printf("Not Found!\n");
        return p;
    }
    else{
        printf("Found! : %d %s %s %s\n\n", p->rollNum ,p ->name, p ->address, p->dateOfBirth);
        return p;
    }
}

void Update(List L){          //Modifies data of student
    char name[10], address[10], dateOfBirth[10];
    Pos p;
    printf("\nEnter the id of the student you want to Modify:");
    int x;
    scanf("%d",&x);
    p = L ->Next;
    while(p != NULL && p ->rollNum != x)
        p = p ->Next;
    if(p == NULL){
        printf("The input you entered is Not Available!\n\n");
    }
    else{
    printf("The data you want to modify are:\n %d %s %s %s\n\n", p->rollNum ,p ->name, p ->address, p->dateOfBirth);
    printf("Re-enter the updated name, address and date of birth: \n");
    scanf("%s %s %s",name, address, dateOfBirth);
    strcpy(p->name, name);
    strcpy(p->address, address);
    strcpy(p->dateOfBirth, dateOfBirth);
    printf("\nNew data are: %d %s %s %s\n", p->rollNum ,p ->name, p ->address, p->dateOfBirth);
    }
}
#endif // STUDENT_H_INCLUDED

#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node2 * ptr2;
typedef ptr2 List2;
typedef ptr2 Pos2;
struct Node2{
    int accessionNum;
    char auther[20];
    char title[20];
    char publisher[20];
    double cost;
    int numOfCopys;
    int numOfReservations;
    Pos2 Next;
};

void DeleteList2(List2 L){   //Deletes the whole list
    Pos2 p, temp;
    p = L ->Next;
    L -> Next = NULL;
    while(p != NULL){
        temp = p ->Next;
        free(p);
        p = temp;
    }
}

List2 MakeEmpty2(List2 L){    //initialize the list
    if( L != NULL)
        DeleteList2(L);
    L =(struct Node2*)malloc(sizeof(struct Node2));
    if(L == NULL)
        printf("Out of memory!!\n");
    else
        L ->Next = NULL;
    return L;
}

void InsertBook(List2 L){        //Insert Books from file to list
    FILE *in;
    Pos2 p;
    char auther[10], title[10], publisher[10];
    double cost;
    int numOfCopys, numOfReservations;
    int accessionNum = 1;
    in = fopen("Books.dat","r");
    while(fscanf(in,"%s %s %s %lf %d %d",auther, title, publisher, &cost, &numOfCopys, &numOfReservations) != 1){
         if((feof(in)))
           break;
    else{
       p = malloc(sizeof(struct Node2));
    }
    if(p == NULL)
        printf("Out of memory!!");
    else{
        strcpy(p->auther, auther);
        strcpy(p->title, title);
        strcpy(p->publisher, publisher);
        p ->cost= cost;
        p ->numOfCopys = numOfCopys;
        p ->numOfReservations = numOfReservations;
        p ->accessionNum = accessionNum++;
        Pos2 t = L;
        while(t ->Next != NULL && t != NULL)
              t = t ->Next;
        t ->Next = p;
        p ->Next = NULL;
    }
    }
    printf("Books Added!\n\n");
    fclose(in);
}

int IsEmptyBook(List2 L){
    return L ->Next == NULL;
}

int IsLastBook(Pos2 p, List2 L){
    return L ->Next == NULL;
}

Pos2 FindPreviousBook(int x, List2 L){    //finds the previous position of a node
    Pos2 p;
    p = L;
    while(p != NULL && p ->Next ->accessionNum != x)
        p = p ->Next;
    return p;
}

void DeleteBook(List2 L){    //Delete a specified node
    int x;
    printf("\nEnter the Accession Number of the Book you want to Delete:");
    scanf("%d",&x);
    Pos2 p, temp;
    p = L ->Next;
    while(p != NULL && p ->accessionNum != x)
        p = p ->Next;
    if(p == NULL || p->numOfReservations > 0){
        printf("Not Available to Delete!\n");
    }
    else{
    p = FindPreviousBook(x, L);
    if(!IsLastBook(p, L)){
        temp = p ->Next;
        p ->Next = temp ->Next;
        free(temp);
        printf("Deleted!\n");
    }
    }
}

void printBooks(List2 L, FILE *out){  //print all books data on screen and file
    Pos2 p = L ->Next;
    if(p == NULL){
        printf("No Books to Display!\n");
        fprintf(out,"No Books to Display!\n");
    }
    else{
       while(p != NULL){
        printf("Accession Num:[%d], Auther:[%s], Title:[%s], Publisher:[%s], Cost:[%.2f], Num of Copies:[%d], Num of Reservations:[%d]\n",
                p->accessionNum, p->auther, p->title,p->publisher, p->cost, p->numOfCopys, p->numOfReservations);
        fprintf(out,"Accession Num:[%d], Auther:[%s], Title:[%s], Publisher:[%s], Cost:[%.2f], Num of Copies:[%d], Num of Reservations:[%d]\n",
                p->accessionNum, p->auther, p->title,p->publisher, p->cost, p->numOfCopys, p->numOfReservations);
        p = p ->Next;
    }
    }
}

Pos2 FindBook(List2 L){      //returns the location of a specified book
    Pos2 p;
    printf("\nEnter the Title or the Author's Name of the Book you want to find: ");
    char x[10];
    scanf("%s",x);
    p = L ->Next;
    while(p!= NULL && !((strcasecmp(p ->title,x))==0 || (strcasecmp(p ->auther,x))==0))
        p = p ->Next;
    if(p == NULL){
        printf("Not Found!\n\n");
        return p;
    }
    else{
        printf("Found!: %d %s %s %s %.2f %d %d\n\n", p->accessionNum, p->auther, p->title,
               p->publisher, p->cost, p->numOfCopys, p->numOfReservations);
        return p;
    }
}

void UpdateBook(List2 L){     //Modifies the data of the book(cost, number of copies, number of reservations)
    double cost;
    int numOfCopys, numOfReservations;
    Pos2 p;
    printf("\nEnter the Accession Number of the book you want to Modify:");
    int x;
    scanf("%d",&x);
    p = L ->Next;
    while(p != NULL && p ->accessionNum != x)
        p = p ->Next;
    if(p == NULL){
        printf("The input you entered is Not Available!\n\n");
    }
    else{
    printf("The data you want to modify are:\n %s %s %s %.2f %d %d\n\n", p->auther, p->title,
                p->publisher, p->cost, p->numOfCopys, p->numOfReservations);
    printf("Re-enter the updated cost, number of copies and number of reservations: \n");
    scanf("%lf %d %d",&cost, &numOfCopys, &numOfReservations);
    p ->cost = cost;
    p ->numOfCopys = numOfCopys;
    p ->numOfReservations = numOfReservations;
    printf("\nNew data are: %s %s %s %.2f %d %d\n\n", p->auther, p->title,
                p->publisher, p->cost, p->numOfCopys, p->numOfReservations);
    }
}
#endif // BOOK_H_INCLUDED

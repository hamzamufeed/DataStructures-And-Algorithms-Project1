#ifndef RESERVATION_H_INCLUDED
#define RESERVATION_H_INCLUDED
#define MAX 2
#include <time.h>
typedef struct Node3 * ptr3;    //A node manages the issue and return operations
typedef ptr3 List3;             //It contains the data of books and students who borrowed books and the dates of operations
typedef ptr3 Pos3;
struct Node3{
    List L1;
    List2 L2;
    char StudentName[15];
    int StudentId;
    char BookTitle[15];
    char BookNum;
    int dayIssued;
    int monthIssued;
    int yearIssued;
    int dueDay;
    int dueMonth;
    int dueYear;
    Pos3 Next;
};
void DeleteList3(List3 L){  //Delete the whole list
    Pos3 p, temp;
    p = L ->Next;
    L -> Next = NULL;
    while(p != NULL){
        temp = p ->Next;
        free(p);
        p = temp;
    }
}

List3 MakeEmpty3(List3 L){   //initialize the list
    if( L != NULL)
        DeleteList3(L);
    L =(struct Node3*)malloc(sizeof(struct Node3));
    if(L == NULL)
        printf("Out of memory!!\n");
    else
        L ->Next = NULL;
    return L;
}

void printBorrowed(List3 L,FILE *out){      //print all list's data on screen and on function
    Pos3 p = L ->Next;
    if(p == NULL){
        printf("No Borrowed Books to Display!\n");
        fprintf(out,"No Borrowed Books to Display!\n");
    }
    else{
        while(p != NULL){
        printf("Student's Roll Num:[%d] ,Student's Name:[%s] ,Book's Accession Num:[%d] ,Book's Title:[%s], Date Issued:[%d\\%d\\%d], Due Date:[%d\\%d\\%d]\n",
               p->StudentId ,p ->StudentName, p ->BookNum, p->BookTitle, p->dayIssued, p->monthIssued, p->yearIssued,p->dueDay,p->dueMonth,p->dueYear);
        fprintf(out,"Student's Roll Num:[%d] ,Student's Name:[%s] ,Book's Accession Num:[%d] ,Book's Title:[%s], Date Issued:[%d\\%d\\%d], Due Date:[%d\\%d\\%d]\n",
               p->StudentId ,p ->StudentName, p ->BookNum, p->BookTitle, p->dayIssued, p->monthIssued, p->yearIssued,p->dueDay,p->dueMonth,p->dueYear);
        p = p ->Next;
    }
    }
}

void InsertBorrow(List3 L3, Pos p1, Pos2 p2){   //insert data of borrowing operation
    Pos3 p3;
    int day, month, year;
    int dueDay, dueMonth, dueYear;

    p3 = malloc(sizeof(struct Node3));
    if(p3 == NULL)
        printf("Out of memory!!");
    else{
        printf("Enter the Date of Reservation by this format DD MM YYYY:");
        scanf("%d %d %d", &day, &month, &year);
        printf("%d\\%d\\%d\n",day,month,year);

        printf("\nEnter the Due Date by this format DD MM YYYY:");
        scanf("%d %d %d", &dueDay, &dueMonth,&dueYear);
        printf("%d\\%d\\%d\n",dueDay, dueMonth, dueYear);

        p3->dayIssued = day;
        p3->monthIssued = month;
        p3->yearIssued = year;
        p3->dueDay = dueDay;
        p3->dueMonth = dueMonth;
        p3->dueYear = dueYear;
        strcpy(p3->StudentName, p1->name);
        p3 ->StudentId = p1 ->rollNum;
        strcpy(p3->BookTitle, p2->title);
        p3 ->BookNum = p2 ->accessionNum;

        Pos3 t = L3;
        while(t ->Next != NULL && t != NULL)
              t = t ->Next;
        t -> Next = p3;
        p3 ->Next = NULL;
    }
}

void Issue(List3 L3, List L1, List2 L2){    //Manages the borrowing operation of books
    Pos p1 = Find(L1);   //return the position of the student who want to borrow a book
    Pos2 p2 = FindBook(L2);  //returns the position of the book to be borrowed
    if(p1 !=NULL && p2 != NULL){
        if(p1->reservations < MAX && p2 ->numOfCopys !=0){   //checking if the book is available and if the student can borrow it
            p2 ->numOfCopys--;
            p2 ->numOfReservations++;
            p1 ->reservations++;
            p1 ->NextBorrowed = malloc(sizeof(struct Node2));  //inserting book to the student's list of borrowed books
            Pos2 t = p1->BooksBorrowed;
            while(t ->Next != NULL && t != NULL)
                t = t ->Next;
            t -> Next = p1->NextBorrowed;
            p1->NextBorrowed ->Next = NULL;
            InsertBorrow(L3, p1, p2);
            printf("Book borrowed successfully!\n\n");
        }
        else if(p1->reservations == MAX)
            printf("This student has reached the maximum number of reservations!\n\n");

        else if(p2 -> numOfCopys == 0)
            printf("This Book is not available to borrow!\n\n");
    }
    else
        printf("Book Borrowing Failed!\n");
}

Pos3 FindBorrow(Pos p1, Pos2 p2, List3 L){    //returns a specified location of the borrowed book in the list of reservations
        Pos3 p;
        p = L ->Next;
        while(p != NULL && p1->BooksBorrowed->accessionNum != p->BookNum && p->StudentId != p1->rollNum)
            p = p ->Next;
        if(p == NULL)
           return p;
        else
           return p;
}

int IsLastBorrow(Pos3 p, List3 L){
    return p->Next==NULL;
}
Pos3 FindPreviousBorrow(int studentnum, int booknum, List3 L){
    Pos3 p = L;
    while(p!=NULL && p->Next->BookNum != booknum && p->Next->StudentId != studentnum)
        p = p->Next;
    return p;
}
void DeleteBorrowed(int studentnum, int booknum, List3 L){   //Deletion node in case of return
    Pos3 p,temp;
    p = FindPreviousBorrow(studentnum,booknum,L);
    if(!IsLastBorrow(p,L)){
        temp = p->Next;
        p ->Next = temp ->Next;
        free(temp);
    }
}

void Return(List L1, List2 L2, List3 L3){  //Manages the returning operations
    Pos p1 = Find(L1);      //position of the student who borrowed a book
    Pos2 p2 = FindBook(L2);   //position of the book borrowed
    Pos3 p3 = FindBorrow(p1,p2,L3);   //finds if the data of the students and book exists in the list of reservations
    double Fine;
    int dayReturned, monthReturned, yearReturned;
    if(p1!=NULL && p2!=NULL && p3!=NULL){
                if(p3 !=NULL && (p1->reservations)!=0 && (p2->numOfReservations)>0){
                    p1->reservations--;
                    p2->numOfReservations--;
                    p2->numOfCopys++;

                    printf("Enter the Return Date by this format DD MM YYYY:");
                    scanf("%d %d %d", &dayReturned, &monthReturned, &yearReturned);
                    printf("%d\\%d\\%d\n",dayReturned ,monthReturned,yearReturned);

                    struct tm date = {0};       //struct to operate the date
                    date.tm_year = p3->dueYear - 1900;
                    date.tm_mon  = p3->dueMonth -1;
                    date.tm_mday = p3->dueDay;
                    time_t dt1 = mktime(&date);

                    date.tm_year = yearReturned - 1900;
                    date.tm_mon  = monthReturned - 1;
                    date.tm_mday = dayReturned;
                    time_t dt2 = mktime(&date);

                    double seconds = difftime(dt2,dt1);    //returns the difference of the dates in seconds
                    int days = (seconds/(60*60*24));      //converting from seconds to days
                    if(days > 0){                         //Checks if the date returned is late
                        Fine = days*0.75;
                        printf("Student has Exceeded the Due Date by %d Days!! Fine must be paid!\n",days);
                        printf("Fine to pay = %.2f JD\n\n",Fine);
                    }
                    DeleteBorrowed(p3->StudentId, p3->BookNum,L3);
                    printf("Book Returned!\n\n");
                }
                else
                    printf("Book is not Borrowed!!\n\n");
    }
    else
        printf("Book is not Borrowed!!\n\n");
}

#endif // RESERVATION_H_INCLUDED

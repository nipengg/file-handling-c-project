#include <stdio.h>
#include <stdlib.h>

typedef struct ticket{
    char nameCustomer[20];
    char eventType[20];
    char eventName[20];
    int ticketTotal;
    int ticketPrice;
    int total;
}ticket;

void create()
{
    ticket *t;
    FILE *fp;
    int n, i, j;
    printf("Enter how many tickets you want to create? : ");
    scanf("%d", &n);

    t = (ticket*)calloc(n, sizeof(ticket));
    fp = fopen("sales.txt", "a");


    for (int i = 0; i < n; i++)
    {
        t[i].total = 0;
        fflush(stdin);
        printf("Enter Customer Name : ");
        scanf("%[^\n]s", t[i].nameCustomer);
        fflush(stdin);
        printf("Enter Event Type    : ");
        scanf("%[^\n]s", t[i].eventType);
        fflush(stdin);
        printf("Enter Event Name    : ");
        scanf("%[^\n]s", t[i].eventName);
        fflush(stdin);
        printf("Enter Total Ticket  : ");
        scanf("%d", &t[i].ticketTotal);
        printf("Enter Ticket Price  : ");
        scanf("%d", &t[i].ticketPrice);
        t[i].total  = t[i].ticketTotal * t[i].ticketPrice;
        fwrite(&t[i], sizeof(ticket), 1, fp);
    }
    fclose(fp);
}

void display()
{
    ticket t1;
    FILE *fp;
    int j;
    fp = fopen("sales.txt", "r");
    printf("===================================================");
    while (fread(&t1, sizeof(ticket), 1, fp))
    {
        printf("\n%-10s%-10s%-10s", t1.nameCustomer, t1.eventType, t1.eventName);
        printf("%-5d%-10d%-10d\n", t1.ticketTotal, t1.ticketPrice, t1.total);
    }
    printf("===================================================\n");
    fclose(fp);
}

int main()
{
    int menu;
    do
    {
        printf("1. Create\n");
        printf("2. Display\n");
        printf("3. Exit\n");;

        printf("Enter Menu : \n");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            create();
            break;

        case 2:
            display();
            break;
        }

    } while (menu != 3);
}
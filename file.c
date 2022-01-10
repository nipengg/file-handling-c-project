#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tanggal{
		int hari;
		int bulan;
		int tahun;
}tanggal;

typedef struct ticket{
	char customerName[10];
	char eventType[20];
	char eventName[20];
	int ticketTotal;
	int ticketPrice;
	int total;
	tanggal tanggal;
}ticket;
ticket data[100];

int count;
void readData()
{
	FILE *fp = fopen("sales.txt", "r");
	count = 0;
	char customerName[10], eventType[100], eventName[100];
	int ticketTotal, ticketPrice, total, hari, bulan, tahun;
	while (fscanf(fp, "%s %s %s %d %d %d %d/%d/%d\n", customerName, eventType, eventName, &ticketTotal, &ticketPrice, &total, &hari, &bulan, &tahun) != EOF)
	{
		strcpy(data[count].customerName, customerName);
		strcpy(data[count].eventType, eventType);
		strcpy(data[count].eventName, eventName);
		data[count].ticketTotal, ticketTotal;
		data[count].ticketPrice, ticketPrice;
		data[count].total, total;
		data[count].tanggal.hari = hari;
		data[count].tanggal.bulan = bulan;
		data[count].tanggal.tahun = tahun;
		count++;
	}
	fclose(fp);
}

void display()
{
	if (count == 0)
    {
		printf("[ERROR] File does not exist. Type 1 to create file\n");
		system("pause");
	}
    else
    {
		FILE * fp = fopen("sales.txt", "r");
		char customerName[100], eventType[100], eventName[100], date[100];
		int ticketTotal, ticketPrice, total, i = 0;
		printf("No. | Transaction Date  |  Customer Name       |  Event Type       | Event Name		 | Total Ticket |  Ticket Price    |      Total       |\n");
  		printf("=================================================================================================================================================\n");
		while (fscanf(fp, "%s %s %s %s %d %d %d\n", date, customerName, eventType, eventName, &ticketTotal, &ticketPrice, &total) != EOF)
        {
			printf("%-3d | %-17s | %-20s | %-17s | %-19s | %-12d | Rp.%-13d | Rp.%-13d |\n", ++i , date, customerName, eventType, eventName, ticketTotal, ticketPrice, total);
		}
		printf("=================================================================================================================================================\n");
		system("pause");
	}
}

int checkDate(char date[])
{
	if ((strlen(date) < 8 || strlen(date) > 8) && (date[2] != '/' || date[5] != '/'))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void create()
{
	char date[100];
	int n;
	printf("Enter how many tickets you want to create? : ");
	scanf("%d", &n);
	FILE *fp = fopen("sales.txt" , "a");
	for (int i = 0; i < n; i++)
	{
		printf("Ticket #%d : \n", i + 1);
		fflush(stdin);
		do
		{
			printf("Enter Transaction Date [dd/mm/yy]: ");
			scanf("%s", date);
		}while(checkDate(date) == 0);

		char customerName[100];
		fflush(stdin);
		printf("Enter Customer Name: ");
		scanf("%[^\n]s", customerName);
		char eventType[100];
		fflush(stdin);
		printf("Enter Event Type   : ");
		scanf("%s", eventType);
		char eventName[100];
		fflush(stdin);
		printf("Enter Event Name   : ");
		scanf("%s", eventName);
		int ticketTotal;
		fflush(stdin);
		printf("Enter Total Ticket : ");
		scanf("%d", &ticketTotal);
		int ticketPrice;
		fflush(stdin);
		printf("Enter Ticket Price : ");
		scanf("%d", &ticketPrice);
		int total;
		total  = ticketTotal * ticketPrice;

		fprintf(fp, "\n%s %s %s %s %d %d %d\n", date, customerName, eventType, eventName, ticketTotal, ticketPrice, total);
	}
	fclose(fp);
	system("pause");
}

void sortByDate()
{
	struct tanggal temp;
	int i = 0, T, j;
	char str;

	FILE *fp = fopen("sales.txt", "r");
	if (fp == NULL)
	{
		printf("\n Belum ada data \n");
		system("pause");
	}

	while (str != EOF)
	{
		fscanf(fp, "%d/%d/%d %s %s %s %d %d %d\n", &data[i].tanggal.hari, &data[i].tanggal.bulan, &data[i].tanggal.tahun, data[i].customerName, data[i].eventType, data[i].eventName, &data[i].ticketTotal, &data[i].ticketPrice, &data[i].total);
		str = fgetc(fp);
		i++;
	}

	T = i - 1;

	// DATE SORT
	for (i = 1; i <= T; i++)
    {
		for (j = 0; j <= T - i; j++)
        {
		    if (data[j + 1].tanggal.tahun < data[j].tanggal.tahun)
		    {
			    ticket temp = data[j];
			    data[j] = data[j + 1];
			    data[j + 1] = temp;
		    }
		    if (data[j + 1].tanggal.tahun == data[j].tanggal.tahun && data[j + 1].tanggal.bulan < data[j].tanggal.bulan)
		    {
			    ticket temp = data[j];
			    data[j] = data[j + 1];
			    data[j + 1] = temp;
		    }
		    if (data[j + 1].tanggal.tahun == data[j].tanggal.tahun && data[j + 1].tanggal.bulan == data[j].tanggal.bulan && data[j + 1].tanggal.hari < data[j].tanggal.hari)
		    {
			    ticket temp = data[j];
			    data[j] = data[j + 1];
			    data[j + 1] = temp;
		    }
		}
	}

	fp = fopen("sales.txt","w");
	for (i = 0; i <= T; i++)
    {
        fprintf(fp,"\n%02d/%02d/%02d %s %s %s %d %d %d\n", data[i].tanggal.hari, data[i].tanggal.bulan, data[i].tanggal.tahun, data[i].customerName, data[i].eventType, data[i].eventName, data[i].ticketTotal, data[i].ticketPrice, data[i].total);
    }
	fclose(fp);
}

int main()
{
	int menu;
	readData();
	do
    {
        printf("\n1. Create\n");
        printf("2. Display\n");
        printf("3. Sort by Date\n");
        printf("4. Exit\n");;

        printf("Enter Menu : ");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            create();
            break;

        case 2:
            display();
            break;

        case 3:
            sortByDate();
            display();
            break;
        }
    } while (menu != 4);
}
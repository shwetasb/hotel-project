#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

void addcust();
void viewcust();
void dailyreport();
void totalcash();
void totaltables();
void totaldish();
struct cust_order
{
int tableno,quantity,bill;
char recipe[30];
}co;
 
int main()
{
	int choice;
	printf("1.Add Customer Information\n2.View Customer Information\n3.Daily report\n4.Exit\n");
	printf("Enter the choice\n");
	scanf("%d", &choice);
	switch(choice) {
		case 1:
			addcust();
			break;
		case 2:
			viewcust();
			break;
		case 3:
			dailyreport();
			break;
		case 4:
			exit(0);
		default:
			printf("Wrong choice");
			break;
	}
	return 0;
}

//Funtion to add details of the customer 
void addcust() {
	FILE *fptr;
	char name[50];
	int i;
   	printf("Enter the filename\n");
	scanf("%s",&name);
	fptr= fopen(name, "a");
    /* opens file to write customer details */
    	if (fptr == NULL) {
      		printf("File does not exist \n");
			return;
		}

	printf("Enter the table no \n");
   	scanf("%d", &co.tableno);
    fprintf(fptr, "Table no  = %d\n",co.tableno);
    
   	printf("Enter the recipe\n");
    scanf("%s", co.recipe);
   	fprintf(fptr, "Recipe = %s\n",co.recipe);
    
    printf("Enter the quantity\n");
	scanf("%d", &co.quantity);
    fprintf(fptr, "Quantity = %d\n",co.quantity);
	
	printf("Enter the bill\n");
    scanf("%d", &co.bill);
    fprintf(fptr, "Bill = %d\n",co.bill);
}

// function to view the details of the customer
void viewcust() {
	FILE *fptr;
	char name[50];
	printf("Enter the filename");
	scanf("%s",&name);
	fptr= fopen(name, "r");
  	int ch = getc(fptr);
	while (ch != EOF) {
    		putchar(ch); 
    		ch = getc(fptr);
  	}
   
  	if (feof(fptr))
     		printf("\n End of file reached.");
  	else
     		printf("\n Something went wrong.");
  	
	fclose(fptr);
    	getchar();

}

// funtion to get daily reports 
void dailyreport() {
	int choice=0;
	while(choice!=4) {
		printf("1.Todays cash collection\n2.Total no of tables served\n3.Total number of dishes\n4.Exit\n");
		printf("Enter the choice\n");
		scanf("%d",&choice);
		switch(choice) {
				case 1:
					totalcash();
					continue;
				case 2:
					totaltables();
					continue;
				case 3:
					totaldish();
					continue;
				case 4:
					exit(0);
				default:
					printf("Wrong choice");
					break;
		}
	}
}

void totalcash() {
	int total=0;
	char name[50];
	char* string[100];
	char line[100];
	char *p;
	FILE *fptr;
	printf("Enter the filename");
	scanf("%s",&name);
	fptr = fopen(name, "r");
	while(fgets(line, sizeof line, fptr)!=NULL) {		
		p = strstr(line,"Bill");
			if(p) {			
				//printf("%s", line);//
				p=strchr(line,'=');		
				/*printf ("First occurrence of character \"=\" in \"%s\" is" \
           		" \"%s\"",string, p+1);*/
				total = total + atoi(p+1);
			}
	}  
	printf("Total Bill of the day is %d\n", total);
	fclose(fptr);
}

void totaltables() {
	int table=0;
	char name[50];
	char* string[100];
	char line[100];
	char *p;
	FILE *fptr;
	printf("Enter the filename");
	scanf("%s",&name);
	fptr = fopen(name, "r");
	while(fgets(line, sizeof line, fptr)!=NULL) {		
		p = strstr(line,"Table");
			if(p) {
				table = table + 1;
			}
	}  
	printf("Total Nuber of tables served today is %d\n", table);
	fclose(fptr);
}

void totaldish() {
	int dish=0;
	char name[50];
	char* string[100];
	char line[100];
	char *p;
	FILE *fptr;
	printf("Enter the filename");
	scanf("%s",&name);
	fptr = fopen(name, "r");
	while(fgets(line, sizeof line, fptr)!=NULL) {		
		p = strstr(line,"Quantity");
			if(p) {			
				p=strchr(line,'=');
				dish = dish + atoi(p+1);
			}
	}  
	printf("Total number of dishes served today is %d\n", dish);
	fclose(fptr);
}






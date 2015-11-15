#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

//User defined functions

void customer();
void menu();
void dailyreport();

//customer related functions
void addcustomer();
void viewcustomer();
void deletefile();
void searchcustomer();
void deletecustomer();

//reports functions
void totaltables();

//menu functions
void printmenu();
void addmenu();
void viewmenu(); 
void updatemenu();
void deletemenu();;


struct customerorder {
int tableno,quantity,bill;
char recipe[30];
}co;


// Main funtion 
int main() {
	int choice = 0;

	while(choice != 4) {
	
	printf("***********************************************************************************************\n");
	printf("----------------------- W E L C O M E    T O   H O T E L  P A R A D I S E ---------------------\n");
	printf("***********************************************************************************************\n");

	printf("\n1.Menu Management\n2.Customer Management\n3.Reports\n4.Exit\n");
	printf("Enter the choice\n");
	scanf("%d", &choice);

		switch(choice) {
			case 1:
				menu();
				continue; 
			case 2:
				customer();
				continue;
			case 3:
				dailyreport();
				continue; 
			case 4:
				break;
			default:
				printf("Wrong choice");
				continue;
		}
	}
	return 0;

}	

// Handle customer details
void customer() {
	int choice = 0;

	while(choice != 6) {

	printf("\n ******************************  C U S T O M E R   D E T A I L S ************************* \n");
	printf("\n1.Add Customer Information\n2.View Customer Information\n3.Deletecustomer\n4.Search Customer\n5.Deletefile\n6.Exit\n");
	
	printf("Enter the choice\n");
	scanf("%d", &choice);

		switch(choice) {
			case 1:
				addcustomer();
				continue;
			case 2:
				viewcustomer();
				continue;
			case 3:
				deletecustomer();
				continue;
			case 4:
				searchcustomer();
				continue;
			case 5:
				deletefile();
				continue;		
			case 6:
				break;
			default:
				printf("Wrong choice");
				continue;
		}
	}

}

//Funtion to add details of customer order
void addcustomer() {
	FILE *fptr;
	char name[50];
	int returnvalue = 0;
	int choice,viewmenu;
	int bill = 0;
	char pass[50];
	FILE *fmenu;
	char *p;
	char line[500];
	int flag = 0;
	
	
	// get the file details
   	printf("Enter the filename\n");
	scanf("%s", name);
	fptr= fopen(name, "a");
    	/*  open file to write customer details */
    	if(fptr == NULL) {
      		printf("File does not exists \n");
		return;
	 }

	// get the details into the customer object
	printf("Enter the table no\n");
   	scanf("%d", &co.tableno);
    	fprintf(fptr, "Tableno = %d    ", co.tableno);
	
	printf("Do you want to view menu? Enter 1 to view !\n");
	scanf("%d", &viewmenu);
	if(viewmenu == 1) {
		fmenu = fopen("menu.txt", "r");
		while(fgets(line, sizeof line, fmenu) != NULL) {
		printf("%s\n", line);		
		}		
		fclose(fmenu);
	}

	printf("Do you want to order? Enter 1 to continue your order and other number to stop the order!\n");
	scanf("%d", &choice);

	while(choice == 1) {    
		printf("Enter the recipe\n");
        	scanf("%s", co.recipe);
		
		fmenu = fopen("menu.txt","r");
			while(fgets(line, sizeof line, fmenu) != NULL) {		
				p = strstr(line, co.recipe);
				if(p) {	
					p=strchr(line, '=');		
					returnvalue = atoi(p+1);
							
				}
			}
		fclose(fmenu);

		if(returnvalue != 0) {
	    		fprintf(fptr, "Recipe = %s        ",co.recipe);
	    
	    		printf("Enter the quantity\n");
			scanf("%d", &co.quantity);
	    		fprintf(fptr, "Quantity = %d  ",co.quantity);

			bill = bill + (co.quantity * returnvalue);
			returnvalue = 0;
		}
		else {
			printf("Invalid menu option. Menu not present please select another menu\n");
		}
		printf("Do you want to order? Enter 1 to continue your order and other number to stop the order!\n");
		scanf("%d", &choice);

	}

	printf("\nTotal Payment for given order = %d\n", bill);
    	fprintf(fptr, "Bill=%d\n", bill);
	fclose(fptr);
}

// function to view the details of the customer order
void viewcustomer() {
	FILE *fptr;
	char name[50];
	printf("Enter the filename");
	scanf("%s", name);
	fptr= fopen(name, "r");
  	int ch = getc(fptr);
	while (ch != EOF)
	{
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

//Deletes the customer details
void deletecustomer() {
	char tableno[50];
	char name[50];
	char stringop[100] = "Tableno = ";
	char line[500];
	char *p;
	int find = 0;
	FILE *fptr, *temp;

	printf("Enter the filename");
	scanf("%s", name);
	
	printf("Enter the table no you want to delete");
	scanf("%s", tableno);
	strcat(stringop, tableno);
	fptr = fopen(name, "r");
	temp = fopen("temp", "w");


	while(fgets(line, sizeof line, fptr) != NULL) {		
		p = strstr(line, stringop);
		
		if(p) {				
			find = 1;
		}
		else {
			fprintf(temp, "%s", line);
		}
	}
	if(find == 0) {
		printf("No Record Found ");
		remove("temp");
	}
	else {
		remove(name);
		rename("temp", name);
	}
	fclose(fptr);
	fclose(temp);

}

//Searches the particular customer
void searchcustomer() {

	char tableno[50];
	char name[50];
	char stringop[100] = "Tableno = ";
	char line[500];
	char *p;
	int find = 0;
	FILE *fptr;
	printf("Enter the filename");
	scanf("%s",name);
	
	printf("Enter the table no you want to search");
	scanf("%s",tableno);
	strcat(stringop, tableno);
	fptr = fopen(name, "r");
	while(fgets(line, sizeof line, fptr) != NULL) {		
		p = strstr(line,stringop);
		
		if(p) {				
			
			printf("%s", line);
			find = 1;
		}
	}
	if(find == 0) {
		printf("No Record Found ");
	}
	fclose(fptr);

}

void deletefile() {
	char name[30];
	int t;
	FILE *fptr;
	printf("Enter the file to be deleted");
	scanf("%s", name);
	fptr=fopen(name, "r");
	if(fptr == NULL) {
		printf("File does not exist\n");
		return;
	}
	fclose(fptr);
	t=remove(name);
	if(t == 0) {
		printf("File deleted sucessfully\n");
	}

}


//Function to maintain menu details
void menu() {
	int choice = 0;

	while(choice != 5) {

	printf("\n ******************************  M E N U    D E T A I L S ************************* \n");

	printf("\n1.Add Menu\n2.Update Menu\n3.View Menu\n4.Delete Menu\n5.Exit\n");
	
	printf("Enter the choice\n");
	scanf("%d",&choice);

		switch(choice) {
			case 1:
				addmenu();
				continue;
		
			case 2:
				updatemenu();
				continue;
			case 3:
				viewmenu();
				continue;
			case 4:
				deletemenu();
				continue;
			case 5:
				break;
			default:
				printf("Wrong choice\n");
				continue;
		}
	}

}

//adds menu
void addmenu() {
	FILE *fmenu;
	int choice = 1;
	char recipename[100];
	char price[5];
	
	fmenu = fopen("menu.txt","a");
	while(choice == 1) {
		
		printf("Enter the recipe name :\n");
		scanf("%s", recipename);

		printf("Enter the price :\n");
		scanf("%s",price);
		
		strcat(recipename, "=");
		strcat(recipename, price);
		strcat(recipename, "\n");

		//printf("output menu %s",recipename);

		fprintf(fmenu,"%s", recipename);

		printf("Press 1 to continue to add menu\n");
		scanf("%d", &choice);
	
	}
	fclose(fmenu);
}

//view menu 
void viewmenu() {
	FILE *fmenu;
	char name[50];
	char line[500];

	fmenu = fopen("menu.txt","r");
	while(fgets(line, sizeof line, fmenu) != NULL) {
		printf("%s\n", line);		
	}		
		
	fclose(fmenu);
}

//deletes particular menu
void deletemenu() {
	char name[50];
	char recipename[50];
	char updateprice[50];
	char line[500];
	char *p;
	int find = 0;
	int viewmenu;
	FILE *fptr,*temp,*fmenu;

	printf("Enter the filename\n");
	scanf("%s", name);

	
	printf("Do you want to view menu? Enter 1 to view !\n");
	scanf("%d", &viewmenu);
	if(viewmenu == 1) {
		fmenu = fopen(name,"r");
		while(fgets(line, sizeof line, fmenu) != NULL) {
		printf("%s\n", line);		
		}		
		
	}
	printf("Enter the recipe name to remove from menu\n");
	scanf("%s", recipename);
	strcat(recipename, "=");
	
	fptr = fopen(name, "r");
	temp = fopen("temp", "w");


	while(fgets(line, sizeof line, fptr)!=NULL) {		
		p = strstr(line, recipename);
		
		if(p) {				
			find = 1;
		}
		else {
			fprintf(temp,"%s",line);
		}
	}
	if(find == 0) {
		printf("No Record Found \n");
		remove("temp");
	}
	else {
		remove(name);
		rename("temp", name);
		printf("Menu Removed Sucessfully \n");
	}
	fclose(fptr);
	fclose(temp);
	
}

//updates particular menu
void updatemenu() {
	char name[50];
	char recipename[50];
	char updateprice[50];
	char line[500];
	char *p;
	int find = 0;
	int viewmenu;
	FILE *fptr, *temp, *fmenu;

	printf("Enter the filename\n");
	scanf("%s", name);

	printf("Do you want to view menu? Enter 1 to view !\n");
	scanf("%d", &viewmenu);
	if(viewmenu == 1){
		fmenu = fopen(name,"r");
		while(fgets(line, sizeof line, fmenu) != NULL) {
		printf("%s\n", line);		
		}
		fclose(fmenu);		
		
	}
	
	printf("Enter the recipe name\n");
	scanf("%s", recipename);
	strcat(recipename, "=");
	
	fptr = fopen(name, "r");
	temp = fopen("temp", "w");


	while(fgets(line, sizeof line, fptr) != NULL) {		
		p = strstr(line, recipename);
		
		if(p) {				
			printf("Record Found : %s\n", line);
			find = 1;
			printf("Enter the price you want to update\n");
			scanf("%s", updateprice);
			strcat(recipename, updateprice);
			strcat(recipename, "\n");
			fprintf(temp, "%s", recipename);
			
		}
		else {
			fprintf(temp, "%s", line);
		}
	}
	if(find == 0) {
		printf("No Record Found \n");
		remove("temp");
	}
	else {
		remove(name);
		rename("temp", name);
		printf("Menu Price Updated Sucessfully \n");
	}
	fclose(fptr);
	fclose(temp);

}



// funtion to get daily reports 
void dailyreport() {
	int choice = 0;
	while(choice != 4) {
	printf("1.Total no of tables served\n2.Exit\n");
	printf("Enter the choice\n");
	scanf("%d",&choice);
	
		switch(choice) {

			case 1:
				totaltables();
				continue;
			case 2:
				exit(0);
				
			default:
				printf("Wrong choice");
				continue;
		}
	}

}

//total tables served
void totaltables() {

	int table=0;
	char name[50];
	char* string[100];
	char line[100];
	char *p;
	FILE *fptr;
	printf("Enter the filename\n");
	scanf("%s", name);
	fptr = fopen(name, "r");
	if(fptr == NULL) {
      		printf("File does not exists \n");
	 }
	else {
		
		while(fgets(line, sizeof line, fptr)!=NULL) {		
			p = strstr(line,"Table");
			if(p) {

				table = table + 1;
			}
		}  
		printf("Total Nuber of tables served today is %d\n", table);
		
	}
	fclose(fptr);
}









































    	
    	
    




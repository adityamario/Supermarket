#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
int count=0,tem=1;
struct customer{
	char name[31];
	int opsi;
	int index=1;
}a;
struct barang{
	char productcode[10];
	char productname[100];
	int quantity;
	float price;
}b[120];
struct struk{
	float belanjaan;
	char productcod[10];
	char productnam[100];
	int quantit;
	float pric;
}c[120];


int linear( char key1[],int bataskanan){
	int tanda=-69;
	for(int a=1;a<=bataskanan;a++){
		if(strcmp(b[a].productcode,key1)==0){   //search the item
			tanda=a;
			break;
		}
	}
	return tanda;
}

void opsi1(){
	system("cls");
	FILE*data = fopen("data.txt", "r"); //scan the data from txt
	while(!feof(data)){
        fscanf(data, "%[^#]#%[^#]#%d#%f\n", &b[a.index].productcode, &b[a.index].productname, &b[a.index].quantity, &b[a.index].price);
        a.index++;
    }
    fclose(data);
}

void buy(){
	char key[10];
	int ll,banyak;
	printf("\nWhat do you want to buy, %s?\n", a.name);
	printf("Input product code: ");
	scanf("%s", &key);
	ll=linear(key,a.index-1); // validate item
	if(ll < 0){
		printf("Sorry, we don't have that item :(");
		getchar(); getchar();
		system("cls");
		printf("===PRODUCT LIST===\n");
   		 	printf("Code Name Qty Price\n"); // if the item dont exist
    		for(int i=1;i<a.index;i++){
    			if(b[i].quantity!=0){
    				printf("%s  %s  %d  %.0f\n", b[i].productcode, b[i].productname, b[i].quantity, b[i].price);
				}
			}
			buy();
	}else{
		printf("\nHow many do you want to buy?\n");; // if the item exist
		printf("Input quantity: ");
		scanf("%d", &banyak);
		if((b[ll].quantity-banyak)<0){
			printf("Sorry, but we dont have that much :(\n"); // if the item is over the limit of the stock
			getchar(); getchar();
			system("cls");
			printf("===PRODUCT LIST===\n");
   		 	printf("Code Name Qty Price\n");
    		for(int i=1;i<a.index;i++){
    			if(b[i].quantity!=0){
    				printf("%s  %s  %d  %.0f\n", b[i].productcode, b[i].productname, b[i].quantity, b[i].price);
				}
			}
			buy();
		}else{
			b[ll].quantity-=banyak;
			count++;
			strcpy(c[count].productcod,b[ll].productcode); // if the item is within the limit
			strcpy(c[count].productnam,b[ll].productname);
			c[count].quantit=banyak;
			c[count].pric=b[ll].price;
		}
	}
} 

void produk(){
	system("cls");
	printf("===PRODUCT LIST===\n");
    printf("Code Name Qty Price\n");
    for(int i=1;i<a.index;i++){
    	if(b[i].quantity!=0){
    		printf("%s  %s  %d  %.0f\n", b[i].productcode, b[i].productname, b[i].quantity, b[i].price);
		}
    	
	}
	buy();
}

void homescreen(){
	puts(" _ _ _     _  ");
	puts("| | | |___| |___ ___ _____ ___ ");
	puts("| | | | -_| |  _| . |     | -_|");
	puts("|_____|___|_|___|___|_|_|_|___|");
	printf("Hi, my dear customer!\n");
	printf("May i know your name?\n");
	printf("Input name(5-30 Char): ");
	scanf("%[^\n]", &a.name);
	if(strlen(a.name)<=4){
		printf("Your name is too short, please try again!\n");
		getchar();getchar();
		system("cls");
		homescreen();
	}else if(strlen(a.name)>=31){
		printf("Your name is too long, please try again!\n");
		getchar();getchar();
		system("cls");
		homescreen();
	}
}

void pilih(){
	scanf("%d", &a.opsi);
	if(a.opsi==1){
		produk();
	}else if(a.opsi==2){
		system("cls");
		char judul[60];
		float belanja;
		
		sprintf(judul, "[%s].txt", a.name);
		FILE *lala = fopen (judul, "w");
		fprintf(lala,"Thank you %s\n", a.name);
		fprintf(lala,"Purchase List\n");
		fprintf(lala,"=============\n");
		float subtot=0;
		for(int z=1;z<=count;z++){
			c[z].belanjaan=c[z].pric*c[z].quantit;
			subtot+=c[z].belanjaan;
			fprintf(lala,"%s %d %.0f %.0f\n",c[z].productnam,c[z].quantit,c[z].pric,c[z].belanjaan);
		}
		float discount;
		if(subtot>300000 && subtot<=500000){
			discount=0.05;
		}else if(subtot>500000 && subtot<1000000){ //discount amount based on the purchase
			discount=0.08;
		}else if(subtot>=1000000){
			discount=0.1;
		}else{
			discount=0;
		}
		float tempora=subtot*discount;
		float hargaa=subtot-tempora;
		fprintf(lala,"Total: %.0f\n", subtot);
		fprintf(lala,"Discount: %.0f%%\n",discount*100);
		fprintf(lala,"Disc Amt: %.2f\n", tempora);
		fprintf(lala,"Amount Due: %.2f\n",hargaa);
		fclose(lala);
		
		printf("Thank you %s\n", a.name);
		printf("Purchase List\n");
		printf("=============\n\n");
		printf("ProductName Qty Price SubTotal\n");
		for(int z=1;z<=count;z++){
			c[z].belanjaan=c[z].pric * c[z].quantit;
			printf("%s %d %.0f %.0f\n",c[z].productnam,c[z].quantit,c[z].pric,c[z].belanjaan);
		}
		printf("\nTotal: %.2f\n", subtot);
		printf("Discount: %.0f%%\n",discount*100);
		printf("Disc Amt: %.2f\n", tempora);
		printf("Amount Due: %.2f\n",hargaa);
		printf("PRESS ENTER TO CONTINUE!\n");
		getchar();getchar();
		system("cls");
		printf("Hi %s!\n", a.name);
		printf("What do you want to do?\n\n");
		printf("====COMMAND====\n");
		printf("1. Input Sales\n2. Finish Sales\n3. Exit\n\nInput Command: ");
		pilih();
	}else if(a.opsi==3){
		FILE *edit = fopen("data.txt","w");
		for(int i=1;i<a.index;i++){
    		if(b[i].quantity!=0){
    			fprintf(edit,"%s#%s#%d#%.0f\n", b[i].productcode, b[i].productname, b[i].quantity, b[i].price);
			}
    	
		}
		fclose(edit);
		tem=3;
		system("cls");
		printf("Thank you for coming!\n");
	}else{
		printf("Inputted command doesn't exist!\nPlease try again: ");
		pilih();
	}
}

void option(){
	system("cls");
	printf("Hi %s!\n", a.name);
	printf("What do you want to do?\n\n");
	printf("====COMMAND====\n");
	printf("1. Input Sales\n2. Finish Sales\n3. Exit\n\nInput Command: ");
	pilih();
}

int main(){
	opsi1();
	homescreen();
	option();
//	int tem=1;
	while (tem!=2 || tem!=3){
		if (tem==3){
			break;
		}
		system("cls");
		printf("Successfully save the purchased, please press enter to continue");
		getchar();
		getchar();
		option();
	}
	
	

	return 0;
}


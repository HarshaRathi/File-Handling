#include<stdio.h>
#include "filelib.c"

int main() {
	File *f1, *f2, *f3, *f4, *f5, *f6;
	FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6;
	fpos pos;
	fpos_t pos1;
	int n;
	char str[30] = "Today is a Sunny Day";
	char str1[30] = "Today is a Rainy Day";
	char str2[30] = "Today is a Fun Day ";
	char ptr[100], ptr1[100], ptr2[100];

	printf("My Function : Writing a data into a file using 'w' mode \n");
	f1 = fileopen("data.txt", "w");
	if(f1 == NULL) {
		printf("Error in a opening a file : 'data.txt'\n");
	}
	else{
		filewrite(str, 3, 10, f1);
		fileclose(f1);
	} 

	printf("Original Function : Writing a data into a file using 'w' mode \n");
	fp1 = fopen("data1.txt", "w");
	if(fp1 == NULL) {
		printf("Error in a opening a file : 'data1.txt'\n");
	}
	else {
		fwrite(str, 3, 10, fp1);
		fclose(fp1);
	} 
	
	printf("My Function : Reading a data from a file using 'r' mode \n");
	f1 = fileopen("data.txt", "r");
	if(f1 == NULL) {
		printf("Error in a opening a file : 'data.txt'\n");
	}
	else{
		fileread(ptr, 3, 10, f1);
		printf("%s\n", ptr);
		fileclose(f1);
	} 
	printf("Original Function : Reading a data from a file using 'r' mode\n");
	fp1 = fopen("data1.txt", "r");
	if(fp1 == NULL) {
		printf("Error in a opening a file : 'data1.txt'\n");
	}
	else {
		ptr[0] = '\0';
		fread(ptr, 3, 10, fp1);
		printf("%s\n", ptr);
		fclose(fp1);
	} 
	printf("My Function : Append Function 'a' mode\n");
	f1 = fileopen("data.txt","a");
	if(f1 == NULL) {
		printf("Error in a opening a file : data.txt");	
	}
	else {
		filewrite(str1, 3, 10, f1);
		fileclose(f1);	
	}
	
	printf("Original Function : Append Function 'a' mode \n");
	fp1 = fopen("data1.txt","a");
	if(fp1 == NULL) {
		printf("Error in a opening a file : data.txt");	
	}
	else {
		fwrite(str1, 3, 10, fp1);
		fclose(fp1);	
	}


	printf("My Function : writing and reading a data from a file using 'w+' mode\n");
	f1 = fileopen("data.txt", "w+");
	if(f1 == NULL) {
		printf("Error in opening file : data.txt");	
	}
	else {
		filewrite(str2, 3, 10, f1);
		fileread(ptr, 3, 10, f1);
		printf("%s\n", ptr);
		fileclose(f1);	
	}

	printf("Original Function : Writing and Reading a data using 'w+' mode \n");
	fp1 = fopen("data1.txt", "w+");
	if(fp1 == NULL) {
		printf("Error in opening file : data1.txt");	
	}
	else {
		fwrite(str2, 3, 10, fp1);
		ptr[0] = '\0';
		fread(ptr, 3, 10, fp1);
		printf("%s\n", ptr);
		fclose(fp1);	
	}

	printf("My Function : writing and reading a data from a file using 'r+' mode\n");
	f1 = fileopen("data.txt", "r+");
	if(f1 == NULL) {
		printf("Error in opening file : data.txt");	
	}
	else {
		filewrite(str2, 3, 10, f1);
		//fileread(ptr, 3, 10, f1);
		//printf("%s\n", ptr);
		fileclose(f1);	
	}
	printf("Original Function : writing and reading a data from a file using 'r+' mode \n");
	fp1 = fopen("data1.txt", "r+");
	if(fp1 == NULL) {
		printf("Error in opening file : data1.txt");	
	}
	else {
		fwrite(str2, 3, 10, fp1);
		fclose(fp1);	
	}
	printf("My Function : writing and reading a data from a file using 'r+' mode\n");
	f1 = fileopen("data.txt", "r+");
	if(f1 == NULL) {
		printf("Error in opening file : data.txt");	
	}
	else {
		fileread(ptr, 3, 10, f1);
		printf("%s\n", ptr);
		fileclose(f1);	
	}
	printf("Original Function : writing and reading a data from a file using 'r+' mode \n");
	fp1 = fopen("data1.txt", "r+");
	if(fp1 == NULL) {
		printf("Error in opening file : data1.txt");	
	}
	else {
		ptr[0] = '\0';
		fread(ptr, 3, 10, fp1);
		printf("%s\n", ptr);
		fclose(fp1);	
	}
	printf("My Function : writing  a data from a file using 'a+' mode\n");
	f1 = fileopen("data.txt", "a+");
	if(f1 == NULL) {
		printf("Error in opening file : data.txt");	
	}
	else {
		filewrite(str2, 3, 10, f1);
		fileclose(f1);	
	}
	printf("Original Function : writing  a data from a file using 'a+' mode \n");
	fp1 = fopen("data1.txt", "a+");
	if(fp1 == NULL) {
		printf("Error in opening file : data1.txt");	
	}
	else {
		fwrite(str2, 3, 10, fp1);
		fclose(fp1);	
	}
	printf("My Function :  reading a data from a file using 'a+' mode\n");
	f1 = fileopen("data.txt", "r+");
	if(f1 == NULL) {
		printf("Error in opening file : data.txt");	
	}
	else {
		fileread(ptr, 5, 20, f1);
		printf("%s\n", ptr);
		fileread(ptr, 5, 20, f1);
		printf("%s\n", ptr);
		fileclose(f1);	
	}
	printf("Original Function : reading a data from a file using 'a+' mode \n");
	fp1 = fopen("data1.txt", "r+");
	if(fp1 == NULL) {
		printf("Error in opening file : data1.txt");	
	}
	else {
		
		ptr[0] = '\0';
		fread(ptr, 5, 20, fp1);
		printf("%s\n", ptr);
		fread(ptr1, 5, 20, fp1);
		printf("%s\n", ptr1);
		fclose(fp1);	
	}
	printf("My Function : filefgetpos and filefsetpos\n");
	f1 = fileopen("data1.txt", "w");
	if(f1 == NULL) 
		printf("Error in Opening a file");
	else {
		filefgetpos(f1, &pos);
		filewrite(str, 2, 20, f1);
		filefsetpos(f1, &pos);
		filewrite(str1, 2, 20, f1);
	}	
	fileclose(f1);
	
	printf("My Function : fseek and ftell\n");
	f1 = fileopen("data.txt", "r");
	if(f1 == NULL) 
		printf("Error in Opening a file\n");
	else {
		filefseek(f1, 0, 2);
		n = fileftell(f1);	
		printf("ftell() = %d\n", n);
	}
	printf("Original Function : fseek and ftell\n");
	fp1 = fopen("data.txt", "r");
	if(fp1 == NULL) 
		printf("Error in Opening a file");
	else {
		fseek(fp1, 0, 2);
		n = ftell(fp1);	
		printf("ftell() = %d\n", n);
	}
	
	f1 = fileopen("data.txt", "w");
	fileclose(f1);
	fp1 = fopen("data.txt", "w");
	fclose(fp1);
	f2 = fileopen("data.txt", "r");
	fileclose(f2);
	fp2 = fopen("data.txt", "r");
	fclose(fp2);
	f3 = fileopen("data.txt", "a");
	fileclose(f3);
	fp3 = fopen("data.txt", "a");
	fclose(fp3);
	f4 = fileopen("data.txt", "w+");
	fileclose(f4);
	fp4 = fopen("data.txt", "w+");
	fclose(fp4);
	f5 = fileopen("data.txt", "r+");
	fileclose(f5);
	fp5 = fopen("data.txt", "r+");
	fclose(fp5);
	return 0;
	
}

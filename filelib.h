
#include<stddef.h>
#define BUFSIZE 1024	//Setting Buffersize to 1024
#define OPEN_MAX 20	//maximum files open at a time

//structure for fgetpos and fsetpos
typedef struct fpos {
	int pos;	//current position of file pointer in a file 
	char mod;
}fpos;

//FILE Structure
typedef struct iobuf {
	int count;	//chararcters left
	int count1;     //keeps count of number of characters read
	char *ptr;	//next character position
	char *base;	//location of buufer
	int flags;	//flag
	int fd;		//file descriptor
	char mode;	//mode of file access
	int c;		//keeps current location of pointer for fseek
}File;

File file[OPEN_MAX]; 	//array of file

#define filestdin (&file[0]) //for input
#define filestdout (&file[1]) //for output
#define filestderr (&file[2]) //for error

enum flags {
	Read = 01, //file open for reading
	Write = 02, //file open for writing
	Unbuf = 04, //file is unbuffered
	Eof = 010,  //EOF has occured on this file
	Err = 20 //Errorr occured in this file
};

#define fileeof(fp) (((fp)->flags & Eof ) != 0)		//to check End of file
#define fileerror(fp) (((fp)->flags & Err) != 0)  	//to check error
#define filenumber(fp) ((fp)->fd))			//to get the value of file descriptor


File *fileopen(char *name, char *mode);		//Equivalent to fopen

int fileclose(File *f);				//Equivalent to fclose

size_t fileread(void *ptr, size_t size, size_t nmemb, File *fp);	//Equivalent to fread

int filefillbuf(File *fp);		//Equivalent to _fillbuf

size_t filewrite(void *ptr, size_t size, size_t nmemb, File *fp);	//Equivalent to fwrite

int fileflushbuf(int c, File *fp);	//Equivalent to _flushbuf

int filefsetpos(File *fp, fpos *pos);	//Equivalent to fsetpos

int filefgetpos(File *fp, fpos *pos);	//Equivalent to fgetpos

long int fileftell(File *f);	//Equivalent to ftell

int filefseek(File *f, long offset, int whence);	//Equivalent to fseek





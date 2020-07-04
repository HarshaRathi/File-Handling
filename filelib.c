#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<stdio.h>
#include <fcntl.h>
#include<string.h>
#include "filelib.h"

#define PERMS 0666	//RW for owner, group, others

long int len = 0;	//valued returned by fileftell
int seek = 0;
long a = 0;
int b = 0;
int append = 0;		//used to dertermine mode "a+" in fileread
fpos apos;

File file[OPEN_MAX] = { 
				{0, 0, (char *)0, (char *)0, Read, 0, (char)0, 0 },
				{0, 0, (char *)0, (char *)0, Write, 1, (char)0, 0},
				{0, 0, (char *)0, (char *)0, Write|Unbuf, 2, (char)0, 0}
		      };

/*The fileopen() function opens the file whose name is the string pointed to by pathname and 
associates a stream with it*/
File *fileopen(char *name, char *mode) {
	int fd;
	File *fp;
	
	for(fp = file; fp < file + OPEN_MAX; fp++) {	//found free slot 
		if((fp->flags & (Read | Write)) == 0)
			break;
	}	

	if(fp >= file + OPEN_MAX) {	// no free slots 
		return NULL;
	}
	
	if((strcmp(mode, "r+") == 0)) {			//checking if opening mode is 'r+'	
		fd = open(name, O_RDWR, S_IWUSR|S_IRUSR);
		fp->flags = Read | Write;		//Setting a flag value
		fp->fd = fd;
		fp->mode = 'r';
		apos.mod = 'r';
		lseek(fd, 0L, 0);
	}
	else if(strcmp(mode, "w+") == 0) {		//checking if opening mode is 'w+'
		fd = creat(name, PERMS);
		fd = open(name, O_RDWR|O_CREAT, S_IWUSR|S_IRUSR);
		fp->fd = fd;
		fp->flags = Read|Write;			//Setting a flag value
		fp->mode = 'w';
		apos.mod = 'w';
 		lseek(fd, 0L, 0);
	}
	else if(strcmp(mode, "a+") == 0) {		//checking if opening mode is 'a+'
		fd = open(name, O_RDWR|O_CREAT, S_IWUSR|S_IRUSR);	
		fp->fd = fd;
		fp->flags = Read|Write;			//Setting a flag value
		fp->mode = 'a';
		apos.mod = 'a';
		lseek(fd, 0L, 2);
	}
	else if(*mode == 'w') {   			//checking if opening mode is 'w'
		fd = creat(name, PERMS);
		fd = open(name, O_WRONLY);
		fp -> flags = Write;			//Setting a flag value
		fp -> mode = 'w';
		apos.mod = 'w';
		lseek(fp->fd, 0, 0);
	}
	else if(*mode == 'r') {  			//checking if opening mode is 'r'
		fd  = open(name, O_RDONLY, S_IRUSR);
		if(fd == -1){
			return NULL;		
		}
		fp->fd = fd;
		fp->flags = Read;			//Setting a flag value
		fp->mode = 'r';
		apos.mod = 'r';
		lseek(fp -> fd, 0, 0);
	}
	else if(*mode == 'a') { 			//checking if opening mode is 'a'
		fd = open(name, O_WRONLY, 0);
		if((fd == -1)) {
			fd = creat(name, PERMS);
		}
		fp->fd = fd;
		fp->flags = Read | Write;		//Setting a flag value
		fp->mode = 'a';
		apos.mod = 'a';
		lseek(fd, 0L, 2);
	}
	else {					//if opening mode is other
		return NULL;	
	}

	if (fd == -1)         			// if couldn't access name 
		return NULL;

	fp->fd = fd;
	fp->count = 0;
	fp->base = NULL;
	fp -> count1 = 0;
	fp -> c = 0;
	return fp;
}

//fileclose function closes a file stream.
int fileclose(File *f) {
	int fd;
	if (f == NULL) {
	        return -1;
	}

    	fd = f->fd;
    	f->count = 0;
    	f->ptr = NULL;

    	if (f->base != NULL) {
        	free(f->base);
	}

   	f->base = NULL;
    	f->flags = 0;
    	f->fd = -1;	//Assigning a -1 value to the file descriptor
    	return close(fd);
}

//Fills the buffer on a call to myfread
int filefillbuf(File *fp) {
	int bufsize;

	if((fp->flags & (Read|Eof|Err)) != Read) {	//checking a opening mode
		return Eof;
	}

	bufsize = (fp->flags & Unbuf) ? 1 : BUFSIZE;

	if(fp->base == NULL) {
		if((fp->base = (char*)malloc(bufsize)) == NULL) {	//allocating buffer sized memory
			return Eof;
		}
	}

	fp->ptr = fp->base;

	fp->count = read(fp->fd,fp->ptr,bufsize);

	if(--fp->count < 0) {
		if(fp->count == -1) {
			fp->flags |= Eof;	//Setting EOF Condition
		}
		else {
			fp->flags |= Err;	//Setting ERR Condition
		}		
		fp->count = 0;
		return Eof;
	}

	return (unsigned char) *fp->ptr++;
}


/*The  function  fread()  reads  nmemb  items  of data, each size bytes long, from the stream
pointed to by stream, storing them at the location given by ptr.*/

size_t fileread(void *ptr, size_t size, size_t nmemb, File *fp) {
	int i = 0, j = 0, count = 0;
	char *tmp = ptr;
	int bytes_read = size * nmemb;
	fp->count = nmemb;

	if(fp -> mode == 'w' ||  fp -> mode == 'r' || fp -> mode == 'a') {
		if(seek == 1) {
			lseek(fp->fd, a, b); 
			seek = 0;
			a = 0;
			b = 0;
		}	

		if(fp->mode == 'a' && append == 0) {	//setting file pointer beginning of a file in a 							 "a+" mode.
			append = 1;
			lseek(fp->fd, 0, 0);		
		}
			
		count = read(fp -> fd, tmp, bytes_read);	//reading a data from a file

		if(count == 0) {
			fp -> flags = Eof;			//setting a flag to EOF
		}

		len = count;
		return count;
	}
	return count;
}

//Flushes the buffer on a call to myfwrite
int fileflushbuf(int c, File *f) {
	int num_written;

	if (((f->flags & (Write | Eof | Err)) != Write ) && ((f->flags & (Write | Eof | Err)) != (Read| 	Write ))) { //checking for a opening mode
 	 	return Eof;
	}
 
	if (f->base == NULL && ((f->flags & Unbuf) == 0)) {
        /* no buffer yet */
        	if ((f->base = malloc(BUFSIZE)) == NULL) {
           	 /* could not allocate a buffer, so try unbuffered */
           		f->flags |= Unbuf;
 		}
       		else {
	    		f->ptr = f->base;
            		f->count = BUFSIZE - 1;
        	}
	}

    	if (f->flags & Unbuf) {
        	/* unbuffered write */
        	f->ptr = f->base = NULL;
        	f->count = 0;
        	if (c == Eof) {
            		return Eof;
       		}
		return 0;
	} 
       	else {
		if (f->mode == 'a') {	//for a append mode moving a file pointer to a end of file
			lseek(f->fd, 0, 2); 	
		}
        	num_written = write(f->fd, f->base, c);	//writing a data to a file
        	f->count = BUFSIZE - 1;
    	}

    	if (num_written == c) {		//return number of bytes written in a file
	 	   return c;
    	}
    	else {				//setting a flag to error and return end of file
		f->flags |= Err;	
        	return Eof;
	}
}

//Writes 'nmemb' no. of elements each of size 'size' from the given array pointed to by pointer into the stream.
size_t filewrite(void *ptr, size_t size, size_t nmemb, File *fp) {
	int i = 0, j = 0, count = 0, c , no = 0;
	char *tmp;
	tmp = ptr;
	int bytes_to_write;
	bytes_to_write = size * nmemb;
	fp -> base = (char*)malloc(BUFSIZE);		//allocating buffer 
	fp -> count = BUFSIZE - 1;		
	c = fp -> count;
					
	if(fp -> mode == 'a') {
		lseek(fp -> fd, 0, 2);
	}

	for(i = 0; i < bytes_to_write; i = i + 1) {
		fp -> base[j] = tmp[i];
		j++;
		fp -> count--;
                no ++;
		if(no == BUFSIZE - 1) {					
			fileflushbuf(no, fp);
			if(fp->flags & Unbuf) {				//Unbuffered write
				count = write(fp->fd, tmp, sizeof(bytes_to_write));
				fp->c = fp->c + count;
				fp -> count1 = fp -> count1 + count;
				return count;			
			}
			fp->base = (char *)malloc(sizeof(BUFSIZE));	//allocating a buffer memory
			c = fp -> count;
			no = 0;	
			j = 0;
		}
		fp -> count1++;
		fp -> c++;
		count++;
	}
	if(no < BUFSIZE) {
		fileflushbuf(no, fp);	
		no = 0;
	}
	len = fp->c;		//setting pointer to current location
	return count;		//returns the number of characters write
}

//Sets the file position of the given stream to the given position. The argument pos is a position given by the function fgetpos.
int filefgetpos(File *fp, fpos *pos) {
	pos -> pos = fileftell(fp);
	return 0;
}

//Gets the current file position of the stream and writes it to pos.
int filefsetpos(File *fp, fpos *pos) {
	int whence = 0, n;
        n = lseek(fp->fd, pos->pos, whence);
	return (n > 0);	
}


//Returns the current file position of the given stream.
long int fileftell(File *fp) {
	return len;	//returns the value set by myfwrite or myfseek
}

//Sets the file position of the stream to the given offset. The argument offset signifies the number of bytes to seek from the given whence position.
int filefseek(File *fp, long offset, int whence) {	
	len = lseek(fp -> fd, offset, whence);
  	if(whence >= 3) {	
		return -1;	
	}
	a = offset;
	b = whence;
	seek = 1;
	return (len > 0);
}



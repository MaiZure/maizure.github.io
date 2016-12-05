/*  Bit shifts Traffic Department 2192 .MAP files to non-control data
*	argv[1] points to Face data file
*
* Five issues:
*  1) This program is a security nightmare - don't compile and store
*  2) No trapping, feedback, instructions, or any output whatsoever
*  3) SDL_Surface normally needs to be locked due to concurrency
*  4) Free the SDL surface - in this case, the OS does it
*  5) Void pointer implicit cast (not portable to C++)
*  6) User must preporcess input file Name and extension
*/

#include <stdio.h>	/* Opening Files */
#include <string.h>	/* Manipulating File Names */
#include <stdint.h> /* Fixed-width data types (C99) */

int main(int argc, char* argv[])
{
	FILE *fin;
	FILE *fout; 				     /* Input Pointer */
	uint16_t current_byte;			/* Named iterator */
	uint8_t FILENAME_LEN; 			/* File Name length*/
	char fname_out[12]; 			/* New filename container */
	
	/* Make output file based on input file name */
	FILENAME_LEN = strlen(argv[1]);    		/* Length of input file name */
	strncpy(fname_out,argv[1],FILENAME_LEN-3);  	/* Remove extension */
	fname_out[FILENAME_LEN-3]='\0'; 				/* Nullterm*/
	strncat(fname_out,"MP2",3);  				/* Attach new extension */
	
	/* Open Files*/
	fin = fopen(argv[1],"rb");
	fout = fopen(fname_out,"wb");
	
	/* Process byte stream */
	for(current_byte=0; current_byte < 40401; current_byte++)
	{
		fputc((fgetc(fin) + 0x20),fout);	
		fputc('\r',fout);
		fputc('\n',fout);
	}
	
	fclose(fin);
	fclose(fout);
	
	
	 
	return 0;
}
/*  Shifts Traffic Department 2192 Mission file data out of C0 and C1
*	argv[1] points to input mission data file
*/

#include <stdio.h>	/* Opening Files */
#include <string.h>	/* Manipulating File Names */
#include <stdint.h> /* Fixed-width data types (C99) */

void write_utfsafe_byte(uint16_t new_byte, uint8_t shift, FILE *fout)
{	
	fputc(shift, fout);
	fputc(new_byte, fout);
	fputc('\r',fout);
	fputc('\n',fout);
		
}

int main(int argc, char* argv[])
{
	FILE *fin;
	FILE *fout; 				     /* Input Pointer */
	uint16_t current_byte;			/* Iterator */
	uint8_t old_byte;				/* byte read in */
	uint16_t expanded_byte;
	uint8_t new_byte;	
	uint8_t shift;                	/* 32 bit shift */
	uint8_t FILENAME_LEN; 			/* File Name length*/
	char fname_out[12]; 			/* New filename container */
	
	/* Make output file based on input file name */
	FILENAME_LEN = strlen(argv[1]);    		/* Length of input file name */
	strncpy(fname_out,argv[1],FILENAME_LEN);  	/* Copy filename */
	fname_out[FILENAME_LEN-3]='M'; 				/* Punch out extention */
	fname_out[FILENAME_LEN-2]='S';
	fname_out[FILENAME_LEN]='\0';
	
	/* Open Mission File*/
	fin = fopen(argv[1],"rb");
	fout = fopen(fname_out,"wb");
	
	/* Process file sequentially */
	for(current_byte=0x00; current_byte < 0x4e70; current_byte++)
	{
		shift = 0x20;
		old_byte = fgetc(fin);
		
		/* ensure no bytes in C0 */
		expanded_byte = old_byte+0x20;
		
		/* shift and count bytes between 0x20 and 0x7f */
		while (expanded_byte > 0x7f)
		{
			expanded_byte-=0x60;
			shift+=0x01;
		}
		
		/* expanded byte should be between 0x20 and 0x7f */
		new_byte = expanded_byte;
		
		/* Grab ship types */
		if (current_byte>=0x28 && current_byte <=0x3b)
			write_utfsafe_byte(new_byte, shift, fout);
		
		/* Grab first coordinate for 20 ships */
		if (current_byte>=0x50 && current_byte <=0x275f)
			write_utfsafe_byte(new_byte, shift, fout);
		
		/* Grab second coordinate for 20 ships */
		if (current_byte>=0x2760 && current_byte <0x4e70)
			write_utfsafe_byte(new_byte, shift, fout);
	}
	fclose(fin);
	fclose(fout);
	 
	return 0;
}
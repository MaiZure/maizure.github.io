/*  SCR to BMP file converter designed for use with Traffic Department 2192 .SCR files
*	argv[1] points to .SCR file
*
* Code Issues:
*  1) This program is a security nightmare - don't compile and store
*  2) No trapping, feedback, instructions, or any output whatsoever
*  3) SDL_Surface normally needs to be locked due to concurrency
*  4) Free the SDL surface - in this case, the OS does it
*  5) Void pointer implicit cast (sorry C++ folks)
*/

#include <stdio.h>	/* Opening Files */
#include <string.h>	/* Manipulating File Names */
#include <stdint.h> /* Fixed-width data types (C99) */
#include <SDL.H>	/* Using SDL data structure */

int main(int argc, char* argv[])
{
	SDL_Surface *surface; 			/* SDL Surface struct pointer*/
	uint8_t *dst_byte;				/* Pointer to surface struct Pixels */
	FILE *fin; 						/* Input File pointer */
	uint16_t current_byte; 			/* Generic iterator */
	uint8_t palette[768]; 			/* Palette array */
	uint8_t src_byte; 				/* Single byte read from input */
	uint8_t red_p, green_p, blue_p;	/* Palette bytes by color channel*/
	uint8_t FILENAME_LEN; 			/* Length of input filename */
	char fout[12]; 					/* New filename container */
	
	/* Make surface and point to the pixel data */
	surface = SDL_CreateRGBSurface(0, 320, 200, 32, 0,0,0,0);
	dst_byte = (uint8_t*)surface->pixels;
	
	/* Open SCR File passed as argument 1*/
	fin = fopen(argv[1],"rb");
	
	/* Extract palette from first 768 bytes of SCR file */
	for (current_byte=0; current_byte<768; current_byte++)
		palette[current_byte] = fgetc(fin) << 2; 	 /* Reranging values 63 -> 252 */
	
	/* Extract 64kb of image data, match to palette, write to surface */
	for (current_byte=0; current_byte<64000; current_byte++) {
		src_byte = fgetc(fin);           /* Read Byte From File */
		red_p = palette[src_byte*3];     /* Palette Red Channel */
		green_p = palette[src_byte*3+1]; /* Palette Green Channel */
		blue_p = palette[src_byte*3+2];  /* Palette Blue Channel */
		
		dst_byte[current_byte*4]   = blue_p;	/* Set Blue channel pixel */
		dst_byte[current_byte*4+1] = green_p;   /* Set Green channel pixel */
		dst_byte[current_byte*4+2] = red_p;    	/* Set Red channel pixel */
		dst_byte[current_byte*4+3] = 0xff;      /* Set Alpha channel pixel */
	}
	fclose(fin);
	
	/* New output filename with .BMP extension */
	FILENAME_LEN = strlen(argv[1]);    		/* Length of input file name */
	strncpy(fout,argv[1],FILENAME_LEN-3);  	/* Chop off SCR extension */
	fout[FILENAME_LEN-3]='\0'; 				/* Nullterm it */
	strncat(fout,"BMP",3);  				/* Attach BMP extension */
	
	/* Save BMP*/
	SDL_SaveBMP(surface, fout); 
	
	return 0;
}
/*  Menu to BMP file converter designed for use with Traffic Department 2192 Menu files
*	argv[1] points to Face data file
*
* Five issues:
*  1) This program is a security nightmare - don't compile and store
*  2) No trapping, feedback, instructions, or any output whatsoever
*  3) SDL_Surface normally needs to be locked due to concurrency
*  4) Free the SDL surface - in this case, the OS does it
*  5) Void pointer implicit cast (not portable to C++)
*/

#include <stdio.h>	/* Opening Files */
#include <string.h>	/* Manipulating File Names */
#include <stdint.h> /* Fixed-width data types (C99) */
#include <SDL.H>	/* Using SDL data structure */

int main(int argc, char* argv[])
{
	FILE *fin, *fpal; 				/* Input File and palette file pointers */
	uint32_t FILE_SIZE;				/* Get file size */
	uint32_t IMAGE_WIDTH; 			/* Pixel width of a single frame*/
	uint32_t IMAGE_HEIGHT; 			/* Pixel width of a single frame*/
	SDL_Surface *surface; 			/* SDL Surface struct */
	uint8_t *dst_byte;				/* Pointer to surface struct Pixels */
	uint32_t current_byte;			/* Named iterator */
	uint8_t palette[768]; 			/* Palette array: 3 x 8-bit*/
	uint8_t src_byte; 				/* Single byte read from input */
	uint8_t red_p, green_p, blue_p;	/* Palette lookup bytes by color */
	uint8_t FILENAME_LEN; 			/* File Name length*/
	char fout[12]; 					/* New filename container */
	
	/* Open Menu and PAL File and find file size*/
	fin = fopen(argv[1],"rb");
	fpal = fopen("TDMEN.PAL","rb");
	
	/* Find File Size */
	fseek(fin, 0, SEEK_END);
	FILE_SIZE = ftell(fin);
	rewind(fin);
	
	/* Calculate File Metrics */
	IMAGE_WIDTH = 320;  			/* Pre-determined widths */
	IMAGE_HEIGHT = FILE_SIZE / IMAGE_WIDTH;
	
	/* Make surface strip and pixel data pointer. Each Image is 160x100 */
	surface = SDL_CreateRGBSurface(0, IMAGE_WIDTH, IMAGE_HEIGHT, 32, 0,0,0,0);
	dst_byte = surface->pixels;
	
	/* Extract image palette - guaranteed 768 bytes*/
	for (current_byte=0; current_byte<768; current_byte++)
		palette[current_byte] = fgetc(fpal) << 2;  /* Reranging values 63 -> 255 */
	fclose(fpal);
	
	/* Extract 64kb of image data, match to palette, write to surface */
	for (current_byte=0; current_byte < (IMAGE_WIDTH*IMAGE_HEIGHT); current_byte++) {
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
	strncpy(fout,argv[1],FILENAME_LEN-3);  	/* Chop off PIC extension */
	fout[FILENAME_LEN-3]='\0'; 				/* Nullterm it */
	strncat(fout,"BMP",3);  				/* Attach BMP extension */
	
	/* Save BMP*/
	 SDL_SaveBMP(surface, fout); 
	 
	return 0;
}
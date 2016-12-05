/*  Face to BMP file converter designed for use with Traffic Department 2192 NEWFACES files
*	argv[1] points to Face data file
*
* Five issues:
*  1) This program is a security nightmare - don't compile and store
*  2) No trapping, feedback, instructions, or any output whatsoever
*  3) SDL_Surface normally needs to be locked due to concurrency
*  4) Free the SDL surface - in this case, the OS does it
*  5) Void pointer implicit cast (not portable to C++)
*  6) User must preprocess input file Name and extension
*/

#include <stdio.h>	/* Opening Files */
#include <string.h>	/* Manipulating File Names */
#include <stdint.h> /* Fixed-width data types (C99) */
#include <SDL.H>	/* Using SDL data structure */

int main(int argc, char* argv[])
{
	FILE *fin; 						/* Input File pointer */
	uint32_t FILE_SIZE;				/* Get file size */
	uint8_t IMAGE_COUNT;            /* Number of packed images */
	uint16_t SURFACE_WIDTH;          /* Width of the output surface */
	SDL_Surface *surface; 			/* SDL Surface struct */
	uint8_t *dst_byte;				/* Pointer to surface struct Pixels */
	uint8_t current_image;			/* Named iterator */
	uint16_t current_byte;			/* Named iterator */
	uint8_t palette[768]; 			/* Palette array: 3 x 8-bit*/
	uint8_t src_byte; 				/* Single byte read from input */
	uint8_t red_p, green_p, blue_p;	/* Palette lookup bytes by color */
	uint8_t image_row, image_col;   /* Current image pixel location */
	uint32_t surface_offset;        /* Byte offset in surface */
	uint8_t FILENAME_LEN; 			/* File Name length*/
	char fout[12]; 					/* New filename container */
	
	/* Open Face File and find file statistics*/
	fin = fopen(argv[1],"rb");
	fseek(fin, 0, SEEK_END);
	FILE_SIZE = ftell(fin);
	rewind(fin);
	IMAGE_COUNT = FILE_SIZE/16768;
	
	/* Make surface strip and pixel data pointer. Each Image is 160x100 */
	SURFACE_WIDTH = IMAGE_COUNT * 160;
	surface = SDL_CreateRGBSurface(0, SURFACE_WIDTH, 100, 32, 0,0,0,0);
	dst_byte = surface->pixels;
	
	/* Process each image in file sequentially */
	for(current_image=0; current_image < IMAGE_COUNT; current_image++)
	{
		/* Extract image palette - guaranteed 768 bytes*/
		for (current_byte=0; current_byte<768; current_byte++)
			palette[current_byte] = fgetc(fin) << 2;  /* Reranging values 63 -> 255 */
		
		/* Extract 16kb of image data, match to palette, write to surface */
		for (current_byte=0; current_byte<16000; current_byte++) {
			src_byte = fgetc(fin);           /* Read Byte From File */
			red_p = palette[src_byte*3];     /* Lookup Red Channel */
			green_p = palette[src_byte*3+1]; /* Lookup Green Channel */
			blue_p = palette[src_byte*3+2];  /* Lookup Blue Channel */
			
			image_row = current_byte / 160; /* Int type clips fractions*/
			image_col = current_byte % 160;
			surface_offset = (current_image*160 + image_row*SURFACE_WIDTH
							  +image_col)*4;
			
			dst_byte[surface_offset] = blue_p; 		/* Set Blue channel pixel */
			dst_byte[surface_offset+1] = green_p;   /* Set Green channel pixel */
			dst_byte[surface_offset+2] = red_p;    	/* Set Red channel pixel */
			dst_byte[surface_offset+3] = 0xff;      /* Set Alpha channel pixel */
		}
	}
	fclose(fin);
	
	/* New output filename with .BMP extension */
	FILENAME_LEN = strlen(argv[1]);    		/* Length of input file name */
	strncpy(fout,argv[1],FILENAME_LEN-3);  	/* Chop off extension */
	fout[FILENAME_LEN-3]='\0'; 				/* Nullterm it */
	strncat(fout,"BMP",3);  				/* Attach BMP extension */
	
	/* Save BMP*/
	 SDL_SaveBMP(surface, fout); 
	 
	return 0;
}
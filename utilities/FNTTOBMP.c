/*  Fonts to BMP file converter designed for use with Traffic Department CIN/LTR/LT2 files
*	argv[1] points to Face data file
*
* Five issues:
*  1) This program is a security nightmare - don't compile and store
*  2) No trapping, feedback, instructions, or any output whatsoever
*  3) SDL_Surface normally needs to be locked due to concurrency
*  4) Free the SDL surface - in this case, the OS does it
*  5) Void pointer implicit cast (not portable to C++)
*  6) IMAGE_SIZE is truncated
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
	uint32_t IMAGE_HEIGHT; 			/* Pixel height of a single frame*/
	uint8_t IMAGE_COUNT;            /* Number of packed images */
	uint16_t SURFACE_WIDTH;         /* Width of the output surface */
	SDL_Surface *surface; 			/* SDL Surface struct */
	uint8_t *dst_byte;				/* Pointer to surface struct Pixels */
	uint16_t current_byte;			/* Named iterator */
	uint8_t current_image;			/* Named iterator */
	uint8_t palette[768]; 			/* Palette array: 3 x 8-bit*/
	uint8_t src_byte; 				/* Single byte read from input */
	uint8_t red_p, green_p, blue_p;	/* Palette lookup bytes by color */
	uint8_t image_row, image_col;   /* Current image pixel location */
	uint32_t surface_offset;        /* Byte offset in surface */
	uint8_t FILENAME_LEN; 			/* File Name length*/
	char fout[12]; 					/* New filename container */
	
	/* Open Font and PAL File and find file size*/
	fin = fopen(argv[1],"rb");
	fpal = fopen("TD.PAL","rb");
	
	/* Set Image Dimensions */
	if (!strcmp(argv[1],"CIN.CIN")) { IMAGE_WIDTH = 8; IMAGE_HEIGHT = 8; }
	else if (!strcmp(argv[1],"LTR.LTR")) { IMAGE_WIDTH = 12; IMAGE_HEIGHT = 16;}
	else if (!strcmp(argv[1],"LT2.LT2")) { IMAGE_WIDTH = 5; IMAGE_HEIGHT = 5;}
	
	/* Find File Size */
	fseek(fin, 0, SEEK_END);
	FILE_SIZE = ftell(fin);
	rewind(fin);
	
	/* Count the images */
	IMAGE_COUNT = FILE_SIZE / (IMAGE_WIDTH * IMAGE_WIDTH);
	
	/* Make surface strip and pixel data pointer. Each Image is 160x100 */
	SURFACE_WIDTH = IMAGE_COUNT * IMAGE_WIDTH;
	surface = SDL_CreateRGBSurface(0, SURFACE_WIDTH, IMAGE_HEIGHT, 32, 0,0,0,0);
	dst_byte = surface->pixels;
	
	/* Extract image palette - guaranteed 768 bytes*/
	for (current_byte=0; current_byte<768; current_byte++)
		palette[current_byte] = fgetc(fpal) << 2;  /* Reranging values 63 -> 255 */
	fclose(fpal);
	
	/* Process each image in file sequentially */
	for(current_image=0; current_image < IMAGE_COUNT; current_image++)
	{	
		/* Extract 16kb of image data, match to palette, write to surface */
		for (current_byte=0; current_byte<(IMAGE_WIDTH*IMAGE_HEIGHT); current_byte++) {
			src_byte = fgetc(fin);           /* Read Byte From File */
			red_p = palette[src_byte*3];     /* Lookup Red Channel */
			green_p = palette[src_byte*3+1]; /* Lookup Green Channel */
			blue_p = palette[src_byte*3+2];  /* Lookup Blue Channel */
			
			image_row = current_byte / IMAGE_WIDTH; /* Int type clips fractions*/
			image_col = current_byte % IMAGE_WIDTH;
			surface_offset = (current_image*IMAGE_WIDTH + image_row*SURFACE_WIDTH
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
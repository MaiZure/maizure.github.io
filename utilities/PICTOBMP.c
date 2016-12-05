/*  PIC to BMP file converter designed for use with Traffic Department 2192 .PIC files
*	argv[1] points to .PIC file
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
	uint8_t has_pal;				/* Bool - embedded palette? */
	uint16_t IMG_W, IMG_H; 			/* Dimensions of the image */
	SDL_Surface *surface; 			/* SDL Surface struct */
	uint8_t *dst_byte;				/* Pointer to surface struct Pixels */
	FILE *fin, *fpal; 				/* Input File and Palette pointers */
	uint32_t FILE_SIZE; 			/* Length of File*/
	uint16_t current_byte; 			/* Generic iterator */
	uint8_t palette[768]; 			/* Palette array */
	uint8_t src_byte; 				/* Single byte read from input */
	uint8_t red_p, green_p, blue_p;	/* Palette lookup bytes by color */
	uint8_t FILENAME_LEN; 			/* Length of input filename */
	char fout[12]; 					/* New filename container */
	
	/* Get image dims based on input file name */
	has_pal = 1; /* assume image has embedded palette */
	if (!strcmp(argv[1],"SECRET.PIC")) { IMG_W=320; IMG_H=32; }
	else if (!strcmp(argv[1],"TD1-13.PIC")) { IMG_W=202; IMG_H=86; }
	else if (!strcmp(argv[1],"TD1-14.PIC")) { IMG_W=200; IMG_H=200; }
	else if (!strcmp(argv[1],"TD1-15.PIC")) { IMG_W=255; IMG_H=121; }
	else if (!strcmp(argv[1],"TD1-16.PIC")) { IMG_W=150; IMG_H=170; }
	else if (!strcmp(argv[1],"TD1-17.PIC")) { IMG_W=320; IMG_H=90; has_pal = 0;}
	else if (!strcmp(argv[1],"TD1-18.PIC")) { IMG_W=170; IMG_H=104; }
	else if (!strcmp(argv[1],"TD1-19.PIC")) { IMG_W=320; IMG_H=72; has_pal = 0;}
	else if (!strcmp(argv[1],"TD1-20.PIC")) { IMG_W=320; IMG_H=100; }
	
	/* Make surface and point to the pixel data */
	surface = SDL_CreateRGBSurface(0, IMG_W, IMG_H, 32, 0,0,0,0);
	dst_byte = surface->pixels;
	
	/* Open PIC File passed as argument 1*/
	fin = fopen(argv[1],"rb");
	
	/* Get file size */
	fseek(fin,0,SEEK_END);
	FILE_SIZE = ftell(fin);
	rewind(fin);
	
	/* Extract palette from PIC file (if present) or default file*/
	fpal = has_pal ? fin : fopen("TD.PAL","rb"); 		/* set pointer to palette */
	for (current_byte=0; current_byte<768; current_byte++)
			palette[current_byte] = fgetc(fpal) << 2; 	/* Reranging values 63 -> 255 */
	
	/* Extract image data, match to palette, write to surface */
	for (current_byte=0; current_byte<FILE_SIZE-(has_pal*768); current_byte++) {
		src_byte = fgetc(fin);           /* Read Byte From File */
		red_p = palette[src_byte*3];     /* Lookup Red Channel */
		green_p = palette[src_byte*3+1]; /* Lookup Green Channel */
		blue_p = palette[src_byte*3+2];  /* Lookup Blue Channel */
		
		dst_byte[current_byte*4]   = blue_p;	/* Set Blue channel pixel */
		dst_byte[current_byte*4+1] = green_p;   /* Set Green channel pixel */
		dst_byte[current_byte*4+2] = red_p;    	/* Set Red channel pixel */
		dst_byte[current_byte*4+3] = 0xff;      /* Set Alpha channel pixel */
	}
	
	fclose(fin);
	if (!has_pal) /* Don't close file twice (posix would segfault ~20 years ago..) */
		fclose(fpal);
	
	/* New output filename with .BMP extension */
	FILENAME_LEN = strlen(argv[1]);    		/* Length of input file name */
	strncpy(fout,argv[1],FILENAME_LEN-3);  	/* Chop off PIC extension */
	fout[FILENAME_LEN-3]='\0'; 				/* Nullterm it */
	strncat(fout,"BMP",3);  				/* Attach BMP extension */
	
	/* Save BMP*/
	SDL_SaveBMP(surface, fout); 
	
	return 0;
}
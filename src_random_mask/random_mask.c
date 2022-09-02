/**
 * @file random_mask.c
 *
 * @brief Generates random images.
 *
 * @author Bati Sengul
 *
 * @version 1.3
 *
 * @section LICENSE
 *
 *    Copyright (c) 2012, Bati Sengul
 *
 *	 This program is free software: you can use, modify and/or
 *	 redistribute it under the terms of the simplified BSD License. You
 *	 should have received a copy of this license along this program. If
 *	 not, see <http://opensource.org/licenses/BSD-3-Clause>.
 *
 */ 
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "io_png.h"
#include "drawtext.h"



inline int MAX(int x, int y){
		return x<=y ? y:x;
}
inline int MIN(int x, int y){
		return x<=y ? x:y;
}

int width, height;

/**
 * @brief Generates an image on which each pixel white with probability 1/2.
 *
 * @param im Image to write on.
 */ 
void bernoulli(float *im){
		srand( time(NULL) );
		int i;
		for(i = 0; i < height*width; i++){
				if(rand() % 2 == 1){
						im[i] = 255;
						im[i + width*height] = 255;
						im[i + 2*width*height] = 255;
				}
		}
}

/**
 * @brief Generates an image of a random walk.
 *
 * @param im Image to write the random walk on.
 */ 
void rw(float *im){
		srand( time(NULL) );
		int steps = width*height/((rand() % 50) + 1);
		int i;
		int x, y;
		x = rand() % width;
		y = rand() % height;
		for(i = 0; i < steps; i++){
				switch(rand() % 4){
						case 0:
								y += 1;
								break;
						case 1:
								x -= 1;
								break;
						case 2:
								y -= 1;
								break;
						case 3:
								x += 1;
								break;
				}
				x = MIN(MAX(x,0), width-1);
				y = MIN(MAX(y,0), height-1);
				im[x + y*width] = 255;
				im[x + y*width + width*height] = 255;
				im[x + y*width + 2*width*height] = 255;
		}
}

/**
 * @brief Generates random text.
 *
 * Uses the drawtext function from Pascal Getreuer.
 *
 * @param im Image to write the random text on.
 */ 
void random_letters(float *im){
		srand( time(NULL) );
		/* Several text samples about TV inpainting */
		static const char Text0[] =
				"A coalescent process is a many particle system which evolves in time by merging particles into clusters. "
				"They have found a variety of applications in genetics where the coalescent models ancestral relationships as time runs backwards. "
				"The work on coalescents with pairs of particles merging dates back to the seminal paper of Kingman [Kin82]. "
				"In [Pit99] and [Sag99], this is extended to the case where multiple merges are allowed to happen. We defer the precise defiition to Section 3. "
				"In this paper we shall examine the Kingman's coalescent and Beta(2-a, a)-coalescents with 1 < a < 2. "
				"These have the property that they come down from infinity, that is, when starting with infinitely many particles, " 
				"the process has finitely many particles for any time t > 0. Our goal is to gain precise information. ";
		static const char Text1[] = 
				"about the behaviour near time zero by constructing a scaling limit in some suitable sense. "
				"Our limiting object will be a coalescent process with infinite mass. "
				"This requires us to change the usual definition of a coalescent process. Formally, we will be working "
				"In this article we discuss the implementation of the combined 1st and 2nd order total variation inpainting "
				"that was introduced in [13]. We describe the algorithm (split Bregman) in detail and we give some examples "
				"that indicate the difference between pure first and pure second order total variation inpainting. "
				"Finally we provide a source code for the algorithm written in C and an online demonstration for the IPOL website. ";
		static const char Text2[] =
				"Image inpainting methods can be roughly separated in four categories, depending on being variational or non-variational "
				"and local or non-local. The variational methods in contrast with the non-variational are characterised by the fact that "
				"the reconstructed image ur is obtained as a mimimiser of a certain energy functional. A method is local if the information "
				"that is needed to fill in the inpainting domain is only taken by the neighboring points of the boundary of D. "
				"Non-local or global inpainting methods take into account all the information from the known part of the image, "
				"usually weighted by its distance to the point that is to be filled in. The latter class of methods is very powerful, "
				"allowing to fill in structures and textures almost equally well. However, they still have some disadvantages. ";
		static const char Text3[] =
				"Mathematicians, those adorable and nerdy creatures... Not many people know what they actually do... "
				"or even if what they do is useful, but almost everybody has a mental picture of what they look like. "
				"Some people imagine bearded men walking aimlessly in circles while muttering words to themselves; "
				"others picture men with thick glasses making sums and multiplications all day long with a powerful "
				"mental skill; the most generous ones think of 'beautiful minds'. No, I do not do a PhD because I "
				"want to become a high school teacher, but because I want to do research. No, not everything has "
				"been discovered in Mathematics. Actually there is still a lot to be discoreved. And yes,... I wear thick glasses. ";
		const char *Text;
		int TextLength;
		char LineBuffer[1024];
		int i, j, y;

		for(y = -4; y < height; y += 28)
		{
				i = rand()%4;

				if(i == 0)
						Text = Text0;
				else if(i == 1)
						Text = Text1;
				else if(i == 2)
						Text = Text2;
				else
						Text = Text3;

				TextLength = strlen(Text);
				i = rand()%TextLength;
				j = 0;

				do
				{
						LineBuffer[j] = Text[i % TextLength];
						LineBuffer[j + 1] = '\0';
						i++;
						j++;
				}while(j < 1023 && TextWidth(LineBuffer) < width + 5);

				/* Draw the text with an 18-point sans serif font */
				DrawText(im, width, height, -2, y, LineBuffer);
		}

}

int main(int argc, char **argv){
		if(argc < 4){
				printf("Too few arguments.\n");
				printf("Syntax: random_mask [mask type] [image] [output] \n");
				printf("\t [mask type]  can be 'rw', 'rl' or 'bernoulli'\n");
				printf("\t [image]      a png image to take dimensions\n");
				printf("\t [output]     a png image to output the created image\n\n");
				printf("Example:\n");
				printf("\t random_mask rw sotiris.png random.png\n");
				return 0;
		}

		float *im = NULL;
		size_t swidth, sheight;
		im = io_png_read_f32_rgb(argv[2], &swidth, &sheight);
		if(im == NULL){
				printf("Are you sure %s is a png image?\n", argv[1]);
				return 0;
		}

		width = (int) swidth;
		height = (int) sheight;

		memset(im, 0, sizeof(float)*height*width*3);

		if( !strcmp(argv[1], "rw") )
				rw(im);
		else if( !strcmp(argv[1], "bernoulli") )
				bernoulli(im);
		else if( !strcmp(argv[1], "rl") )
				random_letters(im);
		else{
				printf("Too few arguments.\n");
				printf("Syntax: random_mask [mask type] [image] [output] \n");
				printf("\t [mask type]  can be 'rw', 'rl' or 'bernoulli'\n");
				printf("\t [image]      a png image to take dimensions\n");
				printf("\t [output]     a png image to output the created image\n\n");
				printf("Example:\n");
				printf("\t random_mask rw sotiris.png random.png\n");
				return 0;
		}

		io_png_write_f32(argv[3], im, swidth, sheight, 3);

		free(im);
		return 0;
}

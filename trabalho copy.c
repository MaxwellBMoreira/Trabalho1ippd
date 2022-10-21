#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>


int readYUV(const char *filename, uint32_t width, uint32_t height)
{
	FILE *fp;
    fp = fopen(filename, "rb");
	if(!fp)
	{
		perror("Error opening yuv image for read");
		return 1;
	}
	int	frameSize=width*height;
    unsigned char Y[width][height];
    unsigned char Y2[width][height];
    unsigned char UV[width/2][height/2];
	//*Y = malloc((width*height)*sizeof(int));

	fread(Y, sizeof(unsigned char[width][height]), 1, fp);// LE PRIMEIRO FRAME
    /*for(int i=0;i<frameSize;i++){
        Y[i]=i+1;
    }*/

    printf("!!!!\n");

	/*if (frame != frameSize) {
		perror("Error reading yuv image");
		fclose(fp);
		return 3;
	}*/


    printf("Filename: %s \nWidth: %d \nHeight: %d \nFrameSize: %d\n",filename,width,height,frameSize);
    int teste;
    scanf("%d",&teste);
    int i,j;

    for(i=0;i<width;i++){
        printf("\n");
        for(j=0;j<height;j++){
            //printf("[%d/%d=%d]  ",i,j,Y[i*height+j]);
            printf("%d  ",Y[i][j]);
        }
    }

    printf("Frame 1\n");

    
    //fread(UV, sizeof(unsigned char[width/2][height/2]), 1, fp); //LER TAMANHO UV PARA SER DESCARTADO
    printf("Lido UV 1\n");
    scanf("%d",&teste);
    fread(Y2, sizeof(unsigned char[width][height]), 1, fp); //LE SEGUNDO FRAME
    printf("Lido Frame 2\n");
    scanf("%d",&teste);
    
    for(i=0;i<width;i++){
        printf("\n");
        for(j=0;j<height;j++){
            //printf("[%d/%d=%d]  ",i,j,Y[i*height+j]);
            printf("%d  ",Y2[i][j]);
        }
 
    }

	fclose(fp);
	return 0;
}


int main(int argc, char *argv[]){


    if(argc<4)
	{
        printf("ERRO!!! Enter: ./trabalho <filename> <width> <height>");
        return 1;
    }
    const char *filename = argv[1];
    uint32_t width, height;
    const char *out;
    uint8_t *Y;

    width = atoi(argv[2]);
    height = atoi(argv[3]);
    
    // read input data and allocate output data
    if(readYUV(filename, width, height)!=0)
    {
        printf("Error reading image file, check that the file exists and has the correct format and resolution.\n");
        return 1;
    }

 }
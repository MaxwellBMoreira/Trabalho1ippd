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
    unsigned char YUV[width][height];
	//*YUV = malloc((width*height)*sizeof(int));

	fread(YUV, sizeof(unsigned char[width][height]), 1, fp);
    /*for(int i=0;i<frameSize;i++){
        YUV[i]=i+1;
    }*/
    printf("!!!!\n");

	/*if (frame != frameSize) {
		perror("Error reading yuv image");
		fclose(fp);
		return 3;
	}*/


    printf("Filename: %s \nWidth: %d \nHeight: %d \nFrameSize: %d\n",filename,width,height,frameSize);
    int i,j;

    for(i=0;i<width;i++){
        printf("\n");
        for(j=0;j<height;j++){
            //printf("[%d/%d=%d]  ",i,j,YUV[i*height+j]);
            printf("%d  ",YUV[i][j]);
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
    uint8_t *YUV;

    width = atoi(argv[2]);
    height = atoi(argv[3]);
    
    // read input data and allocate output data
    if(readYUV(filename, width, height)!=0)
    {
        printf("Error reading image file, check that the file exists and has the correct format and resolution.\n");
        return 1;
    }

 }
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>


int readYUV(const char *filename, uint32_t width, uint32_t height)
{
	/*
	//*Y = malloc((width*height)*sizeof(int));

	
    /*for(int i=0;i<frameSize;i++){
        Y[i]=i+1;
    }*/

    printf("!!!!\n");

	/*if (frame != frameSize) {
		perror("Error reading yuv image");
		fclose(fp);
		return 3;
	}


    printf("Filename: %s \nWidth: %d \nHeight: %d \nFrameSize: %d\n",filename,width,height,frameSize);
    int teste;
    scanf("%d",&teste);
    

    

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

	
	return 0;
*/
}


int main(int argc, char *argv[]){


    if(argc<4)
	{
        printf("ERRO!!! Enter: ./trabalho <filename> <width> <height>");
        return 1;
    }
    const char *filename = argv[1];
    uint32_t width, height;

    width = atoi(argv[2]);
    height = atoi(argv[3]);

    //DEFINIÇÃO DO ARQUIVO DE LEITURA E TAMANHO DOS FRAMES
    FILE *fp;
    fp = fopen(filename, "rb");
	if(!fp)
	{
		perror("Error opening yuv image for read");
		return 1;
	}

	int	frameSize=width*height;
    unsigned char reference[width][height];
    unsigned char atual[width][height];
    unsigned char U[width/4][height/4];
    unsigned char V[width/4][height/4];
    unsigned char blocoComp[8][8];
    int blockCounter=1;
    int i,j,teste;

    //leitura frame referencia

    fread(reference, sizeof(unsigned char[width][height]), 1, fp);// LE PRIMEIRO FRAME
    printf("Frame referencia lido, pressione enter para continuar\n");
    system("pause");
    for(i=0;i<width;i++){
        if(i<8)
            printf("\n");
        for(j=0;j<height;j++){
            //printf("[%d/%d=%d]  ",i,j,Y[i*height+j]);
            if(i<8 & j<8)
                printf("%d  ",reference[i][j]);
        }
    }

    //printf("Canal U\n");
    //scanf("%d",&teste);
    //leitura dos descartes
    fread(U, sizeof(unsigned char[width/4][height/4]), 1, fp);// LE PRIMEIRO FRAME
    /*for(i=0;i<width/4;i++){
        printf("\n");
        for(j=0;j<height/4;j++){
            //printf("[%d/%d=%d]  ",i,j,Y[i*height+j]);
            printf("%d  ",U[i][j]);
        }
    }*/


    //printf("Canal V\n");
    //("%d",&teste);
    fread(V, sizeof(unsigned char[width/4][height/4]), 1, fp);// LE PRIMEIRO FRAME
    /*for(i=0;i<width/4;i++){
        printf("\n");
        for(j=0;j<height/4;j++){
            //printf("[%d/%d=%d]  ",i,j,Y[i*height+j]);
            printf("%d  ",V[i][j]);
        }
    }*/

    printf("Frame atual\n");
    scanf("%d",&teste);
    fread(atual, sizeof(unsigned char[width][height]), 1, fp);// LE PRIMEIRO FRAME
    for(i=0;i<width;i++){
        printf("\n");
        for(j=0;j<height;j++){
            //printf("[%d/%d=%d]  ",i,j,Y[i*height+j]);
            printf("%d  ",atual[i][j]);
        }
    }



    //comparação entre referencia e atual
    scanf("%d",&teste);
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            //printf("[%d/%d=%d]  ",i,j,Y[i*height+j]);
            blocoComp[i][j]=reference[i][j];
        }
    }

    for(i=0;i<8;i++){
        printf("\n");
        for(j=0;j<8;j++){
            //printf("[%d/%d=%d]  ",i,j,Y[i*height+j]);
            printf("%d ",blocoComp[i][j]);
        }
    }

    fclose(fp);
    return 1;
 }
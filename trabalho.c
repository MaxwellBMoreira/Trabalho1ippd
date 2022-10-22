#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define WIDTH 176
#define HEIGHT 144
    

unsigned char frameReferencia[WIDTH][HEIGHT];
unsigned char frameAtual[WIDTH][HEIGHT];
unsigned char U[WIDTH/2][HEIGHT/2];
unsigned char V[WIDTH/2][HEIGHT/2];
unsigned char blocoProcurado[8][8];
unsigned char blocoNoFrameRef[8][8];
unsigned char matrizVizinha[24][24];




int readYUV(const char *filename)
{
	/*
	//*Y = malloc(frameSize*sizeof(int));

	
    /*for(int i=0;i<frameSize;i++){
        Y[i]=i+1;
    }*/

    //printf("!!!!\n");

	/*if (frame != frameSize) {
		perror("Error reading yuv image");
		fclose(fp);
		return 3;
	}


    printf("Filename: %s \nWidth: %d \nHEIGHT: %d \nFrameSize: %d\n",filename,WIDTH,HEIGHT,frameSize);
    int teste;
    scanf("%d",&teste);
    

    

    printf("Frame 1\n");

    
    //fread(UV, sizeof(unsigned char[WIDTH/2][HEIGHT/2]), 1, fp); //LER TAMANHO UV PARA SER DESCARTADO
    printf("Lido UV 1\n");
    scanf("%d",&teste);
    fread(Y2, sizeof(unsigned char[WIDTH][HEIGHT]), 1, fp); //LE SEGUNDO FRAME
    printf("Lido Frame 2\n");
    scanf("%d",&teste);
    
    for(i=0;i<WIDTH;i++){
        printf("\n");
        for(j=0;j<HEIGHT;j++){
            //printf("[%d/%d=%d]  ",i,j,Y[i*HEIGHT+j]);
            printf("%d  ",Y2[i][j]);
        }
 
    }

	
	return 0;
*/
}


int main(int argc, char *argv[]){


    if(argc<2)
	{
        printf("ERRO!!! Enter: ./trabalho <filename>");
        return 1;
    }
    const char *filename = argv[1];

    //DEFINIÇÃO DO ARQUIVO DE LEITURA E TAMANHO DOS FRAMES
    FILE *fp;
    fp = fopen(filename, "rb");
	if(!fp)
	{
		perror("Error opening yuv image for read");
		return 1;
	}

    FILE *out;
    out = fopen("out.yuv", "wb");
    if(!out)
	{
		perror("Error opening yuv image for read");
		return 1;
	}

	float frameSize=WIDTH*HEIGHT;

    int blockCounter=0;
    int l,c,i,j,ii,jj,pixelDif;

    //leitura frame referencia

    fread(frameReferencia, sizeof(unsigned char), frameSize, fp);// LE PRIMEIRO FRAME
    fread(U, sizeof(unsigned char), frameSize/4, fp);// LE PRIMEIRO le o primeiro U
    fread(V, sizeof(unsigned char), frameSize/4, fp);// LE PRIMEIRO FRAME

    

    /*
    fwrite(frameReferencia,sizeof(unsigned char),frameSize,out);
    fwrite(U,sizeof(unsigned char),frameSize/4,out);
    fwrite(V,sizeof(unsigned char),frameSize/4,out);
    */



    while(!feof(fp)){

    //LE O QUADRO frameAtual 
    fread(frameAtual, sizeof(unsigned char), frameSize, fp);// LE PRIMEIRO FRAME
    fread(U, sizeof(unsigned char), frameSize/4, fp);// LE PRIMEIRO le o primeiro U
    fread(V, sizeof(unsigned char), frameSize/4, fp);// LE PRIMEIRO FRAME


    //memcpy(frameAtual,frameReferencia,sizeof(frameReferencia));
 
            /*

            MONTA 1 BLOCO PRA COMPARAÇÃO (FRAME frameAtual)
            PROCURA ESSE BLOCO DE COMPARAÇÃO NO VIZINHANÇA DELE NO FRAME DE REFERENCIA
            SE ENCONTROU = ANOTA O DESLOCAMENTO

            */
    //INICIA O LOOP PARA PERCORRER TODO O FRAME frameAtual        
        for(l=0;l<HEIGHT;l=l+8)
        {
            for(c=0;c<WIDTH;c=c+8)
            {
                //MONTA BLOCO DE REFERENCIA DESTE FRAME frameAtual
                for(i=0;i<8;i++)
                {
                    for(j=0;j<8;j++)
                    {
                        blocoProcurado[i][j]=frameAtual[l+i][c+j];
                        printf("%d |",blocoProcurado[i][j]);
                    }
                    printf("\n");
                }
                printf("Bloco que desejmos procurar foi montado\n");


            //PERCORRE A VIZINHANÇA DO BLOCO frameAtual (1 BLOCO DE OFFSET)
            //printf("Matriz de Vizinnhança\n");
            for(i=l-8;i<l+16;i++)
                {
                    for(j=c-8;j<c+16;j++)
                    {
                        if(i<0 || j<0 || i>HEIGHT || j >WIDTH){//ISSO EVITA QUE ELE PEGUE VALORES DE FORA DA MATRIZ (LIXO)
                            //matrizVizinha[i][j]=0;
                        }
                        else
                        {

                        //monta bloco de comparação das vizinhanças do bloco de referencia
                        //ou seja, os blocs na volta do bloco
                        
                        for(ii=0;ii<8;ii++){
                            for(jj=0;jj<8;jj++){
                                blocoNoFrameRef[ii][jj]=frameReferencia[ii+i][jj+j];
                                printf("%d |",blocoNoFrameRef[ii][jj]);
                            }
                            printf("\n");
                        }

                        printf("Bloco comparacao montado\n");

                        pixelDif=0;//VALOR DE TOLERANCIA/DIFERENÇA ACEITAVEL ENTRE OS BLOCOS
                        for(ii=0;ii<8;ii++){
                            for(jj=0;jj<8;jj++){
                                printf("|%d-%d|=%d\n",blocoNoFrameRef[ii][jj],blocoProcurado[ii][jj],abs(blocoNoFrameRef[ii][jj]-blocoProcurado[ii][jj]));
                                pixelDif=pixelDif+abs(blocoNoFrameRef[ii][jj]-blocoProcurado[ii][jj]);
                            }
                            printf("\n");
                            system("pause");
                        }
                        system("pause");
                        printf("Diferenca: %d\n",pixelDif);
                        if(pixelDif<1000){//SE A DIFERENÇA FOR MENOR QUE MIL, CONSIDERA OS BLOCOS POSSIVELMENTE IGUAIS
                            printf("Blocos possivelmente iguais\n");
                            system("pause");
                        }

                        blockCounter++;
                

                        }

                    }
                    //printf("\n");
                }
                printf("Bloco nao encontrado na vizinhanca, %d blocos analizados\n",blockCounter/8);
                blockCounter=0;
                system("pause");
            }
        }
        printf("Novo Frame!!\n");
    }


/*
                    for(ii=0;ii<8;ii++){
                        for(jj=0;jj<8;jj++){
                            blocoNoFrameRef[ii][jj]=frameAtual[i][j];
                            printf("%d . %d |",blocoNoFrameRef[ii][jj],frameAtual[i][j]);
                        }
                        printf("\n");
                    }
                    system("pause");


                    if(memcmp(blocoProcurado,blocoNoFrameRef,sizeof(blocoNoFrameRef))==0){
                        printf("Blocos sao iguais");
                        system("pause");
                    }
                    else
                    {
                        //printf("!");
                    }
*/


    /*
    fwrite(frameAtual,sizeof(unsigned char),frameSize,out);
    fwrite(U,sizeof(unsigned char),frameSize/4,out);
    fwrite(V,sizeof(unsigned char),frameSize/4,out);
    */

   
    

    //comparação entre referencia e frameAtual
    /* 
    printf("Primeiro bloco 8x8 do quadro de referencia copiado para area de comparação");
    for(i=0;i<8;i++){
        printf("\n");
        for(j=0;j<8;j++){
            //printf("[%d/%d=%d]  ",i,j,Y[i*HEIGHT+j]);
            blocoProcurado[i][j]=frameReferencia[i][j];
            printf("%d ",blocoProcurado[i][j]);
        }
    }

   printf("\n");
    printf("primeiro Bloco 8x8 do quadro frameAtual\n");

    for(i=0;i<8;i++){
        printf("\n");
        for(j=0;j<8;j++){
            printf("%d ",frameAtual[i][j]);
        }
    }

*/

      
    fclose(fp);
    fclose(out);
    return 1;
 }  
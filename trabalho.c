/*Membros do Grupo
Gabriel Heifel
Maxwell Moreira
Rafael Martins
Willians Júnior
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define WIDTH 640
#define HEIGHT 360
#define blockSize 8
    

unsigned char frameReferencia[WIDTH][HEIGHT];
unsigned char frameAtual[WIDTH][HEIGHT];
unsigned char U[WIDTH/2][HEIGHT/2];
unsigned char V[WIDTH/2][HEIGHT/2];


//unsigned char matrizVizinha[24][24];
FILE *outVectors;



int procuraNaVizinhanca(unsigned char blocoProcurado[blockSize][blockSize],int beginLine, int beginCol, float tolerancia){

    int linJanViz,colJanViz,i,j;
    float somaErros,erroMedioGeral;
    unsigned char blocoNoFrameRef[blockSize][blockSize];

    for (linJanViz = beginLine - 8;linJanViz < beginLine + 16;linJanViz++)//loop que percorre a janela de vizinhan�a, definida por 1 bloco inteiro ao redor do procurado
        {
            for (colJanViz = beginCol - 8;colJanViz < beginCol + 16;colJanViz++)
            {
                if (linJanViz<0 || colJanViz<0 || linJanViz>HEIGHT || colJanViz >WIDTH) {//ISSO EVITA QUE ELE VERIFIQUE VALORES DE FORA DA MATRIZ (LIXO)
                    
                }
                else
                {

                    //Aqui eu monto o bloco no frame referencia para fazer a compara��o com o bloco que procuro
                    //Deve ser levado em conta a posi��o na janela de vizinhan�a que esta sendo verificado
                    for (i = 0;i < 8;i++) {
                        for (j = 0;j < 8;j++) {
                            if (i<0 || j<0 || i>HEIGHT || j >WIDTH) {//ISSO EVITA QUE ELE VERIFIQUE VALORES DE FORA DA MATRIZ (LIXO)
                                blocoNoFrameRef[i][j] = 0;
                            }
                            else {
                                blocoNoFrameRef[i][j] = frameReferencia[i + linJanViz][j + colJanViz];
                            }         
                        }
                    }

                    

                    somaErros = 0; //VAR que acumula a diferen�a entre os blocos
                    //Aqui eu realizo a compra��o entre os blocos
                    for (i = 0;i < 8;i++) {
                        for (j = 0;j < 8;j++) {
                            somaErros += abs(blocoProcurado[i][j]-blocoNoFrameRef[i][j]);
                        }
                    }

                    erroMedioGeral = somaErros / 64; //Calcula a media do erro



                    if (erroMedioGeral < tolerancia) { //se a media for menor que a tolerancia estabelecida considero os blocos iguais
                        #pragma omp critical
                        {
                        fprintf(outVectors,"Ra[%d][%d] > Rv[%d][%d] \n", beginLine, beginCol, linJanViz, colJanViz);
                        }
                        return 1; //se o bloco ja foi encontrado, entao a thread pode avan�ar para o proximo bloco
                    }     
                }
            }
        }
    return 0;
}

int procuraBlocoNaLinha(int beginLine){
    
    int i, j;
    

    double tolerancia;
    int beginCol;
    int blocosEncontrados=0;
    int res=0;
    unsigned char blocoProcurado[blockSize][blockSize];

    tolerancia = 1.3;//define a tolerancia no erro relativo a diferenca nos pixeis

    for(beginCol=0;beginCol<WIDTH;beginCol=beginCol+blockSize){
        //Monta o bloco a ser procurado usando as linhas e colunas recebidas inicialmente
        for (i = 0;i < 8;i++) {
            for (j = 0;j < 8;j++) {
                if (i<0 || j<0 || i>HEIGHT || j >WIDTH) {//ISSO EVITA QUE ELE VERIFIQUE VALORES DE FORA DA MATRIZ (LIXO)
                    blocoProcurado[i][j] = 0;
                }else{
                    blocoProcurado[i][j] = frameAtual[i + beginLine][j + beginCol];
                }            
            }
        }

        res = procuraNaVizinhanca(blocoProcurado,beginLine,beginCol,tolerancia);

        if(res==1){
           blocosEncontrados++;
        }
    }
   
    return blocosEncontrados;
}

int main(int argc, char *argv[]){


    if(argc<3)
	{
        printf("ERRO!!! Enter: ./trabalho <filename> <number of threads>");
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


    outVectors = fopen("outVectors.txt", "w");
    if(!outVectors)
	{
		perror("Error opening yuv image for read");
		return 1;
	}

	float frameSize=WIDTH*HEIGHT;
    int nThreads = atoi(argv[2]);
    int tid;

    clock_t t;
    double time_taken;

 
    omp_set_num_threads(nThreads);

    int line;
    int somaBlocos = 0;
    int res=0;



    //leitura frame referencia

    fread(frameReferencia, sizeof(unsigned char), frameSize, fp);// LE PRIMEIRO FRAME
    fread(U, sizeof(unsigned char), frameSize/4, fp);// LE PRIMEIRO le o primeiro U
    fread(V, sizeof(unsigned char), frameSize/4, fp);// LE PRIMEIRO FRAME

    

    //while(!feof(fp)){

    //LE O QUADRO frameAtual 
    fread(frameAtual, sizeof(unsigned char), frameSize, fp);// LE PRIMEIRO FRAME
    fread(U, sizeof(unsigned char), frameSize/4, fp);// LE PRIMEIRO le o primeiro U
    fread(V, sizeof(unsigned char), frameSize/4, fp);// LE PRIMEIRO FRAME

    //Reescreve o video
    fwrite(frameReferencia,sizeof(unsigned char),frameSize,out);
    fwrite(U,sizeof(unsigned char),frameSize/4,out);
    fwrite(V,sizeof(unsigned char),frameSize/4,out);
    

 
            /*

            MONTA 1 BLOCO PRA COMPARAÇÃO (FRAME frameAtual)
            PROCURA ESSE BLOCO DE COMPARAÇÃO NO VIZINHANÇA DELE NO FRAME DE REFERENCIA
            SE ENCONTROU = ANOTA O DESLOCAMENTO

            */


        t = clock();//inicia o timer;


        //INICIA O LOOP PARA PERCORRER TODO O FRAME frameAtual 
        //PARALELIZANDO AQUI, CADA THREAD FICA COM UMA LINHA PARA PROCURAR OS BLOCOS EM SUA VIZINHANÇA
        #pragma omp parallel for private (res) reduction(+:somaBlocos)
        for(line=0;line<HEIGHT;line=line+blockSize)
        {
            res = procuraBlocoNaLinha(line);
            somaBlocos += res;
        }


    //}

    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;

    printf("Total de blocos iguais encontrados: %d\n Tempo decorrido: %f segundos \n", somaBlocos,time_taken);
    



    fclose(fp);
    fclose(out);
    fclose(outVectors);
    return 1;
 }  
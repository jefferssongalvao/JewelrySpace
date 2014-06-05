#ifndef _QUICKSORT_
    #define _QUICKSORT_
        /*
         * O algoritmo Quicksort é um método de ordenação muito rápido e eficiente, 
         * inventado por C.A.R. Hoare em 19601 , quando visitou a Universidade de Moscovo como estudante. 
         * Naquela época, Hoare trabalhou em um projeto de tradução de máquina para o National Physical Laboratory. 
         * Ele criou o 'Quicksort ao tentar traduzir um dicionário de inglês para russo, ordenando as palavras, 
         * tendo como objetivo reduzir o problema original em subproblemas que possam ser resolvidos mais facil 
         * e rapidamente. Foi publicado em 1962 após uma série de refinamentos.
         */
        	// Quick Sort
                void quickSort(int vetor[], int inicio, int fim){
                    int pivo, aux, i, j, meio;

                    i = inicio;
                    j = fim;

                    meio = (int) ((i + j) / 2);
                    pivo = vetor[meio];

                    do{
                        while (vetor[i] < pivo) i = i + 1;
                        while (vetor[j] > pivo) j = j - 1;

                        if(i <= j){
                            aux = vetor[i];
                            vetor[i] = vetor[j];
                            vetor[j] = aux;
                            i = i + 1;
                            j = j - 1;
                        }
                    }while(j > i);

                    if(inicio < j) quickSort(vetor, inicio, j);
                    if(i < fim) quickSort(vetor, i, fim);

                }
#endif    
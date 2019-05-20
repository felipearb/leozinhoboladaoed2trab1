#include <stdio.h>
#include <stdlib.h>
/*
1
5
1 102 2 62
1 128 3 127
1 144 4 80
1 102 5 101
2 62 3 61
2 100 4 80
2 88 5 82
3 79 4 90
3 87 5 100
4 110 5 99
*/
struct entrada {
    int x, y, z, w;
};
  typedef  struct
    {
    int pontos,media,feitos,sofridos,id;
    }mtr;

int maiorq(mtr time1,mtr time2)//retorna 1 se time 1 e melhor ranqueado parece estar certo
{
    if(time1.pontos>time2.pontos/*caso1*/  ||  ((time1.pontos==time2.pontos)&&(time1.media>time2.media))/*caso2*/ || ((time1.pontos==time2.pontos)&&(time1.media==time2.media)&&(time1.feitos>time2.feitos))/*caso 3*/||((time1.pontos==time2.pontos)&&(time1.media==time2.media)&&(time1.feitos==time2.feitos)&&(time1.id<time2.id))/*caso4*/ )
    {
        //time1>time2
        return 1;
    }
    return 0;
}

/*void bubble(mtr *intera,int tam)// pode estar errado
{
    int c1,c2;
    mtr temp;

     for(c2=1;c2<=tam-1;c2++)// bubble sort
    {
     for(c1=0;c1<tam-c2;c1++)
        {
            if(maiorq(intera[c1],intera[c1+1]))
            {
                temp=intera[c1+1];
                intera[c1]=intera[c1+1];
                intera[c1]=temp;

            }
        }
    }
}*/


void quicksort( mtr *vetor, int inicio, int fim){//pode estra errado

   int  i, j, meio;
   mtr pivo, aux;

   i = inicio;
   j = fim;

   meio = (int) ((i + j) / 2);
   pivo = vetor[meio];

   do{
      while (maiorq(pivo,vetor[1])) i = i + 1;
      while (maiorq(vetor[j],pivo)) j = j - 1;

      if(i <= j){
         aux = vetor[i];
         vetor[i] = vetor[j];
         vetor[j] = aux;
         i = i + 1;
         j = j - 1;
      }
   }while(j > i);

   if(inicio < j) quicksort(vetor, inicio, j);
   if(i < fim) quicksort(vetor, i, fim);

}


int *solucao(struct entrada *entradas, int m, int n_teams)
{
    int *ret = (int *) malloc(n_teams * sizeof(int));

    int c1;
    int *rank;
    mtr *mtr1;

    mtr1=calloc(sizeof(mtr),n_teams);//matriz de n vetores,


    rank=calloc(sizeof(int),n_teams);


    for(c1=0;c1<n_teams;c1++)
    {
        rank[c1]=c1+1;
        mtr1[c1].id=c1+1;
    }


    for(c1=0;c1<m;c1++)//atribui os pontos de cada time
    {
        mtr1[entradas[c1].x-1].feitos+=entradas[c1].y;//soma as cestas do time entradas[c1].x
        mtr1[entradas[c1].x-1].sofridos+=entradas[c1].w;//soma as cestas sofridos do time entradas[c1].x

        mtr1[entradas[c1].z-1].feitos+=entradas[c1].w;//soma as cestas do time entradas[c1].z
        mtr1[entradas[c1].z-1].sofridos+=entradas[c1].y;//soma as cestas sofridos do time entradas[c1].z

        if(entradas[c1].w<entradas[c1].y)//soma dos pontos
        {
            mtr1[entradas[c1].x-1].pontos+=2;//vitori de x
            mtr1[entradas[c1].z-1].pontos++;
        }
        else
        {
            if(entradas[c1].w!=entradas[c1].y)
            {
                mtr1[entradas[c1].z-1].pontos+=2;//vitoria de z
                mtr1[entradas[c1].x-1].pontos++;
            }
            //empate
        }
    }

    for(c1=0;c1<n_teams;c1++)//faz media!!!
    {
        if(mtr1[c1].sofridos==0)
        {
            mtr1[c1].media=mtr1[c1].feitos;
        }
        else
        {
            mtr1[c1].media=mtr1[c1].feitos/mtr1[c1].sofridos;
        }

    }

    //bubble(mtr1,n_teams);// nao funciona com esse

    quicksort(mtr1,0,n_teams-1);// nao funciona com esse

    for(c1=0;c1<n_teams;c1++)
    {
        ret[c1]=mtr1[c1].id;
    }

    return ret;
}

int main()
{
    int *ret;
    int t, i;
    int T, N;

    scanf("%d", &T);

    for (t = 0; t < T; t++) {

        scanf("%d", &N);

        int m = (int) (N * (N - 1)/2);
        struct entrada *entradas = (struct entrada *) malloc(m * sizeof(struct entrada));
        for (i = 0; i < m; i++) {
            scanf("%d %d %d %d", &entradas[i].x, &entradas[i].y, &entradas[i].z, &entradas[i].w);
        }

        ret = solucao(entradas, m, N);

        printf("Caso de teste %d\n", t);
        for (i = 0; i < N; i++)
            if (i + 1 < N)
                printf("%d ", ret[i]);
            else
                printf("%d\n", ret[i]);
    }

    return 0;
}

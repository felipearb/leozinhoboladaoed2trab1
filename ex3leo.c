#include <stdio.h>
#include <stdlib.h>

struct entrada {
    int x, y, z, w;
};
  typedef  struct
    {
    int pontos,media,feitos,sofridos,id;
    }mtr;

int maior(mtr time1,mtr time2)//retorna 1 se time 1 e melhor ranqueado
{
    if(time1.pontos>time2.pontos/*caso1*/  ||  ((time1.pontos==time2.pontos)&&(time1.media>time2.media))/*caso2*/ || ((time1.pontos==time2.pontos)&&(time1.media==time2.media)&&(time1.pontos==time2.pontos)&&(time1.feitos>time2.feitos))/*caso 3*/||((time1.pontos==time2.pontos)&&(time1.media==time2.media)&&(time1.pontos==time2.pontos)&&(time1.feitos==time2.feitos)&&(time1.id<time2.id))/*caso4*/ )
    {
        //time1>time2
        return 1;
    }
    return 0;
}
int quicksort( mtr *vet,int ini,int fim)//ordena o bagulho
{
    int c1,c2;
    int pivo=fim;
    mtr temp;

    for(c1=ini,c2=fim-1;c1<=fim;c1++)//divide o vetor
    {
        if(maior(vet[pivo],vet[c1]))//pivo>c1
        {
            c2++;
            temp=vet[c1];
            vet[c1]=vet[c2];
            vet[c2]=temp;
        }
    }

    temp=vet[pivo];
    vet[pivo]=vet[c2+1];
    vet[c2+1]=vet[pivo];
    pivo=c2+1;//coloca o pivo no lugar certo

    quicksort(vet,pivo,fim);
    quicksort(vet,ini,pivo);
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


    for(c1=m;c1>0;c1--)//atribui os pontos de cada time
    {
        mtr1[entradas[c1].x].feitos+=entradas[c1].z;//soma as cestas do time entradas[c1].x
        mtr1[entradas[c1].x].sofridos+=entradas[c1].w;//soma as cestas sofridos do time entradas[c1].x

        mtr1[entradas[c1].y].feitos+=entradas[c1].w;//soma as cestas do time entradas[c1].y
        mtr1[entradas[c1].y].sofridos+=entradas[c1].z;//soma as cestas sofridos do time entradas[c1].y

        if(entradas[c1].w>entradas[c1].z)//soma dos pontos
        {
            mtr1[entradas[c1].x].pontos+=2;//vitori de x
            mtr1[entradas[c1].y].pontos++;
        }
        else
        {
            if(entradas[c1].w==entradas[c1].z)
            {//empate
            }
            mtr1[entradas[c1].y].pontos+=2;//vitoria de y
            mtr1[entradas[c1].x].pontos++;
        }
    }

    for(c1=0;1<n_teams;c1++)//faz media!!!
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

    //quicksort


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

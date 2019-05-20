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

int maiorq(mtr time1,mtr time2)//retorna 1 se time 1 e melhor ranqueado
{
    if(time1.pontos>time2.pontos/*caso1*/  ||  ((time1.pontos==time2.pontos)&&(time1.media>time2.media))/*caso2*/ || ((time1.pontos==time2.pontos)&&(time1.media==time2.media)&&(time1.feitos>time2.feitos))/*caso 3*/||((time1.pontos==time2.pontos)&&(time1.media==time2.media)&&(time1.feitos==time2.feitos)&&(time1.id<time2.id))/*caso4*/ )
    {
        //time1>time2
        return 1;
    }
    return 0;
}

//mergesort
void merging(mtr *a,mtr *b,int low, int mid, int high) {
   int l1, l2, i;

   for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
      if (!maiorq(a[l1],a[l2]))
         b[i] = a[l1++];
      else
         b[i] = a[l2++];
   }

   while(l1 <= mid)
      b[i++] = a[l1++];

   while(l2 <= high)
      b[i++] = a[l2++];

   for(i = low; i <= high; i++)
      a[i] = b[i];
}

void sort(mtr *a, mtr *b,int low, int high) {
   int mid;

   if(low < high) {
      mid = (low + high) / 2;
      sort(a,b,low, mid);
      sort(a,b,mid+1, high);
      merging(a,b,low, mid, high);
   } else {
      return;
   }
}

int *solucao(struct entrada *entradas, int m, int n_teams)
{
    int *ret = (int *) malloc(n_teams * sizeof(int));

    int c1;
    int *rank;
    mtr *mtr1,*mtr2;

    mtr1=calloc(sizeof(mtr),n_teams);//matriz de n vetores,
    mtr2=calloc(sizeof(mtr),n_teams);


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
            if(entradas[c1].w==entradas[c1].y)
            {//empate
            }
            mtr1[entradas[c1].z-1].pontos+=2;//vitoria de z
            mtr1[entradas[c1].x-1].pontos++;
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
    if(!maiorq(mtr1[0],mtr1[1]))
    {
        printf("deu bom");
    }
    sort(mtr1,mtr2,0,n_teams-1);


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

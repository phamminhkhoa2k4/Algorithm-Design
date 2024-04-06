#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct{
    char TenDV[30];
    float TL, GT, DG;
    int PA;
}DoVat;

void Swap(DoVat *x, DoVat *y){
    DoVat Temp = *x;
    *x = *y;
    *y = Temp;
}

int Min(int a, int b){
    return (a < b) ? a : b;
}

void BubbleSort(DoVat *dsdv, int n){
    int i, j;
    for(i = 0; i <= n - 2; i++){
        for(j = n - 1; j >= i + 1; j--){
            if(dsdv[j].DG > dsdv[j-1].DG)
                Swap(&dsdv[j], &dsdv[j-1]);
        }
    }
}

DoVat *ReadFromFile(float *W, int *n){
    FILE *f;
    f = fopen("CaiBalo1.inp", "r");
    fscanf(f, "%f", W);
    DoVat *dsdv;
    dsdv=(DoVat*)malloc(sizeof(DoVat));
    int i = 0;
    while(!feof(f)){
        fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].TenDV);
        dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
        dsdv[i].PA = 0;
        i++;
        dsdv=(DoVat*)realloc(dsdv, sizeof(DoVat) *(i+1)); 
    }
    *n = i;
    fclose(f);
    return dsdv;

}
void INDSDV(DoVat *dsdv, int n, float w){
    int i;
    float TongGT = 0.0, TongTL = 0.0;
    printf("|---|------------------|---------|---------|---------|---------|\n");
    printf("|STT|  Ten do vat      |   TL    |   GT    |   DG    |   PA    |\n");
    printf("|---|------------------|---------|---------|---------|---------|\n");
    for(i = 0; i < n; i++){
        printf("|%2d |%-18s|%9.2f|%9.2f|%9.2f|%9d|\n",i+1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
        TongTL = TongTL + dsdv[i].PA * dsdv[i].TL;
        TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
    }
    printf("|---|------------------|---------|---------|---------|---------|\n");
    printf("Trong luong cua balo = %.2f\n",w);
    printf("Tong trong luong cua do vat = %.2f\n", TongTL);
    printf("Tong gia tri cua do vat = %.2f\n", TongGT);
    printf("Phuong an X (");
    for(int i = 0 ; i < n; i++){
        printf("%d",dsdv[i].PA);
        if(i != (n - 1))
            printf(", ");
    }
    printf(")");

}
 void TaoNutGoc(float W, float *CT, float *TGT, float *TLConlai, float *GiaLNTT, float DGLN){
     *TGT = 0.0;
     *GiaLNTT = 0.0;
     *TLConlai = W;
     *CT = W * DGLN;

 }

void CapnhatPA_TNTT(DoVat *dsdv, int x[], int n, float *GiaLNTT, float TGT){
    if(*GiaLNTT < TGT){
        *GiaLNTT = TGT;
        for(int i = 0; i < n; i++){
            dsdv[i].PA = x[i];
        }
    }
}

void NhanhCan(DoVat *dsdv, int x[], int n, int i, float *TGT, float *GiaLNTT, float *TLConlai, float *CT){
    int j;
    int SDVMAX;
    SDVMAX = *TLConlai/dsdv[i].TL;

    for(j = SDVMAX; j >= 0; j--){
        *TGT = *TGT + j*dsdv[i].GT;
        *TLConlai = *TLConlai - j*dsdv[i].TL;
        *CT = *TGT + *TLConlai * dsdv[i+1].DG;

        if(*CT > *GiaLNTT){
            x[i] = j;
            if(i == n - 1 || (*TLConlai == 0))
                CapnhatPA_TNTT(dsdv, x, n, GiaLNTT, *TGT);
            else
                NhanhCan(dsdv, x, n, i+1, TGT, GiaLNTT, TLConlai, CT);
        }
    

    x[i] = 0;
    *TGT = *TGT - j*dsdv[i].GT;
    *TLConlai = *TLConlai + j*dsdv[i].TL;
	}

}

int main(){
    DoVat *dsdv;
    int n;
    float W, CT, TGT, TLConlai, GiaLNTT;
    
    dsdv = ReadFromFile(&W, &n);
    int x[n];   //Luu phuong an tot nhat tam thoi
    BubbleSort(dsdv, n);

    TaoNutGoc(W,&CT,&TGT,&TLConlai,&GiaLNTT,dsdv[0].DG);
    NhanhCan(dsdv, x, n, 0, &TGT, &GiaLNTT, &TLConlai, &CT);

    INDSDV(dsdv, n, W);

    free(dsdv);
    return 0;
}






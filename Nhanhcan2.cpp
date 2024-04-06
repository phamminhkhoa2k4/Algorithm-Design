#include<stdio.h>
#include<malloc.h>
typedef struct{
    char TenDV[20];
    float TL, GT, DG;
    int SL, PA;
}DoVat;
void Swap(DoVat *x, DoVat *y){
    DoVat Temp = *x;
    *x = *y;
    *y = Temp;
}
DoVat *ReadFromFile(float *W,int *n){
	FILE *f;
	f = fopen("CaiBalo2.inp", "r");
	fscanf(f, "%f", W);
	DoVat *dsdv;
	dsdv=(DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while (!feof(f)){
	fscanf(f, "%f%f%d%[^\n]",&dsdv[i].TL,&dsdv[i].GT,&dsdv[i].SL,&dsdv[i].TenDV);
	dsdv[i].DG=dsdv[i].GT/dsdv[i].TL; 
	dsdv[i].PA=0;
	i++;
	dsdv=(DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1)); 
	}
	*n=i;
	fclose(f);
	return dsdv; 
}
void TaoNutGoc(float W, float  *TLConlai, float *CT, float *GiaLNTT, float *TGT, float DGLN){
    *TGT = 0.0;
    *TLConlai = W;
    *CT = *TLConlai * DGLN; //Can tren cua nut goc
    *GiaLNTT = 0.0;
}
//Cap nhat phuong an tot nhat tam thoi
void CapNhatPA_TNTT(float TGT, float *GiaLNTT, int x[], DoVat *dsdv, int n){
        if(*GiaLNTT < TGT){
            *GiaLNTT = TGT;
            for(int i = 0; i < n; i++){
                dsdv[i].PA = x[i];
            }
        }
}
int min(int a, int b){
    return (a < b) ? a : b;
}

void NhanhCan(int i, float *TGT, float *CT, float *TLConlai, float *GiaLNTT, int x[], DoVat *dsdv, int n){
    int j;  //So do vat duoc chon
    int SDVLN;  //So do vat lon nhat co the chon
    SDVLN = min(dsdv[i].SL, *TLConlai/dsdv[i].TL);

    for(j = SDVLN; j >= 0; j--){        //xet tat ca cac kha nang co the phan nhanh theo do vat i
        //ung voi 1 gia tri cua j, ta co 1 nut tren cay
        *TGT = *TGT + j*dsdv[i].GT;
        *TLConlai = *TLConlai - j*dsdv[i].TL;
        *CT = *TGT + *TLConlai*dsdv[i+1].DG;     //dsdv[i+1].DG: DG cua vat ke tiep

        if(*CT > *GiaLNTT){         //Neu CT <= GiaLNTT thi cat tia 
            x[i] = j;
            if((i == n - 1) || (*TLConlai == 0))        //Xet tat ca cac do vat hoac da day balo
                CapNhatPA_TNTT(*TGT, GiaLNTT, x, dsdv, n);
            else
                NhanhCan(i+1, TGT, CT, TLConlai, GiaLNTT, x, dsdv, n);      //Xet nut con cua i
        }

        //Quay lui de xet nut khac, ung voi gia tri khac cua j
        x[i] = 0;
        *TGT = *TGT - j*dsdv[i].GT;                 //Tra lai tong gia tri cua nut cha
        *TLConlai = *TLConlai + j*dsdv[i].TL;       //Tra lai trong luong con lai cua nut cha
    }

}
void InDSDV(DoVat *dsdv, int n, float w){
	int i;
	float TongTL=0.0, TongGT=0.0;
	printf("\nPhuong an Cai Ba lo 2 dung thuat toan THAM AN nhu sau:\n");
	printf("|---|------------------|---------|---------|---------|-----------|-----------|\n");
	printf("|STT| Ten Do Vat       | T Luong | Gia Tri |So Luong | Don Gia   | Phuong an |\n");
	printf("|---|------------------|---------|---------|---------|-----------|-----------|\n");
	for(i = 0; i < n; i++){
		printf("|%2d |%-18s|%9.2f|%9.2f|%9d|%11.2f|%11d|\n",i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].SL,dsdv[i].DG,dsdv[i].PA);
		TongTL = TongTL + dsdv[i].PA * dsdv[i].TL;
		TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
	}
	printf("|---|------------------|---------|---------|---------|-----------|-----------|\n");
	printf("Trong luong cua ba lo = %-9.2f\n",w);
	printf("Tong trong luong = %-9.2f\n",TongTL);
	printf("Tong gia tri = %-9.2f\n",TongGT);
	printf("Phuong an X (");
	for(int i = 0; i < n; i++){
		printf("%d",dsdv[i].PA);
		if(i != (n - 1))	printf(",");
	}
	printf(")");
}
void BubbleSort(DoVat *dsdv, int n){
	int i,j;
	for(i = 0; i <= n - 2; i++)
		for (j  = n - 1; j >= i + 1; j--){
			if (dsdv[j].DG > dsdv[j - 1].DG)
				Swap(&dsdv[j], &dsdv[j - 1]);
		}  
}
int main(){
    DoVat *dsdv;
    int n;
    float W, CT, TGT, TLConlai, GiaLNTT;
    
    dsdv = ReadFromFile(&W, &n);
    int x[n];   //Luu phuong an tot nhat tam thoi
    BubbleSort(dsdv, n);

    TaoNutGoc(W, &TLConlai, &CT, &GiaLNTT, &TGT, dsdv[0].DG);
    NhanhCan(0, &TGT, &CT, &TLConlai, &GiaLNTT, x, dsdv, n);

    InDSDV(dsdv, n, W);

    free(dsdv);
    return 0;
    
}

#include <stdio.h>

typedef int keytype;
typedef float othertype;
typedef struct {
	keytype key;
	othertype otherfields;
} recordtype;

void Swap(recordtype &x, recordtype &y){
	recordtype temp;
	temp = x;
	x = y;
	y = temp;
}

int FindPivot(recordtype a[], int i, int j){
	keytype firstkey;
	int k = i + 1;
	firstkey = a[i].key;
	while( (k <= j) && (a[k].key == firstkey) )
		k++;
	if(k > j)
		return -1;
	if(a[k].key > firstkey)
		return k;
	return i;
}

int Partition(recordtype a[], int i, int j, int pivot){
	int L, R;
	L = i;
	R = j;
	while(L <= R){
		while(a[L].key < pivot)
			L++;
		while(a[R].key >= pivot)
			R--;
		if(L < R)
			Swap(a[L], a[R]);
		
	}
	return L;
}

void QuickSort(recordtype a[], int i, int j){
	keytype pivot;
	int pivotindex, k;
	pivotindex = FindPivot(a, i, j);
	if(pivotindex != -1){
		pivot = a[pivotindex].key;
		k = Partition(a, i, j, pivot);
		QuickSort(a, i, k - 1);
		QuickSort(a, k, j);
	}
}

int main(){
	recordtype a[100];
	int n;
	FILE* file = fopen("dayso.inp", "r");
	fscanf(file, "%d", &n);
	for(int i = 0; i < n; i++){
		fscanf(file, "%d", &a[i]);
	}
	printf("\nThuat toan QuickSort\n\n");
	printf("Day so truoc khi sap xep: \n");
	for(int i = 0; i < n; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
	QuickSort(a, 0, n - 1);
	
	printf("Day so sau khi sap xep: \n");
	for(int i = 0; i < n; i++){
		printf("%d ", a[i]);
	}
}

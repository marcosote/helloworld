#include<stdio.h>
#include<stdlib.h>
#define SIZE_OF_LINE 255

void free_matrix(int n, int m, int ** matrix){
	int i;
	free(matrix);
	for(i=0;i<n;i++){
		free(matrix[i])
	}

}

void print_matrix(int n, int m, int **matrix){
	int i, j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++){
			printf("%d\t",matrix[i][j]);
		}
		printf("\n");
	}
}
int** read_matrix(const char* filename, int* n, int* m){
	int i, row=0;
	int **matrix=NULL;
	int index;
	char line[SIZE_OF_LINE], token; 

	FILE * f=fopen(filename,"r");
	if( f==NULL) {
		puts("error when opening file");
		return 0;
	}

	while(!feof(f)){
		//protocol (extracts headers)
		fscanf(f, "%c",&token);
		if(token=='d'){
			fgets(line, SIZE_OF_LINE, f);
			if(sscanf(line,"%d %d",n,m)!=2)
			{
				puts("error when reading dimension");
				return NULL;
			}
			//dynamic allocation of memory
			matrix=(int **)malloc(sizeof(int*)*(*n));//(int**) casting para convertirlo en puntero
			for(index=0;index<(*n);index++){
				matrix[index]=(int*)malloc(sizeof(int)*(*m));
			}

		}
		else if(token=='r'){
			//read elements one by one, for each row
			for(i=0;i<(*m);i++){
				fscanf(f,"%d",&matrix[row][i]);
			}
			//read what is left of this line
			fgets(line, SIZE_OF_LINE,f);
			row++;
		}
		//protocol using swith-case
		//***
		else{
			puts("unrecognized protocol");
			return 0;
		}

	}
	return matrix;
}
void main(){
//client application
	int n, m;
	int ** matrix;
	matrix=read_matrix("matriz.txt", &n, &m);
	print_matrix(n, m,matrix);
	free_matrix(n, m, matrix);
}

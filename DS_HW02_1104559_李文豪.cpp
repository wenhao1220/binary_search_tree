#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void inorder(int tree[], char type[], int i);
void deletion_right(int tree[], char type[], int i, int j);
void deletion_left(int tree[], char type[], int i, int j);

int main(){
	
	int n, degree = 0, i, a = 0, j, layer = 1, add;
	char option;
	
	printf("Please input a number: "); 
	scanf("%d", &n);//輸入這棵樹的root
	
	int tree[10000]; //宣告一個陣列儲存樹裡面的值 
	char type[10000]; //宣告一個陣列判斷該值是否為空值 
	
	for(i = 0; i < 10000; i++) //將陣列tree 1~10000的值設為-1 
		tree[i] = -1;
	
	for(i = 0; i < 10000; i++) //將陣列type 1~10000的值設為f
		type[i] = 'f';
	
	tree[0] = n;
	type[0] = 't';

	scanf("%c", &option); //輸入一個選項 
	while(a == 0){
		
		printf("Please input a option: ");
		scanf("%c", &option);
		if(option == 't'){ //如果輸入t，則顯示inorder的值以及圖形介面 
			printf("Inorder: ");
			inorder(tree, type, 0); //呼叫inorder函數 
			printf("\n\n");
			
			//輸出圖形介面 
			int l = 1;
			for(j = 0; j < pow(2,layer)-1; j++){ //
				if(type[j] == 'f'){
					if(j == (int)pow(2,l-1)-1){
						for(i = 0; i < (int)pow(2, layer-l)-1; i++)
							printf("%4c", ' ');
					}else{
						for(i = 0; i < (int)pow(2, layer-l+1)-1; i++)
							printf("%4c", ' ');
					}
					
					printf("%3c ", 'x');
				}else{
					if(j == (int)pow(2,l-1)-1){
						for(i = 0; i < (int)pow(2, layer-l)-1; i++)
							printf("%4c", ' ');
					}else{
						for(i = 0; i < (int)pow(2, layer-l+1)-1; i++)
							printf("%4c", ' ');
					}
					
					printf("%3d ", tree[j]);
				}
				
				if(j == (int)pow(2,l)-2){
					printf("\n");
					l++;
				}
			}
			printf("\n");
		}else if(option == 'i'){ //如果輸入i，則選擇要插入的樹 
			printf("Please input a number you want to insert: ");
			scanf("%d", &n);
			i = 0;
			do{
				if(n < tree[i]){
					if((i + 1) * 2 - 1 >= pow(2, layer)-1)
						layer++;
					i = (i + 1) * 2 - 1;
				}else{
					if((i + 1) * 2 - 1 >= pow(2, layer)-1)
						layer++;
					i = (i + 1) * 2;
				}
			}while(type[i] != 'f');
			
			tree[i] = n;
			type[i] = 't';
			
		}else if(option == 'd'){
			printf("Please input a number you want to delete: ");
			scanf("%d", &n);
			i = 0;
			do{
				if(type[i] == 'f' || i >= pow(2, layer)-1){
					printf("Error, %d is not in this tree.\n", n);
					break;
				}else if(n < tree[i]){
					i = (i + 1) * 2 - 1;
				}else if(n > tree[i]){
					i = (i + 1) * 2;
				}else if(n == tree[i]){
					if(type[(i+1)*2-1] == 'f' && type[(i+1)*2] == 'f'){
						tree[i] = -1;
						type[i] = 'f';
					}else if(type[(i+1)*2-1] == 'f'){
						deletion_right(tree, type, i, (i+1)*2);
					}else if(type[(i+1)*2] == 'f'){
						deletion_left(tree, type, i, (i+1)*2-1);
					}else{
						j = i;
						i = (i+1)*2-1;
						while(type[(i+1)*2] == 't'){
							i = (i+1)*2;
						}
						tree[j] = tree[i];
						type[i] = 'f';
						
						if(type[(i+1)*2-1] == 't')
							deletion_left(tree, type, i, (i+1)*2-1);
					}
					break;
				}
			}while(1);
		}else if(option == 's'){
			printf("Please input a number you want to search: ");
			scanf("%d", &n);
			i = 0;
			do{
				if(type[i] == 'f' || i >= pow(2, layer)-1){
					printf("Error, %d is not in this tree.\n", n);
					break;
				}else if(n < tree[i]){
					i = (i + 1) * 2 - 1;
				}else if(n > tree[i]){
					i = (i + 1) * 2;
				}else if(n == tree[i]){
					printf("%d's index value = %d\n", n, i);
					break;
				}
			}while(1);
		}else if(option == 'q'){
			a = 1;
		}
		
		scanf("%c", &option);
	}
	
	return 0;
}

void inorder(int tree[], char type[], int i){
	if(type[(i+1)*2-1] == 't')
		inorder(tree, type, (i+1)*2-1);
		
	printf("%d ", tree[i]);
	
	if(type[(i+1)*2] == 't')
		inorder(tree, type, (i+1)*2);
}

void deletion_right(int tree[], char type[], int i, int j){
	tree[i] = tree[j];
	type[i] = 't';
	type[j] = 'f';
	
	if(type[(j + 1) * 2 - 1] == 't'){
		i = j - 1;
		j = (j + 1) * 2 - 1;
		deletion_right(tree, type, i, j);
	}
	if(type[(i + 1) * 2] == 't'){
		i = j;
		j = (j + 1) * 2;
		deletion_right(tree, type, i, j);
	}
}

void deletion_left(int tree[], char type[], int i, int j){
	tree[i] = tree[j];
	type[i] = 't';
	tree[j] = -1;
	type[j] = 'f';
	
	if(type[(j + 1) * 2 - 1] == 't'){
		i = j;
		j = (j + 1) * 2 - 1;
		deletion_left(tree, type, i, j);
	}
	
	if(type[(i + 1) * 2] == 't'){
		i = j + 1;
		j = (j + 1) * 2;
		deletion_left(tree, type, i, j);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

void inorder(int tree[], char type[], int i);
void deletion_right(int tree[], char type[], int i, int j);
void deletion_left(int tree[], char type[], int i, int j);

int main(){
	
	int n, degree = 0, i, a = 0, j, layer = 1, add;
	char option, s[100];
	
	printf("Please input a number: "); //輸入一個數字當作root
	while(scanf("%d", &n) != 1){ //若是輸入英文則重新輸入
		scanf("%s", s);
		printf("Please do not input an English.\n");
		printf("Please input a number: ");
	}
	
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
		
		do{
			scanf("%c", &option);
			if(isdigit(option)){ //若是輸入數字則重新輸入 
				printf("Please do not input a number\n");
				printf("Please input a option: ");
			}
		}while(!isalpha(option));
		
		if(option == 't'){ //如果輸入t，則顯示inorder的值以及圖形介面
			printf("Inorder: ");
			inorder(tree, type, 0); //呼叫inorder函數
			printf("\n\n");
			
			//輸出圖形
			int l = 1;
			for(j = 0; j < pow(2,layer)-1; j++){
				if(type[j] == 'f'){
					if(j == (int)pow(2,l-1)-1){ //判斷需要輸入幾個空格 
						for(i = 0; i < (int)pow(2, layer-l)-1; i++)
							printf("%4c", ' '); 
					}else{
						for(i = 0; i < (int)pow(2, layer-l+1)-1; i++)
							printf("%4c", ' ');
					}
					
					printf("%3c ", 'x'); //若node裡沒有數字，則輸出x 
				}else{
					if(j == (int)pow(2,l-1)-1){ //判斷需要輸入幾個空格
						for(i = 0; i < (int)pow(2, layer-l)-1; i++)
							printf("%4c", ' ');
					}else{
						for(i = 0; i < (int)pow(2, layer-l+1)-1; i++)
							printf("%4c", ' ');
					}
					
					printf("%3d ", tree[j]); //輸出node裡的key 
				}
				
				if(j == (int)pow(2,l)-2){ //換到下一層繼續輸出圖形 
					printf("\n");
					l++;
				}
			}
			printf("\n");
		}else if(option == 'i'){ //如果輸入i，則選擇要插入的key
			printf("Please input a number you want to insert: ");
			while(scanf("%d", &n) != 1){ //若是輸入英文則重新輸入
				scanf("%s", s);
				printf("Please do not input an English.\n");
				printf("Please input a number you want to insert: ");
			}
			i = 0;
			
			//往下搜尋到正確的位置 ，把新的key加入tree中
			do{
				if(n < tree[i]){ //尋找key的位置 
					if((i + 1) * 2 - 1 >= pow(2, layer)-1)
						layer++;
					i = (i + 1) * 2 - 1;
				}else if(n > tree[i]){
					if((i + 1) * 2 - 1 >= pow(2, layer)-1)
						layer++;
					i = (i + 1) * 2;
				}else{
					printf("The number is already in the tree.\n"); //若key已存在，則輸出已存在 
					break;
				}
			}while(type[i] != 'f');
			
			if(n != tree[i]){ //插入新的key 
				tree[i] = n;
				type[i] = 't';
			}
			
		}else if(option == 'd'){ //如果輸入d，則選擇要刪除的node
			printf("Please input a number you want to delete: ");
			scanf("%d", &n);
			i = 0;
			do{
				if(type[i] == 'f' || i >= pow(2, layer)-1){ //如果沒有搜尋到需要刪除的值，則輸出錯誤訊息 
					printf("Error, %d is not in this tree.\n", n);
					break;
				}else if(n < tree[i]){ //搜尋需要刪除的值 
					i = (i + 1) * 2 - 1; 
				}else if(n > tree[i]){
					i = (i + 1) * 2;
				}else if(n == tree[i]){ //刪除搜尋到的值 
					if(type[(i+1)*2-1] == 'f' && type[(i+1)*2] == 'f'){ //degree為0時 
						tree[i] = -1;
						type[i] = 'f';
					}else if(type[(i+1)*2-1] == 'f'){ //degree為1時 (只有右子樹) 
						deletion_right(tree, type, i, (i+1)*2); //呼叫 deletion_right函數 
					}else if(type[(i+1)*2] == 'f'){ //degree為1時 (只有左子樹)
						deletion_left(tree, type, i, (i+1)*2-1); //呼叫 deletion_left函數
					}else{ //degree為2時
						j = i;
						i = (i+1)*2-1;
						while(type[(i+1)*2] == 't'){
							i = (i+1)*2;
						}
						tree[j] = tree[i];
						type[i] = 'f';
						
						if(type[(i+1)*2-1] == 't')
							deletion_left(tree, type, i, (i+1)*2-1); //呼叫 deletion_left函數
					}
					break;
				}
			}while(1);
		}else if(option == 's'){ //如果輸入s，則選擇要搜尋的node
			printf("Please input a number you want to search: ");
			scanf("%d", &n);
			i = 0;
			do{
				if(type[i] == 'f' || i >= pow(2, layer)-1){ //如果沒有搜尋到需要刪除的值，則輸出錯誤訊息  
					printf("Error, %d is not in this tree.\n", n);
					break;
				}else if(n < tree[i]){
					i = (i + 1) * 2 - 1;
				}else if(n > tree[i]){
					i = (i + 1) * 2;
				}else if(n == tree[i]){
					printf("%d's index value = %d\n", n, i+1);
					break;
				}
			}while(1);
		}else if(option == 'q'){ //如果輸入q，則離開程式 
			a = 1;
		}
		
		scanf("%c", &option);
	}
	
	return 0;
}

void inorder(int tree[], char type[], int i){
	if(type[(i+1)*2-1] == 't') //L 
		inorder(tree, type, (i+1)*2-1);
		
	printf("%d ", tree[i]); //V
	
	if(type[(i+1)*2] == 't') //R
		inorder(tree, type, (i+1)*2);
}

void deletion_right(int tree[], char type[], int i, int j){ //右邊的樹往左移 
	tree[i] = tree[j];
	type[i] = 't';
	tree[j] = -1;
	type[j] = 'f';
	
	//開始移動樹直到所有值都移完為止 
	if(type[(j + 1) * 2 - 1] == 't'){ //左下往左上移 
		i = j - 1;
		j = (j + 1) * 2 - 1;
		deletion_right(tree, type, i, j);
	}
	if(type[(j + 1) * 2] == 't'){ //右下往左上移 
		i = j;
		j = (j + 1) * 2;
		deletion_right(tree, type, i, j);
	}
}

void deletion_left(int tree[], char type[], int i, int j){ //左邊的樹往右移 
	tree[i] = tree[j];
	type[i] = 't';
	tree[j] = -1;
	type[j] = 'f';
	
	//開始移動樹直到所有值都移完為止
	if(type[(j + 1) * 2 - 1] == 't'){ //左下往右上移 
		i = j;
		j = (j + 1) * 2 - 1;
		deletion_left(tree, type, i, j);
	}
	
	if(type[(j + 1) * 2] == 't'){ //右下往右上移 
		i = j + 1;
		j = (j + 1) * 2;
		deletion_left(tree, type, i, j);
	}
}

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
	scanf("%d", &n);//��J�o�ʾ�root
	
	int tree[10000]; //�ŧi�@�Ӱ}�C�x�s��̭����� 
	char type[10000]; //�ŧi�@�Ӱ}�C�P�_�ӭȬO�_���ŭ� 
	
	for(i = 0; i < 10000; i++) //�N�}�Ctree 1~10000���ȳ]��-1 
		tree[i] = -1;
	
	for(i = 0; i < 10000; i++) //�N�}�Ctype 1~10000���ȳ]��f
		type[i] = 'f';
	
	tree[0] = n;
	type[0] = 't';

	scanf("%c", &option); //��J�@�ӿﶵ 
	while(a == 0){
		
		printf("Please input a option: ");
		scanf("%c", &option);
		if(option == 't'){ //�p�G��Jt�A�h���inorder���ȥH�ιϧΤ��� 
			printf("Inorder: ");
			inorder(tree, type, 0); //�I�sinorder��� 
			printf("\n\n");
			
			//��X�ϧΤ��� 
			int l = 1;
			for(j = 0; j < pow(2,layer)-1; j++){
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
		}else if(option == 'i'){ //�p�G��Ji�A�h��ܭn���J��node
			printf("Please input a number you want to insert: ");
			scanf("%d", &n);
			i = 0;
			
			//���U�j�M�쥿�T����m �A��s��node�[�Jtree�� 
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
			
		}else if(option == 'd'){ //�p�G��Jd�A�h��ܭn�R����node
			printf("Please input a number you want to delete: ");
			scanf("%d", &n);
			i = 0;
			do{
				if(type[i] == 'f' || i >= pow(2, layer)-1){ //�p�G�S���j�M��ݭn�R�����ȡA�h��X���~�T�� 
					printf("Error, %d is not in this tree.\n", n);
					break;
				}else if(n < tree[i]){ //�j�M�ݭn�R������ 
					i = (i + 1) * 2 - 1; 
				}else if(n > tree[i]){
					i = (i + 1) * 2;
				}else if(n == tree[i]){ //�R���j�M�쪺�� 
					if(type[(i+1)*2-1] == 'f' && type[(i+1)*2] == 'f'){ //degree��0�� 
						tree[i] = -1;
						type[i] = 'f';
					}else if(type[(i+1)*2-1] == 'f'){ //degree��1�� 
						deletion_right(tree, type, i, (i+1)*2); //�I�s deletion_right��� 
					}else if(type[(i+1)*2] == 'f'){ //degree��1�� 
						deletion_left(tree, type, i, (i+1)*2-1); //�I�s deletion_left���
					}else{ //degree��2��
						j = i;
						i = (i+1)*2-1;
						while(type[(i+1)*2] == 't'){
							i = (i+1)*2;
						}
						tree[j] = tree[i];
						type[i] = 'f';
						
						if(type[(i+1)*2-1] == 't')
							deletion_left(tree, type, i, (i+1)*2-1); //�I�s deletion_left���
					}
					break;
				}
			}while(1);
		}else if(option == 's'){ //�p�G��Jd�A�h��ܭn�j�M��node
			printf("Please input a number you want to search: ");
			scanf("%d", &n);
			i = 0;
			do{
				if(type[i] == 'f' || i >= pow(2, layer)-1){ //�p�G�S���j�M��ݭn�R�����ȡA�h��X���~�T��  
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
		}else if(option == 'q'){ //�p�G��Jd�A�h���}�{�� 
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

void deletion_right(int tree[], char type[], int i, int j){ //�k�䪺�𩹥��� 
	tree[i] = tree[j];
	type[i] = 't';
	type[j] = 'f';
	
	//�}�l���ʾ𪽨�Ҧ��ȳ��������� 
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

void deletion_left(int tree[], char type[], int i, int j){ //���䪺�𩹥k�� 
	tree[i] = tree[j];
	type[i] = 't';
	tree[j] = -1;
	type[j] = 'f';
	
	//�}�l���ʾ𪽨�Ҧ��ȳ���������
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

//bcc32 $
//$(base).exe
//stop

#include<stdio.h>
#include<windows.h>

#define NORMAL		0
#define SPARE		1
#define STRIKE		2
#define D_STRIKE	3

//�X�R�A���Z�̃p�^�[��
int scp[4][4][31]={0};	
int scp_10[4][61]={0};	

void make_scp(void);	//���Z�p�^�[���z��쐬
void calc(int f);		//�t���[�����Ƃ̌v�Z
static __int64 score[4][301]={1};	//�g�ݍ��킹�z��
static __int64 score_n[4][301]={0};	//�X�V��g�ݍ��킹�z��

int main(){
	int i,input;
	
	//�z�񐶐�
	make_scp();
	
	//10�t���[���܂Ōv�Z
	for(i=1; i<=10; i++)calc(i);	
	
	//input�ɉ����ăf�[�^��\��
	while(1){
		printf("input number(0-300) >");
		scanf("%d",&input);
		if(0<=input && input<=300){
			printf("pattern:%I64d\n\n", score[0][input]);
		}else if(input == 301){
			for(i=0; i<301; i++){
				printf("%3d: %I64d\n",i,score[0][i]+score[1][i]+score[2][i]+score[3][i]);
				//printf("%3d: %5I64d %5I64d %5I64d %5I64d\n",i,score[0][i],score[1][i],score[2][i],score[3][i]);
			}
			printf("\n");
		}else if(input == -1){
			printf("�I�����܂�\n");
			system("pause");
			return 0;
		}else{
			printf("���̓f�[�^���s���ł��B\n");
		}
	}
	
	return 0;
}

void calc(int f){
	int i,j,k,l;
	int max=30*f+1;
	for(i=0; i<4; i++){
		for(j=0; j<max; j++){
			score_n[i][j]=0;
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<max; j++){

			if(score[i][j]==0)continue;
			if(f != 10){
				for(k=0; k<4; k++){
					for(l=0; l<31; l++){
						if(scp[i][k][l]==0)continue;
						score_n[k][j+l] += score[i][j]*scp[i][k][l];
					}
				}
			}else{
				for(k=0; k<61; k++){
					if(scp_10[i][k]==0)continue;
					score_n[0][j+k] += score[i][j]*scp_10[i][k];
				}
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<max; j++){
			score[i][j] = score_n[i][j];
		}
	}
}

void make_scp(void){
	int i,j,k,m, a,b;
	
	for(m=0; m<4; m++){//�O�t���[���̏�Ԃɂ���Ď��t���[���̌v�Z�̌W�����ω�
		switch(m){
			case NORMAL:	a=1; b=1;	break;
			case SPARE:		a=2; b=1;	break;
			case STRIKE:	a=2; b=2;	break;
			case D_STRIKE:	a=3; b=2;	break;
		}
		//1-9�t���[��
		for(i=0; i<11; i++){
			if(i==10){
				scp[m][b+1][a*i] ++;
			}else{
				for(j=0; i+j<11; j++){
					if(i+j==10){
						scp[m][SPARE][a*i + b*j] ++;
					}else{
						scp[m][NORMAL][a*i +b*j] ++;
					}
				}
			}
		}
		//10�t���[��
		for(i=0; i<11; i++){
			if(i==10){
				for(j=0; j<11; j++){
					if(j==10){
						for(k=0; k<11; k++){
							scp_10[m][a*i +b*j +k] ++;
						}
					}else{
						for(k=0; j+k<11; k++){
							scp_10[m][a*i +b*j +k] ++;
						}
					}
				}
			}else{
				for(j=0; i+j<11; j++){
					if(i+j==10){
						for(k=0; k<11; k++){
							scp_10[m][a*i +b*j +k] ++;
						}
					}else{
						scp_10[m][a*i +b*j] ++;
					}
				}
			}
		}
	}
}


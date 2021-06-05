#include<stdio.h>
#include<stdlib.h>

//��P203ҳ�ı�i��ʾ���е���ʼλ�ã�j��ʾ���еĽ���λ��, L��ʾ����Ե����ֵ
// ����˵L[1][5] ��Ӧ�ľ������еĵ�1����ĸ����5����ĸ�����У���CAUGA���������
// ��ô˵L[0][14] ��Ӧ��������  ACAUGAUGGCCAUGU��������ԣ����Ǳ�����Ľ�


// ���ƹ�ʽ
// ��P201ҳ�У���������е�j����ĸ����ǰ��i��j-4����ĸ����ƥ�䣬��ôL(i,j) = L(i,j-1)
//    ��������е�j����ĸ���t����ĸƥ�䣬����i<t<j-4,��ôL(i,j) = max{1+L(i,t-1)+L(t+1,j)}

// ��P203ҳ�е�  ���½ǿհ׵Ĳ��ֶ�Ϊ0
//  �ݹ��������б�߽�����д�ģ� ˳��Ϊ[0,5],[1,6],[2,7],[3,8],[4,9]������
//   �K�K�K�K


// ����������Ǵ�st[0,n-1] ��ǰ���Ƶõ��ġ�

// ����������st��¼���еĹؼ��㣬�����õ�������ԵĽ��

// �������B�� ���Ÿ���n
// ������Ը���������Լ��� s[][]

int basepair_match(char B[], int s[][2], int n){
	int i,j;
	int t,k
	int sp;
	int max_len,tmp_len
	int tmp;
	int stack[n/2][2]; //ջ����Ѱ�Ҽ������ϵ�ʹ��ʹ�õ�

	int L[n][n]; //L������ż���Եĳ���

	int st[n][n];// ������¼�ؼ��㣬������Ѿ�ƥ�䣬������Ҽ����
//�ǹؼ���ʱ������-1 �� �ؼ���ʱ����¼��֮ƥ�������±�

                                        //��ʼ��dp��L�ж���ֵΪ0��st�ж���ֵΪ-1
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){//��ʼ��
			L[i][j] = 0;
			st[i][j] = -1;
		}
                                            //��дdp��
	for(k=5;k<=n-1;k++){

		for(i=0;i<n-k;i++){

			j = i+k;                            //dp��б����ģ� ��i��j֮ǰ�Ǹ���һ��������

			max_len=0;                  //len�洢����ѭ�������ֵ
			tmp=i;                                  //tmp�洢���ֵ��Ӧ���±�

			for(t=i; t<j-4; t++ ){

				if((B[t]=='A')&&(B[j]=='U') ||
					(B[t]=='U')&&(B[j]=='A')||
					(B[t]=='C')&&(B[j]=='G')||
					(B[t]=='G')&&(B[j]=='C')){

					if(i == t)
                        tmp_len = 1 +L[i+1][j-1];       //i==t ��ʾ�����һ������ƥ��
					else
                        tmp_len = 1 + L[i][t-1] + L[t+1][j-1];          // ��֮ǰ���ҵ�һ��ƥ���

                                            //���統ǰֵ�����ֵlen�󣬾��滻
					if(max_len < tmp_len){
						max_len = tmp_len;
                        tmp = t;
					}
				}
			}
                                        //��������û��ǰ��Ķ࣬����ǰ���ֵ
			if(L[i][j-1] >= max_len)
				L[i][j] = L[i][j-1];

			else
                {                               //����ͽ��и���
				L[i][j] = max_len;
				st[i][j] = tmp;                     //stҲ���и��£�������¼�ؼ���
			}
		}
	}
	//�洢��Ӧ�ļ���� ��������Ե����

	sp = 0;                                     //ջ��ָ��

	k=0;
	stack[0][0] = 0;
	stack[0][1] = n-1;

	while(sp >= 0){
                                            //ȡ��ջ������
		i = stack[sp][0];
		j = stack[sp][1];
		sp = sp-1;                          // ջ��ָ���1

		while(L[i][j]>0){

			if(st[i][j] == -1)
				j = j-1;                    //��ǰ�ƶ�
			else
			{
				s[k][0] = st[i][j];
				s[k++][1] = j;
                                                //���б��ָ�Ϊ����������
				if(st[i][j]-1-i>4)
				{                              //��һ��������ѹ��ջ��
					sp = sp+1;
					stack[sp][0] = i;
					stack[sp][1] = st[i][j] -1;
				}
                                            //�ڶ��������е������յ㣬��������
				i = st[i][j] + 1;
				j = j -1;
			}
		}
	}

	return L[0][n-1];
}

int main(){

    FILE *fp1 = fopen("input.txt","r");
    char str[100];
    char seq[100][100];
    int num = 0;

    while (fgets(str, 100, fp1) != NULL){
        strcpy(seq[num], str);
        num++;
    }
    fclose(fp1);

	FILE *fp2 = fopen("output.txt","w");
//	char B[] = "UGUACCGGUAGUACACCC";
	int s[100][2];

	int len, i, k;
	char tmp[100];

	for (k=0;k<100;++k)
    {
        for(len=0; seq[k][len]!='\0';len++); //�����ַ���B�ĳ���

        for (i=0;i<100;++i)
            tmp[i] = '.';

        int max_pair = basepair_match(seq[k],s,len);

        for(i=0;i<max_pair;i++)
            {
                //printf("%d-%d\n",s[i][0],s[i][1]);
                tmp[s[i][0]] = '(';
                tmp[s[i][1]] = ')';
                tmp[len] = '\0';
            }
            fprintf(fp2, "%s", tmp);
            fprintf(fp2, "\n");
    }
    fclose(fp2);

	return 0;
}

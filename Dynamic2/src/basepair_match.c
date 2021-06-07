#include "Dynamic2.h"

int basepair_match(char B[], int s[][2], int n){
	int i,j;
	int t,k;
	int sp;
	int max_len,tmp_len;
	int tmp;
	int stack[n/2][2]; //栈是在寻找碱基对组合的使用使用的

	int L[n][n]; //L用来存放碱基对的长度

	int st[n][n];// 用来记录关键点，即这个已经匹配，方便查找碱基对
//非关键点时，就是-1 ， 关键点时，记录与之匹配碱基的下标

                                        //初始化dp表，L中都赋值为0，st中都赋值为-1
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){//初始化
			L[i][j] = 0;
			st[i][j] = -1;
		}
                                            //填写dp表
	for(k=5;k<=n-1;k++){

		for(i=0;i<n-k;i++){

			j = i+k;                            //dp是斜着填的， 即i和j之前是隔着一个常数的

			max_len=0;                  //len存储本次循环的最大值
			tmp=i;                                  //tmp存储最大值对应的下标

			for(t=i; t<j-4; t++ ){

				if((B[t]=='A')&&(B[j]=='U') ||
					(B[t]=='U')&&(B[j]=='A')||
					(B[t]=='C')&&(B[j]=='G')||
					(B[t]=='G')&&(B[j]=='C')||
                    (B[t]=='G')&&(B[j]=='U')||
					(B[t]=='U')&&(B[j]=='G')){

					if(i == t)
                        tmp_len = 1 +L[i+1][j-1];       //i==t 表示跟最后一个进行匹配
					else
                        tmp_len = 1 + L[i][t-1] + L[t+1][j-1];          // 在之前的找到一个匹配的

                                            //比如当前值比最大值len大，就替换
					if(max_len < tmp_len){
						max_len = tmp_len;
                        tmp = t;
					}
				}
			}
                                        //碱基配对数没有前面的多，就用前面的值
			if(L[i][j-1] >= max_len)
				L[i][j] = L[i][j-1];

			else
                {                               //否则就进行更新
				L[i][j] = max_len;
				st[i][j] = tmp;                     //st也进行更新，用来记录关键点
			}
		}
	}
	//存储对应的碱基对 ，最大碱基对的组合

	sp = 0;                                     //栈顶指针

	k=0;
	stack[0][0] = 0;
	stack[0][1] = n-1;

	while(sp >= 0){
                                            //取出栈顶数据
		i = stack[sp][0];
		j = stack[sp][1];
		sp = sp-1;                          // 栈顶指针减1

		while(L[i][j]>0){

			if(st[i][j] == -1)
				j = j-1;                    //向前移动
			else
			{
				s[k][0] = st[i][j];
				s[k++][1] = j;
                                                //序列被分割为两个子序列
				if(st[i][j]-1-i>4)
				{                              //第一个子序列压入栈中
					sp = sp+1;
					stack[sp][0] = i;
					stack[sp][1] = st[i][j] -1;
				}
                                            //第二个子序列的起点和终点，继续搜索
				i = st[i][j] + 1;
				j = j -1;
			}
		}
	}

	return L[0][n-1];
}

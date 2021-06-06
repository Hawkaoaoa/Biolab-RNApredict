
#include<stdio.h>
#include<stdlib.h>
 
//在P203页的表，i表示序列的起始位置，j表示序列的结束位置, L表示碱基对的最大值 
// 比如说L[1][5] 对应的就是序列的第1个字母到第5个字母的序列，即CAUGA的最大碱基对 
// 那么说L[0][14] 对应的序列是  ACAUGAUGGCCAUGU的最大碱基对，就是本问题的解 
 
 
// 递推公式
// 在P201页中，如果序列中第j个字母，与前面i到j-4个字母都不匹配，那么L(i,j) = L(i,j-1)
//    如果序列中第j个字母与第t个字母匹配，其中i<t<j-4,那么L(i,j) = max{1+L(i,t-1)+L(t+1,j)}
 
// 在P203页中的  左下角空白的部分都为0 
//  递归表是沿着斜线进行填写的， 顺序为[0,5],[1,6],[2,7],[3,8],[4,9]。。。
//   ↘↘↘↘
 
 
// 碱基对序列是从st[0,n-1] 往前倒推得到的。  
 
// 其中用数组st记录其中的关键点，用来得到最大碱基对的结果 
 
// 碱基符号B， 符号个数n
// 最大碱基对个数，碱基对集合 s[][] 
int basepair_match(char B[], int s[][2], int n){
	int i,j,t,k,sp,len,len1,temp;
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
			
			j = i+k; //dp是斜着填的， 即i和j之前是隔着一个常数的  
			
			len=0;//len存储本次循环的最大值  
			temp=i;//temp存储最大值对应的下标 
			
			for(t=i; t<j-4; t++ ){
				//匹配到对应的碱基 A-U 或者 G-C 
				if((B[t]=='A')&&(B[j]=='U') ||
					(B[t]=='U')&&(B[j]=='A')||
					(B[t]=='C')&&(B[j]=='G')||
					(B[t]=='G')&&(B[j]=='C')){
					
						
					if(i==t) len1 = 1 +L[i+1][j-1];//i==t 表示跟最后一个进行匹配 
					else len1 = 1 + L[i][t-1] + L[t+1][j-1]; // 在之前的找到一个匹配的 
					
					//比如当前值比最大值len大，就替换 
					if(len < len1){ 
						len = len1; temp = t;
					}		
				
				
				}  
				
			}
			
			//碱基配对数没有前面的多，就用前面的值 
			if(L[i][j-1] >= len){
				L[i][j] = L[i][j-1];
			}else{//否则就进行更新 
				L[i][j] = len;
				st[i][j] = temp; //st也进行更新，用来记录关键点 
			} 
		}
	}		
	
	//存储对应的碱基对 ，最大碱基对的组合
	 
	sp = 0; //栈顶指针 
	
	k=0;
	stack[0][0] = 0;  stack[0][1] = n-1;
	while(sp>=0){
		//取出栈顶数据 
		i = stack[sp][0];
		j = stack[sp][1];
		sp = sp-1;// 栈顶指针减1 
		
		
		while(L[i][j]>0){
			if(st[i][j]==-1)
				j = j-1;//向前移动 
			else{
				s[k][0] = st[i][j];
				s[k++][1] = j;
				
				//序列被分割为两个子序列 
				if(st[i][j]-1-i>4){ //第一个子序列压入栈中 
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
	 
	
	//打印st 
	printf("\n"); 
	printf("打印st表\n");
	printf("%3c",' ');
 	for(i=0;i<n;i++)
		printf("%3c",B[i]);
	printf("\n");
	printf("%3c",' ');
	for(i=0;i<n;i++)
		printf("%3d",i);
	printf("\n");
	for(i=0;i<n;i++){
		printf("%3d",i);
		for(j=0; j<n;j++)
			printf("%3d",st[i][j]);
		printf("\n");
	} 
 
	//打印L表
	printf("打印L表\n");
	printf("%3c",' ');
 	for(i=0;i<n;i++)
		printf("%3c",B[i]);
	printf("\n");
	printf("%3c",' ');
	for(i=0;i<n;i++)
		printf("%3d",i);
	printf("\n");
	for(i=0;i<n-5 ;i++){
		printf("%3d",i);
		for(j=0; j<n;j++)
			printf("%3d",L[i][j]);
		printf("\n");
	}  
	
	
	return L[0][n-1];	
} 
 
 
int main(){
	
	
	
	
 
	char B[]= "GGGGCTATGGCGCAGGCTGGTAGCGCGTCTCGTTCGCAATGAGAAGGTCAGGGGTTCGAATCCCCTTAGCTCCA";
//	char B[] = "UGUACCGGUAGUACACCC";
 
	
	int s[100][2];
	
	int len, i;
	for(len=0; B[len]!='\0';len++); //计算字符串B的长度 
	
	int max = basepair_match(B,s,len);
	
	printf("最大碱基配对数为%d\n",max);
	for(i=0;i<max;i++)
		printf("%d-%d\n",s[i][0],s[i][1]);
	
	return 0;
}

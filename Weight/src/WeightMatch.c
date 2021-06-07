# include "Weight.h"

void WeightMatch(int p, int q, int **ptwMatrix, int **ptsMatrix,int len)
{
    int i, j, k, x;
    int begin=p,end=q;
    int ms, me, mk, rs, re, rk, bd;
    int flag, sign;
    int maxweightsum, medweightsum;
    extern finalwtsum;
    if (p + MINFOLDSPAN > q)
        return;

    maxweightsum = 0;
    flag = FALSE;

    for (i = p; i + 2 * (MINSTEMLEN - 1) + MINFOLDSPAN <= q; i++) {
        for (j = i + 2 * (MINSTEMLEN - 1) + MINFOLDSPAN; j <= q; j++) {
#ifdef OUTSIDEGU
            if (ptwMatrix[i][j] == 0)
                continue;
#else
            if(ptwMatrix[i][j]== 0 || ptwMatrix[i][j]==GU)
                continue;
#endif

            for (k = 0, medweightsum = 0; i + k + MINFOLDSPAN <= j - k && ptwMatrix[i + k][j - k] > 0; k++) {
                medweightsum += ptwMatrix[i + k][j - k];
            }
            while (k > 0 && ptwMatrix[i + k - 1][j - k + 1] == GU) {
                medweightsum -= GU;
                k--;
            }

            if (k >= MINSTEMLEN && maxweightsum < medweightsum /*+ (GC + AU + GU) * sqrt(k) / 3*/) {
                maxweightsum = medweightsum /*+ (GC + AU + GU) * sqrt(k) / 3*/;
                ms = i;
                me = j;
                mk = k;
                flag = TRUE;
            }
        }
    }
    if (flag) {
    	//printf("%d\t%d\t%d\t",ms,me,mk);
        for (i = 0; i < mk; i++)
            ptsMatrix[ms + i][me - i] = 1;
        finalwtsum += maxweightsum;

        WeightMatch(p, ms - 1, ptwMatrix, ptsMatrix,len);
        WeightMatch(ms + mk, me - mk, ptwMatrix, ptsMatrix,len);
        WeightMatch(me + 1, q, ptwMatrix, ptsMatrix,len);

        maxweightsum = 0;
        sign = FALSE;
        for (i = p; i <= ms - 1; i++) {
            for (x = p; x <= q && ptsMatrix[i][x] == 0 && ptsMatrix[x][i] == 0; x++);
            if (x <= q)
                continue;

            for (j = q; j >= me + 1; j--) {
#ifdef OUTSIDEGU
                if (ptwMatrix[i][j] == 0)
                    continue;
#else
                if (ptwMatrix[i][j]==O || ptwMatrix[i][j]==GU)
                    continue;
#endif
                k = 0;

                medweightsum = 0;
                bd = ms - i < j - me ? ms - i : j - me;

                while (k < bd && ptwMatrix[i + k][j - k] > 0) {
                    for (x = p; x <= q && ptsMatrix[i + k][x] == 0 && ptsMatrix[x][i + k] == 0; x++);
                    if (x <= q)
                        break;
                    for (x = p; x <= q && ptsMatrix[x][j - k] == 0 && ptsMatrix[j - k][x] == 0; x++);
                    if (x <= q)
                        break;
                    medweightsum += ptwMatrix[i + k][j - k];
                    k++;
                }

                while (k > 0 && ptwMatrix[i + k - 1][j - k + 1] == GU) {

                    k--;

                if (k >= MINSTEMLEN && maxweightsum < medweightsum /*+ (GC + AU + GU) * sqrt(k) / 3*/) {
                        maxweightsum = medweightsum /*+ (GC + AU + GU) * sqrt(k) / 3*/;
                        rs = i;
                        re = j;
                        rk = k;
                        sign = TRUE;
                }
            }

                if (sign) {
                	//printf("%d\t%d\t%d\t",rs,re,rk);
                    for (i = 0; i < rk; i++)
                        ptsMatrix[rs + i][re - i] = 1;
                    finalwtsum += maxweightsum;
                }
                sign = FALSE;
            }
        }
    }
   
}

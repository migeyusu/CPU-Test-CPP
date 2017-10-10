// Solution.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Solution.h"
#include "3d.h"
#include "I_DataStructrue.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#pragma comment(lib, "winmm.lib ")
#define rnd()(rand()%100)
#define byte BYTE
using namespace std;

struct colourPix
{
	byte red;
	byte green;
	byte blue;
};
/*数组排序和查找。ary1从序号1开始,从小到大排序,size仍为数组长度*/
//归并
void _stdcall Merge_Sort(int ary1[],int size)//归并排序
{
	int j, i = 2, hand1, hand2, hand3, hand4;
	int *ary2= new int[size];
	size = size - 1;
	while (i<size)
	{
		j = 1;//起始循环点
		while ((j + i - 1) <= size) //j+i/2表示左边位顶峰
		{
			// int[] ary2 = new int[i+1];
			hand1 = j;   //左边位
			hand2 = j + i / 2;//右边位
			hand3 = j;//复数组位
			do
			{

				if (ary1[hand1] >= ary1[hand2]) //依次赋值
				{
					ary2[hand3] = ary1[hand2];
					hand2 += 1;
					hand3 += 1;

				}
				else
				{
					ary2[hand3] = ary1[hand1];
					hand1 += 1;
					hand3 += 1;
				}
			} while (hand1 <= (j + i / 2 - 1) && hand2 <= (j + i - 1));
			if (hand2 <= j + i - 1)//表示右边仍然有值，返回原数组,如果左边没有值，就直接插回原数组
			{
				for (int s = j; s <= hand3 - 1; s++)
				{
					ary1[s] = ary2[s];
				}
			}
			else//左边有剩余值，右边没有
			{
				hand4 = hand3;//转移指针
				for (int s = hand1; s <= j + i / 2 - 1; s++)
				{
					ary1[hand4] = ary1[s];
					hand4 += 1;
				}
				for (int s = j; s <= hand3 - 1; s++)
				{
					ary1[s] = ary2[s];
				}
			}
			j = j + i;

		}
		i *= 2;
	}
	i = i / 2;
	hand1 = 1;
	hand2 = 1 + i;
	hand3 = 1;
	do
	{
		if (ary1[hand1] >= ary1[hand2]) //依次赋值
		{
			ary2[hand3] = ary1[hand2];
			hand2 += 1;
			hand3 += 1;

		}
		else
		{
			ary2[hand3] = ary1[hand1];
			hand1 += 1;
			hand3 += 1;
		}
	} while (hand1 <= i && hand2 <= size);
	if (hand1>i)  //左边无值，将右边剩余值放入ary2
	{
		for (int s = hand3; s <= size; s++)
		{
			ary2[s] = ary1[s];
		}
	}
	else
	{
		for (int s = hand1; s <= i; s++)
		{
			ary2[hand3] = ary1[s];
			hand3 = hand3 + 1;
		}
	}
	for (int i = 1; i <=size; i++)
	{
		ary1[i] = ary2[i];
	}
	delete[] ary2;
	return;
}
//插入
void _stdcall Insert_Sort(int ary1[],int size)//插入排序
{
	size = size - 1;
	int mid, midint;
	int i, j;
	for (i = 1; i <= size; i++)
	{
		mid = ary1[i];
		midint = i;
		for (j = i + 1; j <= size; j++)
		{
			if (ary1[j] < mid)
			{
				mid = ary1[j];
				midint = j;
			}
		}
		ary1[midint] = ary1[i];
		ary1[i] = mid;
	}
	return;

}
//二分查找
int _stdcall  Mid_Search(int ary1[],int size, int num1)//默认数组从小到大排列
{
	    int val = 0;
	    int len1 = size;
		int upBorder = len1;
		int downBorder = 1;
		int mid = (upBorder + downBorder) / 2;
		do
		{
			if (ary1[mid] == num1)
			{
				return mid;
			}
			else
			{
				if (ary1[mid]>num1)
				{
					upBorder = mid;
				}
				else
				{
					downBorder = mid;
				}
				mid = (upBorder + downBorder) / 2;
			}

		} while ((upBorder - downBorder)>1);	
	return val;
}
//数组归并,len1为ary.length
void _stdcall AryBuild(int ary1[],int len1, int ary2[],int len2,int newAry[])
{
	len1 = len1 - 1;
	len2 = len2 - 1;
	
	int len3 = len1 + len2;
	int ad1 = 1, ad2 = 1, ad3 = 1;
	do
	{
		if (ary1[ad1] < ary2[ad2])
		{
			newAry[ad3] = ary1[ad1];
			ad1=ad1+1;
		}
		else
		{
			newAry[ad3] = ary2[ad2];
			ad2=ad2+1;
		}
		ad3++;
	} while (ad1 <= len1 && ad2 <= len2);
	if (ad1 <= len1)
	{
		for (int i = ad3; i <= len3; i++)
		{
			newAry[i] = ary1[ad1];
			ad1+=1;
		}
	}
	else
	{
		for (int i = ad3; i <= len3; i++)
		{
			newAry[i] = ary2[ad2];
			ad2+=1;
		}
	}
	return;
}
//32位随机整数
int _stdcall Int_Test(int times,int &usedTime)
{
	srand((int)time(0));
	int s;
	int a1 = rnd(), a2 = rnd(), a3 = rnd(), a4 = rnd(), a5 = rnd(),
		a6 = rnd(), a7 = rnd(), a8 = rnd(), a9 = rnd(), a10 = rnd();
	DWORD t1;
	t1 = GetTickCount();
	for (int i = 0; i <times*100000000; i++)
	{
		++a1;
		--a2;
		a3 = a3*(a1 + a2)*a4;
		a4 = (a4 + a3) % 10;
		a5 = a5^a4;
		a6 = (a6 + a5) << 1;
		a7 = ~(a7*a4);
		a8 = a8 | a7;
		a9 = a9&a8;
		a10 = a10^a9;
	}
	usedTime = (int)(GetTickCount() - t1);
	return s = a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10;
}
//单双精度随机浮点
double _stdcall Float_Test(int times, int &usedTime)
{
	srand((int)time(0));
	float a1 = rnd()/ 3.14;
	float a2 = 2+a1, a3 = 3+a1, a4 = 4+a1, a5 = 5+a1;
    double a6 = 6+a1, a7 = 7+a1, a8 = 8+a1, a9 = 9+a1, a10 = 10+a1;
	DWORD t1;
	t1 = GetTickCount();
	for (int i = 0; i < times * 35000000; i++)
	{
		a1 = a1 + 1.1;
		a2 = a1 - 1.3;
		a3 = a3 + 1.1;
		a4 = a4 - 1.2;
		a5 = a1 + a2 + a3 + a4;
		a6 = a6+3.1;
		a7 = a7-1;
		a8 = a8 + 1.4;
		a9 = a9 - 1.5;
		a10 = a6 + a7 + a8 + a9;
		a10 = a10*a5;
		a10 = sqrt(a10);
		a5 = a5/2;
		a6 = cos(sin(a10));
		a2 = abs(a2);
		a4 = abs(a4);
		a7 = abs(a7);
		a9 = abs(a9);
		a10 = pow(a10, 2);
	}
	a10 = a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10;
	usedTime = (int)(GetTickCount() - t1);
	return a7;
}
/*牛顿法计算开平方：计算公式如下 Xn+1=1/2(Xn+S/Xn)*/
 double _stdcall Newton_Sqrt(double x, int y)
{

	double k = x, l = pow((double)10, -y);
	do
	{
		k = (k + x / k) / 2;
	} while (abs(k*k - x)>l);
	return k;
}
 /*泰勒级数计算：F(x)=f(a)+f'(a)(x-a)+f"(a)*(x-a)^2/2!+……*/
 static double Talor_Sqrt(double x, int y)
 {
	 double sum = 0, a = 1,b = 1,c = 1, d = 1, l = pow((double)10, -y);
	 int i = 0;
	 do
	 {
		 sum += d;
		 a *= (0.5 - i);
		 b *= (i + 1);
		 c *= (x - 1);
		 d = a * c / b;
		 i++;
	 } while (abs(d) > l);
	 return sum;
 }
 //泰勒公式求开方
double _stdcall T_Sqrt(double x)//开方运算
 {
	 double cret = 1;
	 while (x >= 2)
	 {
		 x /= 4;
		 cret *= 2;
	 }
	 return Talor_Sqrt(x, 10) * cret;
 }
//整数计算PI
int _stdcall SuperPi(int ary1[], int size)
{
	int *x = new int[size];
	int *z = new int[size];
	for (int i = 0; i < size; i++)
	{
		x[i] = 0;
		z[i] = 0;
	}
	int a = 1, b = 3, c, d, run = 1, cnt = 0;
	x[1] = 2;
	z[1] = 2;
	DWORD t1, t2;
	t1 = GetTickCount();
	while ((run != 0) && (++cnt<size))
	{
		d = 0;
		for (int i = size - 1; i>0; i--)
		{
			c = z[i] * a + d;
			z[i] = (c % 10);
			d = c / 10;
		}
		d = 0;
		for (int i = 0; i<size; i++)
		{
			c = z[i] + d * 10;
			z[i] = (c / b);
			d = c % b;
		}
		run = 0;
		for (int i = size - 1; i>0; i--)
		{
			c = x[i] + z[i];
			x[i] = (c % 10);
			x[i - 1] += (c / 10);
			run |= z[i];
		}
		a++;
		b += 2;
	}
	t2 = GetTickCount() - t1;
	for (int i = 1; i < size; i++)
	{
		ary1[i] = x[i];
	}
	delete[] x;
	delete[] z;
	return (int)t2;
}
//矩阵int32
int _stdcall Int_MatrixMulti(int Lary[], int m, int n, int Rary[], int p, int Ary[])
/*m代表前列长（行数），n代表前行长（列数），p代表后行长（行数），均从0开始，使用前压缩
到一位数组length=m*p以0开始,Lary表示左矩阵*/
{
	DWORD t1;
	t1 = GetTickCount();
	for (int i = 0; i < m; ++i)//前列长
	{
		for (int k = 0; k < p; ++k)//后行长
		{
			for (int j = 0; j < n; ++j)//前行长，后列长
			{
				Ary[i*p + k]+=Lary[i*n + j] * Rary[j + k*n];
			}
		}
	}
	return (int)(GetTickCount() - t1);
}
//矩阵double
int _stdcall Double_MatrixMulti(double Lary[], int m, int n, double Rary[], int p, double Ary[])
{
	DWORD t1;
	t1 = GetTickCount();
	for (int i = 0; i < m; ++i)//前列长
	{
		for (int k = 0; k < p; ++k)//后行长
		{
			for (int j = 0; j < n; ++j)//前行长，后列长
			{
				Ary[i*p + k] += Lary[i*n + j] * Rary[j + k*n];
			}
		}
	}
	return (int)(GetTickCount() - t1);
}
//issue测试,1-40
void _stdcall IssueTest(int resultAry[])
{
	DWORD times;
	int a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8,
		a9 = 9, a10 = 0, a11 = -1, a12 = -2, a13 = -3, a14 = -4, a15 = -5,
		a16 = -6, a17 = -7, a18 = -8, a19 = -9, a20 = -20;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//1
	{
		a1 += 1;

	}
	resultAry[1] =(int)(GetTickCount() - times);
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//2
	{
		a1 += 1;
		a1 -= 2;

	}
	resultAry[2] =(int)GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//3
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;

	}
	resultAry[3] =(int)(GetTickCount()-times);
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//4
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;

	}
	resultAry[4] =(int)(GetTickCount()-times);
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//5
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;

	}
	resultAry[5] =(int)(GetTickCount()-times);
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//6
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;

	}
	resultAry[6] =(int)(GetTickCount()-times);
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//7
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;
		a1 += 7;

	}
	resultAry[7] = GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//8
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;
		a1 += 7;
		a1 -= 8;

	}
	resultAry[8] =(int)(GetTickCount()-times);
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//9
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;
		a1 += 7;
		a1 -= 8;
		a1 += 9;

	}
	resultAry[9] =(int)(GetTickCount()-times);
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//10
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;
		a1 += 7;
		a1 -= 8;
		a1 += 9;
		a1 -= 10;

	}
	resultAry[10] =(int)(GetTickCount()-times);
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//11
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;
		a1 += 7;
		a1 -= 8;
		a1 += 9;
		a1 -= 10;
		a1 += 11;

	}
	resultAry[11] =(int)(GetTickCount()-times);
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//12
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;
		a1 += 7;
		a1 -= 8;
		a1 += 9;
		a1 -= 10;
		a1 += 11;
		a1 -= 12;

	}
	resultAry[12] =(int)(GetTickCount()-times);
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//13
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;
		a1 += 7;
		a1 -= 8;
		a1 += 9;
		a1 -= 10;
		a1 += 11;
		a1 -= 12;
		a1 += 13;

	}
	resultAry[13] =(int)(GetTickCount()-times);
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//14
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;
		a1 += 7;
		a1 -= 8;
		a1 += 9;
		a1 -= 10;
		a1 += 11;
		a1 -= 12;
		a1 += 13;
		a1 -= 14;

	}
	resultAry[14] = GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//15
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;
		a1 += 7;
		a1 -= 8;
		a1 += 9;
		a1 -= 10;
		a1 += 11;
		a1 -= 12;
		a1 += 13;
		a1 -= 14;
		a1 += 15;

	}
	resultAry[15] =(int)(GetTickCount()-times);
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//16
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;
		a1 += 7;
		a1 -= 8;
		a1 += 9;
		a1 -= 10;
		a1 += 11;
		a1 -= 12;
		a1 += 13;
		a1 -= 14;
		a1 += 15;
		a1 -= 16;

	}
	resultAry[16] = GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//17
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;
		a1 += 7;
		a1 -= 8;
		a1 += 9;
		a1 -= 10;
		a1 += 11;
		a1 -= 12;
		a1 += 13;
		a1 -= 14;
		a1 += 15;
		a1 -= 16;
		a1 += 17;

	}
	resultAry[17] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//18
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;
		a1 += 7;
		a1 -= 8;
		a1 += 9;
		a1 -= 10;
		a1 += 11;
		a1 -= 12;
		a1 += 13;
		a1 -= 14;
		a1 += 15;
		a1 -= 16;
		a1 += 17;
		a1 -= 18;

	}
	resultAry[18] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)  //19
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;
		a1 += 7;
		a1 -= 8;
		a1 += 9;
		a1 -= 10;
		a1 += 11;
		a1 -= 12;
		a1 += 13;
		a1 -= 14;
		a1 += 15;
		a1 -= 16;
		a1 += 17;
		a1 -= 18;
		a1 += 19;
	}
	resultAry[19] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//20
	{
		a1 += 1;
		a1 -= 2;
		a1 += 3;
		a1 -= 4;
		a1 += 5;
		a1 -= 6;
		a1 += 7;
		a1 -= 8;
		a1 += 9;
		a1 -= 10;
		a1 += 11;
		a1 -= 12;
		a1 += 13;
		a1 -= 14;
		a1 += 15;
		a1 -= 16;
		a1 += 17;
		a1 -= 18;
		a1 += 19;
		a1 -= 20;
	}
	resultAry[20] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//1
	{
		a1 += 1;
	}
	resultAry[21] =(int)(GetTickCount()-times);
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//2
	{
		a1 += 1;
		a2 -= 2;
	}
	resultAry[22] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//3
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
	}
	resultAry[23] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//4
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
	}
	resultAry[24] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//5
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
	}
	resultAry[25] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//6
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
	}
	resultAry[26] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//7
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
		a7 += 7;
	}
	resultAry[27] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//8
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
		a7 += 7;
		a8 -= 8;
	}
	resultAry[28] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//9
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
		a7 += 7;
		a8 -= 8;
		a9 += 9;
	}
	resultAry[29] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//10
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
		a7 += 7;
		a8 -= 8;
		a9 += 9;
		a10 -= 10;
	}
	resultAry[30] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//11
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
		a7 += 7;
		a8 -= 8;
		a9 += 9;
		a10 -= 10;
		a11 += 11;
	}
	resultAry[31] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//12
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
		a7 += 7;
		a8 -= 8;
		a9 += 9;
		a10 -= 10;
		a11 += 11;
		a12 -= 12;
	}
	resultAry[32] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//13
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
		a7 += 7;
		a8 -= 8;
		a9 += 9;
		a10 -= 10;
		a11 += 11;
		a12 -= 12;
		a13 += 13;
	}
	resultAry[33] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//14
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
		a7 += 7;
		a8 -= 8;
		a9 += 9;
		a10 -= 10;
		a11 += 11;
		a12 -= 12;
		a13 += 13;
		a14 -= 14;
	}
	resultAry[34] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//15
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
		a7 += 7;
		a8 -= 8;
		a9 += 9;
		a10 -= 10;
		a11 += 11;
		a12 -= 12;
		a13 += 13;
		a14 -= 14;
		a15 += 15;
	}
	resultAry[35] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//16
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
		a7 += 7;
		a8 -= 8;
		a9 += 9;
		a10 -= 10;
		a11 += 11;
		a12 -= 12;
		a13 += 13;
		a14 -= 14;
		a15 += 15;
		a16 -= 16;
	}
	resultAry[36] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//17
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
		a7 += 7;
		a8 -= 8;
		a9 += 9;
		a10 -= 10;
		a11 += 11;
		a12 -= 12;
		a13 += 13;
		a14 -= 14;
		a15 += 15;
		a16 -= 16;
		a17 += 17;
	}
	resultAry[37] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//18
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
		a7 += 7;
		a8 -= 8;
		a9 += 9;
		a10 -= 10;
		a11 += 11;
		a12 -= 12;
		a13 += 13;
		a14 -= 14;
		a15 += 15;
		a16 -= 16;
		a17 += 17;
		a18 -= 18;
	}
	resultAry[38] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//19
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
		a7 += 7;
		a8 -= 8;
		a9 += 9;
		a10 -= 10;
		a11 += 11;
		a12 -= 12;
		a13 += 13;
		a14 -= 14;
		a15 += 15;
		a16 -= 16;
		a17 += 17;
		a18 -= 18;
		a19 += 19;
	}
	resultAry[39] =  GetTickCount() - times;
	times = GetTickCount();
	for (int i = 0; i <= 70000000; i++)//20
	{
		a1 += 1;
		a2 -= 2;
		a3 += 3;
		a4 -= 4;
		a5 += 5;
		a6 -= 6;
		a7 += 7;
		a8 -= 8;
		a9 += 9;
		a10 -= 10;
		a11 += 11;
		a12 -= 12;
		a13 += 13;
		a14 -= 14;
		a15 += 15;
		a16 -= 16;
		a17 += 17;
		a18 -= 18;
		a19 += 19;
		a20 -= 20;
	}
	resultAry[40] =  GetTickCount() - times;
}
//cache测试,1-21
void _stdcall CacheTest(int resultAry[])
{
	int stepAry[22];
	stepAry[1] = 256;
	stepAry[2] = 2048;
	stepAry[3] = 4096;
	stepAry[4] = 8192;
	stepAry[5] = 16384;
	stepAry[6] = 32768;
	stepAry[7] = 131072;
	stepAry[8] = 262144;
	stepAry[9] = 524288;
	stepAry[10] = 786432;
	stepAry[11] = 1048576;
	stepAry[12] = 1572864;
	stepAry[13] = 2097152;
	stepAry[14] = 2621440;
	stepAry[15] = 3145728;
	stepAry[16] = 3670016;
	stepAry[17] = 4194304;
	stepAry[18] = 5242880;
	stepAry[19] = 7864320;
	stepAry[20] = 10485760;
	stepAry[21] = 13107200;
	int step1;
	DWORD t1;
	int *ar1;
	for (int j = 1; j <= 21; j++)
	{
		step1 = stepAry[j];
		ar1 = new int[step1];
		t1 = GetTickCount();
		for (int k = 0; k < 100; k++)
		{
			for (int i = 0; i < step1; i += 16)
			{
				ar1[i] = 1;
			}
		}
		resultAry[j]=(int)(GetTickCount()-t1);
	}
	return;
}
//branch测试,未完成
void _stdcall List_Test(int resultAry[])
{
	int stepAry[22];
	stepAry[1] = 256;
	stepAry[2] = 2048;
	stepAry[3] = 4096;
	stepAry[4] = 8192;
	stepAry[5] = 16384;
	stepAry[6] = 32768;
	stepAry[7] = 131072;
	stepAry[8] = 262144;
	stepAry[9] = 524288;
	stepAry[10] = 786432;
	stepAry[11] = 1048576;
	stepAry[12] = 1572864;
	stepAry[13] = 2097152;
	stepAry[14] = 2621440;
	stepAry[15] = 3145728;
	stepAry[16] = 3670016;
	stepAry[17] = 4194304;
	stepAry[18] = 5242880;
	stepAry[19] = 7864320;
	stepAry[20] = 10485760;
	stepAry[21] = 13107200;
	int *testary;
	DWORD t1;
	for (int  i = 1; i <= 6; ++i)
	{
		int steps = stepAry[i];
		testary = new int[steps];
		Create_List(testary, steps);
		t1 = GetTickCount();
		for (int j = 0; j <steps; j++)
		{
			List_Search(i);
		}
		resultAry[i] = (int)(GetTickCount() - t1);
		List_Clean();
	}
}

int _stdcall TalorSeries_Test(int times)
{
	DWORD t1;
	double x;
	t1 = GetTickCount();
	for (int i = 0; i <times*10000; i++)
	{
		x=Talor_Sqrt(i / (times * 10000) * 2, 10);
	}
	return GetTickCount() - t1;
}

int _stdcall renderTest(int size)
{
	DWORD t1;
	t1 = GetTickCount();
	picOut3d(size);
	return (int)(GetTickCount()-t1) ;
}
//3000,2,需要循环
void  imageVary(colourPix image1[], colourPix image2[], int size, int size0, int multiple)
{

	int newsize = size0;

	int y1, y2, x1, x2, xx, yy;
	float fx1, fx2, fy1, fy2;
	colourPix cp;
	for (int y = 0; y < newsize; ++y)//高
	{
		yy = y / multiple;
		y1 = (int)yy;
		if (y1 == size - 1)
		{
			y2 = y1;

		}
		else
		{
			y2 = y1 + 1;
		}
		fy1 = y1 - yy;
		fy2 = 1.0f - fy1;
		for (int x = 0; x < newsize; ++x)
		{
			xx = x / multiple;
			x1 = (int)xx;
			if (x1 == size - 1)
			{
				x2 = x1;
			}
			else
			{
				x2 = x1 + 1;
			}
			fx1 = y1 - yy;
			fx2 = 1.0f - fx1;
			float s1 = fx1*fy1;
			float s2 = fx2*fx1;
			float s3 = fx2*fx2;
			float s4 = fx1*fx2;
			colourPix c1, c2, c3, c4;
			c1 = image1[x1 + y1*size];
			c2 = image1[x2 + y1*size];
			c3 = image1[x1 + y2*size];
			c4 = image1[x2 + y2*size];
			byte r, g, b;
			r = (byte)(c1.red*s3) + (byte)(c2.red*s4) + (byte)(c3.red*s2) + (byte)(c4.red*s1);
			g = (byte)(c1.green*s3) + (byte)(c2.green*s4) + (byte)(c3.green*s2) + (byte)(c4.green*s1);
			b = (byte)(c1.blue*s3) + (byte)(c2.blue*s4) + (byte)(c3.blue*s2) + (byte)(c4.blue*s1);
			cp.blue = b;
			cp.green = g;
			cp.red = r;
			image2[x + y*newsize] = cp;
		}
	}
}

int _stdcall imageDeal(int x, int y)//图像和放大的倍数
{
	int size = 300, mult = 1.5;
	int newsize = size * mult;
	int len1 = size*size;
	int len2 = size*mult*size*mult;
	colourPix *image1 = new colourPix[len1];
	colourPix *image2 = new colourPix[len2];
	//for (int i = 0; i < size*size; i++)
	//{
	//	image1[i].blue = rand() % 256;
	//	image1[i].red = rand() % 256;
	//	image1[i].green = rand() % 256;
	//}
	DWORD t1 = GetTickCount();
	for (int i = 0; i < 3000; i++)
	{
		imageVary(image1, image2, size, newsize, mult);
	}
	t1 = GetTickCount() - t1;
	delete[] image1;
	image1 = NULL;
	delete[] image2;
	image2 = NULL;
	return (int)t1;
}


//ary1从0开始
/*————————————单链表操作————————————*/

Oneway_List OLs;
void _stdcall Create_List(int ary[], int size)
{
	OLs.OneWay_Chain = NULL;
	OLs.createList(OLs.OneWay_Chain, ary, size);
}
void _stdcall List_Append(int x)
{
	OLs.nodeAppend(OLs.OneWay_Chain,x);
}
void _stdcall List_Insert(int preNode, int nextNode)
{
	OLs.nodeInsert(OLs.OneWay_Chain, preNode, nextNode);
}
int  _stdcall List_Count()
{
	return OLs.listCount(OLs.OneWay_Chain);
}
void _stdcall List_Print(int ary[], int size)
{
	OLs.listPrint(OLs.OneWay_Chain, ary, size);
}
void _stdcall List_Search(int x)
{
	OLs.nodeSearch(OLs.OneWay_Chain, x);
}
void _stdcall List_Delete(int delenode)
{
	OLs.nodeDelete(OLs.OneWay_Chain, delenode);
}
void _stdcall List_Clean()
{
	OLs.nodeClean(OLs.OneWay_Chain);
}

/*供C#调用*/
/*—————————————B树操作————————————*/

B_tree Bts;
void _stdcall Btree_Create(int ary1[], int size)
{
	Bts.MainBst = NULL;
	Bts.Result_Ary = NULL;
	Bts.btreebuild(Bts.MainBst, ary1, size);
}
void _stdcall Btree_Sort(int ary1[], int size, bool keep)
{
	Bts.MainBst = NULL;
	Bts.Result_Ary = ary1;
	Bts.btreebuild(Bts.MainBst, ary1, size);
	Bts.Inorder(Bts.MainBst);
	ary1 = Bts.Result_Ary;
	if (!keep)
	{
		Bts.MainBst = NULL;
	}
}
void _stdcall Btree_Insert(int seeds)
{
	Bts.InsertIn(Bts.MainBst, seeds);
}
bool _stdcall Btree_Find(int field)
{
	return Bts.FindData(Bts.MainBst, field);
}
void _stdcall Btree_Print(int ary1[])
{
	Bts.Result_Ary = ary1;
	Bts.Inorder(Bts.MainBst);
}
int _stdcall  Btree_Count()
{
	return Bts.NodeCount(Bts.MainBst);
}
void _stdcall Btree_Clean()
{
	Bts.clearbstree(Bts.MainBst);
}
bool _stdcall Btree_Delete(int x)
{
	return Bts.DeleteOn(Bts.MainBst, x);
}

/*————————————双链表———————————*/

Twoway_List<int> tlt;
void _stdcall TwowayList_Create(int ary[],int size)
{
	tlt.create();
	for (int i = 0; i <size; i++)
	{
		tlt.tailappend(ary[i]);
	}
}
void _stdcall TwowayList_Append(int x)
{
	tlt.tailappend(x);
}
void _stdcall TwowayList_Print(int ary[])
{
	tlt.print(ary);
}
int _stdcall TwowayList_Count()
{
	return tlt.count();
}
bool _stdcall TwowayList_Search(int x)
{
	return tlt.search(x);
}
void _stdcall TwowayList_Headin(int x)
{
	tlt.headinsert(x);
}
void _stdcall TwowayList_Headde()
{
	tlt.headdelete();
}
void _stdcall TwowayList_Clean()
{
	tlt.clean();
}
void _stdcall TwowayList_Dele(int x)
{
	tlt.dele(x);
}
void _stdcall TwowayList_Insert(int x1, int x2)
{
	tlt.insert(x1, x2);
}
void _stdcall TwowayList_Tailde()
{
	tlt.taildelete();
}

/*—————————————队列——————————*/

I_Queue Myqueue;
void _stdcall Queue_Ini()
{
	Myqueue.createQueue();
}
void _stdcall Queue_Push(int x)
{
	Myqueue.push(x);
}
bool _stdcall Queue_Pop(int &x)
{
	return Myqueue.pop(x);
}
bool _stdcall Queue_Peek(int &x)
{
	return Myqueue.peek(x);
}
void _stdcall Queue_Clear()
{
	Myqueue.queueClear();
}

/*————————————栈—————————————*/

I_Stack<int> Mystack;
void _stdcall Stack_Create(int x)
{
	Mystack.iniStack(x);
}
void _stdcall Stack_Clear(int x)
{
	Mystack.clearStack();
}
void _stdcall Stack_Close()
{
	Mystack.closeStack();
}
void _stdcall Stack_Push(int x)
{
	Mystack.push(x);
}
bool _stdcall Stack_Pop(int &x)
{
	return Mystack.pop(x);
}
bool _stdcall Stack_Peek(int &x)
{
	return Mystack.peek(x);
}
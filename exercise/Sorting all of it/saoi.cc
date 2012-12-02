/*************************************************************************
	> File Name: saoi.cc
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2012年11月28日 星期三 23时41分01秒
    > Describition: 例2.7：Sorting it all out
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX	100
#define	ALP	26

using namespace std;

int	d_in[ALP];	//	记录顶点的入度
int	tmp[ALP];	//	d_in的复制版，用于拓扑排序时的修改
char	rlt[3];		//	读入对象间的关系
char	path[ALP];	//	存储拓扑排序的结果
bool	alpha[ALP];	// 记录对象是否已经访问过

int	vexnum, arcnum;
vector< vector<char> > v;// 使用STL的成员vector莱存储节点

/* 
 * 拓扑排序 
 */
// 返回拓扑排序后得到的序列中的元素个数，如果发现矛盾则返回-1
int topsort(int c)
{
	int	cnt = 0;	// The number of vextices whose in degree is zero
	int flag;	// Flag if we can get a sorted sequence after topsort
	int	r,rear = 0;

	for (int i = 0; i < vexnum; i ++)
		tmp[i] = d_in[i];
	
	while (c --) {
		cnt = 0;
		for (int i = 0; i < vexnum; i ++) 
			if (tmp[i] == 0) {
				r = i;
				cnt ++;
			}
		if (cnt >= 1) {
			if (cnt > 1)
				flag = 0;	// Can't get a determiated sequence
			for (int i = 0; i < v[r].size(); i ++)
				tmp[v[r][i]] --;
			path[rear ++] = r;
			path[rear] = 0;
			tmp[r] = -1;
		}
		else if (cnt == 0)
			return -1;		// The Graph contain cycle
		}
	if (flag == 1)
		return rear;
	else 
		return 0;
}

int main(void)
{
	while (1) {
		cin >> vexnum >> arcnum;

		if (vexnum == 0 && arcnum == 0)
			break;
		memset(tmp, 0, sizeof(tmp));
		memset(alpha, 0, sizeof(alpha));
		memset(d_in, 0, sizeof(d_in));
		v.clear();
		v.resize(vexnum);
		
		int	cnt = 0;	// Record the number of vextices been discovered
		int	decide = 0;
		int result;
		int	k;
		for (int i = 0; i < arcnum; i ++) {
			cin >> rlt;
			v[rlt[0] - 'A'].push_back(rlt[2] - 'A');
			if (!alpha[rlt[0] - 'A']) {
				alpha[rlt[0] - 'A'] = 1;
				cnt ++;
			}
			if (!alpha[rlt[2] - 'A']) {
				alpha[rlt[2] - 'A'] = 1;
				cnt ++;
			}
			d_in[rlt[2] - 'A'] ++;
		
			if (decide == 0) {
				result = topsort(cnt);
				if (result == -1) {
					decide = -1;
					k = i + 1;
				}
				else if (result == vexnum) {
					decide = 1;
					k = i + 1;
				}
			}
		}
		if (decide == -1)
			cout << "Inconsicency at " << k << endl;
		else if(decide == 0)
//			cout << "Sorted sequence (at " << k << "): " << path << endl;
			printf("Sorted sequence (at %d): %s\n", k, path);
		else 
			cout << "Can't sort!" << endl;
	}
	return 0;
}


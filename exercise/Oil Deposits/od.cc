/*************************************************************************
	> File Name: od.cc
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2012年11月28日 星期三 23时19分59秒
    > Describition: 
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <string.h>

#define N	100
using namespace std;

char	oil[N][N];	// 油田的信息
int		m, n;		// 油田规模
int		dir[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

void bfs(int x, int y)
{
	int	queuei[N];
	int	queuej[N];
	int	rear, front;

	rear = front = 0;
	queuei[rear] = x;
	queuej[rear ++] = y;

	while (front != rear) {
		int out = front ++;
		oil[queuei[out]][queuej[out]] = '*';
		for (int i = 0; i < 8; i ++) {
			int nexti = queuei[out] + dir[i][0];
			int	nextj = queuej[out] + dir[i][1];
			if (oil[nexti][nextj] == '@') {
				queuei[rear] = nexti;
				queuej[rear ++] = nextj;
			}
		}
	}
}

void dfs(int x, int y)
{
	oil[x][y] = '*';
	for (int i = 0; i < 8; i ++) 
		if (oil[x + dir[i][0]][y + dir[i][1]] == '@')
			dfs(x + dir[i][0],y + dir[i][1]);
	return;
}

int main(void)
{
	int	cnt;
	while (1) {
		cin >> m >> n;
		cnt = 0;
		if (m == 0 && n == 0)
			break;
		memset(oil, 0, sizeof(oil));
		for (int i = 1; i <= m; i ++)
			for (int j = 1; j <= n; j ++)
				cin >> oil[i][j];
		for (int k = 0; k <= m; k ++)
			for (int l = 0; l <= n; l ++)
				if (oil[k][l] == '@') {
				//	bfs(k, l);
					dfs(k, l);
					cnt ++;
				}
		cout << cnt << endl;
	}
	return 0;
}

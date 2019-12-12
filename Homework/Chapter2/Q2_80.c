#include <stdio.h>
#include <limits.h>
int threefourths(int x) {
	int res1 = ((x >> 2) << 1) + ((x >> 2) << 0);
	int res2 = ((x & 0x3) << 1) + ((x & 0x3) << 0);
	int sign = x & INT_MIN;
	(sign)&&(res2+= ((1 << 1) + 1));
	return (res1 + (res2 >> 2));
}
int main() {
	printf("x=5, res=%d\n", threefourths(5));
	printf("x=-5, res=%d", threefourths(-5));
	return 0;
}

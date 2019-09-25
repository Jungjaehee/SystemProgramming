#include <stdio.h>
#include <limits.h>

int tsub_ok(int x, int y) {
	int res = 1;
	if (y == INT_MIN) {
		res = 0;
	}
	int pos = (x >= 0) && (y < 0) && ((x - y) < 0);
	int neg = (x < 0) && (y >= 0) && ((x - y) > 0);
	return res&&!pos&&!neg;
}

int main(void) {
	printf("1 : %d\n",tsub_ok(0, INT_MAX));
	printf("2 : %d\n", tsub_ok(-2, INT_MAX));
	printf("3 : %d\n", tsub_ok(0, INT_MIN));
	printf("4 : %d\n", tsub_ok(INT_MAX, -2));
	return 0;
}
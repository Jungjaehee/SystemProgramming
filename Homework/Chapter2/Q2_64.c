#include <stdio.h>
int any_add_one(unsigned x) {
	return ((x & 0xAAAAAAAA) && 1);
}
int main(void) {
	printf("0x00000001 : 0x%x\n", any_add_one(0x00000001));
	printf("0x00000002 : 0x%x\n", any_add_one(0x00000002));
	printf("0x00000003 : 0x%x", any_add_one(0x00000003));
}

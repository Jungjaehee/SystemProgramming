#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b) {
	char *pointer = (char*)&x;
	pointer[i] = b;	
	return x;
}

int main(void) {
	printf("0x%x\n", replace_byte(0x12345678, 2, 0xAB));
	printf("0x%x", replace_byte(0x12345678, 0, 0xAB));
	return 0;
}
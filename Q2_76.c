#include <stdio.h>
#include <string.h>
#include <limits.h>
void *calloc(size_t nmemb, size_t size) {
	if (nmemb == 0 || size == 0)
		return NULL;
	size_t buffer = nmemb * size;
	if (nmemb == buffer / size) {
		void *pointer = malloc(nmemb*size);
		if (pointer != NULL)
			memset(pointer, 0, nmemb*size);
		return pointer;
	}
	return NULL;
}
int main(void) {
	void* p;
	p = calloc(0x1234,1);
	printf("nmemb=0x1234, size=1 , calloc 결과 = %p\n", p);
	free(p);
	p = calloc(INT_MIN, 1);
	printf("nmemb=INT_MIN, size=1 , calloc 결과 = %p", p);
	free(p);
	return 0;
}
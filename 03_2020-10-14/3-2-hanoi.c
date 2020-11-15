#include <stdio.h>

void hanoi(int n, int from, int temp, int to) {
	if (n == 1) {
		printf("%d --> %d\n", from, to);
	} else {
		hanoi(n - 1, from, to, temp);
		printf("%d --> %d\n", from, to);
		hanoi(n - 1, temp, from, to);
	}
}

int main() {
	int n;
	printf("Inserisci il numero di dischi: ");
	scanf(" %d", &n);
	hanoi(n, 0, 1, 2);
	return 0;
}

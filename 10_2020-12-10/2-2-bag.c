#include <stdio.h>
#include <stdlib.h>

typedef struct Type_ {
	int w, v; // weight, value
} * Type;

void printIntArr(int arr[], int len) {
	for (int i = 0; i < len; i++)
		printf("%d: %d\n", i, arr[i]);
	printf("\n");
}

int main() {
	Type *types = malloc(0);
	int typesNum = 0;
	printf("Capacity:\n");
	int size;
	scanf(" %d", &size);
	printf("Types ([weight value]):\n");
	for (int w, v; scanf(" %d %d\n", &w, &v) == 2; types = realloc(types, (typesNum + 1) * sizeof(Type)), types[typesNum] = malloc(sizeof(struct Type_)), types[typesNum]->w = w, types[typesNum++]->v = v)
		;
	int s[size + 1][typesNum + 1];
	for (int i = 0; i <= size; i++)
		for (int j = 0; j <= typesNum; j++)
			s[i][j] = 0;
	for (int j = 1; j <= typesNum; j++)
		for (int i = 1; i <= size; i++) {
			s[i][j] = s[i][j - 1];
			int otherCoord = i - types[j - 1]->w;
			if (otherCoord >= 0) {
				int candidate = s[otherCoord][j - 1] + types[j - 1]->v;
				if (candidate > s[i][j])
					s[i][j] = candidate;
			}
		}
	printf("\n     |   ");
	for (int j = 0; j <= typesNum; j++)
		printf("%d\t ", j);
	printf("\n-----|--------------------------------------------\n");
	for (int i = 0; i <= size; i++) {
		printf("%2d   | ", i);
		for (int j = 0; j <= typesNum; j++)
			printf("%2d\t", s[i][j]);
		printf("\n");
	}
	int filter[typesNum];
	for (int i = size, j = typesNum; j > 0; j--) {
		if (s[i][j - 1] < s[i][j]) {
			filter[j - 1] = 1;
			i -= types[j - 1]->w;
		} else
			filter[j - 1] = 0;
	}
	printf("\nTotal value: %d\nTypes:\n", s[size][typesNum]);
	for (int i = 0; i < typesNum; i++)
		if (filter[i])
			printf("%d %d\n", types[i]->w, types[i]->v);
	return 0;
}

#include "../include/heap.h"
#include <stdlib.h>
#include <string.h>

#define heap_parent(npos) ((int)(((npos)-1) / 2))
#define heap_left(npos) (((npos)*2) + 1)
#define heap_right(npos) (((npos)*2) + 2)

void heap_init(Heap *heap, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data)) {
	// Initialize the heap.
	heap->size = 0;
	heap->compare = compare;
	heap->destroy = destroy;
	heap->tree = NULL;
	return;
}

void heap_destroy(Heap *heap) {
	int i;
	// Remove all the nodes from the heap.
	if (heap->destroy != NULL) {
		for (i = 0; i < heap_size(heap); i++) {
			// Call a user-defined function to free dynamically allocated data.
			heap->destroy(heap->tree[i]);
		}
	}
	// Free the storage allocated for the heap.
	free(heap->tree);
	// No operations are allowed now, but clear the structure as a precaution.
	memset(heap, 0, sizeof(Heap));
	return;
}

int heap_insert(Heap *heap, const void *data) {
	void *temp;
	int ipos, ppos;
	// Allocate storage for the node.
	if ((temp = (void **)realloc(heap->tree, (heap_size(heap) + 1) * sizeof(void *))) == NULL) {
		return -1;
	} else {
		heap->tree = temp;
	}
	// Insert the node after the last node.
	heap->tree[heap_size(heap)] = (void *)data;
	// Heapify the tree by pushing the contents of the new node upward.
	ipos = heap_size(heap);
	ppos = heap_parent(ipos);
	while (ipos > 0 && heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0) {
		// Swap the contents of the current node and its parent.
		temp = heap->tree[ppos];
		heap->tree[ppos] = heap->tree[ipos];
		heap->tree[ipos] = temp;
		// Move up one level in the tree to continue heapifying.
		ipos = ppos;
		ppos = heap_parent(ipos);
	}
	// Adjust the size of the heap to account for the inserted node.
	heap->size++;
	return 0;
}

static void heapify(Heap *heap, int ipos) {
	void *temp;
	int lpos, rpos, mpos;
	// Heapify the tree by pushing the contents of the new top downward.
	lpos = heap_left(ipos);
	rpos = heap_right(ipos);
	while (1) {
		// Select the child to swap with the current node.
		lpos = heap_left(ipos);
		rpos = heap_right(ipos);
		if (lpos < heap_size(heap) && heap->compare(heap->tree[lpos], heap->tree[ipos]) > 0) {
			mpos = lpos;
		} else {
			mpos = ipos;
		}
		if (rpos < heap_size(heap) && heap->compare(heap->tree[rpos], heap->tree[mpos]) > 0) {
			mpos = rpos;
		}
		// When mpos is ipos, the heap property has been restored.
		if (mpos == ipos) {
			break;
		} else {
			// Swap the contents of the current node and the selected child.
			temp = heap->tree[mpos];
			heap->tree[mpos] = heap->tree[ipos];
			heap->tree[ipos] = temp;
			// Move down one level in the tree to continue heapifying.
			ipos = mpos;
		}
	}
}

int heap_extract(Heap *heap, void **data) {
	void *save, *temp;
	// Do not allow extraction from an empty heap.
	if (heap_size(heap) == 0)
		return -1;
	// Extract the node at the top of the heap.
	*data = heap->tree[0];
	// Adjust the storage used by the heap.
	save = heap->tree[heap_size(heap) - 1];
	if (heap_size(heap) - 1 > 0) {
		if ((temp = (void **)realloc(heap->tree, (heap_size(heap) - 1) * sizeof(void *))) == NULL) {
			return -1;
		} else {
			heap->tree = temp;
		}
		// Adjust the size of the heap to account for the extracted node.
		heap->size--;
	} else {
		// Manage the heap when extracting the last node.
		free(heap->tree);
		heap->tree = NULL;
		heap->size = 0;
		return 0;
	}
	// Copy the last node to the top.
	heap->tree[0] = save;
	heapify(heap, 0);
	return 0;
}

void heapSort(void **arr, int len, int (*compare)(const void *key1, const void *key2)) {
	Heap h;
	h.compare = compare;
	h.size = len;
	h.tree = arr;
	for (int i = len / 2; i >= 0; i--)
		heapify(&h, i);
	void *temp;
	for (h.size = len - 1; h.size >= 1; h.size--) {
		temp = h.tree[0];
		h.tree[0] = h.tree[h.size];
		h.tree[h.size] = temp;
		heapify(&h, 0);
	}
}

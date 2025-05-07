#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_TREE_HT 100
#define MAX_CHARS 256

struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

void printArr(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void printCodes(struct MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (!(root->left) && !(root->right)) {
        printf("'%c': ", root->data);
        printArr(arr, top);
    }
}

void storeCodes(struct MinHeapNode* root, int arr[], int top, char* huffmanCode[]) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, huffmanCode);
    }

    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, huffmanCode);
    }

    if (!(root->left) && !(root->right)) {
        huffmanCode[root->data] = (char*)malloc((top + 1) * sizeof(char));
        for (int i = 0; i < top; i++) {
            huffmanCode[root->data][i] = arr[i] + '0';
        }
        huffmanCode[root->data][top] = '\0';
    }
}

void printTree(struct MinHeapNode* root, int space) {
    if (root == NULL)
        return;

    space += 10;
    printTree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    
    if (root->data == '$')
        printf("(%u)\n", root->freq);
    else
        printf("%c(%u)\n", root->data, root->freq);

    printTree(root->left, space);
}

void HuffmanCodes(char data[], int freq[], int size) {
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    
    printf("\nHuffman Codes:\n");
    printCodes(root, arr, top);
    
    printf("\nHuffman Tree Structure:\n");
    printTree(root, 0);
}

void compressString(char* input) {
    int freq[MAX_CHARS] = {0};
    int len = strlen(input);
    
    for (int i = 0; i < len; i++) {
        freq[(int)input[i]]++;
    }
    
    char data[MAX_CHARS];
    int freqArr[MAX_CHARS];
    int size = 0;
    
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) {
            data[size] = (char)i;
            freqArr[size] = freq[i];
            size++;
        }
    }
    
    printf("\nCharacter frequencies in '%s':\n", input);
    for (int i = 0; i < size; i++) {
        printf("'%c': %d\n", data[i], freqArr[i]);
    }
    
    struct MinHeapNode* root = buildHuffmanTree(data, freqArr, size);
    
    int arr[MAX_TREE_HT], top = 0;
    char* huffmanCode[MAX_CHARS] = {NULL};
    storeCodes(root, arr, top, huffmanCode);
    
    int compressedBits = 0;
    for (int i = 0; i < len; i++) {
        if (huffmanCode[(int)input[i]] != NULL) {
            compressedBits += strlen(huffmanCode[(int)input[i]]);
        }
    }
    
    printf("\nHuffman Codes:\n");
    for (int i = 0; i < size; i++) {
        printf("'%c': %s\n", data[i], huffmanCode[(int)data[i]]);
    }
    
    printf("\nHuffman Tree Structure:\n");
    printTree(root, 0);
    
    for (int i = 0; i < MAX_CHARS; i++) {
        if (huffmanCode[i] != NULL) {
            free(huffmanCode[i]);
        }
    }
}

int main() {
    char input[1000];
    int choice;
    
    do {
        printf("\n=== Huffman Coding Algorithm ===\n");
        printf("1. Encode a string\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 
        
        switch (choice) {
            case 1:
                printf("Enter a string to encode: ");
                fgets(input, sizeof(input), stdin);
                
                size_t len = strlen(input);
                if (len > 0 && input[len-1] == '\n') {
                    input[len-1] = '\0';
                }
                
                if (strlen(input) > 0) {
                    compressString(input);
                } else {
                    printf("Please enter a valid string.\n");
                }
                break;
            case 2:
                printf("Exiting program...\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 2);
    
    return 0;
}

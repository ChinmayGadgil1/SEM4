#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256

struct Node {
    char data;
    int freq;
    struct Node *left, *right;
    int first_occurrence;
    int tree_num;
};

struct QueueNode {
    struct Node* treeNode;
    struct QueueNode* next;
};

// Global front pointer for the priority queue
struct QueueNode* front = NULL;

struct Node* createNode(char data, int freq, int first_occurrence, int tree_num) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    node->first_occurrence = first_occurrence;
    node->tree_num = tree_num;
    return node;
}

// Returns 1 if node 'a' should come before node 'b' in priority queue
int shouldComeBefore(struct Node* a, struct Node* b) {
    // Rule 1: Lower frequency comes first
    if (a->freq != b->freq) {
        return a->freq < b->freq;
    }
    
    // Rule 2: Character nodes (leaf nodes) have priority over internal nodes
    int a_is_leaf = (a->data != '$');
    int b_is_leaf = (b->data != '$');
    
    if (a_is_leaf != b_is_leaf) {
        return a_is_leaf;  // Leaf nodes come before internal nodes
    }
    
    // Rule 3: If both are leaf nodes, earlier occurrence comes first
    if (a_is_leaf && b_is_leaf) {
        return a->first_occurrence < b->first_occurrence;
    }
    
    // Rule 4: If both are internal nodes, lower tree number comes first
    return a->tree_num < b->tree_num;
}

void enqueue(struct Node* node) {
    struct QueueNode* qNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    qNode->treeNode = node;
    qNode->next = NULL;
    
    // If queue is empty or new node should come first
    if (front == NULL || shouldComeBefore(node, front->treeNode)) {
        qNode->next = front;
        front = qNode;
        return;
    }
    
    // Find the correct position to insert
    struct QueueNode* current = front;
    while (current->next != NULL && !shouldComeBefore(node, current->next->treeNode)) {
        current = current->next;
    }
    
    qNode->next = current->next;
    current->next = qNode;
}

struct Node* dequeue() {
    if (front == NULL) return NULL;
    
    struct QueueNode* temp = front;
    struct Node* node = temp->treeNode;
    front = front->next;
    free(temp);
    return node;
}

int isQueueEmpty() {
    return front == NULL;
}

int getQueueSize() {
    int count = 0;
    struct QueueNode* current = front;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void clearQueue() {
    while (front != NULL) {
        struct QueueNode* temp = front;
        front = front->next;
        free(temp);
    }
}

void freeHuffmanTree(struct Node* root) {
    if (root == NULL) return;
    
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    free(root);
}

void storeCodes(struct Node* root, char* code, int depth, char huffmanCodes[][100]) {
    if (root == NULL) return;
    
    // If this is a leaf node, store the code
    if (root->left == NULL && root->right == NULL) {
        code[depth] = '\0';
        strcpy(huffmanCodes[(int)root->data], code);
        return;
    }
    
    // Traverse left subtree with '0'
    if (root->left) {
        code[depth] = '0';
        storeCodes(root->left, code, depth + 1, huffmanCodes);
    }
    
    // Traverse right subtree with '1'
    if (root->right) {
        code[depth] = '1';
        storeCodes(root->right, code, depth + 1, huffmanCodes);
    }
}

struct Node* buildHuffmanTree(char* text) {
    int freq[MAX_CHARS] = {0};
    int first_occurrence[MAX_CHARS];
    int len = strlen(text);
    
    // Initialize first occurrence array
    for (int i = 0; i < MAX_CHARS; i++) {
        first_occurrence[i] = -1;
    }
    
    // Count frequency and record first occurrence of each character
    for (int i = 0; i < len; i++) {
        int ch = (int)text[i];
        freq[ch]++;
        if (first_occurrence[ch] == -1) {
            first_occurrence[ch] = i;
        }
    }
    
    // Create leaf nodes and add to priority queue
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) {
            struct Node* node = createNode((char)i, freq[i], first_occurrence[i], 0);
            enqueue(node);
        }
    }
    
    int tree_count = 0;
    
    // Build Huffman tree by merging nodes
    while (getQueueSize() > 1) {
        struct Node* left = dequeue();
        struct Node* right = dequeue();
        
        tree_count++;
        // Create internal node (marked with '$')
        struct Node* merged = createNode('$', left->freq + right->freq, 999999, tree_count);
        merged->left = left;
        merged->right = right;
        
        enqueue(merged);
    }
    
    struct Node* root = dequeue();
    clearQueue();  // Clean up the queue
    
    return root;
}

void huffmanCoding(char* text) {
    printf("Input text: %s\n", text);
    
    struct Node* root = buildHuffmanTree(text);
    
    // Special case: only one unique character
    if (root && root->left == NULL && root->right == NULL) {
        printf("\nHuffman Codes:\n");
        printf("'%c': 0\n", root->data);
        printf("\nEncoded string: ");
        for (int i = 0; i < strlen(text); i++) {
            printf("0");
        }
        printf("\n");
        freeHuffmanTree(root);
        return;
    }
    
    // Generate Huffman codes
    char huffmanCodes[MAX_CHARS][100];
    for (int i = 0; i < MAX_CHARS; i++) {
        huffmanCodes[i][0] = '\0';
    }
    
    char code[100];
    storeCodes(root, code, 0, huffmanCodes);
    
    // Display the codes
    printf("\nHuffman Codes:\n");
    for (int i = 0; i < MAX_CHARS; i++) {
        if (huffmanCodes[i][0] != '\0') {
            printf("'%c': %s\n", (char)i, huffmanCodes[i]);
        }
    }
    
    // Display encoded string
    printf("\nEncoded string: ");
    for (int i = 0; i < strlen(text); i++) {
        printf("%s", huffmanCodes[(int)text[i]]);
    }
    printf("\n");
    
    freeHuffmanTree(root);
}

int main() {
    char text[1000];
    
    printf("Enter text to encode: ");
    fgets(text, sizeof(text), stdin);
    
    // Remove newline character if present
    int len = strlen(text);
    if (text[len-1] == '\n') {
        text[len-1] = '\0';
    }
    
    if (strlen(text) > 0) {
        huffmanCoding(text);
    } else {
        printf("Please enter valid text.\n");
    }
    
    return 0;
}
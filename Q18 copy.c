#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* add */
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
/* add */

#define MAX_ENTRIES 16
// maxinum number of data item each node can hold. Sample Output shows the
// result when MAX_ENTRIES is 2
#define MAX_NAME_LEN 50  // maxinum number of character for item name

typedef struct {
  double minX, minY;
  double maxX, maxY;
} Box;

typedef struct {
  double latitude, longitude;
  char name[MAX_NAME_LEN];
} Data;

typedef struct {
  Data data;
  double distance;
} SearchResult;

typedef struct RTreeNode {
  int isLeaf;  // 是否為葉節點is leaf or not
  int count;   // number of node
  Box mbr;     // minimum bounding rectangle
  struct RTreeNode* children[MAX_ENTRIES + 1];
  Data data[MAX_ENTRIES + 1];  //
} Node;

/* pre dec */
Node* insertWithinNode(Node** node, Data* item);
/* pre dec */

Box* mergedMBR_Node(Node* node, Node* child) {
  Box* mbr = (Box*)malloc(sizeof(Box));
  mbr->minX = fmin(node->mbr.minX, child->mbr.minX);
  mbr->minY = fmin(node->mbr.minY, child->mbr.minY);
  mbr->maxX = fmax(node->mbr.maxX, child->mbr.maxX);
  mbr->maxY = fmax(node->mbr.maxY, child->mbr.maxY);
  return mbr;
}
Box* mergedMBR_Leaf(Box* box, Data* data) {
  Box* mbr = (Box*)malloc(sizeof(Box));
  mbr->minX = fmin(box->minX, data->latitude);
  mbr->minY = fmin(box->minY, data->longitude);
  mbr->maxX = fmax(box->maxX, data->latitude);
  mbr->maxY = fmax(box->maxY, data->longitude);
  return mbr;
}
Box* MBR(Node* node) {  // minimum bounding range of a node
  Box* mbr;
  if (node->isLeaf)
    for (int i = 0; i < node->count; i++)  //
      mbr = mergedMBR_Leaf(&node->mbr, &node->data[i]);
  else
    for (int i = 0; i < node->count; i++)
      mbr = mergedMBR_Node(node, node->children[i]);
  return mbr;
}

void mergeData(Node* node, Data* data) {
  if (data == NULL) return;
  node->mbr = *mergedMBR_Leaf(&node->mbr, data);
  node->data[node->count++] = *data;
}
void mergeNode(Node* node, Node* child) {
  if (child == NULL) return;
  node->mbr = *mergedMBR_Node(node, child);
  node->children[node->count++] = child;
}

// area of the given box
double area(Box* box) {
  return (box->maxX - box->minX) * (box->maxY - box->minY);
}
// area of the box after merging with the given data
double mergedArea(Box* box, Data* data) {
  return area(mergedMBR_Leaf(box, data));
}
// difference of the area of merged box and the original box
double enlargement(Box* box, Data* data) {
  return mergedArea(box, data) - area(box);
}

int firstLeastEnlargement(Node* node, Data* data) {
  double minEnlargement = DBL_MAX;
  int index = 0;
  for (int i = 0; i < node->count; i++) {
    if (node->children[i] == NULL) continue;
    double volume = enlargement(&node->children[i]->mbr, data);
    if (volume < minEnlargement) {
      minEnlargement = volume;
      index = i;
    }
  }
  return index;
}
// create new node with data and return the new node
Node* newNode(Data* item) {
  Node* node = (Node*)malloc(sizeof(Node));
  node->isLeaf = 1;
  node->count = 1;
  mergeData(node, item);

  return node;
}

void sortData(Node* node, int i, int j, int axis) {
  if (axis == 0 ? node->data[i].latitude > node->data[j].latitude
                : node->data[i].longitude > node->data[j].longitude) {
    Data temp = node->data[i];
    node->data[i] = node->data[j];
    node->data[j] = temp;
  }
}
void sortNode(Node* node, int i, int j, int axis) {
  if (axis == 0 ? node->children[i]->mbr.minX > node->children[j]->mbr.minX
                : node->children[i]->mbr.minY > node->children[j]->mbr.minY) {
    Node* temp = node->children[i];
    node->children[i] = node->children[j];
    node->children[j] = temp;
  }
}

Node* splitNode(Node* node) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->isLeaf = (*node).isLeaf;
  newNode->count = 0;
  /* Determine split dimension */
  int axis = node->mbr.maxY - node->mbr.minY > node->mbr.maxX - node->mbr.minX
                 ? 1   // longitude
                 : 0;  // latitude
  /* Determine split dimension */
  /* sort data/node by axis */
  for (int i = 0; i < node->count; i++)
    for (int j = 0; j < node->count; j++)
      if (node->isLeaf)
        sortData(node, i, j, axis);
      else
        sortNode(node, i, j, axis);
  /* sort data/node by axis */
  /* assign sorted data/node to new node */
  for (int i = node->count / 2; i < node->count; i++)
    if (node->isLeaf)
      newNode->data[newNode->count++] = node->data[i];
    else
      newNode->children[newNode->count++] = node->children[i];
  /* assign sorted data/node to new node */
  /* rearrange */
  node->count = node->count - newNode->count;
  /* here */
  node->mbr = *MBR(node);
  newNode->mbr = *MBR(newNode);
  /* rearrange */
  return newNode;
}
// insert data toward node
Node* insert_Node(Node** node, Data* item) {
  Node* newNode = insertWithinNode(
      &((*node)->children[firstLeastEnlargement(*node, item)]), item);
  if (newNode == NULL) return NULL;  // no new node created

  mergeNode(*node, newNode);
  if ((*node)->count <= MAX_ENTRIES) return NULL;  // no split needed

  return splitNode(*node);  // split
}

// insert data toward leaf
Node* insert_Leaf(Node** node, Data* item) {
  mergeData(*node, item);
  if ((*node)->count <= MAX_ENTRIES) return NULL;  // no split needed

  return splitNode(*node);  // split
}
// insert data toward node or leaf
Node* insertWithinNode(Node** node, Data* item) {
  return (*node)->isLeaf ? insert_Leaf(node, item) : insert_Node(node, item);
}
Node* splitRoot(Node* root) {
  Node* newNode = splitNode(root);
  Node* newRoot = (Node*)malloc(sizeof(Node));
  newRoot->isLeaf = 0;
  newRoot->count = 2;
  newRoot->children[0] = root;
  newRoot->children[1] = newNode;
  newRoot->mbr = *MBR(newRoot);
  return newRoot;
}
// insert data
void insert(Node** root, Data item) {
  if (*root == NULL) {
    *root = (Node*)malloc(sizeof(Node));
    (*root)->isLeaf = 1;
    (*root)->count = 0;
    mergeData(*root, &item);

  } else if ((*root)->isLeaf) {
    mergeData(*root, &item);
  } else {
    Node* newNode = insertWithinNode(root, &item);
    if (newNode) mergeNode(*root, newNode);
  }

  if ((*root)->count > MAX_ENTRIES) *root = splitRoot(*root);
}
// search data
SearchResult* search(Node* node, double latitude, double longitude, int n) {
  //
}

// print tree
void printTree(Node* root, int depth) {
  for (int i = 0; i < depth; i++) printf("  ");
  printf("Node (count=%d, isLeaf=%d):\n", root->count, root->isLeaf);
  for (int i = 0; i < root->count; i++) {
    if (root->isLeaf) {
      for (int j = 0; j < depth + 1; j++) printf("  ");
      printf("Data: %s (%.2f, %.2f)\n", root->data[i].name,
             root->data[i].latitude, root->data[i].longitude);

    } else {
      printTree(root->children[i], depth + 1);
    }
  }
}

int main() {
  Node* root = NULL;
  Data item;
  double latitude, longitude;
  SearchResult* results;

  char command[50];

  while (1) {
    scanf("%s", command);
    if (strcmp("insert", command) == 0) {
      scanf("%lf%lf%s", &item.latitude, &item.longitude, item.name);
      insert(&root, item);
    } else if (strcmp("print", command) == 0) {
      printTree(root, 0);
    } else if (strcmp("exit", command) == 0) {
      break;
    } else if (strcmp("search", command) == 0) {
      scanf("%lf%lf", &latitude, &longitude);
      SearchResult* result = search(root, latitude, longitude, 2);
      for (int i = 0; i < 2; i++) {
        printf("%s (%.2f, %.2f) - Distance: %.2f\n", results[i].data.name,
               results[i].data.latitude, results[i].data.longitude,
               results[i].distance);
      }
    } else {
      printf("Unknow command.\n");
    }
  }
  return 0;
}

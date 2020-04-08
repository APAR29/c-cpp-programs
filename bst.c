#include <stdio.h>
#include <math.h>

struct bst {
    int data;
    struct bst *left;
    struct bst *right;
    struct bst *parent;
};

void deleteBST(struct bst *node) {
    struct bst *temp;
    if(node->left == NULL && node->right == NULL) {
        node = node -> parent;
        free(node -> left);
        free(node -> right);
        node -> left = NULL;
        node -> right = NULL;
    }
    else if(node -> left == NULL && node -> right != NULL) {
        node -> parent -> right = node -> right;
        node -> right -> parent = node -> parent;
    }
    else if(node -> left != NULL && node -> right == NULL) {
        node -> parent -> left = node -> left;
        node -> left -> parent = node -> parent;
    }
    else {
        struct bst *trav;
        if(node->parent->left == node) {
            node->parent->left = node -> right;
            node->right->parent = node -> parent;
            trav = node -> left;
            while(trav -> right != NULL) {
                trav = trav -> right;
            }
            trav -> right = node -> right -> left;
            node -> right -> left = node -> left;
            node -> left -> parent = node -> right;
            node -> right -> left -> parent = trav;
            free(node);
        }
        else {
            node -> parent -> right = node -> right;
            node -> right -> parent = node -> parent;
            trav = node -> left;
            while(trav -> right != NULL) {
                trav = trav -> right;
            }
            trav -> right = node -> right -> left;
            node -> right -> left -> parent = trav;
            node -> right -> left = node -> left;
            node -> left -> parent = node -> right;
            free(node);
        }
    }
}

int findNodeLevel1(struct bst *tree, int data, int count) {
    if(tree!=NULL) {
        int left = findNodeLevel1(tree->left, data, count + 1);
        int right = findNodeLevel1(tree->right, data, count + 1);
        if(tree->data == data) {
            return count + 1;
        }
        else {
            if(left != 0) {
                return left;
            }
            if(right != 0) {
                return right;
            }
            return 0;
        }
    }
    else {
        return 0;
    }
}

int findMaxlevel(struct bst *tree, int count) {
    if(tree!=NULL) {
        int left = findMaxlevel(tree->left, count + 1);
        int right = findMaxlevel(tree->right, count + 1);
        if(left > right) {
            return left;
        }
        else {
            return right;
        }
    }
    else {
        return count;
    }
}

int findNodes(struct bst *tree, int count) {
    if(tree!=NULL) {
        return findNodes(tree->left, count + 1) + 1 + findNodes(tree->right, count + 1);
    }
    else {
        return 0;
    }
}

int findSibling(struct bst *tree, int data1, int data2) {
    if(tree != NULL) {
        if(findSibling(tree->left, data1, data2) == 0) {
            if(tree->left != NULL && tree->right != NULL) {
                if((tree->left->data == data1 && tree->right->data == data2) || (tree->left->data == data2 && tree->right->data == data1)) {
                    return 1;
                }
            }
            return findSibling(tree -> right, data1, data2);
        }
        else {
            return 1;
        }
    }
    else {
        return 0;
    }
}

int findComplete(struct bst *tree) {
    if(tree != NULL) {
        if(findComplete(tree->left) == 1) {
            if(!((tree->left == NULL && tree -> right == NULL) || (tree->left != NULL && tree -> right != NULL))) {
                return 0;
            }
            return findComplete(tree->right);
        }
        else {
            return 0;
        }
    }
    else {
        return 1;
    }
}

void findBottomNodes(struct bst *tree) {
    if(tree != NULL){
        findBottomNodes(tree->left);
        if(tree->left == NULL && tree->right == NULL) {
            printf("%d\n", tree->data);
        }
        findBottomNodes(tree->right);
    }
}

void insertion(struct bst *t, int data, struct bst *root) {
    if(data <= t->data) {
        if(t->left != NULL) {
            insertion(t->left, data, root);
        }
        else {
            t -> left = malloc(sizeof(struct bst));
            t -> left -> data = data;
            t -> left -> left = NULL;
            t -> left -> right = NULL;
            t -> left -> parent = t;
        }
    }
    else {
        if(t->right != NULL) {
            insertion(t->right, data, root);
        }
        else {
            t -> right = malloc(sizeof(struct bst));
            t -> right -> data = data;
            t -> right -> left = NULL;
            t -> right -> right = NULL;
            t -> right -> parent = t;
        }
    }
}

void printTree(struct bst *tr) {
    if(tr!=NULL) {
        printTree(tr -> left);
        printf("%d\n", tr -> data);
        printTree(tr -> right);
    }
}

void inOrder(struct bst *tr, int data) {
    if(tr!=NULL) {
        inOrder(tr -> left, data);
        if(tr->data == data) {
            deleteBST(tr);
        }
        inOrder(tr -> right, data);
    }
}

int main() {
    int comp, sib, count, level=1, full = 0, lenn, maxlevel, desired;
    struct bst *tree, *q;
    int arr[] = {8,2, 6,3,9, 11}, len = 6;
    tree = malloc(sizeof(struct bst));
    tree -> data = 5;
    tree -> left = NULL;
    tree -> right = NULL;
    tree -> parent = tree;

    q = tree;
    for(int i=0; i<len; i++) {
        insertion(q, arr[i], q);
    }

    printTree(q);
    printf("Complete tree?\n");
    comp = findComplete(q);
    printf("%d\n", comp);
    printf("Siblings?\n");
    sib = findSibling(q, 2, 3);
    printf("%d\n", sib);
    printf("Bottom nodes\n");
    findBottomNodes(q);
    lenn = findNodes(q, 0);
    maxlevel = findMaxlevel(q, 0);
    printf("Maximum Level %d\n", maxlevel);
    printf("Total Number of Nodes %d\n", lenn);
    desired = pow(2, maxlevel) - 1;
    full = (desired == lenn) ? 1 : 0;
    printf("Full Binary Tree? %d\n", full);
    printf("Given Node Level? %d\n", findNodeLevel1(q, 5, 0));

    // inOrder(q, 8);
    // printf("After deleting 8\n");
    // printTree(q);
    return 0;
}
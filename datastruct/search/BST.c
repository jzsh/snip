// https://www.codesdope.com/blog/article/binary-search-tree-in-c/
// http://www.cnblogs.com/skywang12345/p/3576328.html

#include <stdlib.h>
#include <stdio.h>

typedef int Key;
typedef int Value;

typedef struct node {
    int key;
    int value;
    struct node *left;
    struct node *right;
} node;


// 递归
node *get(node *root, int key)
{
    if(root == NULL || root->key == key)
        return root;

    if(root->key < key)
        return get(root->right, key);

    return get(root->left, key);
}

// 迭代版
node *get2(node *root, int key)
{
    node *curr = root;
    if(root == NULL || root->key == key)
        return root;

    while(curr != NULL) {
        if(key < curr->key)
            curr = curr->left;
        else if(key > curr->key)
            curr = curr->right;
        else
            break;
    }
    return curr;
}

node *min(node *root)
{
    node *min_node = root;

    if(root == NULL)
        return NULL;

    while(min_node->left != NULL)
        min_node = min_node->left;

    return min_node;
}

node* max(node* root)
{
    node* max_node = root;

    if (root == NULL) {
        return NULL;
    }

    while (max_node->right != NULL) {
        max_node = max_node->right;
    }

    return max_node;
}

node *new_node(int key)
{
    node *p = malloc(sizeof(node));
    if(p == NULL)
        return p;
    p->key = key;
    p->left = NULL;
    p->right = NULL;
    return p;
}

node *insert(node *root, int key)
{
    if(root == NULL)
        return new_node(key);
    else if(key > root->key)
        root->right = insert(root->right, key);
    else if(key < root->key)
        root->left = insert(root->left, key);
    else
        root->key = key;
    return root;
}


node *delete(node *root, int key)
{
    if(root == NULL)
        return NULL;
    if(key > root->key)
        root->right = delete(root->right, key);
    else if(key < root->key)
        root->left = delete(root->left, key);
    else {
        // No children
        if(root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // one children
        else if(root->left == NULL || root->right == NULL) {
            node *tmp;
            if(root->left == NULL)
                tmp = root->right;
            else
                tmp = root->left;
            free(root);
            return tmp;
        }
        // two child
        else {
            // 找到右子树最小值, 交换到root处，然后删除该最小值
            node *tmp = min(root->right);
            root->key = tmp->key;
            root->right = delete(root->right, tmp->key);
        }
    }

    return root;
}


void inorder(node *root)
{
    if(root != NULL) {
        inorder(root->left);
        printf(" %d ", root->key);
        inorder(root->right);
    }
}

int main()
{
    node *root; 
    root = new_node(20);
    insert(root,5);
    insert(root,1);
    insert(root,15);
    insert(root,9);
    insert(root,7);
    insert(root,12);
    insert(root,30);
    insert(root,25);
    insert(root,40);
    insert(root,45);
    insert(root,42);

    inorder(root);
    printf("\n");

    root = delete(root, 1);
    root = delete(root, 40);
    root = delete(root, 45);
    root = delete(root, 9);

    inorder(root);
    printf("\n");

    return 0;
}







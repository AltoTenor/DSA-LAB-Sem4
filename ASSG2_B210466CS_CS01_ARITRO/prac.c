#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b)
{
	return (a > b)? a : b;
}

struct node{
    int val;
    int height;
    struct node * left;
    struct node * right;
};

int height (struct node * temp){
    if (temp==NULL) return 0;
    else return temp->height;
}

struct node * create(int key){
    struct node * temp=(struct node *)malloc(sizeof(struct node));
    temp->height=1;
    temp->val=key;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

int balanc(struct node * temp){
    if (temp==NULL) return 0;
    else return height(temp->left)-height(temp->right);
}

struct node * leftrotate(struct node * x){
    struct node * y=x->right;
    struct node * T=y->left;
    y->left=x;
    x->right=T;
    x->height = max(height(x->left),height(x->right)) + 1;
	y->height = max(height(y->left),height(y->right)) + 1;
    return y;
}

struct node * rightrotate(struct node * x){
    struct node * y=x->left;
    struct node * T=y->right;
    y->right=x;
    x->left=T;
    x->height = max(height(x->left),height(x->right)) + 1;
	y->height = max(height(y->left),height(y->right)) + 1;
    return y;
}


struct node * insert(struct node * Node,int key){
    if (Node==NULL) return create(key);
    else if (Node->val < key) Node->right= insert(Node->right,key);
    else if (Node->val > key) Node->left = insert(Node->left,key);
    // else return Node;
    Node->height = 1 + max(height(Node->left),height(Node->right));
    int balance=balanc(Node);
    if (balance > 1 && key< Node->left->val ){
        return rightrotate(Node);
    }
    if (balance <-1  && Node->right->val < key){
        return leftrotate(Node);
    }
    if (balance > 1 && Node->left->val < key){
        Node->left=leftrotate(Node->left);
        return rightrotate(Node);
    }
    if (balance <-1 && Node->right->val > key){
        Node->right=rightrotate(Node->right);
        return leftrotate(Node);
    }
    return Node;
    
}

void preorder(struct node *root)
{
	if(root != NULL)
	{
		printf("%d ", root->val);
		preorder(root->left);
        
		preorder(root->right);
	}
}


int main()
{
    struct node *root = NULL;

    /* Constructing tree given in the above figure */
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    /* The constructed AVL Tree would be
            30
            / \
           20 40
          / \   \
         10  25  50
    */

    printf("Preorder traversal of the constructed AVL"
            " tree is \n");
    preorder(root);

    return 0;
}

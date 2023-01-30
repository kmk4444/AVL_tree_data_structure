#include<stdio.h>
#include<stdlib.h>
// An AVL TreeNode
typedef struct TreeNode
{
    int item;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
}TreeNode;

int getHeightOfTree(TreeNode *);
int getMax(int a, int b);
TreeNode * rightRotate(TreeNode *);
TreeNode * leftRotate(TreeNode *);
int getBalanceFactor(TreeNode *);
TreeNode* insertInTreeNode(TreeNode*, int);
void preOrder(TreeNode *);
void inOrder(TreeNode *);
void postOrder(TreeNode *);
TreeNode * balance(TreeNode *, int);
void printAux(TreeNode*, int, int, char);
/* The constructed AVL Tree in example would be
              28
             /  \
           27    72
          /  \   /  \
         18  27  36  108
                     /  \
                    90  117
*/

int main() {
    TreeNode *root = NULL;
    int temp;
    scanf("%d", &temp);
    while(temp != -1){
        root = insertInTreeNode(root, temp);
        scanf("%d", &temp);
    }

   // printf("Preorder traversal of the constructed AVL tree is \n");
    // preOrder(root);

   // printf("\nInorder traversal of the constructed AVL tree is \n");
    inOrder(root);

    int level = getHeightOfTree(root);
    printf("\n");
    for (int node = 1; node <= level; node++) {
        printAux(root, node, -1, ' ');
        printf("\n");
    }

   // printf("\nPostOrder traversal of the constructed AVL tree is \n");
    // postOrder(root);
    return 0;
}


// get the height of the tree
int getHeightOfTree(TreeNode *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

//get maximum of two integers
int getMax(int a, int b)
{
    return (a > b)? a : b;
}

// right rotate subtree rooted with y
// See the diagram given above.
TreeNode * rightRotate(TreeNode *node)
{
    TreeNode *lhs = node->left;
    TreeNode *rhs = node->right;

    // Perform rotation
    lhs->right = node;
    node->left = rhs;

    // Update heights
    node->height = getMax(getHeightOfTree(node->left), getHeightOfTree(node->right)) + 1;
    node->height = getMax(getHeightOfTree(node->left), getHeightOfTree(node->right)) + 1;
    return lhs;
}

//left rotate subtree rooted with x

TreeNode * leftRotate(TreeNode *node)
{
    TreeNode *rhs = node->right;
    TreeNode *lhs = rhs->left;

    // Perform rotation
    rhs->left = node;
    node->right = lhs;

    //  Update heights
    node->height = getMax(getHeightOfTree(node->left),
                       getHeightOfTree(node->right)) + 1;
    rhs->height = getMax(getHeightOfTree(rhs->left), getHeightOfTree(rhs->right)) + 1;

    return rhs;

}

// Get Balance factor of node N
int getBalanceFactor(TreeNode *node)
{
    if (node == NULL)
        return 0;
    return getHeightOfTree(node->left) - getHeightOfTree(node->right);
}

// insert into root
TreeNode* insertInTreeNode(TreeNode* node, int item)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL) {
       node = (TreeNode *) malloc(sizeof(TreeNode));
        node->item = item;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;  // new node is initially added at leaf

    }
    else if(item < node->item )
        node->left = insertInTreeNode(node->left, item);
    else if (item > node->item)
        node->right = insertInTreeNode(node->right, item);
    else
        return node;
    node->height = 1 + getMax(getHeightOfTree(node->left),getHeightOfTree(node->right));
    return balance(node, item);
}

TreeNode * balance(TreeNode *node, int newItem){
    /* 3. Get the balance factor of this ancestor node to check whether this node became unbalanced */
    int balanceN = getBalanceFactor(node);

    // If this node becomes unbalanced, then there are 4 cases
    // Case 1. Left-Left Case
    if (balanceN > 1 && newItem < node->left->item)
        node = rightRotate(node);

    // Case 2. Right-Right Case
    else if (balanceN < -1 && newItem > node->right->item)
        node = leftRotate(node);

    // Case 3. Left-Right Case
    else if (balanceN > 1 &&newItem > node->left->item)
    {
        node->left = leftRotate(node->left);
        node = rightRotate(node);
    }

    // Case 4. Right-Left Case
    else if (balanceN < -1 && newItem < node->right->item)
    {
        node->right = rightRotate(node->right);
        node = leftRotate(node);
    }

    return node;

}
//  print preorder traversal of the tree.
void preOrder(TreeNode *root)
{
    if(root != NULL)
    {
        printf("%d ", root->item);
        preOrder(root->left);
        preOrder(root->right);
    }
}
// print inOrder traversal of the tree.
void inOrder(TreeNode *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        printf("%d\n", root->item);
        inOrder(root->right);
    }
}

// print postOrder traversal of the tree.
void postOrder(TreeNode *root)
{
    if(root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->item);
    }
}

void printAux(TreeNode *node, int level, int parent, char pos) {
    static int sign = 1;
    if (node == NULL)
        return;

    if (sign) {
        printf("%d (%d B)", node->item, getBalanceFactor(node));
        sign = 0;
    }

    else if (level == 1) {
        printf("%d (%d %c) (%d B) ", node->item, parent, pos, getBalanceFactor(node));
    }

    if (level > 1) {
        printAux(node->left, level-1, node->item, 'L');
        printAux(node->right, level-1, node->item, 'R');
    }
}
/* First of all we need 2 buckets that operates as Stacks (Last-in Fist-out)
 * 1) Tree Stack: which will hold operands and mini-tree that we will create
 * 2) The Operator Stack: This holds the math operator (+,-,*,/)
 *
 * To create the Tree we need to:
 * - Take the top operator od the Operator Stack
 * - Take the top 2 operands out of the Tree Stack
 * - Make the operator the "Parent node", and attach the 2 operands as its left and right "Leaf or children"
 * - Drop this new "mini-tree" back into the Tree Stack
 *
 * Rules:
 * 1) I read an operand: make it standalone node and drop it into the Tree Stack
 * 2) I read an open parenthesis '(': drop it into the Operator Stack
 * 3) I read a close parenthesis ')': finish everything inside the brackets, repeatedly combining operators and operands
 * mini trees until the top operator of Operator Stack is the open parenthesis '(' and throw it in the trash.
 * 4) I read an operator: I need to look at the very first operator in Operator Stack, compare it to my current operator
 * and the stronger operator or equal must go first to create the mini tree. Keep checking until the top operator
 * is weaker than the operator I'm holding, and then I can drop my operator in.
 *
 * 5) I've read everything, but I have still pending operators in my Operator Stack so I just create the last mini trees
 * until my Operator Stack is completely empty.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef char DATA;

/* Binary Tree */
typedef struct TreeNode  // This is the struct which will hold my operators and operands (1, 2, 3, +, *, ...)
{
    DATA data;  // 1, 2, 3, +, *, ...
    struct TreeNode *left, *right; // Left and right child or leaf
}TreeNode;

/* Linked list used as a stack for operands */
typedef struct TreeStack
{
    TreeNode *treeNode;
    struct TreeStack *next;
}TreeStack;

/* Linked list used as a stack for operands */
typedef struct OperatorStack
{
    DATA data;
    struct OperatorStack *next;
}OperatorStack;

int getOpStrenght(DATA data);

TreeNode *createTreeNode(DATA data);

TreeStack *createTreeStackNode(TreeNode *newTreeNode);
void pushTreeStack(TreeStack **top, TreeNode *newTreeNode);
TreeNode *popTreeStack(TreeStack **top);

OperatorStack *createOperatorStackNode(DATA data);
void pushOperatorStack(OperatorStack **top, DATA data);
DATA popOperatorStack(OperatorStack **top);
DATA peekOperatorStack(const OperatorStack *top);

void createTree(TreeStack **treeStack, OperatorStack **opStack);
TreeNode *shuntingYard(const char *expression);

void read_reverse_polish_notation(TreeNode *tree);
void read_human_notation(TreeNode *tree);

void freeTree(TreeNode *tree);

int main(void)
{

    TreeNode *tree = shuntingYard("((A + B) * (C - D)) / E");
    printf("Human Notation: ");
    read_human_notation(tree);
    printf("\n");
    printf("Reverse Polish Notation: ");
    read_reverse_polish_notation(tree);

    freeTree(tree);

    return 0;
}

void freeTree(TreeNode *tree)
{
    if (tree == NULL) return;
    freeTree(tree->left);
    freeTree(tree->right);
    free(tree);
}

// In order to read a reverse polish notation from a tree
// we need to navigate on the left side of the tree, and then read in this order: left, right and parent
void read_reverse_polish_notation(TreeNode *tree)
{
    if (tree == NULL) return;
    read_reverse_polish_notation(tree->left);
    read_reverse_polish_notation(tree->right);
    printf("%c ", tree->data);
}

// In order to read a reverse polish notation from a tree
// we need to navigate on the left side of the tree, and then read in this order: left, parent and right
void read_human_notation(TreeNode *tree)
{
    if (tree == NULL) return;
    if (tree->left != NULL && tree->right != NULL) printf("(");  // If a node does not have leafs it's an operator so we open a bracket
    read_human_notation(tree->left);
    printf("%c", tree->data);
    read_human_notation(tree->right);
    if (tree->left != NULL && tree->right != NULL) printf(")"); // If a node does not have leafs it's an operator so we close a bracket
}

TreeNode *shuntingYard(const char *expression)
{
    OperatorStack *opStack = NULL;
    TreeStack *treeStack = NULL;

    for (int i = 0; expression[i] != '\0'; i++)
    {
        if (expression[i] == ' ') continue;
        if (isalpha(expression[i])) pushTreeStack(&treeStack, createTreeNode(expression[i]));  // 1)
        else if (expression[i] == '(') pushOperatorStack(&opStack, expression[i]);  // 2)
        else if (expression[i] == ')')  // 3)
        {
            while (peekOperatorStack(opStack) != '(') createTree(&treeStack, &opStack);
            popOperatorStack(&opStack);
        }else
        {   // 4)
            while (peekOperatorStack(opStack) != '\0' && peekOperatorStack(opStack) != '(' && getOpStrenght(peekOperatorStack(opStack)) >= getOpStrenght(expression[i]))
            {
                createTree(&treeStack, &opStack);
            }
            pushOperatorStack(&opStack, expression[i]);
        }
    }
    while (peekOperatorStack(opStack) != '\0') createTree(&treeStack, &opStack);
    return popTreeStack(&treeStack);  // The last parent node
}

int getOpStrenght(DATA data)
{
    if (data == '+' || data == '-')
    {
        return 1;
    }
    if (data == '*' || data == '/')
    {
        return 2;
    }
    return 0;
}

void createTree(TreeStack **treeStack, OperatorStack **opStack)
{
    char op = popOperatorStack(opStack); // Takes the operator

    TreeNode *right = popTreeStack(treeStack);
    TreeNode *left = popTreeStack(treeStack);

    TreeNode *parent = createTreeNode(op);
    parent->left = left;
    parent->right = right;

    pushTreeStack(treeStack, parent);
}

TreeNode *createTreeNode(DATA data)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeStack *createTreeStackNode(TreeNode *newTreeNode)
{
    TreeStack *newStackNode = (TreeStack *)malloc(sizeof(TreeStack));  // Create a new StackNode for my stack
    newStackNode->treeNode = newTreeNode;  // Inserting the pointer to a Tree Node in my stack
    newStackNode->next = NULL;  // Initializing next to NULL
    return newStackNode;
}

void pushTreeStack(TreeStack **top, TreeNode *newTreeNode)
{
    TreeStack *newStackNode = createTreeStackNode(newTreeNode);
    newStackNode->next = *top;
    *top = newStackNode;
}

TreeNode *popTreeStack(TreeStack **top)
{
    if (*top == NULL )  // If the stack is empty
    {
        return NULL;
    }

    TreeStack *temp = *top;  // I take the reference to the top
    *top = (*top)->next;  // Move the pointer top forward
    TreeNode *treeNode = temp->treeNode;  // Take the data inside the StackNode (the tree)
    free(temp);  // Free the memory
    return treeNode;  // returning the popped element
}

OperatorStack *createOperatorStackNode(const DATA data)
{
    OperatorStack *newOpStackNode = (OperatorStack *)malloc(sizeof(OperatorStack));
    newOpStackNode->data = data;
    newOpStackNode->next = NULL;
    return newOpStackNode;
}
void pushOperatorStack(OperatorStack **top, const DATA data)
{
    OperatorStack *newOpStackNode = createOperatorStackNode(data);
    newOpStackNode->next = *top;
    *top = newOpStackNode;
}

DATA popOperatorStack(OperatorStack **top)
{
    if (*top == NULL )
    {
        return '\0';
    }

    OperatorStack *temp = *top;
    *top = (*top)->next;
    DATA data = temp->data;
    free(temp);
    return data;
}

DATA peekOperatorStack(const OperatorStack *top)  // This allows us to peek the first element without changing the reference
{
    if (top == NULL )
    {
        return '\0';
    }
    return top->data;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char* data;
    char color;
    struct Node *left,*right,*parent;
} Node;



typedef struct Tree
{

    Node*root;
    int sizetotal;

} Tree;


void inorderTree(Node* root);


Node *newNode(char* val)
{
    Node *n=malloc(sizeof(Node));
    n->data = malloc(strlen(val)+1);
    if(n->data)
        strcpy(n->data, val);
//    n->data=val;
    n->left=NULL;
    n->right=NULL;
    n->parent=NULL;
    n->color='r';
    return n;
}

int max(int a, int b)
{
    return a>b?a:b;
}

int height(Node*root)
{
    if(root==NULL)
        return 0;
    else
        return 1 + max(height(root->left), height(root->right));
}
Node * search(Node*t, char* val)
{

    while(strcasecmp(t->data,val)!=0)
    {

        if(t != NULL)
        {

            if(strcasecmp(t->data, val)>0)
                t = t->left;
            else
                t = t->right;

            if(t == NULL)
            {
                return NULL;
            }
        }
    }

    return t;


}

Node* BSTInsert(Node  *root, Node *node)
{

    if (root == NULL)
        return node;

    if (strcasecmp(node->data, root->data) <0)
    {
        root->left  = BSTInsert(root->left, node);
        root->left->parent=root;
        //if(node->parent)
        //  printf("inserted %s\t parent is %s\n", node->data, node->parent->data);
    }

    else if (strcasecmp(node->data, root->data)>0)
    {
        root->right = BSTInsert(root->right, node);
        root->right->parent = root;
        // if(node->parent)
        // printf("inserted %s\t parent is %s\n", node->data, node->parent->data);
    }
    return root;
}


void RBTrotateLeft(Tree *t, Node *node)
{

    Node *node_right = node->right;
    node->right = node_right->left;

    if(node_right->left != NULL)
        node_right->left->parent=node;

    node_right->parent = node->parent;

    if (node->parent == NULL)
        t->root=node_right;
    else if(node == node->parent->left)
        node->parent->left=node_right;
    else
        node->parent->right=node_right;

    node_right->left=node;
    node->parent=node_right;

}


void RBTrotateRight(Tree*t, Node *node)
{
    Node *node_left = node->left;
    node->left = node_left->right;

    if(node_left->right != NULL)
        node_left->right->parent=node;

    node_left->parent = node->parent;

    if (node->parent == NULL)
        t->root=node_left;
    else if(node == node->parent->left)
        node->parent->left=node_left;
    else
        node->parent->right=node_left;

    node_left->right=node;
    node->parent=node_left;
}

void RBTfix(Tree*t, Node*node)
{
    //printf("node is %s\n",node->data);
    Node* parent_node=node->parent;

    Node*grandapa_node=NULL;

    char temp[2] = "0";
    Node* Uncle_node=newNode(temp);
    Uncle_node->color='b';

//    there's no parent for node then node is the root of the tree
    if(node->parent==NULL)
    {
        node->color='b';
        t->root=node;
        return;
    }
//    there's no grandpa for the node   then tree is a two nodes only
    if(node->parent->parent==NULL)
        return;
    else
    {
        grandapa_node=node->parent->parent;
        //  printf("granpa is %d\n", grandapa_node->data);
        // int a = parent_node->color!='b' ;
        //        int b = grandapa_node != NULL;
        // if parent red&&grandpa exist
        if (parent_node->color!='b'&&grandapa_node != NULL)
        {
            //casec 1:leftleft
            /* if current node is leftparent and parent leftgrandpa
             * Uncle will be right grandpa
             * check uncle color  null /black
             * if black recolour  parent &grandpa then rotateright grandpa
                else recolor uncle &grandpa &parent and fix grandpa */
            if( node==parent_node->left&&
                    parent_node==grandapa_node->left)
            {
                Uncle_node=grandapa_node->right;
                if (Uncle_node==NULL|| Uncle_node->color=='b')
                    //uncle color black or ni
                {
                    parent_node->color='b';
                    grandapa_node->color='r';
                    RBTrotateRight(t,grandapa_node);

                }
                else
                {
                    //change color
                    Uncle_node->color='b';
                    parent_node->color='b';
                    grandapa_node->color='r';
                    RBTfix(t,grandapa_node);
                }
            }
            //case 2:RightRight
            /* if current node is rightparent and parent rightgrandpa
             * Uncle will be leftgrandpa
             * check uncle color  null /black
             * if black recolour  parent &grandpa then rotateleft grandpa
                else recolor uncle &grandpa &parent and fix grandpa  */
            if(node==parent_node->right&&
                    parent_node==grandapa_node->right)
            {
                Uncle_node=grandapa_node->left;
                if (Uncle_node==NULL|| Uncle_node->color=='b')
                    //uncle color black or nil
                {
                    parent_node->color='b';
                    grandapa_node->color='r';
                    RBTrotateLeft(t,grandapa_node);

                }
                else
                {
                    //change color
                    Uncle_node->color='b';
                    parent_node->color='b';
                    grandapa_node->color='r';
                    RBTfix(t,grandapa_node);

                }

            }
            //casec 3:leftright

            /*if current node is rightparent and parent leftgrandpa
            * Uncle will be rightgrandpa
            * check uncle color  null /black
            * if black rotateleft parentnode then case( 1 )"leftleft "recolour  parent &grandpa then rotateright grandpa
               else recolor uncle &grandpa &parent and fix grandpa  */
            if(  node==parent_node->right&&
                    parent_node==grandapa_node->left)
            {
                Uncle_node=grandapa_node->right;


                if (Uncle_node==NULL|| Uncle_node->color=='b')
                    //uncle color black or nil
                {
                    RBTrotateLeft(t,parent_node);
                    parent_node->parent=node;
                    node->parent=grandapa_node;
                    node->color='b';
                    node->parent->color='r';
                    RBTrotateRight(t,node->parent);


                }


                else
                {
                    //change color
                    Uncle_node->color='b';
                    parent_node->color='b';
                    grandapa_node->color='r';
                    RBTfix(t,grandapa_node);
                }
            }

            //case 4:right left
            /*if current node is leftparent and parent rightgrandpa
            * Uncle will be left grandpa
            * check uncle color  null /black
            * if black rotateright parentnode then case( 2 ) recolour parent &grandpa then rotateleft grandpa
            else recolor uncle &grandpa &parent and fix grandpa  */

            if(  node==parent_node->left&&parent_node==grandapa_node->right)
            {
                Uncle_node=grandapa_node->left;
                if (Uncle_node==NULL|| Uncle_node->color=='b')
                    //uncle color black or nil
                {
                    RBTrotateRight(t,parent_node);
                    parent_node->parent=node;
                    node->parent=grandapa_node;
                    node->color='b';
                    node->parent->color='r';
                    RBTrotateLeft(t,node->parent);

                }
                else
                {
                    //change color
                    Uncle_node->color='b';
                    parent_node->color='b';
                    grandapa_node->color='r';
                    RBTfix(t,grandapa_node);
                }
            }
        }
    }
}


// Function to insert a new node with given data
void RBTinsert(Tree*t,char* data)
{
    Node *node = newNode(data);

    // Do a normal BST insert
    t->root = BSTInsert(t->root, node);
    // printf("before fix\n*************\n");
    //inorderTree(t->root);
    // printf("\n\n");
    //  fix Red Black Tree violations
    RBTfix(t, node);
    // printf("after fix\n*************\n");
    //inorderTree(t->root);
}


void NewInsert(Tree*t,char* data)
{
    // Node* n= newNode(data);
    Node* node=search(t->root,data);
    if(node==NULL)
    {
        node= newNode(data);
        t->root = BSTInsert(t->root,node);
        RBTfix(t, node);
        t->sizetotal++;
        printf("inserted Done\n\n");
    }
    else
        printf("ERROR: Word already in the dictionary!\n\n");

}

void Lookup(Tree*t,char*data)
{
    Node*node=search(t->root,data);
    if(node==NULL)
    {
        printf("NO\n\n");//notfound
    }
    else
        printf("Yes\n\n");//found

}




void PrintDictionarySize(Tree*t)
{

    printf("\n\nDictionary Size=%d",t->sizetotal);
    printf("\n\n");
}

//Display RBT - Inorder Traversal/
void inorderTree(Node* root)
{

    if (root != NULL)
    {
        inorderTree(root->left);
        printf("\n\n %s-%c \n\n",root->data,root->color);
        inorderTree(root->right);
    }
    return;
}


Tree* rebuildtree()
{
    FILE *fp;
    int size=1;
    char input[20];
    Node*root= malloc(sizeof(Node));

    fp=fopen("dictionary.txt","r");
    fscanf(fp," %[^\n]",input);
    root=newNode(input);
    root->color='b';
    Tree* tree=malloc(sizeof(Tree));
    tree->root=root;

    char data[20];
    while(fscanf(fp," %[^\n]",data)!=EOF)
    {
        //printf("%s\n",data);
        RBTinsert(tree,data);
        size++;
    }

    fclose(fp);
    tree->sizetotal=size;


    return tree;
}



int main()
{

    Tree *t=rebuildtree();

    char val[100];
    char name[100];
    int selection;
    do
    {
        printf("select(1) if you want to print DictionarySize\n");
        printf("select(2) if you want to print tree InOrdertraversal \n");
        printf("select(3) if you want to insert newword\n");
        printf("select(4) if you want to Lookup for a word\n");
        printf("select(5) if you want to print Heightof RBT\n");
        printf("Enter your selection:");

        scanf("%d",&selection);

        if(selection==1)
        {
            PrintDictionarySize(t);
        }
        else if(selection==2)
        {

            inorderTree(t->root);
        }

        else if(selection==3)
        {
            printf("\nEnter the word you want to insert: ");
            scanf(" %[^\n]",val);
            NewInsert(t,val);
            printf("The height of the tree = %d",height(t->root));/*For validation purposes, you are required to print
                                                                          both the size of the dictionary and the height of your
                                                                       Red-Black tree after each insertion*/
            PrintDictionarySize(t);
            printf("\n\n");


        }
        else if(selection==4)
        {
            printf("\n\nWrite the word you want to Lookup: ");
            scanf(" %[^\n]",name);
            Lookup(t,name);

        }
        else if(selection==5)
        {

            printf("\nThe height of the tree = %d",height(t->root));
            printf("\n\n");

        }
        else
        {
            printf("\nWrong Choice. Please try again.\n\n");
            main();
        }

    }
    while(selection<6);



    return 0;
}

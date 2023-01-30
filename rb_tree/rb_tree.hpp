#include <iostream>

#define NIL NULL
#define LEFT 0
#define RIGHT 1
#define left child[LEFT]
#define right child[RIGHT]
#define RotateDir(N, dir) RotateDirRoot(T, N, dir);
#define RotateLeft(N) RotateDirRoot(T, N, LEFT);
#define RotateRight(N) RotateDirRoot(T, N, RIGHT);
#define childDir(N) ( N == (N->parent)->right ? RIGHT : LEFT )

enum color_t { BLACK, RED };

struct RBnode
{
    RBnode*         parent;   // == NIL if root of the three
    RBnode*         child[2];  // == NIL if child is empty
            // Index is:
            // LEFT := 0, if (key < parent->key)
            // RIGHT := 1, if (key > parent->key)
    enum color_t    color;
    int             key;
};

struct RBtree
{
    RBnode* root;
};

namespace ft
{
    template <
        class T1,
        class T2,
        class CMP,
        class Alc
    > class RB_Tree
    {
        
    };
};

RBnode* RotateDirRoot(RBtree* T, RBnode* P, int dir)
{
    RBnode* G = P->parent;
    RBnode* S = P->child[1 - dir];
    RBnode* C;
    assert(S != NIL); // pointer to true node required
    C = S->child[dir];
    P->child[1 - dir] = C; if (C != NIL) C->parent = P;
    S->child[dir] = P; P->parent = S;
    S->parent = G;
    if (G != NULL)
        G->child[ P == G->right ? RIGHT : LEFT] = S;
    else
        T->root = S;
    return S; // new root of subtree
}

void RBinsert1(RBtree* T, struct RBnode* N, struct RBnode* P, int dir) // P is the parent node of N// N is the node to be inserted
{
    struct RBnode* G; // parent node of P
    struct RBnode* U; // uncle of N

    N->color = RED;
    N->left = NIL;
    N->right = NIL;
    N->parent = P;
    if (P == NULL)
    {
        T->root = N; // There is no parent and N is the new root of the tree T
        return ;
    }
    P->child[dir] = N; // insert N as dir-child of P
    // start of rebalance loop
    do
    {
        // Case I1 current notes parent P is black. 3 and 4 holds.
        if (P->color == BLACK)
            return ;
        if ((G = P->parent) == NULL)
            goto Case_I4; // P red and root
        // else: P red and G!=NULL.
        dir = childDir(P); // the side of parent G on which node P is located
        U = G->child[1 - dir]; // uncle
        if (U == NIL || U->color == BLACK)
            goto Case_I56; // P red && U black

        // Case_I2 (P+U red):
        P->color = BLACK;
        U->color = BLACK;
        G->color = RED;
        N = G; // new current node
        // iterate 1 black level higher
    } while ((P = N->parent) != NULL);
    return ;

    Case_I4: // P is the root and red:
        P->color = BLACK;
        return ;

    Case_I56: // P red && U black
        if (N == P->child[1 - dir])
        { // Case_I5 (P red && U black && N inner grandchild of G):
            RotateDir(P, dir); // P is never the root
            N = P; // new current node
            P = G->child[dir]; // new parent of N
            // fall through to Case_I6
        }

    // Case_I6 (P red && U black && N outer grandchild of G):
    RotateDirRoot(T, G, 1 - dir);
    P->color = BLACK;
    G->color = RED;
    return ;
}

void RBdelete2 (RBtree* T, struct RBnode* N)
{
    struct RBnode* P = N->parent;
    int dir; // where N is located on P
    struct RBnode* S; // sibling of N
    struct RBnode* C; // close nephew
    struct RBnode* D; // distant nephew

    // P != NULL, since N is not the root
    dir = childDir(N); // side of parent P on which the node N is located
    // Replace N at its parent P by NIL:
    P->child[dir] = NIL;
    goto Start_D;
    do
    {
        dir = childDir(N);
    Start_D:
        S = P->child[1 - dir]; // sibling of N (has black height >= 1)
        D = S->child[1 - dir]; // distant nephew
        C = S->child[dir]; // close nephew
        if (S->color == RED)
            goto Case_D3;  // S red => P+C+D black
        // S is black
        if (D != NIL && D->color == RED) // not considered black
            goto Case_D6; // D red && S black
        if (C != NIL && C->color == RED) // not considered black
            goto Case_D5; // C red && S+D black
        // Here both newphes are == NIL (first iteration) or black (later).
        if (P->color == RED)
            goto Case_D4; // P red && C+S+D black
        // Case_D1 (P == NULL):
        return ;
        // Case_D2 (P+C+S+D black):
        S->color = RED;
        N = P; // new current node (maybe the root)
        // iterate 1 black level
    } while((P = N->parent) != NULL);

    Case_D3: // S red && P+C+D black:
    RotateDirRoot(T, P, dir); // P may be the root
    P->color = RED;
    S->color = BLACK;
    S = C; // != NIL
    // now: P red && S black
    D = S->child[1 - dir]; // distant nephew
    if (D != NIL && D->color == RED)
        goto Case_D6; // D red && S black
    C = S->child[dir]; //close nephew
    if (C != NIL && C->color == RED)
        goto Case_D5; // C red && S+D black
    // Otherwise C+D considered black.
    // fall through to Case_D4
    Case_D4: // P red && S+C+D black;
        S->color = RED;
        P->color = BLACK;
        return ;
    Case_D5: // C red && S+D black:
        RotateDir(S, 1 - dir); // S is never the root
        S->color = RED;
        C->color = BLACK;
        D = S;
        S = C;
        // now: D red && S black
        // fall through to Case_D6
    Case_D6: // D red && S black:
        RotateDirRoot(T, P, dir); // P may be the root
        S->color = P->color;
        P->color = BLACK;
        D->color = BLACK;
        return ;
}
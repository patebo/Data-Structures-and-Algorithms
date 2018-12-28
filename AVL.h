#ifndef _AVL_H
#define _AVL_H

typedef struct AVLTreeData* AVLTree;
typedef struct TreeNodeData* TreeNode;

AVLTree avl_create();
void avl_destroy(AVLTree T) ;
void avl_print(AVLTree T);

void avl_insert(AVLTree T, int key);
TreeNode avl_lookup(AVLTree T, int key);
void avl_delete(AVLTree T, int key);

#endif

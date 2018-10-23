#include "btNode.h"
#include <iostream>
void dumpToArrayInOrder(btNode* bst_root, int* dumpArray)
{
   if (bst_root == 0) return;
   int dumpIndex = 0;
   dumpToArrayInOrderAux(bst_root, dumpArray, dumpIndex);
}

void dumpToArrayInOrderAux(btNode* bst_root, int* dumpArray, int& dumpIndex)
{
   if (bst_root == 0) return;
   dumpToArrayInOrderAux(bst_root->left, dumpArray, dumpIndex);
   dumpArray[dumpIndex++] = bst_root->data;
   dumpToArrayInOrderAux(bst_root->right, dumpArray, dumpIndex);
}

void tree_clear(btNode*& root)
{
   if (root == 0) return;
   tree_clear(root->left);
   tree_clear(root->right);
   delete root;
   root = 0;
}

int bst_size(btNode* bst_root)
{
   if (bst_root == 0) return 0;
   return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}

void bst_insert(btNode*& bst_root, int insInt)
{
    if(!bst_root)
   {
       btNode* temp = new btNode();
       temp->data = insInt;
       temp->left = 0;
       temp->right = 0;
       bst_root = temp;
       return;
   }
   btNode* cur = bst_root;
   btNode* pre = 0;
   while(cur != 0)
   {
       if(cur->data == insInt)
       {
           cur->data = insInt;
           return;
       }
       pre = cur;
       if(cur->data < insInt)
           cur = cur->right;
       else cur = cur->left;
   }
   btNode* temp = new btNode();
   temp->data = insInt;
   temp->left = 0;
   temp->right = 0;
   if(pre->data < insInt)
   {
       pre->right = temp;
       return;
   }
   else
   {
       pre->left = temp;
       return;
   }
}

bool bst_remove(btNode*& bst_root, int remInt)
{
  if(!bst_root) return false;
  if(remInt < bst_root->data) {
       return bst_remove(bst_root->left, remInt);
   }
  if(remInt > bst_root->data) {
       return bst_remove(bst_root->right, remInt);
   }
  else if(remInt == bst_root->data)
  {
     if(!bst_root->left && !bst_root->right)
     {
        delete bst_root;
        bst_root = 0;
        return true;
     }
     else if(bst_root->left && !bst_root->right)
     {
        btNode* temp = bst_root;
        bst_root = bst_root->left;
        delete temp;
        return true;
     }
     else if(!bst_root->left && bst_root->right)
     {
        btNode* temp = bst_root;
        bst_root = bst_root->right;
        delete temp;
        return true;
     }
     else if(bst_root->left && bst_root->right)
     {
        bst_remove_max(bst_root->left, bst_root->data);
        return true;
     }
  }
   return false;
}

void bst_remove_max(btNode*& bst_root, int& removed)
{
  if(!bst_root) return;
  else if(!bst_root->right)
  {
     removed = bst_root->data;
       btNode* temp = bst_root;
       bst_root = bst_root->left;
     delete temp;
  }
  else
     bst_remove_max(bst_root->right, removed);
}




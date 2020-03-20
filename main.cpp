#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};

class Solution {
public:
    int count = 0;
    TreeNode* KthNode(TreeNode* pRoot, int k) {
        if (pRoot == nullptr || k <= 0) {
            return nullptr;
        }

        {
            if (pRoot->left)
            {
                TreeNode *left = KthNode(pRoot->left, k);
                if (left) {
                    return left;
                }
            }

            ++count;
            if (count == k) {
                return pRoot;
            }
            if (pRoot->right)
            {
                TreeNode *right = KthNode(pRoot->right, k);
                if (right) {
                    return right;
                }
            }
        }
        return nullptr;
    }
};
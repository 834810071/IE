#include <thread>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode
{
    TreeNode(int a)
    {
        val = a;
        left = nullptr;
        right = nullptr;
    }
    TreeNode* left;
    TreeNode* right;
    int val;
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
       vector<vector<int>> res;
       if (root == nullptr)
       {
           return res;
       }

       TreeNode* cur = root;
       TreeNode* next = root;
       vector<int> v;
       queue<TreeNode*> q;
       q.push(cur);
       while (!q.empty())
       {
           if (cur == next)
           {
               res.push_back(v);
               v.clear();
               next = q.back();
           }

           if (cur->left)
           {
               q.push(cur->left);
           }
           if (cur->right)
           {
               q.push(cur->right);
           }
           cur = q.front();
           v.push_back(cur->val);
           q.pop();
       }
       return res;
    }
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == nullptr)
        {
            return res;
        }

        TreeNode* cur = root;
        queue<TreeNode*> q;
        q.push(t);
        vector<int> v;
        while (!q.empty())
        {
            TreeNode* tmp = q.front(); q.pop();
            v.push_back(tmp->val);
            if (tmp->left)
            {
                q.push(tmp->left);
            }
            if (tmp->right)
            {
                q.push(tmp->right);
            }

            if (tmp == cur)
            {
                cur = q.back();
                res.push_back(v);
                v.clear();
            }
        }
        return res;
    }
};    TreeNode* t = root;


int main()
{
    vector<int> arr = {-2,  1, -3, 4, -1, 2, 1, -5, 4};
    Solution s;
    cout << s.maxsum(arr);

}

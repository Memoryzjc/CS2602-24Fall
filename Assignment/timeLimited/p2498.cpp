#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* buildTree(vector<int>& nums) {
        if (nums.empty()) return nullptr;
        
        vector<TreeNode*> nodes;
        for (int num : nums) {
            nodes.push_back(new TreeNode(num));
        }
        
        int n = nodes.size();
        for (int i = 0; i < n/2; i++) {
            if (2*i + 1 < n) nodes[i]->left = nodes[2*i + 1];
            if (2*i + 2 < n) nodes[i]->right = nodes[2*i + 2];
        }
        
        return nodes[0];
    }
    
    TreeNode* findNode(TreeNode* root, int target) {
        if (!root || root->val == target) return root;
        
        TreeNode* left = findNode(root->left, target);
        if (left) return left;
        
        return findNode(root->right, target);
    }
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root;
        
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        
        if (left && right) return root;
        return left ? left : right;
    }
    
    int getDistance(TreeNode* root, TreeNode* target) {
        if (!root) return -1;
        if (root == target) return 0;
        
        int leftDist = getDistance(root->left, target);
        if (leftDist >= 0) return leftDist + 1;
        
        int rightDist = getDistance(root->right, target);
        if (rightDist >= 0) return rightDist + 1;
        
        return -1;
    }
    
    int getNodeDistance(TreeNode* root, int a, int b) {
        TreeNode* nodeA = findNode(root, a);
        TreeNode* nodeB = findNode(root, b);
        TreeNode* lca = lowestCommonAncestor(root, nodeA, nodeB);
        
        int distA = getDistance(lca, nodeA);
        int distB = getDistance(lca, nodeB);
        
        return distA + distB;
    }
};

int main() {
    int n;
    cin >> n;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    int a, b;
    cin >> a >> b;
    
    Solution solution;
    TreeNode* root = solution.buildTree(nums);
    cout << solution.getNodeDistance(root, a, b) << endl;
    
    return 0;
}
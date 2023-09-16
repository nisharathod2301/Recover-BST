#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <climits>
using namespace std;

struct treenode {
    int val;
    treenode* left;
    treenode* right;
    treenode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<string> values;

treenode* buildtree(string input) {
    istringstream iss(input);
    string words;
    while (getline(iss, words, ' ')) {
        if (words == "null") {
            values.push_back("-1");
        } else {
            values.push_back(words);
        }
    }

    int n = values.size();
    if (n == 0 || values[0] == "-1") {
        return nullptr;
    }

    queue<treenode*> q;
    treenode* root = new treenode(stoi(values[0]));
    q.push(root);

    int idx = 1;
    while (!q.empty() && idx < n) {
        treenode* curr = q.front();
        q.pop();
        string leftele = values[idx++];
        if (!(leftele == "-1")) {
            curr->left = new treenode(stoi(leftele));
            q.push(curr->left);
        }
        if (idx < n) {
            string rightele = values[idx++];
            if (!(rightele == "-1")) {
                curr->right = new treenode(stoi(rightele));
                q.push(curr->right);
            }
        }
    }
    return root;
}

void printLevelOrder(struct treenode* root) {
    if (root == nullptr) return;

    queue<treenode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++) {
            treenode* node = q.front();
            q.pop();
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
            cout << node->val << " ";
        }
        // cout << endl; // Print a new line for the next level
    }
}

void recoverTree(treenode* root) {
    treenode *first,*mid,*last,*prev;
    first=mid=last=nullptr;
    prev=new treenode(INT_MIN);
    treenode *curr=root;
    while(curr){
    if(!curr->left){ 
        if(curr->val<prev->val){
            if(!first){
                first=prev;
                mid=curr;
            }
            else last=curr;
        }
        prev=curr;
        curr=curr->right;
    }
    else{
        treenode *now=curr->left;
        while(now->right && now->right!=curr)
            now=now->right;
        if(!now->right){
            now->right=curr;
            curr=curr->left;
        }
        else{
            now->right=nullptr;
            if(curr->val<prev->val){
                if(!first){
                    first=prev;
                    mid=curr;
                }
                else last=curr;
            }
            prev=curr;
            curr=curr->right;
        }
    }
}
if(!last) swap(first->val,mid->val); // Case-2
else swap(first->val,last->val); // Case-1
}

int main() {
    cout << "Enter values: ";
    string input;
    getline(cin, input);
    treenode* root = buildtree(input);
    recoverTree(root);
    printLevelOrder(root);
    return 0;
}

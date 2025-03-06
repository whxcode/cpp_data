#include "../include/mk-hash.hpp"

#include <queue>
#include <stack>

static void levelEach(const TreeNode* root) {
    std::queue<const TreeNode*> queue;

    queue.push(root);

    while (!queue.empty()) {
        const auto& value = queue.front();
        queue.pop();
        printf("[%d] ", value->fValue);

        if (value->fLeft) {
            queue.push(value->fLeft);
        }

        if (value->fRight) {
            queue.push(value->fRight);
        }
    }

    printf("\n");
}

static void levelEach_v1(const TreeNode* root) {
    std::stack<const TreeNode*> queue;

    queue.push(root);

    while (!queue.empty()) {
        const auto value = queue.top();
        queue.pop();

        printf("[%d] ", value->fValue);
        if (value->fRight) {
            queue.push(value->fRight);
        }

        if (value->fLeft != nullptr) {
            queue.push(value->fLeft);
        }
    }

    printf("\n");
}

static void levelEach_v2(const TreeNode* root) {
    std::vector<int> result;
    std::stack<const TreeNode*> stack;
    const TreeNode* current = root;

    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->fLeft;
        }

        current = stack.top();
        stack.pop();
        printf("[%d] ", current->fValue);
        current = current->fRight;
    }

    printf("\n");
}

//
static void levelEach_v3(const TreeNode* root) {
    std::vector<int> result;
    std::stack<const TreeNode*> stack;
    stack.push(root);

    while (!stack.empty()) {
        auto current = stack.top();
        stack.pop();
        result.push_back(current->fValue);

        if (current->fLeft != nullptr) {
            stack.push(current->fLeft);
        }

        if (current->fRight != nullptr) {
            stack.push(current->fRight);
        }
    }
    for (auto i = result.rbegin(); i != result.rend(); ++i) {
        printf("[%d] ", *i);
    }

    printf("\n");
}

void testHash() {
    /*
      MkHash hash(22);
      hash.insert(12, 100);
      hash.insert(122, 200);

      printf("hash.get(12).fKey[%d]:[%d]\n", hash.get(12).fKey, hash.get(12).fValue);
      printf("hash.get(122).fKey[%d][%d]\n", hash.get(122).fKey, hash.get(122).fValue);

    MkHash_v1<std::string> hash(22);
    hash[12] = "whx";
    std::cout << hash[12] << std::endl;

    hash[22] = "xhw";
    hash[12] = "fog";

    std::cout << hash[12] << std::endl;
    std::cout << hash[22] << std::endl;

    hash.erase(12);

    std::cout << hash[12] << std::endl;

    */
    TreeNode* n0 = new TreeNode(1);
    TreeNode* n1 = new TreeNode(2);

    TreeNode* n2 = new TreeNode(3);
    TreeNode* n3 = new TreeNode(4);
    TreeNode* n4 = new TreeNode(5);

    TreeNode* n5 = new TreeNode(6);
    TreeNode* n6 = new TreeNode(7);

    n0->fLeft = n1;
    n0->fRight = n2;

    n1->fLeft = n3;
    n1->fRight = n4;

    n2->fLeft = n5;
    n2->fRight = n6;

    /*
      levelEach(n0);
      levelEach_v1(n0);
      levelEach_v2(n0);
    */
    levelEach_v3(n0);
    // levelEach(n0);
}

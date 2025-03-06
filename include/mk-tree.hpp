#pragma once
#include <concepts>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>

void testTree();

template <typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
    { a == b } -> std::convertible_to<bool>;
};

template <Comparable T>
struct MkTreeNode {
    MkTreeNode(const T &v) : fData(v) {}

    T fData;
    MkTreeNode<T> *fLeft{nullptr};
    MkTreeNode<T> *fRight{nullptr};
};

template <Comparable T>
class MkBinSearchTree {
public:
    using Call = std::function<void(const T &v)>;

public:
    void levelEach(const Call &call) {
        std::queue<MkTreeNode<T> *> q;
        q.push(fRoot);

        while (!q.empty()) {
            auto top = q.front();
            call(top->fData);
            q.pop();
            if (top->fLeft) {
                q.push(top->fLeft);
            }
            if (top->fRight) {
                q.push(top->fRight);
            }
        }
    }
    // 打印树形结构
    void printTree() const {
        if (fRoot == nullptr) {
            std::cout << "Tree is empty!" << std::endl;
            return;
        }
        printTreeRecursive(fRoot, 0);
    }

    void inOrderTraversal(const Call &call) const { this->inOrderTraversal(fRoot, call); }

    void add(const T &v) { fRoot = insert(fRoot, v); }
    void push(const T &v) {
        if (fRoot == nullptr) {
            fRoot = new MkTreeNode<T>(v);
            return;
        }

        auto cur = fRoot;
        MkTreeNode<T> *pre = nullptr;

        while (cur) {
            pre = cur;

            if (v == cur->fData) {
                return;
            } else if (v < cur->fData) {
                cur = cur->fLeft;
            } else if (v > cur->fData) {
                cur = cur->fRight;
            }
        }

        if (v < pre->fData) {
            pre->fLeft = new MkTreeNode<T>(v);
        }

        if (v > pre->fData) {
            pre->fRight = new MkTreeNode<T>(v);
        }
    }

    const MkTreeNode<T> *find(const T &v) const {
        auto temp = fRoot;

        while (temp != nullptr) {
            if (v < temp->fData) {
                temp = temp->fLeft;
            } else if (v > temp->fData) {
                temp = temp->fRight;
            } else {
                return temp;
            }
        }

        return nullptr;
    }

    size_t height() { return height(fRoot); }

    size_t heightV2() {
        if (fRoot == nullptr) {
            return 0;
        }

        std::queue<MkTreeNode<T> *> queue;
        queue.push(fRoot);
        size_t level = 0;
        queue.push(fRoot);

        while (!queue.empty()) {
            ++level;
            const auto size = queue.size();

            for (size_t i = 0; i < size; ++i) {
                auto top = queue.front();
                queue.pop();

                if (top->fLeft) {
                    queue.push(top->fLeft);
                }
                if (top->fRight) {
                    queue.push(top->fRight);
                }
            }
        }

        return level;
    }

private:
    MkTreeNode<T> *insert(MkTreeNode<T> *node, const T &v) {
        if (node == nullptr) {
            return new MkTreeNode<T>(v);
        }

        if (v < node->fData) {
            node->fLeft = this->insert(node->fLeft, v);
        } else if (v > node->fData) {
            node->fRight = this->insert(node->fRight, v);
        }

        return node;
    }

    void inOrderTraversal(MkTreeNode<T> *node, const Call &call) const {
        if (node == nullptr) return;

        inOrderTraversal(node->fLeft, call);
        call(node->fData);
        inOrderTraversal(node->fRight, call);
    }

    // 递归打印树形结构
    void printTreeRecursive(MkTreeNode<T> *node, int space) const {
        const int COUNT = 4;  // 控制节点之间的空格数
        if (node == nullptr) return;

        space += COUNT;

        // 打印当前节点
        std::cout << std::endl;
        for (int i = COUNT; i < space; i++) {
            std::cout << " ";
        }
        std::cout << node->fData << std::endl;

        // 打印右子树
        printTreeRecursive(node->fRight, space);

        // 打印左子树
        printTreeRecursive(node->fLeft, space);
    }

    size_t height(const MkTreeNode<T> *node) {
        if (node == nullptr) {
            return 0;
        }

        auto left = height(node->fLeft);
        auto right = height(node->fRight);

        return std::max(left, right) + 1;
    }

private:
    MkTreeNode<T> *fRoot{nullptr};
};

template <typename T, typename Compare = std::less<T>>
class MkPileUp {
public:
    size_t getLeftIndex(const size_t i) { return i * 2 + 1; }
    size_t getRightIndex(const size_t i) { return i * 2 + 2; }
    int getParentIndex(const size_t i) { return i == 0 ? -1 : (i - 1) / 2; }

    const T &top() { return fData.front(); }

    void push(const T &v) {
        fData.push_back(v);

        shiftUp(fData.size() - 1);
    }

    bool empty() { return fData.empty(); }

    void pop() {
        if (fData.size() == 0) {
            return;
        }

        swap(0, fData.size() - 1);
        fData.pop_back();
        shiftDown(0);
    }

private:
    void swap(const size_t i, const size_t j) {
        auto temp = fData[i];
        fData[i] = fData[j];
        fData[j] = temp;
    }

    void shiftUp(const size_t i) {
        size_t index = i;

        while (true) {
            const auto &v = fData[index];
            const auto &p = getParentIndex(index);

            if (p < 0 || !fComp(fData[index], fData[p])) {
                return;
            }

            swap(index, p);
            index = p;
        }
    }

    void shiftDown(const size_t i) {
        size_t index = i;

        while (true) {
            auto leftIndex = getLeftIndex(index);
            auto rightIndex = getRightIndex(index);
            auto maxIndex = index;

            if (leftIndex < fData.size() && fComp(fData[leftIndex], fData[maxIndex])) {
                maxIndex = leftIndex;
            }
            if (rightIndex < fData.size() && fComp(fData[rightIndex], fData[maxIndex])) {
                maxIndex = rightIndex;
            }

            if (maxIndex == index) {
                break;
            }

            swap(index, maxIndex);
        }
    }

private:
    std::vector<T> fData;
    Compare fComp;  // 比较器，用于决定是大顶堆还是小顶堆
};

#pragma once
#include <cstring>
#include <functional>
#include <iostream>

class MkHash {
public:
    struct Bucket {
        int fValue{0};
        int fKey{0};
    };

public:
    MkHash(const size_t cap) : fCap(cap) { fBuckets = std::vector<Bucket*>(cap); }

    const int hash(const int key) const { return key % fCap; }

    void insert(const int key, const int value) {
        const auto& index = this->hash(key);
        if (fBuckets[index] != nullptr) {
            printf("hash 冲突\n");
            return;
        }

        auto bucket = new Bucket;
        bucket->fKey = key;
        bucket->fValue = value;
        fBuckets[index] = bucket;
    }

    const Bucket& get(const int key) { return *fBuckets[this->hash(key)]; }

private:
    std::vector<Bucket*> fBuckets;
    size_t fCap{0};
};

template <class T>
class MkHash_v1 {
public:
    struct Bucket {
        T fValue{0};
        int fKey{0};
    };

public:
    MkHash_v1(const size_t cap) : fCap(cap) { fBuckets.resize(cap); }
    const int hash(const int key) const { return key % fCap; }

    ~MkHash_v1() {
        for (const auto& bucket : fBuckets) {
            for (const auto& item : bucket) {
                delete item;
            }
        }
    }

    T& operator[](const int key) {
        const auto& index = this->hash(key);
        auto& buffers = fBuckets[index];

        for (auto& item : buffers) {
            if (item->fKey == key) {
                return item->fValue;
            }
        }

        auto bucket = new Bucket;
        bucket->fKey = key;
        buffers.push_back(bucket);

        ++fSize;

        return bucket->fValue;
    }

    void extend() {
        if ((double)fSize / (double)fCap < 0.75) {
            return;
        }

        fCap *= 2;
        fSize = 0;
        auto temp = fBuckets;
        fBuckets = {};
        fBuckets.resize(fCap);

        for (auto& bucket : temp) {
            for (auto& item : bucket) {
                this[item->fKey] = item->fValue;
                delete item;
            }
        }
    }

    void erase(const int key) {
        const auto& index = this->hash(key);
        auto& buffers = fBuckets[index];

        size_t i = 0;
        for (auto& item : buffers) {
            if (item->fKey == key) {
                buffers.erase(buffers.begin() + i);
                delete item;
                break;
            }
            i++;
        }
    }

private:
    std::vector<std::vector<Bucket*>> fBuckets;
    size_t fCap{0};
    size_t fSize;
};

struct TreeNode {
public:
    TreeNode(const int value) : fValue(value) {}
    int fValue{0};
    TreeNode* fLeft{nullptr};
    TreeNode* fRight{nullptr};
};

void testHash();

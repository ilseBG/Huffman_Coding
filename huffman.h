#ifndef _HUFFMAN_TREENODE_
#define _HUFFMAN_TREENODE_


#include<string>
#include<queue>
#include<map>
#include<vector>
#include<iostream>
#include <iomanip>
#include <fstream>

struct HuffmanNode{
    char    ch;
    int     freq;
    HuffmanNode *left, *right;

    HuffmanNode();
    HuffmanNode(char character, int freqency);
    HuffmanNode(char character, int freqency, HuffmanNode* lchild, HuffmanNode* rchild);
};

struct CompareNode {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq; // 频率小的优先
    }
};

class HuffmanTree {
private:
    HuffmanNode* root;
    std::map<char, std::string> codes;
    std::map<char, int> frequencies;
    void generateCodes(HuffmanNode* node, const std::string& code);
    void deleteTree(HuffmanNode* node);
    void rebuildHFtree();

public:
    HuffmanTree(const std::map<char, int>& freqmap);
    HuffmanTree(const std::map<char, std::string>& codesmap);
    ~HuffmanTree();
    void buildTree();
    std::string getCode(char ch);
    void printTree();

    
    
    friend class huffmanEncoder;
    friend class huffmanDecoder;
    friend void testRebuildHFtree();
};

#endif 
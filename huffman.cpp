#include "huffman.h"


HuffmanNode::HuffmanNode(): ch('\0'), freq(0), left(nullptr), right(nullptr) {}

HuffmanNode::HuffmanNode(char character, int freqency): ch(character), freq(freqency), left(nullptr), right(nullptr)  {}

HuffmanNode::HuffmanNode(char character, int freqency, HuffmanNode* lchild, HuffmanNode* rchild) : ch(character), freq(freqency), left(lchild), right(rchild) {}

void HuffmanTree::generateCodes(HuffmanNode* node, const std::string& code) {
    if(!node) return;
    if(!node->left && !node->right) {
        codes[node->ch] = code;
        return;
    }
    generateCodes(node->left , code + '0');
    generateCodes(node->right, code + '1');
}

void HuffmanTree::deleteTree(HuffmanNode* node) {
    if(node == nullptr) return;
    if(node->left) deleteTree(node->left);
    if(node->right) deleteTree(node->right);
    delete node;
}

HuffmanTree::HuffmanTree(const std::map<char, int>& freqmap) {
    frequencies = freqmap;
    buildTree();
    generateCodes(root, "\0");
}

HuffmanTree::HuffmanTree(const std::map<char, std::string>& codesmap): codes(codesmap) {
    rebuildHFtree();
}

HuffmanTree::~HuffmanTree() {
    deleteTree(root);
}

void HuffmanTree::buildTree() {
    // build min heap from `frequencies` map
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNode> pq;
    for(auto &[ch, freq] : frequencies) {
        HuffmanNode* node = new HuffmanNode(ch, freq);
        pq.emplace(node);
    }
    // build huffman tree from min heap
    while(pq.size() >= 2) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* node = new HuffmanNode('\0', left->freq + right->freq, left, right);

        pq.emplace(node);
    }
    
    root = pq.top();
}

void HuffmanTree::rebuildHFtree(){
    root = new HuffmanNode();
    for(auto & code : codes) {
        HuffmanNode* currentNode = root;
        for(char &bit : code.second) {
            if(bit == '0') {
                if(!currentNode->left)
                    currentNode->left = new HuffmanNode();
                currentNode = currentNode->left;
            } else if(bit == '1') {
                if(!currentNode->right)
                    currentNode->right = new HuffmanNode();
                currentNode = currentNode->right;
            }
        }
        currentNode->ch = code.first;
    }
}

std::string HuffmanTree::getCode(char ch) {
    if(codes.count(ch))
        return codes[ch];
    return "";
}

void HuffmanTree::printTree() {
    if (!root) return;
    if(frequencies.size() == codes.size()) {
        for(auto &[ch, code] : codes) {
            std::cout << "[" << ch << ", " << frequencies[ch] << ", code: " << code << "]" << std::endl; 
        }
    } else {
        for(auto &[ch, code] : codes) {
            std::cout << "[" << ch  << ", code: " << code << "]" << std::endl; 
        }
    }
}
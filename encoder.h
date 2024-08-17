#ifndef _HUFFMAN_H_ENCODER_
#define _HUFFMAN_H_ENCODER_

#include"huffman.h"
#include <bitset>

class huffmanEncoder{
private:
    std::fstream* in_file;
    std::fstream* out_file;
    HuffmanTree* HF_tree;

    void createHFtree();

public:
    huffmanEncoder()=delete;
    huffmanEncoder(HuffmanTree* tree);
    huffmanEncoder(std::fstream* in_file, std::fstream* out_file);
    ~huffmanEncoder();
    void printHFtree();
    void encodeToFile(const std::string& codeFileName);
    inline HuffmanTree* getHFtree() { return HF_tree;}

};

#endif
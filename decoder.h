#ifndef _HUFFMAN_H_DECODER_
#define _HUFFMAN_H_DECODER_

#include"huffman.h"
class huffmanDecoder{
private:
    std::fstream* code_file;      // codefile: end with .hdr
    HuffmanTree* HF_tree;
    HuffmanTree* getCodesFromFile();
public:
    huffmanDecoder()=delete;
    huffmanDecoder(const std::string codefilename);
    huffmanDecoder(std::fstream* codefile);
    huffmanDecoder(std::map<char, std::string> codes);
    ~huffmanDecoder();
    HuffmanTree* setCodeFile(const std::string codefilename);
    bool decodeFromFile(std::fstream* infile, std::fstream* outfile);
    bool decodeFromFile(std::string infile, std::string outfile);
    void printTree(std::string str);
};

#endif
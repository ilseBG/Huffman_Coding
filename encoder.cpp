#include"encoder.h"

huffmanEncoder::huffmanEncoder(HuffmanTree* tree): HF_tree(tree), in_file(nullptr), out_file(nullptr) {}

huffmanEncoder::huffmanEncoder(std::fstream* in_file, std::fstream* out_file): in_file(in_file), out_file(out_file), HF_tree(nullptr) {
    createHFtree();
}

huffmanEncoder::~huffmanEncoder() {
    delete HF_tree;
}

void huffmanEncoder::createHFtree() {

    std::map<char, int> freqMap;
    char ch;

    // 确保文件是打开的
    if (in_file->is_open()) {
        while (in_file->get(ch)) {
            freqMap[ch]++;
        }
    }

    HF_tree = new HuffmanTree(freqMap);
}

void huffmanEncoder::printHFtree() {
    if (HF_tree) {
        HF_tree->printTree();
    } else {
        std::cout << "Huffman Tree is not created yet." << std::endl;
    }
}

void huffmanEncoder::encodeToFile(const std::string& codeFileName) {
    if (!in_file || !out_file || !HF_tree) return;
    
    std::ofstream codeFile(codeFileName, std::ios::out);
    if (!codeFile.is_open()) {
        std::cerr << "Could not open the code file!" << std::endl;
        return;
    }

    // 保存编码表到单独的文件
    for (const auto& pair : HF_tree->codes) {
        codeFile << '[' << pair.first << ',' << pair.second << "]";
    }
    codeFile.close();

    char ch;

    // reset the positon of reading out_file
    in_file->clear();
    in_file->seekg(0, std::ios::beg);

    // encode the in_file
    unsigned char buffer = 0;  // 8-bit buffer to hold bits
    int bitCount = 0;          // To track the number of bits in the buffer
    int charCount = 0;
    int totalbitcnt = 0;
    std::string encodedContent;
    while (in_file->get(ch)) {
        auto code = HF_tree->getCode(ch);
        charCount+=1;
        encodedContent += code;
        for(char & bi : code) {
            buffer = (buffer << 1) | (bi - '0');
            totalbitcnt++;
            if(++bitCount == 8) {
                // std::bitset<8> bits(buffer);
                // std::cout << bits;
                out_file->put(buffer);
                bitCount = 0;
                buffer = 0;
            }
        }
    }
    std::fstream stringverion("output.txt", std::ios::out);
    stringverion << encodedContent;
    stringverion.close();
    
    // If there are remaining bits in the buffer, pad with zeros and write
    if (bitCount > 0) {
        buffer <<= (8 - bitCount);  // Shift left to pad with zeros
        out_file->put(buffer);
        totalbitcnt += bitCount;
    }
    std::cout << "write " << charCount << "characters, total bit cnt : " << totalbitcnt <<  std::endl;
    out_file->flush();  // Ensure all data is written
    out_file->close();
}
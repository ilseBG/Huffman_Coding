#include"decoder.h"

huffmanDecoder::huffmanDecoder(const std::string codefilename) {
    HF_tree =  setCodeFile(codefilename);
}

huffmanDecoder::huffmanDecoder(std::fstream* codefile): code_file(codefile) {
    HF_tree = getCodesFromFile();
}

huffmanDecoder::huffmanDecoder(std::map<char, std::string> codes) {
    HF_tree = new HuffmanTree(codes);
}

//修改 => 用智能指针
huffmanDecoder::~huffmanDecoder(){
    if(code_file) code_file->close();
    delete code_file;
    delete HF_tree;
}

HuffmanTree* huffmanDecoder::getCodesFromFile(){
    if(code_file == nullptr)
        return nullptr;
    if (!code_file->is_open()) {
        std::cerr << "Could not open the code file!" << std::endl;
        return nullptr;
    }
    std::map<char, std::string> codes;
    char ch;
    std::string code;

    while (*code_file >> ch) {
        if (ch == '[') {
            code_file->get(ch); // 读取字符
            code_file->ignore(1, ','); // 跳过逗号
            std::getline(*code_file, code, ']'); // 读取编码直到 ']'
            codes[ch] = code; // 存储到映射表中
        }
    }
    code_file->close();
    HF_tree = new HuffmanTree(codes);
    return HF_tree;
}

HuffmanTree* huffmanDecoder::setCodeFile(const std::string codefilename) {
    code_file = new std::fstream(codefilename, std::ios::in);
    return getCodesFromFile();
}


bool huffmanDecoder::decodeFromFile(std::fstream* infile, std::fstream* outfile) {
    if(!HF_tree || !infile || !outfile) return false;
    
    // 获取文件的总字节数
    infile->seekg(0, std::ios::end);
    std::streampos totalBytes = infile->tellg();
    infile->seekg(0, std::ios::beg);  // 移回文件开头

    if (!infile->is_open()) {
        std::cerr << "Could not open the infile!" << std::endl;
        return false;
    }

    int charCount = 0;
    char buffer;
    int totalbitcnt = 0;
    HuffmanNode* currentnode = HF_tree->root;
    while(infile->get(buffer)) {
        // 获取当前字节位置
        std::streampos currentPos = infile->tellg();
        // 计算当前读取进度百分比
        double progress = (static_cast<double>(currentPos) / totalBytes) * 100.0;
        totalbitcnt += 8;
        for(int i = 7; i >= 0; --i) {
            bool bit = buffer & (1 << i);
            if(bit) {
                currentnode = currentnode->right;
            } else {
                currentnode = currentnode->left;
            }
            if(!currentnode->left && !currentnode->right) {
                outfile->put(currentnode->ch);
                ++charCount;
                currentnode = HF_tree->root;
            }
        }
    }
    std::cout << "\ndecoder " << charCount << " characters totally" << totalbitcnt << std::endl;
    return true;
}

bool huffmanDecoder::decodeFromFile(std::string infile, std::string outfile){
    std::fstream in_file(infile, std::ios::binary | std::ios::in);
    std::fstream out_file(outfile, std::ios::out);
    return decodeFromFile(&in_file, &out_file);
}

void huffmanDecoder::printTree(std::string str) {
    std::cout << str << std::endl;
    HF_tree->printTree();
}
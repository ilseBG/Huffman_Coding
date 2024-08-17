#include"encoder.h"
#include"decoder.h"
#include<map>

void testRebuildHFtree(){
    std::map<char, int> freqmap;

    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' }; 
    int freq[] = { 5, 9, 12, 13, 16, 45 }; 

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
        freqmap[arr[i]] = freq[i];
    }

    HuffmanTree* HFtree = new HuffmanTree(freqmap);
    huffmanEncoder encoder(HFtree);
    encoder.printHFtree();
    huffmanDecoder* decoder = new huffmanDecoder(HFtree->codes);
    decoder->printTree("\n[After Decoding]\n");
}

void testEncodeFile() {
    std::string codefilename = "output.hdr";
    std::fstream inputFile("OriginalFile.txt", std::ios::in);
    std::fstream outputFile("output.huf", std::ios::binary | std::ios::out);
    std::fstream codefile(codefilename, std::ios::out);

    std::fstream* infile = &inputFile;
    std::fstream* outfile = &outputFile;
    std::fstream* codefile_ptr = &codefile;

    huffmanEncoder encoder(infile, outfile);

    encoder.printHFtree();
    encoder.encodeToFile(codefilename);
}

void testDecodeFile() {
    testEncodeFile();
    huffmanDecoder decoder("output.hdr");
    decoder.printTree("After Decoder:");
    decoder.decodeFromFile("output.huf", "decoded_text.txt");
}

int main(){
    // testEncodeFile();
    testDecodeFile();
    return 0;
}
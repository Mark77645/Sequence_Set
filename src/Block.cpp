//
// Created by marks on 12/26/2021.
//
#include "fstream"
#include "Block.h"
#include <iostream>

using namespace std;
static int noofrecords;
static int noofblocks;
int Block::getKey() const {
    return key;
}

void Block::setKey(int key) {
    Block::key = key;
}

int Block::getValue() const {
    return value;
}

void Block::setValue(int value) {
    Block::value = value;
}

int *Block::getValues() const {
    return values;
}

void Block::setValues(int *values) {
    Block::values = values;
}

Block::~Block() {
    delete values;
}

Block::Block(int key, int value, int *values) : key(key), value(value), values(values) {
    this->key = key;
    this->value = value;
    this->values = nullptr;
}

bool Block::CreateRecordFile(string filename, int m,
                             int n) { // m is no. of blocks // n is no. of fixed length records in each block
    noofrecords = n;
    noofblocks = m;
    fstream file;
    Block blocks[m];
    blocks[0].setKey(-1); //First non-empty block
    blocks[0].setValue(1); // First empty block
    for (int i = 1; i < m; i++) { // Initializing blocks headers and records inside the blocks
        if (i == m - 1) {
            blocks[i].setValue(-1);
        } else {
            blocks[i].setValue(i + 1);
        }
        blocks[i].values = new int[(n - 1) * 2]; // Because there is one record for the header of the block
    }
    file.open(filename, ios::out);
    if (!file) {
        cout << "Error";
        return false;
    }
    file << to_string(blocks[0].getKey()) << to_string(blocks[0].getValue());
    for (int i = 1; i < m; i++) {
        file << to_string(blocks[i].getKey()) << to_string(blocks[i].getValue());
        for (int j = 0; j < (n - 1) * 2; j++) {
            file << to_string(blocks[i].values[j] = 0);
        }
    }
    file.close();
    return true;
}

int Block::InsertVal(string cIndexFile, int iToken, int iKey) {

    return 0;
}

int Block::GetKey(string cIndexFile, int iBlock, int iRecord) {
    fstream file;
    char s;
    int key = 0;
    int negative = Block::NumberOfNegativeSign(cIndexFile, iBlock);
    file.open(cIndexFile, ios::in);
    if (iBlock == 1) {
        file.seekg(negative + iRecord * 2, ios::beg);
    } else {
        int temp = 2 + (4 * 2); //size for 1 block // "4" is the number of records
        file.seekg((2 + temp * (iBlock - 1) + (2 + 2 * (iRecord - 1)) + negative), ios::beg);
    }
    file >> s;
    if (s == '0') {
        cout << "Empty record\n";
        return -1;
    } else {
        key = s - '0';
    }
    file.close();
    return key;
}

int Block::GetBlockIndex(string cIndexFile, int iToken) { //itoken = ikey
    fstream file;
    file.open(cIndexFile, ios::in);
    char s;
    int key = 0;
    int negative =0;
    int temp=0;
    for(int i=1;i<4;i++){ //"4" must be replaced with number of blocks.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        negative = Block::NumberOfNegativeSign(cIndexFile, i);
        file.seekg(negative+i+2+temp,ios::beg);
        file>>s;
        key=s-'0';
        temp+=1+4*2;
        if (key>=iToken){
            return i;
        }
    }cout<<"Not found";
    return -1;
}

int Block::GetRecordIndex(string cIndexFile, int iToken) {
    fstream file;
    file.open(cIndexFile, ios::in);
    char s;
    int key = 0;
    int negative =0;
    int temp=0;
    int blockIndex;
    for(int i=1;i<4;i++){ //"4" must be replaced with number of blocks.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        negative = Block::NumberOfNegativeSign(cIndexFile, i);
        file.seekg(negative+i+2+temp,ios::beg);
        file>>s;
        key=s-'0';
        temp+=1+4*2; //"4" must be replaced!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (key>=iToken){
            blockIndex= i;
            break;
        }
    }
    negative = Block::NumberOfNegativeSign(cIndexFile, blockIndex);
    temp=temp-blockIndex;
    int flag=0;
    for (int i = 1; i <= 8; i+=2) { //"8" must be replaced!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        file.seekg(negative+temp+(i-1),ios::beg);
        file>>s;
        key=s-'0';
        if (key==iToken){
            return i-flag;
        }
        flag++;
    }
    cout<<"Not found\n";
    return -1;
}

void Block::DeleteKey(string cIndexFile, int iToken) {

}

int Block::FirstEmptyBlock(string cIndexFile) {
    fstream file;
    file.open(cIndexFile, ios::in);
    char x;
    int negative = Block::NumberOfNegativeSign(cIndexFile, 0);
    if (negative==0){
        file.seekg(1, ios::beg);
    }else if (negative==1){
        file.seekg(2, ios::beg);
    }
    file>>x;
    int v = x - '0';
    return v;
}

int Block::GetVal(string cIndexFile, int iBlock, int iRecord) {
    fstream file;
    char s;
    int val = 0;
    int negative = Block::NumberOfNegativeSign(cIndexFile, iBlock);
    file.open(cIndexFile, ios::in);
    if (iBlock == 1) {
        file.seekg(negative + iRecord * 2, ios::beg);
    } else {
        int temp = 2 + (4 * 2); //size for 1 block // "4" is the number of records
        file.seekg((2 + temp * (iBlock - 1) + (2 + 2 * (iRecord - 1)) + negative + 1), ios::beg);
    }
    file >> s;
    if (s == '0') {
        cout << "Empty record\n";
        return -1;
    } else {
        val = s - '0';
    }
    file.close();
    return val;
}

Block::Block() {
    this->value = -1;
    this->key = -1;
    this->values = nullptr;
}

int Block::NumberOfNegativeSign(string filename, int blocknumber) {
    fstream file;
    file.open(filename, ios::in);
    char x;
    int number = 0;
    int byteOffset = 0;
    if (blocknumber == 0) {
        byteOffset = 2;
    } else {
        byteOffset = 3+ 2/*noofblocks*/ + (4 * 2) * blocknumber; // "4" is the number of records. //"2" must be replaced!!!!!
    }
    for (int i = 0; i < byteOffset; i++) {
        file >> x;
        if (x == '-') {
            number++;
            file.seekg(i + 1, ios::beg);
        } else {
            file.seekg(i + 1, ios::beg);
        }
    }

    file.close();
    return number;
}

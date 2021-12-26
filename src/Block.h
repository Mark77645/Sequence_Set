//
// Created by marks on 12/26/2021.
//

#ifndef SEQUENCE_SET_BLOCK_H
#define SEQUENCE_SET_BLOCK_H
using namespace std;
class Block {
private:
    int key;
    int value;
    int *values;
public:
    Block(int key, int value, int *values);

    Block();

    virtual ~Block();

    int *getValues() const;

    void setValues(int *values);

    int getKey() const;

    void setKey(int key);

    int getValue() const;

    void setValue(int value);

    // for all the prototypes the Records set is stored in a file called cIndexFile
    bool CreateRecordFile(string cIndexFile, int m,
                          int n); // returns true if success and false if failure. m is the number of blocks in the file and n is the number of records in a block
    int InsertVal(string filename, int iToken,
                  int iKey); // returns index of block in which iToken and iKey were stored and -1 if failed, where iKey is the key of the record, and iToken = iVal in the record.
    int GetKey(string cIndexFile, int iBlock,
               int iRecord); // get value iKey stored in a given block iBlock and given record iRecord – returns -1 if record on block is empty
    int GetVal(string cIndexFile, int iBlock,
               int iRecord); // get value iVal stored in a given block iBlock and given record iRecord – returns -1 if record on block is empty
    int GetBlockIndex(string cIndexFile,
                      int iToken); // get index of block containing iKey = iToken and -1 if record does not exist
    int GetRecordIndex(string cIndexFile,
                       int iToken); // get index of record containing iKey = iToken and -1 if record does not exist
    void DeleteKey(string cIndexFile, int iToken); // delete record containing value iKey = iToken

    int FirstEmptyBlock(string cIndexFile); // return the index of the first empty block.

    int NumberOfNegativeSign(string filename,int blocknumber);
};


#endif //SEQUENCE_SET_BLOCK_H

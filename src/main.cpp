#include <iostream>
#include "Block.h"
using namespace std;
int main(){
    string filename="C:\\Users\\marks\\CLionProjects\\Sequence_Set\\src\\cIndexFile.txt";
    /*int numberOfBlocks;
    int numberOfRecords;
    Block dummy;
    cout<<"Sequence Set, Please enter the number of blocks: \n";
    cin >> numberOfBlocks;
    cout<<"Please enter number of fixed length records: \n";
    cin>>numberOfRecords;
    cout<<"Creating the file first\n";
    dummy.CreateRecordFile(filename,numberOfBlocks,numberOfRecords);
    cout<<"File is created successfully! \n";*/
    Block dummy;
    //dummy.CreateRecordFile(filename,4,5);
    cout<<dummy.GetBlockIndex(filename,9)<<endl;

    cout<<dummy.GetRecordIndex(filename,9);
    return 0;
}
#include <iostream>
#include "Block.h"
using namespace std;
int main(){
    Block dummy;
    string filename="C:\\Users\\marks\\CLionProjects\\Sequence_Set\\src\\cIndexFile.txt";
    //dummy.CreateRecordFile(filename,4,5);
    cout<<dummy.GetBlockIndex(filename,2);

    cout<<dummy.GetRecordIndex(filename,2);
    return 0;
}
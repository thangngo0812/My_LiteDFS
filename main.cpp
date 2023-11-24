#include <iostream>
#include <fcntl.h>
#include "inc/dfs_client.h"

const size_t DFS_INODE_TABLE_SIZE = 1024;
const size_t DFS_CACHE_SIZE = 512;

int main() {
    DFS::instance.listen("10.225.1.98:5001"); // spawn thread accepting connections of DFS nodes
    DFSFile file;
    DFSFileHandle* dfsFile;

    // Open DFS file
    file.open("inodetab.dfs", 0, DFS_INODE_TABLE_SIZE, DFS_CACHE_SIZE, 0);
    dfsFile = new DFSFileHandle();
    dfsFile->assign(file);

    // Write some data
    const char someData_1[] = "Hello Thangnmq. This is liteDFS";
    const char some_data_2[] = "Hello, I* love You";
    size_t blockSize = 4194304;
    size_t data_size_1 = sizeof (someData_1);
    size_t data_size_2 = sizeof (some_data_2);
    off_t pos = 0;      // Set the desired position to read

    // Read data from the file
    char readBuffer[data_size_1];
    BufferedOutput buf(blockSize);
    buf.open(dfsFile);
    buf.write(someData_1, data_size_1);
    buf.write(some_data_2, data_size_2);
    buf.flush(true);

    bool readSuccess = dfsFile->pread(readBuffer, data_size_1, pos, V_NOWAIT);
    if (readSuccess) {
        for (int i = 0; i <= data_size_1; ++i) {
            std::cout << "readBuffer[" << i << "] = " << readBuffer[i] << std::endl;
        }

    } else {
        std::cout << "Failed to read data." << std::endl;
    }

    delete dfsFile;

    // DFS instance will continue listening in the background

    return 0;
}

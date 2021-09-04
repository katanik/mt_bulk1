#include <iostream>

#include "lib/bulk_processor.h"

int main(int argc, char const *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cout<<"Bad format of output data";
            return 0;
        }

        int n = std::stoi(argv[1]);
        if (n < 1)
        {
            std::cout<<"Bad number";
            return 0;
        }

        bulk::BulkProcessor bulkProcessor{n};
        while(bulkProcessor.readNextLine())
        {
            bulkProcessor.processCurrentCmd();
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

#include <iostream>

#include <exception>

#include "lib/bulk_processor.h"

class BadInputException : public std::exception
{
public:
virtual char const * what() const noexcept { return "Bad format of input data."; }
};

int main(int argc, char const *argv[])
{
    try
    {
        if (argc != 2)
            throw BadInputException{};

        int n = std::stoi(argv[1]);
        if (n < 1)
            throw BadInputException{};

        bulk::BulkProcessor bulkProcessor{n};
        bulk::Logger logger{&bulkProcessor};
        bulk::FilePrinter filePrinter{&bulkProcessor};

        while(bulkProcessor.readNextLine())
        {
            bulkProcessor.processCurrentCmd();
        }
    }
    catch(const std::invalid_argument& e)
    {        
        std::cerr << "Conversion of input argument couldn't be performed:" << e.what() << std::endl;
    }
    catch(const BadInputException& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(std::out_of_range& e){
        std::cerr << "The converted input argument value would fall out "
        "of the range of the result type:" << e.what() << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cerr << "Something was wrong:" << e.what() << std::endl;
    }

    return 0;
}

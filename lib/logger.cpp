#include <iostream>
#include <fstream>
#include <sstream>

#include "logger.h"

namespace bulk{

Logger::Logger(IPublisher *publisher)
{
    publisher->subscribe(this);
}

void Logger::run(const bulk::CmdBulk& bulk)
{
    bulk::printCmdBulk(std::cout, bulk);
}

FilePrinter::FilePrinter(IPublisher *publisher)
{
    publisher->subscribe(this);
}

void FilePrinter::run(const bulk::CmdBulk& bulk)
{
    std::ofstream outputFile;
    std::stringstream fileName;
    fileName << "bulk" << bulk.getTimeStamp() << ".log";
    outputFile.open(fileName.str(), std::fstream::out);
    if (!outputFile.is_open())
    {
        std::cout << "failed to create file " << '\n';
        return;
    }
    bulk::printCmdBulk(outputFile, bulk);
    outputFile.close();
}

} // bulk

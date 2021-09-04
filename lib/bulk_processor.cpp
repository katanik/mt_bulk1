#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "bulk_processor.h"

namespace bulk{
    
BulkProcessor::BulkProcessor(int n)
    : m_bulkNumber(n) {}

BulkProcessor::~BulkProcessor()
{
    if (m_braceCounter == 0)
        flushCurrentBulk();
}

bool BulkProcessor::readNextLine()
{
    if (!std::getline(std::cin, m_currentCmd))
        return false;

    return true;
}

void BulkProcessor::processCurrentCmd()
{        
    if (m_currentCmd == "{")
    {
        if (shouldBeFlush())
            flushCurrentBulk();
        m_braceCounter++;
        return;
    }

    if (m_currentCmd == "}")
    {
        m_braceCounter = std::max(0, m_braceCounter - 1);
        if (shouldBeFlush())
            flushCurrentBulk();
        return;
    }

    m_currentCmdBulk.addCmd(m_currentCmd);

    if (m_currentCmdBulk.size() == m_bulkNumber && shouldBeFlush())
        flushCurrentBulk();
}

void BulkProcessor::flushCurrentBulk()
{
    if (m_currentCmdBulk.isEmpty())
        return;

    // print to file
    std::ofstream outputFile;
    std::stringstream fileName;
    fileName << "bulk" << m_currentCmdBulk.getTimeStamp() << ".log";
    outputFile.open(fileName.str(), std::fstream::out);
    if (!outputFile.is_open())
    {
        std::cout << "failed to create file " << '\n';
        return;
    }
    bulk::printCmdBulk(outputFile, m_currentCmdBulk);
    outputFile.close();

    // print to standard output
    bulk::printCmdBulk(std::cout, m_currentCmdBulk);
    m_currentCmdBulk.clear();
}

bool BulkProcessor::shouldBeFlush() const
{
    return m_braceCounter == 0;
}

} // bulk

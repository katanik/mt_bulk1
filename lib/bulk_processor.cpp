#include <iostream>

#include "bulk_processor.h"

namespace bulk{
    
BulkProcessor::BulkProcessor(int n)
    : m_bulkNumber(n) {}

BulkProcessor::~BulkProcessor()
{
    if (m_braceCounter == 0)
        flushCurrentBulk();
}

void BulkProcessor::subscribe(IBulkSibscriber *s)
{
    m_subscribers.push_back(s);
}

void BulkProcessor::notify()
{
    for (auto s : m_subscribers)
    {
        s->run(m_currentCmdBulk);
    }
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

    notify();
    m_currentCmdBulk.clear();
}

bool BulkProcessor::shouldBeFlush() const
{
    return m_braceCounter == 0;
}

} // bulk

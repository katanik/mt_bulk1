#pragma once

#include "lib/cmd_bulk.h"

namespace bulk{

class BulkProcessor
{
public:
    BulkProcessor(int n);
    ~BulkProcessor();

    bool readNextLine();
    void processCurrentCmd();

private:
    void flushCurrentBulk();
    bool shouldBeFlush() const;

private:
    bulk::Cmd m_currentCmd;
    bulk::CmdBulk m_currentCmdBulk;
    int m_braceCounter = 0;
    int m_bulkNumber = 1;
};

} // bulk

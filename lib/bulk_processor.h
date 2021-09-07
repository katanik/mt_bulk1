#pragma once

#include "cmd_bulk.h"
#include "logger.h"

namespace bulk{

class BulkProcessor : public IPublisher
{
public:
    BulkProcessor(int n);
    ~BulkProcessor();

    void subscribe(IBulkSibscriber *s) override;
    void notify();

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

    std::vector<IBulkSibscriber*> m_subscribers;
};

} // bulk

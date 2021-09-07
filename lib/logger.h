#pragma once

#include "cmd_bulk.h"

namespace bulk{

class IBulkSibscriber
{
public:
    IBulkSibscriber() = default;
    virtual ~IBulkSibscriber() = default;

    virtual void run(const bulk::CmdBulk& bulk) = 0;
};

class IPublisher
{
public:
    virtual void subscribe(IBulkSibscriber* s) = 0;
};

class Logger : public IBulkSibscriber {
public:
    Logger(IPublisher *publisher);

    void run(const bulk::CmdBulk& bulk) override;
};

class FilePrinter : public IBulkSibscriber {
public:
    FilePrinter(IPublisher *publisher);

    void run(const bulk::CmdBulk& bulk) override;
};

} // bulk

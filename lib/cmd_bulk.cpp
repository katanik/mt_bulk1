#include "cmd_bulk.h"
#include <chrono>
#include <ctime>
#include <sstream>

namespace bulk{

bool CmdBulk::isEmpty() const
{
    return m_bulk.empty();
}

size_t CmdBulk::size() const
{
    return m_bulk.size();
}

std::string CmdBulk::getTimeStamp() const
{
    return m_timeStampStr;
}

const Cmd& CmdBulk::getCmd(size_t index) const
{
    return m_bulk[index];
}

void CmdBulk::addCmd(const Cmd& cmd)
{
    if (m_bulk.empty())
    {
        //using namespace std::chrono;
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto timeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        std::stringstream ss;
        ss << timeStamp;
        m_timeStampStr = ss.str();
    }

    m_bulk.push_back(cmd);
}

void CmdBulk::clear()
{
    m_bulk.clear();
}

void printCmdBulk(std::ostream& out, const CmdBulk& cmdBulk)
{
    if (cmdBulk.isEmpty())
        return;

    out<< "bulk: ";
    for (size_t idx = 0; idx < cmdBulk.size(); ++idx)
    {
        out << cmdBulk.getCmd(idx);
        if (idx + 1 < cmdBulk.size())
            out << ", ";
    }
    out << std::endl;
}

} // bulk

#pragma once

#include "Log.h"
#include "UnicodeUtil.h"

#include <iostream>
#include <Windows.h>

namespace mmd
{
    DefaultSink::DefaultSink()
    {
        m_defaultLogger = spdlog::stdout_color_mt("default");
        SetConsoleOutputCP(CP_UTF8);
    }

    void DefaultSink::log(const spdlog::details::log_msg & msg)
    {
        m_defaultLogger->log(msg.level, msg.raw.c_str());
    }

    void DefaultSink::flush()
    {
        m_defaultLogger->flush();
    }
}

#pragma once

#include "Time.h"

#include <chrono>

namespace mmd
{
    /// <summary>
    /// 返回时间
    /// </summary>
    /// <returns>秒级精度 /s</returns>
    double GetTime()
    {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(now.time_since_epoch()).count();
    }

    /// <summary>
    /// 返回时间
    /// </summary>
    /// <returns>毫秒级精度 /ms</returns>
    double GetTimeMSec()
    {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(now.time_since_epoch()).count();
    }
    /// <summary>
    /// 返回时间
    /// </summary>
    /// <returns>纳秒级精度 /ns</returns>
    double GetTimeUSec()
    {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::micro>(now.time_since_epoch()).count();
    }
}

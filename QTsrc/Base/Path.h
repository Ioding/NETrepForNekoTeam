#pragma once

#include <string>
#include <vector>

namespace mmd { 
    // 路径类，处理输入路径
    class PathUtil
    {
    public:
        PathUtil() = delete;
        PathUtil(const PathUtil&) = delete;
        PathUtil& operator = (const PathUtil&) = delete;

        static std::string GetCWD();
        static std::string GetExecutablePath();
        static std::string Combine(const std::vector<std::string>& parts);
        static std::string Combine(const std::string& a, const std::string& b);
        static std::string GetDirectoryName(const std::string& path);
        static std::string GetFilename(const std::string& path);
        static std::string GetFilenameWithoutExt(const std::string& path);
        static std::string GetExt(const std::string& path);
        static std::string GetDelimiter();
        static std::string Normalize(const std::string& path);
    };
}
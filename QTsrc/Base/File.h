#pragma once

#include <cstdio>
#include <vector>
#include <cstdint>
#include <string>

namespace mmd
{
    // 文件类，提供对文件的各类检查及操作
    class File
    {
    public:
        // 固定类型大小，防止不同环境出现错误
        using Offset = int64_t;

        enum class SeekDir
        {
            Begin,
            Current,
            End,
        };

        File();
        ~File();

        // 删除默认构造函数
        File(const File&) = delete;
        File& operator = (const File&) = delete;

        // 提供不同方式打开文件的方法
        bool Open(const char* filepath);
        bool OpenText(const char* filepath);
        bool Create(const char* filepath);
        bool CreateText(const char* filepath);

        // 提供对string类型的支持
        bool Open(const std::string& filepath) { return Open(filepath.c_str()); }
        bool OpenText(const std::string& filepath) { return OpenText(filepath.c_str()); }
        bool Create(const std::string& filepath) { return Create(filepath.c_str()); }
        bool CreateText(const std::string& filepath) { return CreateText(filepath.c_str()); }

        // 工具组函数
        void Close();
        bool IsOpen();
        Offset GetSize() const;
        bool IsBad() const;
        void ClearBadFlag();
        bool IsEOF();

        FILE* GetFilePointer() const;

        // 提供对不同类型的方法
        bool ReadAll(std::vector<char>* buffer);
        bool ReadAll(std::vector<uint8_t>* buffer);
        bool ReadAll(std::vector<int8_t>* buffer);

        bool Seek(Offset offset, SeekDir origin);
        Offset Tell();

        // 防止读文件超过大小
        template <typename T>
        bool Read(T* buffer, size_t count = 1)
        {
            // 边界情况处理
            if (buffer == nullptr)
            {
                return false;
            }
            if (!IsOpen())
            {
                return false;
            }

            if (fread_s(buffer, sizeof(T) * count, sizeof(T), count, m_fp) != count)
            {
                m_badFlag = true;
                return false;
            }

            return true;
        }

        // 防止写文件超过大小
        template <typename T>
        bool Write(T* buffer, size_t count = 1)
        {
            if (buffer == nullptr)
            {
                return false;
            }
            if (!IsOpen())
            {
                return false;
            }

            if (fwrite(buffer, sizeof(T), count, m_fp) != count)
            {
                m_badFlag = true;
                return false;
            }
            return true;
        }

    private:
        bool OpenFile(const char* filepath, const char* mode);

    private:
        FILE*    m_fp;
        Offset    m_fileSize;
        bool    m_badFlag;
    };

    class TextFileReader
    {
    public:
        // 删除默认构造函数
        TextFileReader() = default;

        // 防止隐式类型转换
        explicit TextFileReader(const char* filepath);
        explicit TextFileReader(const std::string& filepath);

        bool Open(const char* filepath);
        bool Open(const std::string& filepath);
        void Close();
        bool IsOpen();

        std::string ReadLine();
        void ReadAllLines(std::vector<std::string>& lines);
        std::string ReadAll();
        bool IsEof();

    private:
        mmd::File    m_file;
    };
}

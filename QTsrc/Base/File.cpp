#pragma once

#include "File.h"
#include "UnicodeUtil.h"

#include <iterator>

namespace mmd
{
    File::File()
        : m_fp(nullptr)
        , m_fileSize(0)
        , m_badFlag(false)
    {   }
    
    File::~File()
    {
        Close();
    }
    
    // 通过函数名控制文件打开方式
    bool File::Open(const char * filepath)
    {
        return OpenFile(filepath, "rb");
    }
    bool File::OpenText(const char * filepath)
    {
        return OpenFile(filepath, "r");
    }
    bool File::Create(const char * filepath)
    {
        return OpenFile(filepath, "wb");
    }
    bool File::CreateText(const char * filepath)
    {
        return OpenFile(filepath, "w");
    }

    // 关闭文件
    void File::Close()
    {
        if (m_fp != nullptr)
        {
            fclose(m_fp);
            m_fp = nullptr;
            m_fileSize = 0;
            m_badFlag = false;
        }
    }
    
    bool File::IsOpen()
    {
        return !(m_fp == nullptr);
    }
    
    File::Offset File::GetSize() const
    {
        return m_fileSize;
    }

    bool File::IsBad() const
    {
        return m_badFlag;
    }

    void File::ClearBadFlag()
    {
        m_badFlag = false;
    }

    bool File::IsEOF()
    {
        return feof(m_fp) != 0;
    }

    FILE * File::GetFilePointer() const
    {
        return m_fp;
    }


    bool File::ReadAll(std::vector<char>* buffer)
    {
        if (buffer == nullptr)
        {
            return false;
        }
        
        buffer->resize(m_fileSize);
        Seek(0, SeekDir::Begin);
        if (!Read((*buffer).data(), m_fileSize))
        {
            return false;
        }
        
        return true;
    }

    bool File::ReadAll(std::vector<uint8_t>* buffer)
    {
        if (buffer == nullptr)
        {
            return false;
        }
        
        buffer->resize(m_fileSize);
        Seek(0, SeekDir::Begin);
        if (!Read((*buffer).data(), m_fileSize))
        {
            return false;
        }
        
        return true;
    }

    bool File::ReadAll(std::vector<int8_t>* buffer)
    {
        if (buffer == nullptr)
        {
            return false;
        }

        buffer->resize(m_fileSize);
        Seek(0, SeekDir::Begin);
        if (!Read((*buffer).data(), m_fileSize))
        {
            return false;
        }

        return true;
    }

    bool File::Seek(Offset offset, SeekDir origin)
    {
        if (m_fp == nullptr)
        {
            return false;
        }
        int cOrigin = 0;

        // 边界处理
        switch (origin)
        {
        case SeekDir::Begin:
        {
            cOrigin = SEEK_SET;
            break;
        }
        case SeekDir::Current:
        {
            cOrigin = SEEK_CUR;
            break;
        }
        case SeekDir::End:
        {
            cOrigin = SEEK_END;
            break;
        }
        default:
            return false;
        }

        // 该函数成功返回0
        if (_fseeki64(m_fp, offset, cOrigin) != 0)
        {
            m_badFlag = true;
            return false;
        }

        return true;
    }
    
    // 获得当前文件指针位置
    File::Offset File::Tell()
    {
        if (m_fp == nullptr)
        {
            return -1;
        }
        return (Offset)_ftelli64(m_fp);
    }

    bool File::OpenFile(const char* filepath, const char* mode)
    {
        if (m_fp != nullptr)
        {
            Close();
        }
        std::wstring wFilepath;
        if (!TryToWString(filepath, wFilepath))
        {
            return false;
        }
        std::wstring wMode;
        if (!TryToWString(mode, wMode))
        {
            return false;
        }
        auto err = _wfopen_s(&m_fp, wFilepath.c_str(), wMode.c_str());
        if (err != 0)
        {
            return false;
        }

        ClearBadFlag();

        Seek(0, SeekDir::End);
        m_fileSize = Tell();
        Seek(0, SeekDir::Begin);
        if (IsBad())
        {
            Close();
            return false;
        }
        return true;
    }



    TextFileReader::TextFileReader(const char * filepath)
    {
        Open(filepath);
    }

    TextFileReader::TextFileReader(const std::string & filepath)
    {
        Open(filepath);
    }

    bool TextFileReader::Open(const char * filepath)
    {
        return m_file.OpenText(filepath);
    }

    bool TextFileReader::Open(const std::string & filepath)
    {
        return Open(filepath.c_str());
    }

    void TextFileReader::Close()
    {
        m_file.Close();
    }

    bool TextFileReader::IsOpen()
    {
        return m_file.IsOpen();
    }

    // 按行读取文件
    std::string TextFileReader::ReadLine()
    {
        if (!IsOpen() || IsEof())
        {
            return "";
        }

        std::string line;
        auto outputIt = std::back_inserter(line);
        int ch;
        ch = fgetc(m_file.GetFilePointer());
        while (ch != EOF && ch != '\r' && ch != '\n')
        {
            line.push_back(ch);
            ch = fgetc(m_file.GetFilePointer());
        }
        if (ch != EOF)
        {
            if (ch == '\r')
            {
                ch = fgetc(m_file.GetFilePointer());
                if (ch != EOF && ch != '\n')
                {
                    ungetc(ch, m_file.GetFilePointer());
                }
            }
            else
            {
                ch = fgetc(m_file.GetFilePointer());
                if (ch != EOF)
                {
                    ungetc(ch, m_file.GetFilePointer());
                }
            }
        }

        return line;
    }

    void TextFileReader::ReadAllLines(std::vector<std::string>& lines)
    {
        lines.clear();
        if (!IsOpen() || IsEof())
        {
            return;
        }
        while (!IsEof())
        {
            lines.emplace_back(ReadLine());
        }
    }

    std::string TextFileReader::ReadAll()
    {
        std::string all;

        if (m_file.IsOpen())
        {
            int ch = fgetc(m_file.GetFilePointer());
            while (ch != EOF)
            {
                all.push_back(ch);
                ch = fgetc(m_file.GetFilePointer());
            }
        }
        return all;
    }

    bool TextFileReader::IsEof()
    {
        if (!m_file.IsOpen())
        {
            return false;
        }
        return m_file.IsEOF();
    }
}
#ifndef MMDFILESTRING_H
#define MMDFILESTRING_H

#include <QString>
namespace mmd
{
    template <quint64 Size>
    struct MMDFileString
    {
        MMDFileString()
        {
            Clear();
        }

        void Clear()
        {
            for (auto& ch : m_buffer)
            {
                ch = '\0';
            }
        }

        void Set(const char* str)
        {
            unsigned long long i = 0;
            while (i < Size && str[i] != '\0')
            {
                m_buffer[i] = str[i];
                ++i;
            }
            for (; i < Size + 1; ++i)
            {
                m_buffer[i] = '\0';
            }
        }

        const char* ToCString() const { return m_buffer; }
        QString ToQString() const { return QString(m_buffer); }

        char m_buffer[Size + 1];
    };
}



#endif // MMDFILESTRING_H

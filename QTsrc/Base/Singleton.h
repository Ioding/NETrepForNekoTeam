﻿#pragma once

#include <functional>
#include <mutex>

namespace mmd
{
    // 回收类
    class SingletonFinalizer
    {
    public:
        using FinalizerFunc = std::function<void()>;

        static void AddFinalizer(FinalizerFunc finalizer);
        static void Finalize();
    };

    // 实现单例模式，主要用于日志
    template <typename T>
    class Singleton final
    {
    public:
        static T* Get()
        {
            std::call_once(m_initFlag, Create);
            return m_instance;
        }

    private:
        static void Create()
        {
            m_instance = new T();
            SingletonFinalizer::AddFinalizer(&Singleton<T>::Destroy);
        }

        static void Destroy()
        {
            delete m_instance;
            m_instance = nullptr;
        }

    private:
        static std::once_flag    m_initFlag;
        static T*                m_instance;
    };
    template <typename T> std::once_flag Singleton<T>::m_initFlag;
    template <typename T> T* Singleton<T>::m_instance = nullptr;
}
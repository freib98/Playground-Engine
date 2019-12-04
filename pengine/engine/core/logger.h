#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace PEngine
{
    class Logger
    {
    public:
        Logger() = delete;

        static void Init();

        static std::shared_ptr<spdlog::logger> GetCoreLogger();

    private:
        static std::shared_ptr<spdlog::logger> _coreLogger;
    };
}

#define PENGINE_DEBUG(...) PEngine::Logger::GetCoreLogger()->log(spdlog::source_loc{ __FILE__, __LINE__, SPDLOG_FUNCTION }, spdlog::level::debug, __VA_ARGS__)
#define PENGINE_INFO(...) PEngine::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define PENGINE_WARN(...) PEngine::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define PENGINE_ERROR(...) PEngine::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define PENGINE_CRITICAL(...) PEngine::Logger::GetCoreLogger()->critical(__VA_ARGS__)

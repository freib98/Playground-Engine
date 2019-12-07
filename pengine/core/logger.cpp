#include "logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> PEngine::Logger::_coreLogger;

void PEngine::Logger::Init()
{
    _coreLogger = spdlog::stdout_color_mt("PENGINE CORE");

    _coreLogger->set_pattern(">>> [%^%l%$] [%H:%M:%S] %v %s:%# <<<");

    _coreLogger->set_level(spdlog::level::debug);
}

std::shared_ptr<spdlog::logger>& PEngine::Logger::GetCoreLogger()
{
    return _coreLogger;
}

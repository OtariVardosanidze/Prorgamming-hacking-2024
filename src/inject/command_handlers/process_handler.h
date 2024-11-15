#pragma once

#include <string>
#include <memory>

class ProcessCommunicator{
    public:
        virtual ~ProcessCommunicator()  = default;
        virtual void SetDaemon(bool daemon = true) = 0;
        virtual void Write(const std::string& data) = 0;
        virtual std::string Read() = 0;
};


class ProcessLauncher {
    public:
    static std::unique_ptr<ProcessCommunicator> CreateProcessFunc(const std::string& exec_path);
};
#include <windows.h>
#include <strsafe.h>
#include <iostream>
#include "process_handler.h"
#include <string>
#define BUFSIZE 1024

struct Pipe {
	HANDLE in = INVALID_HANDLE_VALUE;
	HANDLE out = INVALID_HANDLE_VALUE;

	Pipe() = default;
	Pipe(Pipe&& o) : in(std::move(o.in)), out(std::move(o.out)) {
		o.in = o.out = INVALID_HANDLE_VALUE;
	}

	~Pipe() {
		CloseHandle(in);
		CloseHandle(out);
	}

	bool IsValid() const {
		return in != INVALID_HANDLE_VALUE && out != INVALID_HANDLE_VALUE;
	}
};

Pipe CreatePipe() {
	Pipe result;

	SECURITY_ATTRIBUTES saAttr; 
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL; 

	if (! CreatePipe(&result.in, &result.out, &saAttr, 0)){ 
		return result;
	}

	if (! SetHandleInformation(result.in, HANDLE_FLAG_INHERIT, 0)){
		return {};
	}
	if (! SetHandleInformation(result.out, HANDLE_FLAG_INHERIT, 0)){
		return {};
	}

	return result;	
}

class ProcessCommunicatorWin : public ProcessCommunicator{
    public:
    ~ProcessCommunicatorWin() override { ////////
        if (!is_daemon) {
            // Terminate
        }
    }

    void SetDaemon(bool daemon = true) override {
        is_daemon = daemon;
    }

    void Write(const std::string& data) override {
		if (! WriteFile(out_pipe.out, data.c_str(), static_cast<DWORD>(data.size()), nullptr, nullptr)) 
			exit(1);
	}

    std::string Read() override {
		char b[BUFSIZE];
		DWORD rSize;
		if(! ReadFile(in_pipe.in, b, BUFSIZE, &rSize, nullptr)) 
			exit(1); 
		
		if (rSize != 0)
			return std::string(b, rSize);
		else
			return {};
	}

    private:
    friend class ProcessLauncher;
    ProcessCommunicatorWin(HANDLE process, Pipe&& in_pipe, Pipe&& out_pipe):
		process(process),
		in_pipe(std::move(in_pipe)),
		out_pipe(std::move(out_pipe)) {}

    HANDLE process = INVALID_HANDLE_VALUE;
	Pipe in_pipe, out_pipe;
    bool is_daemon = false;
};

// static
std::unique_ptr<ProcessCommunicator> ProcessLauncher::CreateProcessFunc(const std::string& exec_path){
	Pipe in_pipe = CreatePipe();
	if (!in_pipe.IsValid()) {
		return nullptr;
	}

	Pipe out_pipe = CreatePipe();
	if (!out_pipe.IsValid()) {
		return nullptr;
	}

	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));

	cif.cb = sizeof(STARTUPINFO);
	cif.hStdOutput = out_pipe.out;
	cif.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	cif.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	cif.dwFlags |= STARTF_USESTDHANDLES;

	PROCESS_INFORMATION pi;
	if (!CreateProcess(exec_path.c_str(), NULL, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &cif, &pi)){
		return nullptr;
	}
	std::cout << pi.dwProcessId << std::endl;
	WaitForSingleObject(pi.hProcess, INFINITE );

	return std::unique_ptr<ProcessCommunicator>(
		new ProcessCommunicatorWin(pi.hProcess, std::move(in_pipe), std::move(out_pipe)));
}

void main()
{
	auto pc = ProcessLauncher::CreateProcessFunc("c:\\windows\\system32\\cmd.exe");

	pc->Write("Hello");
	//for (;;) {
		std::cout << pc->Read();
		std::cout << "--";
	//}
} 
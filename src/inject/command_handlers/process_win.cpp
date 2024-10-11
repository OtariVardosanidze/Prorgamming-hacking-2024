#include <windows.h>
#include <iostream>
#include "../core/messages/test.pb.h"

void main()
{
	TestMessage m;
    m.set_x(10);
    m.set_y("abc");

    std::cout << m.SerializeAsString() << std::endl;

	std::string s = m.SerializeAsString();

	TestMessage m2;
	m2.ParseFromString(s);

	STARTUPINFO cif;
	ZeroMemory(&cif,sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	if (CreateProcess("c:\\windows\\system32\\cmd.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &cif, &pi) == TRUE){
		//"c:\\windows\\notepad.exe" - имя исполняемого модуля, 
        //NULL - командная строка, NULL - указатель на структуру секьюрити, NULL - тоже, FALSE - флаг наследования текущего процесса, NULL - флаг способа создания процесса, NULL - указатель на блок среды, NULL - текущий диск, &cif - указатель на структуру startupinfo, 
        //&pi - указатель на структуру process_information
        std::cout << "process" << std::endl;
		std::cout << "handle " << pi.hProcess << std::endl;
		Sleep(1000);				// подождать
			// убрать процесс
	}
}
#pragma once

#include <elements.hpp>
#include <string>

namespace ui {
	using namespace cycfi::elements;
}

class Machine {
public:
	Machine(const std::string& name, const std::string& address);

	void set_name(const std::string& name);
	void set_address(const std::string& address);
	std::string get_status() const;

	ui::element_ptr render() const;

private:
	std::string name;
	std::string address;
};
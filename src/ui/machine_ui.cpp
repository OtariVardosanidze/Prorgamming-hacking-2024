#include "machine_ui.h"


Machine::Machine(const std::string& name, const std::string& address) : name(name), address(address) {

}

void Machine::set_name(const std::string& name) {
	this->name = name;
}

void Machine::set_address(const std::string& address) {
	this->address = address;
}

std::string Machine::get_status() const {
	return "online";
}

ui::element_ptr Machine::render() const {
	return ui::share(ui::vtile(
		ui::label(name),
		ui::label(address),
		ui::label(get_status())
	));
}

/*=============================================================================
   Copyright (c) 2016-2023 Joel de Guzman

   Distributed under the MIT License (https://opensource.org/licenses/MIT)
=============================================================================*/
#include <elements.hpp>
using namespace cycfi::elements;

class Workspace {
public:
    auto make_gui() {

    }
};

class Machine {
public:
    Machine(const std::string& name) : name(name) {}


    auto make_gui() {
        return label(name);
    }

    Workspace* get_workspace() {
        return workspace.get();
    }

private:
    std::string name;
    std::unique_ptr<Workspace> workspace;

};

class MachinesList {
public:
    MachinesList() {
        machines.push_back(Machine("Client 1"));
        machines.push_back(Machine("Client 2"));
        machines.push_back(Machine("Super puper machine"));

    }

    void add_machine() {}

    auto make_gui() {
        auto tiles = vtile_composite();
        for (auto& m : machines) {
            auto gui = m.make_gui();
            tiles.push_back(share(gui));
        }
        auto sections = htile(
            layer(
                margin({ 10, 10, 10, 10 },std::move(tiles)),
            margin({ 10, 10, 10, 10 }, label("Select a client to see details."))
        ));
        return sections;
    }

private:
    std::vector<Machine> machines;
};


class Applictaion {
public:

    auto make_gui() {
        // Horizontal layout for buttons
        auto buttons = htile(
            button("Add"),
            button("Edit"),
            button("Delete")
        );

        return vtile(
            margin({ 10, 10, 10, 10 }, buttons),
            machines.make_gui()
        );
    }
private:
    MachinesList machines;
};

auto make_gui()
{
    // Horizontal layout for buttons
    auto buttons = htile(
        button("Add"),
        button("Edit"),
        button("Delete")
    );

    // Vertical layout for sections
    auto sections = htile(
        layer(
            margin({ 10, 10, 10, 10 }, vtile(
                label("Client 1"),
                label("Client 2"),
                label("Client 3")
            ))),
        margin({ 10, 10, 10, 10 }, label("Select a client to see details."))
    );

    return vtile(
        margin({ 10, 10, 10, 10 }, buttons),
        sections
    );
}

int main(int argc, char* argv[])
{
    app _app("Client Management");
    window _win(_app.name());
    _win.on_close = [&_app]() { _app.stop(); };

    view view_(_win);

    Applictaion application;

    view_.content(
        margin({ 10, 10, 10, 10 }, application.make_gui())
    );

    _app.run();
    return 0;
}


/*
#include <elements.hpp>
using namespace cycfi::elements;


int main(int argc, char* argv[])
{
   app _app("Hello Universe");
   window _win(_app.name());
   _win.on_close = [&_app]() { _app.stop(); };

   view view_(_win);

   view_.content(
      scroller(image{"space.jpg"})
   );

   _app.run();
   return 0;
}
*/
/*=============================================================================
   Copyright (c) 2016-2023 Joel de Guzman

   Distributed under the MIT License (https://opensource.org/licenses/MIT)
=============================================================================*/

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

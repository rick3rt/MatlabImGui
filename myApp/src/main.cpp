#include "Demo.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    Demo app("Demo", 1280, 760, argc, argv);
    app.Run();

    return 0;
}

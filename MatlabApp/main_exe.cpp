#include "MatlabApp.h"

int main()
{
    MatlabApp app("MatlabApp App", 1280, 760, 0, nullptr);
    double x[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double y[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    app.setData(x, y, 10);
    app.Run();
    return 0;
}
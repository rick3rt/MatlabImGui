
#include "MatlabApp.h"
#include "mex.h"

#include <memory>
#include <thread>

static MatlabApp *app;
static bool app_running = false;
static std::thread t;

// thread function that starts the matlab app
void run_MatlabApp()
{
    app = new MatlabApp("MatlabApp App", 1280, 760, 0, nullptr);
    app_running = true;
    app->Run();
    app_running = false;
    delete app;
    return;
}

void init()
{
    // print initializing
    mexPrintf("Initializing App...\n");
    t = std::thread(run_MatlabApp);
    t.detach();
    mexPrintf("Initialized! App running in background.\n");
}

void clear()
{
    // print clearing
    mexPrintf("Closing App...\n");
    // check if thread is running
    if (app_running) app->Stop(); // close the app
    app_running = false;
    mexPrintf("Closed!\n");
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{

    mexAtExit(clear);
    if (!app_running)
    {
        init();
        return;
    }
    if (nrhs == 0)
    {
        mexPrintf("App is running at: %p\nNo Command specified. ", app);
        return;
    }

    // read the first input which is a char array with a command
    char *command = mxArrayToString(prhs[0]);

    // check if command is "close"
    if (strcmp(command, "close") == 0)
    {
        clear();
        return;
    }

    // check if command is "plot"
    if (strcmp(command, "plot") == 0)
    {
        if (nrhs != 3)
        {
            mexPrintf("Plotting requires 2 arguments: xdata, ydata\n");
            return;
        }
        mexPrintf("Setting data...\n");
        double *xdata = mxGetDoubles(prhs[1]);
        double *ydata = mxGetDoubles(prhs[2]);
        size_t size = mxGetNumberOfElements(prhs[1]);
        app->setData(xdata, ydata, size);
    }

    if (strcmp(command, "plot_raw") == 0)
    {
        if (nrhs != 3)
        {
            mexPrintf("Plotting requires 2 arguments: xdata, ydata\n");
            return;
        }
        mexPrintf("Setting data...\n");
        double *xdata = mxGetDoubles(prhs[1]);
        double *ydata = mxGetDoubles(prhs[2]);
        size_t size = mxGetNumberOfElements(prhs[1]);
        app->setRawData(xdata, ydata, size);
    }

    if (strcmp(command, "img") == 0)
    {
        if (nrhs != 2)
        {
            mexPrintf("Image plotting requires 1 argument: img\n");
            return;
        }
        mexPrintf("Setting data...\n");
        double *img = mxGetDoubles(prhs[1]);
        size_t rows = mxGetN(prhs[1]);
        size_t cols = mxGetM(prhs[1]);
        app->setImageData(img, rows, cols);
    }

    // check if command is "color"
    if (strcmp(command, "color") == 0)
    {
        if (nrhs != 4)
        {
            mexPrintf("Setting color requires 3 arguments: r, g, b\n");
            return;
        }
        mexPrintf("Setting color...\n");
        double r = mxGetScalar(prhs[1]);
        double g = mxGetScalar(prhs[2]);
        double b = mxGetScalar(prhs[3]);
        app->SetColor(r, g, b);
    }
}
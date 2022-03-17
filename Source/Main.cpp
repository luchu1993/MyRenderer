#include "Core/Api.h"
#include "Launch/Blinn.h"


int main(int argc, char* argv[])
{
    Platform::Get().Initialize();

    {
        Blinn blinn(argv[1]);
        blinn.Initialize();
        blinn.MainLoop();
        blinn.Terminate();
    }

    Platform::Get().Terminate();
}
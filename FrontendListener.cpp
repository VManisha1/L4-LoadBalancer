#include "FrontendListener.h"

void FrontendListener::start() {
    acceptConnections();
    ioContext.run(); // Start the I/O context event loop
}
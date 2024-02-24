/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/

#include "glHeaders.h"
#include "engine.h"
#include "xmlLoader.h"

int main(void) {
    Magick::InitializeMagick(nullptr);

    XMLLoader* textParser = new XMLLoader();
    if (textParser->Init("../planetInfo.xml") == 1) {
        return 1;
    }

    vector<Planet> planetInfo = textParser->ParseXML();

    //We don't need this anymore, so we may as well free up the memory
    delete textParser;
    textParser = NULL;

    //Start the engine
    Engine *engine = new Engine("Solar System Project", 800, 600);
    if (!engine->Init(planetInfo)) {
        cerr << "The engine failed to start" << endl;
        delete engine;
        engine = NULL;
        return 2;
    }
    engine->Run();
    return 0;
}
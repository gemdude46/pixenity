#include <irrlicht.h>
#include <algorithm>
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#define MAIN 0
#define GAME 1

int menu = GAME;

const SColor WHITE = SColor(255, 255, 255, 255);

IrrlichtDevice *device;

ITexture* I2T(video::IImage* image, core::stringc name) {
   ITexture* texture = device->getVideoDriver()->addTexture(name.c_str(),image);
   texture->grab();
   return texture;
}

#include "allX.h"

World world;

int main(){
    INITBLOCKCOLORS();

    device = createDevice(EDT_OPENGL, core::dimension2d<u32>(1000,666));
    
    world = World();
    
    
    while (device->run()){
        device->getVideoDriver()->beginScene(true, false, video::SColor(255,0,0,0));
        if (menu==GAME){
            world.tick();
            world.blit();
        }
        device->getVideoDriver()->endScene();
    }
    return 0;
}

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
const SColor BLACK = SColor(255, 0  , 0  , 0);

inline int pmod(int a, int b)
{ return (a%b+b)%b; }

inline int pdiv(int a, int b)
{ return (a-(a<0?b-1:0))/b; }

inline position2d<s32> D2P(dimension2d<s32> d)
{ return position2d<s32>(d.Width, d.Height); }

inline position2d<s32> uD2P(dimension2d<u32> d)
{ return position2d<s32>(d.Width, d.Height); }

position2d<s32> ofs;

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
        ofs = uD2P(device->getVideoDriver()->getScreenSize() / 2) - position2d<s32>(500,333);
        device->getVideoDriver()->beginScene(true, false, video::SColor(255,0,0,0));
        if (menu==GAME){
            world.tick();
            world.blit(device);
        }
        device->getVideoDriver()->draw2DRectangle(BLACK,rect<s32>(0,0,1001+2*ofs.X,ofs.Y));
        device->getVideoDriver()->draw2DRectangle(BLACK,rect<s32>(0,ofs.Y+666,1001+2*ofs.X,ofs.Y*2+667));
        device->getVideoDriver()->draw2DRectangle(BLACK,rect<s32>(0,ofs.Y,ofs.X,ofs.Y+666));
        device->getVideoDriver()->draw2DRectangle(BLACK,rect<s32>(ofs.X+1000,ofs.Y,1001+2*ofs.X,ofs.Y+666));
        device->getVideoDriver()->endScene();
    }
    return 0;
}

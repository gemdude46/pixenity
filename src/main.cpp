#include <irrlicht.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <time.h>
#include <queue>
#include <stack>
#include <libnoise/noise.h>
#include <string.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;
using namespace noise;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#define MAIN 0
#define GAME 1

int menu = GAME;

module::Perlin noiseGen;

const SColor WHITE = SColor(255, 255, 255, 255);
const SColor BLACK = SColor(255, 0  , 0  , 0);

position2d<s32> mpos;

inline int pmod(int a, int b)
{ return (a%b+b)%b; }

inline int pdiv(int a, int b)
{ return (a-(a<0?b-1:0))/b; }

inline position2d<s32> D2P(dimension2d<s32> d)
{ return position2d<s32>(d.Width, d.Height); }

inline position2d<s32> uD2P(dimension2d<u32> d)
{ return position2d<s32>(d.Width, d.Height); }

void logtime(){
    time_t t = time(NULL);
    char* c = ctime(&t);
    clog << " [";
    for (; *c != '\n'; c++) clog << *c;
    clog << "] ";
}

position2d<s32> ofs;

IrrlichtDevice *device;

ITexture* I2T(video::IImage* image, core::stringc name) {
   ITexture* texture = device->getVideoDriver()->addTexture(name.c_str(),image);
   texture->grab();
   return texture;
}

class MyEventReceiver : public IEventReceiver{
public:
	bool LB, RB;
	virtual bool OnEvent(const SEvent& event){
		if (event.EventType == EET_KEY_INPUT_EVENT){
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        }
        if (event.EventType == EET_MOUSE_INPUT_EVENT){
            switch(event.MouseInput.Event){
            case EMIE_LMOUSE_PRESSED_DOWN:
                LB = true;
                break;

            case EMIE_LMOUSE_LEFT_UP:
                LB = false;
                break;
                
            case EMIE_RMOUSE_PRESSED_DOWN:
                RB = true;
                break;

            case EMIE_RMOUSE_LEFT_UP:
                RB = false;
                break;
            }
        }
		return false;
	}
    virtual bool IsKeyDown(EKEY_CODE keyCode) const{
		return KeyIsDown[keyCode];
	}
	MyEventReceiver(){
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	    LB=false;
	    RB=false;
	}
private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

MyEventReceiver* EVTRR;

#define KD EVTRR->IsKeyDown


#include "allX.h"

World world;

int main(){
    INITBLOCKS();

    EVTRR = new MyEventReceiver();
    device = createDevice(EDT_OPENGL, core::dimension2d<u32>(1000,666), 16, false, false, false, EVTRR);
    
    world = World();
    
    while (device->run()){
        ofs = uD2P(device->getVideoDriver()->getScreenSize() / 2) - position2d<s32>(500,333);
        device->getVideoDriver()->beginScene(true, false, video::SColor(255,0,0,0));
        mpos = device->getCursorControl()->getPosition() - ofs;
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

#define BRUSH_PX                                                               0
#define BRUSH_CIRCLE                                                           1
#define BRUSH_SQUARE                                                           2

class Player {
    public:
    vector2df pos, vel;
    bool noclip;
    int brush;
    vector2d<s32> getIPos(){
        return vector2d<s32>((s32)pos.X,(s32)pos.Y);
    }
    vector2d<s32> getChunkPos(){
        return vector2d<s32>(pdiv(getIPos().X,CHSIZE),pdiv(getIPos().Y,CHSIZE));
    }
    Player(){
        pos = vector2df(0,-16);
        vel = vector2df();
        noclip = false;
        brush = BRUSH_CIRCLE;
    }
    void tick(World*);
};

class Player {
    public:
    vector2df pos, vel;
    vector2d<s32> getIPos(){
        return vector2d<s32>((s32)pos.X,(s32)pos.Y);
    }
    vector2d<s32> getChunkPos(){
        return vector2d<s32>(pdiv(getIPos().X,CHSIZE),pdiv(getIPos().Y,CHSIZE));
    }
    Player(){
        pos = vector2df();
        vel = vector2df();
    }
};

#ifndef _ISCENE_INCLUDE
#define _ISCENE_INCLUDE

class IScene
{
    public:

    IScene() {};
    virtual ~IScene() {};

    virtual void init() = 0;
    virtual void update(int deltaTime) = 0;
    virtual void render() = 0;

};

#endif // _ISCENE_INCLUDE
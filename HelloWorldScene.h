#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#define PTM_RATIO 32
#define WORLD_TO_SCREEN(n) n*PTM_RATIO
using namespace cocos2d;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
  void createFuji(Point p);
    bool touchBegan(Touch* touch,Event* event);
    void addTarget();
    void gameLogic(float dt);
    void spriteMoveFinished(Node* sender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
    PhysicsWorld  *sceneWorld;
    void SetPhysicsWorld(PhysicsWorld *world){sceneWorld = world;} ;  //the setter of physics world
    bool onContactBegin(PhysicsContact &contact);

};

#endif // __HELLOWORLD_SCENE_H__

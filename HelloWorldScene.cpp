#include "HelloWorldScene.h"
#include "MyBodyParser.h"
#include "Box2D/Box2D.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
  //  scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
   // scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
/*
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
    auto edgeNode = Node::create();
    edgeNode -> setPosition(Point (visibleSize.width/2 + origin.x,visibleSize.height/2 +origin.y));
    edgeNode -> setPhysicsBody(edgeBody);

    this->addChild(edgeNode);
    */



    /*
    {
        auto sprite = Sprite::create("fuji.png");
        sprite->setPosition(Point(visibleSize.width/2+ origin.x,visibleSize.height/2+origin.y));

        auto spriteBody = PhysicsBody::createBox(sprite->getContentSize(),PhysicsMaterial(0,1,0));
        spriteBody->setAngularVelocity(100);
    //    spriteBody->setCollisionBitmask(1);
    //    spriteBody->setContactTestBitmask(true);



       // spriteBody->setDynamic(false);
        sprite->setPhysicsBody(spriteBody);

        this -> addChild(sprite);
    }


    {
        auto sprite = Sprite::create("fuji2.png");
        sprite->setPosition(Point(visibleSize.width/2+ origin.x ,visibleSize.height/2+origin.y - 200));
        MyBodyParser::getInstance()-> parseJsonFile("fuji2.json");
        auto spriteBody = MyBodyParser::getInstance()->bodyFormJson(sprite,"fuji2",PhysicsMaterial(1,1,0));
           spriteBody->setVelocity(Vect(100,100));
      if(spriteBody!= nullptr)
         {
             spriteBody -> setDynamic(true);
             sprite->setPhysicsBody(spriteBody);
         }

        sprite->setPhysicsBody(spriteBody);

        this -> addChild(sprite);
    }
    */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin,this);
    this -> getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,this);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener -> onTouchBegan = CC_CALLBACK_2(HelloWorld::touchBegan,this);
    getEventDispatcher()->addEventListenerWithFixedPriority(touchListener,100);

    this->schedule(schedule_selector(HelloWorld::gameLogic), 1.0);
    return true;
}
bool HelloWorld::onContactBegin(PhysicsContact &contact)
{
     PhysicsBody *a = contact.getShapeA()->getBody();
     PhysicsBody *b = contact.getShapeB()->getBody();
     //check if the Body collied
     if((1 == a->getCollisionBitmask()&&2 == b->getCollisionBitmask()) ||
         (2 == a->getCollisionBitmask()&&1 == b->getCollisionBitmask()))
     {
          CCLOG("COLLISION HAS OCCURED");
     }
     return true;
}

//################################################################################################
 //create a physicsBody fuji on the point you click
//###############################################################
bool HelloWorld::touchBegan(Touch* touch,Event* event)
{
    HelloWorld::createFuji(touch->getLocation());
    return true;
}
void HelloWorld::createFuji(Point p)
{


        auto sprite = Sprite::create("fuji2.png");
        sprite->setPosition(p);
        MyBodyParser::getInstance()-> parseJsonFile("fuji2.json");
        auto spriteBody = MyBodyParser::getInstance()->bodyFormJson(sprite,"fuji2",PhysicsMaterial(1,1,0));
           spriteBody->setVelocity(Vect(0,0));
   //     spriteBody->setCollisionBitmask(2);
  //      spriteBody->setContactTestBitmask(true);
         if(spriteBody!= nullptr)
         {
             spriteBody -> setDynamic(true);
             sprite->setPhysicsBody(spriteBody);

         }

        sprite->setPhysicsBody(spriteBody);

        this -> addChild(sprite);



}

//################################################################################################
//create  enemy , remove if it is out of the screen
//######################################################
void HelloWorld::gameLogic(float dt)
{
 this->addTarget();

}

void HelloWorld::addTarget()
{

    {
        auto *sprite = Sprite::create("enemy.png");



        {
         // Determine where to spawn the target along the Y axis
         Size winSize = Director::getInstance()->getWinSize();
         int minY = sprite->getContentSize().height / 2;
         int maxY = winSize.height - sprite->getContentSize().height / 2;
         int rangeY = maxY - minY;
         // srand( TimGetTicks() );
         int actualY = (rand() % rangeY) + minY;

         // Create the target slightly off-screen along the right edge,
         // and along a random position along the Y axis as calculated
         sprite->setPosition(Point(winSize.width + (sprite->getContentSize().width / 2)-100, actualY));
        }


      //  sprite->setPosition(Point(200,200));
        MyBodyParser::getInstance()-> parseJsonFile("enemy.json");
        auto spriteBody = MyBodyParser::getInstance()->bodyFormJson(sprite,"enemy",PhysicsMaterial(1,1,0));
           spriteBody->setVelocity(Vect(-100,0));
      if(spriteBody!= nullptr)
         {
             spriteBody -> setDynamic(true);
             spriteBody -> setGravityEnable(false);
             sprite->setPhysicsBody(spriteBody);
         }

        sprite->setPhysicsBody(spriteBody);
        this -> addChild(sprite);
    }
        /*
        // Determine speed of the target
         int minDuration = (int)2.0;
         int maxDuration = (int)4.0;
         int rangeDuration = maxDuration - minDuration;
         // srand( TimGetTicks() );
         int actualDuration = (rand() % rangeDuration) + minDuration;

         // Create the actions
         FiniteTimeAction* actionMove =
          MoveTo::create((float)actualDuration,
          Point(0 - target->getContentSize().width / 2, actualY));

         FiniteTimeAction* actionMoveDone =
          CallFuncN::create(std::bind(&HelloWorld::spriteMoveFinished, this, std::placeholders::_1));

         target->runAction(Sequence::create(actionMove, actionMoveDone, NULL));

       }

 Sprite *target = Sprite::create("enemy.png", Rect(0, 0, 200, 59));
 // Determine where to spawn the target along the Y axis
 Size winSize = Director::getInstance()->getWinSize();
 int minY = target->getContentSize().height / 2;
 int maxY = winSize.height - target->getContentSize().height / 2;
 int rangeY = maxY - minY;
 // srand( TimGetTicks() );
 int actualY = (rand() % rangeY) + minY;

 // Create the target slightly off-screen along the right edge,
 // and along a random position along the Y axis as calculated
 target->setPosition(Point(winSize.width + (target->getContentSize().width / 2), actualY));
 this->addChild(target);

 // Determine speed of the target
 int minDuration = (int)2.0;
 int maxDuration = (int)4.0;
 int rangeDuration = maxDuration - minDuration;
 // srand( TimGetTicks() );
 int actualDuration = (rand() % rangeDuration) + minDuration;

 // Create the actions
 FiniteTimeAction* actionMove =
  MoveTo::create((float)actualDuration,
  Point(0 - target->getContentSize().width / 2, actualY));

 FiniteTimeAction* actionMoveDone =
  CallFuncN::create(std::bind(&HelloWorld::spriteMoveFinished, this, std::placeholders::_1));

 target->runAction(Sequence::create(actionMove, actionMoveDone, NULL));

 */

}
void HelloWorld::spriteMoveFinished(Node* sender)
{
 Sprite *sprite = (Sprite *)sender;
 this->removeChild(sprite, true);
}

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "extensions\cocos-ext.h"
#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"

enum  Color
{
	RED,
	GREEN
};

enum class Colour
{
	RED,
	GREEN
};

//textField
class KeyboardNotificationLayer : public cocos2d::IMEDelegate, public cocos2d::Layer
{
public:
	KeyboardNotificationLayer();
	virtual void onClickTrackNode(bool bClicked) = 0;
	virtual void keyboardWillShow(cocos2d::IMEKeyboardNotificationInfo& info) override;
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

protected:
	cocos2d::Node* _trackNode;
	cocos2d::Vec2 _beginPos;
};



class HelloWorld :  public cocos2d::extension::TableViewDelegate, cocos2d::extension::TableViewDataSource,
	KeyboardNotificationLayer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void 	initPhysical();
	void update(float delta);
	void AboutClippingNode();
	void AbooutActionManager();
	void AboutFileUtils();
	void AboutEffect();
	void AboutTableView();
	void AboutTimeline();
	void AboutCaptureScreen();
	void callbackCapture();
	void afterCapture(bool succeed, const std::string& str);
	void timelineCallback(cocostudio::timeline::Frame*);
	void AboutLabel();
	void AboutCascade();
	void AboutCocosPhysical();
	void AboutRendering();
	void saveImage(cocos2d::Ref* ref);
	void clearImage(cocos2d::Ref* ref);
	void AboutTexturePart();
	void AboutRenderTextureNode();
	void AboutWildPointer();
	void AboutAutoPolygon();
	void AboutFastTileMap();
	void AboutTextField();
	void AboutProfilerDisplay();
	void AboutClippingNodeAgain();
	void AboutParticles();

	~HelloWorld();
	cocos2d::ActionManager* _actionManager;

	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell) override;
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView* table)override;
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView* table, ssize_t idx)override;
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView* table, ssize_t idx)override;
	virtual void tableCellHighlight(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual void tableCellUnhighlight(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);

	//textTile
	void onClickTrackNode(bool bClicked);

	cocos2d::Scene* _world;
	cocos2d::Vector<cocos2d::Sprite*> _brushs;
	cocos2d::RenderTexture* target;
	cocos2d::DrawNode* _drawNode;
private:
	cocos2d::extension::PhysicsDebugNode* _debugLayer;
	cpSpace* _space;
	cpShape* _walls[4];
};

#endif // __HELLOWORLD_SCENE_H__

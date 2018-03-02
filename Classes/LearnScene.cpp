#include "LearnScene.h"
#include "cocostudio\CocoStudio.h"
#include "ui\UIButton.h"
#include "tinyxml2\tinyxml2.h"
#include "sqlite3.h"
#include <iostream>
//#include "reader/CreatorReader.h"

USING_NS_CC;

cocos2d::Scene * LearnScene::createScene()
{
	auto scene = Scene::create();
	auto learn = LearnScene::create();

	scene->addChild(learn);

	return scene;
}

bool LearnScene::init()
{
	if (!Layer::init())
		return false;

	//AboutParallexNode();
	//AboutSimpleAudioEffect();
	//AboutFrameCallback();
	//AboutBlend();
	//AboutRotAndPosTransmit();
	//dump();
	//AboutTemplate();
	//getRecFromZip();	
	//aboutCsb();
	//aboutRemoveSelf();
	//AboutHttp();
	//AboutWebSocket();
	//AboutZipFile();
	//AboutOperation();
	//AboutCopyConstructor();
	//AboutAllocator();
	//AboutStdMove();
	//AboutIOStream();
	//AboutSth();
	//AboutMacro();
	//About2DLight();
	//AboutSqlite();

	_sp = Sprite::create("green.png");
	_sp->setPosition(300, 300);
	this->addChild(_sp);

	AboutCallfunc();
	
	return true;
}

void LearnScene::AboutParallexNode()
{
	_parallex = ParallaxNode::create();
	addChild(_parallex);

	auto sp = Sprite::create("HelloWorld.png");
	_parallex->addChild(sp, 2, Vec2(1.f, 0), Vec2(480, 320));

	sp = Sprite::create("mario.png");
	_parallex->addChild(sp, 1, Vec2(0.8f, 0), Vec2(480, 320));

	schedule(CC_SCHEDULE_SELECTOR(LearnScene::parallexMove), 1 / 30.f);
}

void LearnScene::parallexMove(float dt)
{
	_parallex->setPosition(_parallex->getPosition() + Vec2(5, 0));
}

#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

void LearnScene::AboutSimpleAudioEffect()
{
	using namespace CocosDenshion;
	using namespace experimental;

	FileUtils::getInstance()->addSearchPath("sound");

	SimpleAudioEngine::getInstance()->preloadEffect("attack.mp3");
	auto id = SimpleAudioEngine::getInstance()->playEffect("attack.mp3");
	log("%u", id);
	id = SimpleAudioEngine::getInstance()->playEffect("attack.mp3");
	log("%u", id);

	
}

void LearnScene::AboutBlend()
{
	FileUtils::getInstance()->addSearchPath("AboutBlend");

	Sprite* bg = Sprite::create("bg_1.jpg");
	bg->setAnchorPoint(Vec2::ZERO);
	addChild(bg);

	ClippingNode* clipNode = ClippingNode::create();
	clipNode->setPosition(Vec2(200, 200));
	clipNode->setStencil(Sprite::create("zombie.png"));
	addChild(clipNode);
	clipNode->setAlphaThreshold(0.1f);

	Sprite* sp = Sprite::create("zombie.png");
	//sp->setPosition(Vec2(300, 400));
	clipNode->addChild(sp);


	Sprite* ice = Sprite::create("hurted.png");
	//ice->setPosition(Vec2(300, 400));
	BlendFunc cbl = { GL_DST_COLOR, GL_ONE };
	ice->setBlendFunc(cbl);
	clipNode->addChild(ice);

}

void LearnScene::AboutFrameCallback()
{
	FileUtils::getInstance()->addSearchPath("naruto");


	auto csb = CSLoader::createNode("Enemy_1.csb");
	addChild(csb);

	auto timeline = CSLoader::createTimeline("Enemy_1.csb");
	csb->runAction(timeline);

	timeline->play("appear", true);
	timeline->setFrameEventCallFunc([](cocostudio::timeline::Frame* ){
		log("123");
	});
}

template  <typename T>
int compare(const T& a, const T& b)
{
	if (std::less<T>() (a , b)) return 1;
	if (std::less<T>()(b, a)) return -1;
	return 0;
}


template <typename T, typename N>
T t_find(T range_a, T range_b, const N& val)
{
	for (auto iter = range_a; iter != range_b; iter++)
	{
		if (*iter == val)
			return iter;
	}
	return range_b;
	
}

template <typename Arr, size_t N>
Arr* t_begin(Arr(&a)[N])
{
	return a;
}

template <typename T>
auto inline t_begin(const T& a)->decltype(a.begin())
{
	return a.begin();
}

template<typename T, ssize_t N>
constexpr ssize_t arraySize(T(&arr)[N])
{
	return N;
}


template<typename T>
class ABCD : public cocos2d::Node
{
public:
	ABCD() = default;
	ABCD(int index) : _index(index) {}
	static T * createWithIndex(int index);
protected:
	int _index;
};

template<typename T>
T * ABCD<T>::createWithIndex(int index)
{
	T* t = new(std::nothrow) T;
	if (t && t->init())
	{
		t->autorelease();
		return t;
	}
	CC_SAFE_DELETE(t);
	return nullptr;
}

class Testa : public ABCD<Testa> {
public:
	Testa() {};
};


void LearnScene::AboutTemplate()
{
	//A a1, a2;
	//compare(a1, a2);

	//std::vector<int> vec{ 1, 2, 3, 4, 5 };
	//auto iter = t_find(vec.begin(), vec.end(), 2);
	//if (iter != vec.end())
	//	log("find it : %d", *iter);
	//else
	//	log("can't find");

	/*int a[10];
	t_begin(a);
	std::vector<int> b;
	t_begin(b);*/

	//int a[10];
	//log("%d", arraySize(a));

	auto t = Testa::createWithIndex(1);
}

void LearnScene::dump()
{
	FileUtils::getInstance()->addSearchPath("skill");

	auto spri = Sprite::create("brokenBrick.png");
	//spri->setPosition(0, 0);
	spri->setScale(2.f);
	addChild(spri);


	auto clip = ClippingNode::create(LayerColor::create(Color4B::BLACK, 73, 70));
	clip->setAlphaThreshold(0.5f);
	clip->setPosition(Vec2(300, 100));
	addChild(clip);
	
	auto node = Node::create();
	int i = 0;
	for ( i ; i < 15; i++)
	{
		auto rand = random(1, 24);
		auto sprite = Sprite::create(String::createWithFormat("skill_%d.png", rand)->getCString());
		sprite->setAnchorPoint(Vec2::ZERO);
		sprite->setPosition(0, -70 * i);
		node->addChild(sprite);
	}

	clip->addChild(node);

	auto btn = ui::Button::create("brokenBrick.png");
	btn->addTouchEventListener([node, i, spri](Ref*, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//spri->setAnchorPoint(Vec2(1, 1));
			node->runAction(EaseOut::create(MoveBy::create(1.5f, Vec2(0, 70 * (i - 1))), 2.f));
		}
	});
	btn->setPosition(Vec2(400.f , 300.f));
	addChild(btn);


	auto bar = ProgressTimer::create(Sprite::create("mario.png"));
	bar->setType(ProgressTimer::Type::BAR);
	bar->setBarChangeRate(Vec2(1, 0));
	bar->setMidpoint(Vec2(0, 0.5f));
	bar->setPercentage(80);
	bar->setPosition(500, 300);
	addChild(bar);

	bar->runAction(ProgressFromTo::create(3.0f, 80, 20));
}


void LearnScene::getRecFromZip()
{
	auto dialog = LayerColor::create(Color4B::MAGENTA);
	dialog->setOpacity(100);
	addChild(dialog);

	auto btn = ui::Button::create("vortex.png");
	btn->addTouchEventListener([](Ref*, ui::Widget::TouchEventType type) {if (type == ui::Widget::TouchEventType::ENDED) log("1"); });
	btn->setPosition(Vec2(200, 300));
	dialog->addChild(btn);

	dialog = LayerColor::create(Color4B::GRAY);
	dialog->setOpacity(100);
	addChild(dialog);
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch*, Event*) {log("q"); return true; };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, dialog);


	//btn = ui::Button::create("tree2.png");
	//btn->addTouchEventListener([](Ref*, ui::Widget::TouchEventType type) {if (type == ui::Widget::TouchEventType::ENDED) log("2"); });
	//btn->setPosition(Vec2(220, 300));
	//addChild(btn, 2);
}

Node* createNodeFromData(std::map<std::string, std::string>& data)
{
	if (data.empty())
		return nullptr;

	auto type = data["type"];
	Node* node = nullptr;
	if (type == "btn")
	{
		auto btn = ui::Button::create(data["filename"]);
		auto cptype = data["cptype"];
		btn->setZoomScale(-0.1f);
		btn->addTouchEventListener(
			[btn, cptype](Ref*, ui::Widget::TouchEventType type) {
				if (type == ui::Widget::TouchEventType::ENDED) { 
					if (!cptype.empty())
						log("apply %s", cptype.c_str());

					btn->getParent()->removeFromParent();
			}
		});

		node = btn;
	}
	else
	{
		node = Sprite::create(data["filename"]);
	}

	node->setScale(data["scale"].empty() ? 1.0f : atof(data["scale"].c_str()));
	node->setRotation(data["rotation"].empty() ? 0 : atof(data["rotation"].c_str()));
	node->setOpacity(data["alpha"].empty() ? 255 : atof(data["alpha"].c_str()));
	node->setLocalZOrder(data["order"].empty() ? 0 : atoi(data["order"].c_str()));
	auto pos = data["position"];
	auto x = atof(pos.substr(0, pos.find(",")).c_str());
	auto y = atof(pos.substr(pos.find(",") + 1).c_str());
	node->setPosition(x, y);
	Action* act = nullptr;
	if (!data["action"].empty())
	{
		auto actType = data["action"];
		if (actType == "breath")
		{
			auto scale = node->getScale();
			act = RepeatForever::create(
				Sequence::create(
					ScaleTo::create(0.2f, scale + 0.1f),
					ScaleTo::create(0.2f, scale - 0.1f),
					nullptr
				)
			);
		}
		else if(actType == "rotate")
		{
			act = RepeatForever::create(
				RotateBy::create(0.3f, 360)
			);
		}
	}

	if (act)
		node->runAction(act);

	return node;
}

class B
{
public :
	B(int) { cocos2d::log("constructor"); }
	B(const B&) { cocos2d::log("copy constrctor"); }
	~B() { cocos2d::log("destructor"); }
};

void BB(B b)
{
	//B a = b;
	//return b;
	return;
}

void LearnScene::aboutCsb()
{
	//B a;
	//B b(a);
	//B b = a;
	BB(2);

	return;
	auto chargeNode = Node::create();
	addChild(chargeNode);
	tinyxml2::XMLDocument doc;
	auto filepath = FileUtils::getInstance()->fullPathForFilename("script1.xml");
	log("path : %s", filepath.c_str());
	if (doc.LoadFile(filepath.c_str()) != tinyxml2::XML_NO_ERROR)
	{
		log("can't find file");
		return;
	}

	auto rootElement = doc.RootElement();
	auto child = rootElement->FirstChildElement();
	while (child)
	{
		auto grandChild = child->FirstChildElement();
		std::map<std::string, std::string> data;
		while (grandChild)
		{
			auto name = grandChild->Name();
			auto text = grandChild->GetText();
			data[name] = text;
			grandChild = grandChild->NextSiblingElement();
		}
		auto node = createNodeFromData(data);
		if(node)
			chargeNode->addChild(node);

		child = child->NextSiblingElement();
	}
}

void LearnScene::aboutRemoveSelf()
{
	auto sp = Sprite::create("tree2.png");
	//addChild(sp);
	sp->retain();
	//runaction如果node不存在会进行retain一次
	sp->runAction(Sequence::create(
		MoveTo::create(0.5f, Vec2(100, 100)),
		CallFuncN::create([](cocos2d::Node* node) {
		node->pause(); 
	}),
		CallFunc::create([]() { log("haha"); }),
		nullptr
	));
}


bool LearnScene::unCompress(const std::string& fileName, const std::string& passWord)
{
	
	return false;
}

#include "network\HttpRequest.h"
#include "network\HttpClient.h"
#include "network\HttpResponse.h"
void LearnScene::AboutHttp()
{
	auto callback = [](network::HttpClient* client, network::HttpResponse* response)
	{
		log("response code  is %d", response->getResponseCode());
		if (response->isSucceed())
		{
			auto str = response->getResponseData();
			std::string context;
			for (const auto& alphabet : *str)
			{
				context.push_back(alphabet);
			}
			log("%s", context.c_str());
		}
	};

	auto request = new network::HttpRequest();
	request->setUrl("http://cl.mobile.ufo78.com/show.aspx?Key=100_201709070410553210_283590");
	request->setRequestType(network::HttpRequest::Type::GET);
	//char data[50] = "abcd";
	//data[0] = 'c';
	//request->setRequestData(data, strlen(data));
	request->setResponseCallback(callback);


	//Client
	auto client = network::HttpClient::getInstance();
	client->setTimeoutForConnect(30);
	client->setTimeoutForRead(100);
	client->send(request);
	request->release();

	auto postReq = new network::HttpRequest();
	postReq->setUrl("http://httpbin.org/post");
	postReq->setRequestType(network::HttpRequest::Type::POST);
	const char* postData = "controller=Joe&action=testHttpPost";
	postReq->setRequestData(postData, strlen(postData));
	postReq->setResponseCallback(callback);


	//client->send(postReq);
	postReq->release();
}

#include "network/WebSocket.h"

class Snake : public network::WebSocket::Delegate
{
public :
	virtual void onOpen(network::WebSocket* ws)
	{
		log("websocket open %p", ws);
	}
	virtual void onMessage(network::WebSocket* ws, const network::WebSocket::Data& data)
	{
		log("websocket send message %p", ws);
		if (!data.isBinary)
		{
			std::string str(data.bytes);
			log("%s", str.c_str());
		}
	}
	virtual void onClose(network::WebSocket* ws)
	{
		log("websocket close %p", ws);
	}
	virtual void onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error)
	{
		log("websocket oerror %p", ws);
	}
};

void LearnScene::AboutWebSocket()
{
	auto snake = new Snake();
	auto websocket = new network::WebSocket();

	auto menu = Menu::create();
	addChild(menu);

	auto label = MenuItemLabel::create(Label::create("init socket", "Arial", 40), [websocket, snake](cocos2d::Ref*) {
		if (!websocket->init(*snake, "ws://echo.websocket.org"))
		{
			delete websocket;
			//delete snake;
		}
	});
	menu->addChild(label);

	label = MenuItemLabel::create(Label::create("send Mes", "Arial", 40), [websocket](cocos2d::Ref*) {
			websocket->send("Hello world");
	});
	menu->addChild(label);

	menu->alignItemsVertically();
}

void LearnScene::AboutZipFile()
{
	ZipFile zip("zz.zip");
	auto filename = zip.getFirstFilename();
	log("filename : %s", filename.c_str());
}

void LearnScene::AboutRotAndPosTransmit()
{
	auto sp = Sprite::create("HelloWorld.png");
	sp->setRotation(30);
	sp->setPosition(300, 200);
	addChild(sp);
	auto ssp = Sprite::create("HelloWorld.png");
	ssp->setPosition(300, 300);
	sp->addChild(ssp);
	log("rotation: %f", ssp->getRotation());
	//runAction(Sequence::create(
	//	DelayTime::create(0),
	//	CallFunc::create([this, ssp]() {
	//			ssp->retain();
	//			auto rotation = ssp->getParent()->getRotation();
	//			auto location = ssp->getParent()->convertToWorldSpace(ssp->getPosition());
	//			ssp->removeFromParentAndCleanup(false);
	//			ssp->setPosition(location);
	//			ssp->setRotation(rotation);
	//			this->addChild(ssp);
	//		}),
	//	nullptr
	//));

}

void macroTwoParameters(int a,int b)
{
	cocos2d::log("a:%d , b:%d", a, b);
}
#define TP(para1, para2) macroTwoParameters(para1, para2)

void LearnScene::AboutMacro()
{
	TP(1, 2);
}

struct Segment
{
	Segment(Vec2 from, Vec2 to) :start(from), end(to) {}
	Segment() = default;
	Vec2 start;
	Vec2 end;
};

float intersection(Segment light, Segment segment)
{
	auto t1_x = light.end.x - light.start.x;
	auto t1_y = light.end.y - light.start.y;
	auto t2_x = segment.end.x - segment.start.x;
	auto t2_y = segment.end.y - segment.start.y;

	//平行
	if (Vec2(t1_x, t1_y).getNormalized() == Vec2(t2_x, t2_y).getNormalized())
	{
		return -1;
	}

	auto t2 = (t1_x * (segment.start.y - light.start.y) + t1_y * (light.start.x - segment.start.x)) / (t2_x * t1_y  - t2_y * t1_x);
	float t1 = (segment.start.x + t2_x * t2 - light.start.x) / t1_x;

	 if (t2 < 0 || t2 > 1 || t1 < 0)
		 return -1;
	 else
		 return t1;
}

void LearnScene::About2DLight()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto drawNode = DrawNode::create();
	this->addChild(drawNode);

	std::vector<Segment> segments;

	Vec2 rect[4] = {
		Vec2(200, 100),
		Vec2(200, 400),
		Vec2(400, 400),
		Vec2(400, 100)
	};
	
	Vec2 polygon[3] = {
		Vec2(800, 100),
		Vec2(900, 300),
		Vec2(850, 50)
	};

	Vec2 poly[4] = {
		Vec2(50, 600),
		Vec2(120, 550),
		Vec2(160, 80),
		Vec2(30, 30)
	};

	Vec2 window[4] = 
	{
		Vec2(0, 0),
		Vec2(0, size.height),
		Vec2(size.width, size.height),
		Vec2(size.width, 0)
	};

	drawNode->drawPoly(rect, 4, true, Color4F::WHITE);
	drawNode->drawPoly(polygon, 3, true, Color4F::WHITE);
	drawNode->drawPoly(poly, 4, true, Color4F::WHITE);
	drawNode->drawPoly(window, 4, true, Color4F::WHITE);

	segments.emplace_back(rect[0], rect[1]);
	segments.emplace_back(rect[1], rect[2]);
	segments.emplace_back(rect[2], rect[3]);
	segments.emplace_back(rect[3], rect[0]);

	segments.emplace_back(polygon[0], polygon[1]);
	segments.emplace_back(polygon[1], polygon[2]);
	segments.emplace_back(polygon[2], polygon[0]);

	segments.emplace_back(poly[0], poly[1]);
	segments.emplace_back(poly[1], poly[2]);
	segments.emplace_back(poly[2], poly[3]);
	segments.emplace_back(poly[3], poly[0]);

	segments.emplace_back(window[0], window[1]);
	segments.emplace_back(window[1], window[2]);
	segments.emplace_back(window[2], window[3]);
	segments.emplace_back(window[3], window[0]);

	std::set<Vec2> allPoints;
	//所有点
	for (auto i = 0; i < segments.size(); i++)
	{
		allPoints.insert(segments.at(i).start);
		allPoints.insert(segments.at(i).end);
	}

	auto drawLight = DrawNode::create();
	this->addChild(drawLight);

	auto mouse = EventListenerMouse::create();
	mouse->onMouseMove = [=](EventMouse* event) {
		drawLight->clear();
		
		auto pos = Vec2(event->getCursorX(), event->getCursorY());
		std::vector<Segment> allLights;
		std::vector<Vec2> drawPoint;

		for(auto iter = allPoints.begin(); iter != allPoints.end(); iter++)
		{
			auto point1 = (*iter).rotateByAngle(pos, CC_DEGREES_TO_RADIANS(0.01f));
			auto point2 = (*iter).rotateByAngle(pos, CC_DEGREES_TO_RADIANS(-0.01f));
			allLights.emplace_back(pos, point1);
			allLights.emplace_back(pos, point2);
		}

		for (auto i = 0; i < allLights.size(); i++)
		{
			float distance = -1;
			for (auto j = 0; j < segments.size(); j++)
			{
				auto dis = intersection(allLights.at(i), segments.at(j));
				if (dis == -1)
				{
					continue;
				}
				else
				{
					if (distance == -1)
						distance = dis;
					else
						distance = distance < dis ? distance : dis;
				}
			}
			Vec2 to;
			if (distance == -1)
			{
				to = allLights.at(i).start + (allLights.at(i).end - allLights.at(i).start).getNormalized() * 1000;
			}
			else
			{
				to = allLights.at(i).start + (allLights.at(i).end - allLights.at(i).start) * distance;
			}
			
			drawLight->drawSegment(allLights.at(i).start, to, 1, Color4F::RED);
			drawPoint.push_back(to);
		}
		
		std::sort(drawPoint.begin(), drawPoint.end(), [pos](Vec2 one, Vec2 two) {
			auto angle_1 = (one - pos).getAngle();
			auto angle_2 = (two - pos).getAngle();
			return angle_1 > angle_2;
		});

		for (auto i = 0; i < drawPoint.size(); i++)
		{
			auto next = i == drawPoint.size() - 1 ? 0 : i + 1;
			Vec2 triangle[3] =
			{
				pos,
				drawPoint.at(i),
				drawPoint.at(next)
			};
			drawLight->drawPolygon(triangle, 3,  Color4F(1.0f, 0.f, 0.f, 0.5f), 0, Color4F::MAGENTA);
		}

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouse, this);
}

int select_callback(void * user, int argc, char ** argv, char** azColName)
{
	//int i;
	//fprintf(stderr, "%s: ", (const char*)data);
	auto ls = static_cast<LearnScene*>(user);
	auto id = -1;
	for (int i = 0; i < argc; i++)
	{
		if (std::strcmp(azColName[i], "id") == 0)
		{
			id = atoi(argv[i]);
			ls->_dataBase[id].id = id;
		}
		else if (std::strcmp(azColName[i], "username") == 0)
		{
			ls->_dataBase[id].username = std::string(argv[i]);
		}
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void LearnScene::AboutSqlite()
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;

	auto fileName = FileUtils::getInstance()->fullPathForFilename("mydata.db");

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto writePath = FileUtils::getInstance()->getWritablePath() + "mydata.db";
	FILE* p = fopen(writePath.c_str(), "r");
	if (!p)
	{
		p = fopen(writePath.c_str(), "wb");
		Data data = FileUtils::getInstance()->getDataFromFile("mydata.db");
		fwrite(data.getBytes(), data.getSize(), 1, p);
	}
	fclose(p);
	fileName = writePath;
#endif

	rc = sqlite3_open(fileName.c_str(), &db);
	if (rc)
	{
		log("Can't open database: %s", sqlite3_errmsg(db));
		return;
	}
	else
	{
		log("Opened database successfully");
	}

	std::string sqlite_terminal = "SELECT * FROM USER";
	rc = sqlite3_exec(db, sqlite_terminal.c_str(), &select_callback, (void*)this, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		log("SQL error: %s \n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		log("Operation done successfully\n");
	}

	for (auto& info : _dataBase)
	{
		log("id: %d  name : %s", info.second.id, info.second.username.c_str());
	}

	sqlite3_close(db);
}

void LearnScene::AboutCallfunc()
{
	static int a = 0;
	if (a == 0)
	{
		//scheduleUpdate();
	}

	log("callfunc__%d", a++);
	CC_SAFE_RELEASE(_seq);
	_seq = Sequence::create(
		DelayTime::create(.2f),
		CallFunc::create(CC_CALLBACK_0(LearnScene::callbackFunc, this)),
		nullptr
	);
	_sp->runAction(_seq);
	CC_SAFE_RETAIN(_seq);
	
}

void LearnScene::callbackFunc()
{
	log("callback func");
	log("action num %d", _sp->getNumberOfRunningActions());
	this->AboutCallfunc();
	log("action num %d", _sp->getNumberOfRunningActions());
}

void LearnScene::update(float dt)
{
	log("rest time : %f", _seq->getElapsed());
}

class AO
{
	friend AO operator+ (const AO& a, const AO& b);
	friend std::ostream& operator<< (std::ostream& os, const AO&);
	friend std::istream& operator >> (std::istream& is, AO*);
public:
	AO(int a) :_a(a) {}
	//AO& operator +(const AO& obj)
	//{
	//	_a += obj._a;
	//	log("member function");
	//	return *this;
	//}

	AO& operator+= (const AO& obj)
	{
		_a += obj._a;
		return *this;
	}

	AO& operator++()
	{		
		++_a;
		return *this;
	}

	AO& operator++(int)
	{
		_a++;
		return *this;
	}

private:
	int _a;
};

std::ostream& operator<< (std::ostream& os, const AO& a)
{
	return os << "a: " << a._a;
}

AO operator + (const AO& a, const AO& b)
{
	log("global function");
	return (a._a + b._a);
}

std::istream& operator >> (std::istream& is, AO* ao)
{
	return std::cin >> ao->_a;
}

void LearnScene::AboutOperation()
{
	AO a(2);
	AO b(2);
	a = a + b;
	auto c = a + b;
	std::cout << a << std::endl;
	a += b;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	//std::cin >> &a;

}

class ACC
{
public:
	ACC() { log("default construct!"); }
	ACC(const ACC&) { log("copy construct!"); }
};

ACC tesT(ACC acc)
{
	return acc;
}

void LearnScene::AboutCopyConstructor()
{
	ACC ac;
	ACC ad = ac, *ap = new ACC(ac);
	*ap = ad;
	ACC arr[4] = { ad, *ap };

	//右值引用
	int &&a = 3;
	a = 4;
}

#include <memory>
void LearnScene::AboutAllocator()
{
	std::vector<int> a{ 1,2,3, 4, 5, 6, 7 };
	std::allocator<int> allo;
	auto pS = allo.allocate(a.size() * 2);
	auto pT = pS;
	auto pC = std::uninitialized_copy(a.begin(), a.end(), pS);
	std::uninitialized_fill(pC, pC + 5, 10);
	while (pT != pC + 5)
		log("%d", *(pT++));
	std::allocator<std::string> alloc;
	auto const p = alloc.allocate(10);
	auto q = p;
	alloc.construct(q++);
	alloc.construct(q++, 10, 'c');
	alloc.construct(q++, "hi");
	log("%s", (p + 1)->c_str());
	//error unconstruct!
	//log("%s", q->c_str());
	while (q != p)
		alloc.destroy(--q);
	alloc.deallocate(p, 10);
}

void LearnScene::AboutStdMove()
{
	std::string a ="3";
	auto b = std::move(a);
	//a = "4";
	log("a : %s, b : %s", a.c_str(), b.c_str());
}

#include <iostream>
#include <fstream>
std::istream& getStream(std::istream& is)
{
	int a = 0;
	while (!is.eof())
	{
		is >> a;
		std::cout << "a :" << a << std::endl;
	}
	
	is.clear();
	std::cout << "stream is clear" << std::endl;

	return is;
}

void LearnScene::AboutIOStream()
{

	//getStream(std::cin);
	std::string path = "C:./Users/Administrator/Desktop/pic2/ab.txt";
	std::ifstream fs(path);
	std::string line = "";
	std::vector<std::string> vecStr;
	if (fs.is_open())
	{
		while (!fs.eof())
		{
			fs >> line;
			std::cout << "push back : " << line << std::endl;
			vecStr.push_back(std::move(line));
		}
	}

}

class BASE
{
	friend void invite(const BASE& pub);
public:
	virtual void pub() const { cocos2d::log("pub"); }
protected:
	virtual void pro()const { cocos2d::log("pro"); }
private:
	virtual void pri()const { cocos2d::log("pri"); }
};

void invite(const BASE& pub)
{
	pub.pri();
	pub.pro();
	pub.pri();
}

class PUB : public BASE
{
	friend void pub_invite(const PUB& pub);
public:
	virtual void pub() const override { cocos2d::log("pub_pub"); BASE::pub(); }
protected:
	virtual void pro()const override { cocos2d::log("pub_pro"); BASE::pro(); }
private:
	virtual void pri()const override { cocos2d::log("pub_pri"); /*pri();*/ }
};

void pub_invite(const PUB& pub)
{
	pub.pub();
	pub.pro();
	pub.pri();
	pub.BASE::pub();
	pub.BASE::pro();
}

class PRO : protected BASE
{
	friend void pro_invite(const PRO& pub);
public:
	virtual void pub() const override { cocos2d::log("pro_pub"); BASE::pub(); }
protected:
	virtual void pro()const override { cocos2d::log("pro_pro"); BASE::pro(); }
private:
	virtual void pri()const override { cocos2d::log("pro_pri");  }
};

void pro_invite(const PRO& pub)
{
	pub.pub();
	pub.pro();
	pub.pri();
	pub.BASE::pub();
	pub.BASE::pro();
}

class PRI : private BASE
{
	friend void pri_invite(const PRI& pub);
public:
	virtual void pub() const override { cocos2d::log("pub_pub"); BASE::pub(); }
protected:
	virtual void pro()const override { cocos2d::log("pub_pro"); BASE::pro(); }
private:
	virtual void pri()const override { cocos2d::log("pub_pri"); }
};

void pri_invite(const PRI& pub)
{
	pub.pub();
	pub.pro();
	pub.pri();
	pub.BASE::pub();
	pub.BASE::pro();
}

class Tank 
{
public:
	int a;
	void go() { as(); }
private:
	int b;
protected:
	int c;
	virtual void as() { cocos2d::log("tank"); }
};

class Brand : public Tank
{
public :
	using Tank::a;
	void as() { cocos2d::log("brand"); }
};

class Band : public Brand
{
public:
	using Brand::a;
};

void LearnScene::AboutSth()
{
	/*
	PRI a;
	pri_invite(a);
	PRO b;
	pro_invite(b);
	PUB c;
	pub_invite(c);
	*/
	Tank* br = new Brand();
	br->go();
}



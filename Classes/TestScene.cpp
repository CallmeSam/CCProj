#include "TestScene.h"
#include "ui\UIWidget.h"
#include "tinyxml2\tinyxml2.h"
#include "cocostudio\CocoStudio.h"
#include "HelloWorldScene.h"
#include "ui\UIHelper.h"

#include "json\rapidjson.h"
#include "json\document.h"
#include "json\prettywriter.h"
#include "json\stringbuffer.h"

#include "tinyxml2\tinyxml2.h"

#include "chipmunk.h"

using namespace rapidjson;

using namespace cocostudio;
USING_NS_CC;

cocos2d::Scene * TestScene::createScene()
{
	Scene* scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setAutoStep(false);
	//scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_SHAPE);

	auto layer = TestScene::create();
	scene->addChild(layer);
	return scene;
}

bool TestScene::init()
{
	if (!Layer::init())
		return false;
	
	//AboutBoundingBox();
	//AboutWidget();
	//AboutSTLMap();
	//AboutSTLSet();
	//AboutSTLFind();
	//AboutSTLFind_If();
	//AboutSTLFor_each();
	//AboutTemplate();
	//AboutArmature();
	//AboutUIButtonClick();
	//AboutJson();
	//AboutXml();
	//AboutFilePointer();
	//AboutSTLDeque();
	//AboutPraseCSV();
	//AboutSwap();
	//AboutAudioEngine();
	//ScaleAndPos();
	
	//AboutRecursiveJson();

	//testFormat();

	//AboutClassAssignment();

	//testFilePointer();
	//testIOstream();
	//AboutSharedPtr();
	//AboutUniquePtr();
	//AboutWeakPtr();
	//AboutTools();
	//testXml();

	//testForAdapt();
	//testForContact();
	//testForTC();
	//AboutLinkList();
	//dumpPhysics();
	//AboutCameraAndRender();
	//AboutActionManager();
	dumpOrCamera();

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [](EventKeyboard::KeyCode code, Event* event) 
	{
		if (code == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			Director::getInstance()->end();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void TestScene::AboutBoundingBox()
{
	FileUtils::getInstance()->addSearchPath("player");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sxcc.plist");

	Sprite* sp = Sprite::create("run3.png");
	addChild(sp);
	log("size1:%f--%f", sp->getBoundingBox().size.width, sp->getBoundingBox().size.height);
	
	sp = Sprite::create("run1.png");
	sp->setPosition(Vec2(100, 200));
	sp->setTag(10);
	sp->setName("hehe");
	addChild(sp);
	log("size2:%f--%f", sp->getBoundingBox().size.width, sp->getBoundingBox().size.height);

	Vector<SpriteFrame*> frames;
	
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("run3.png");
	frames.pushBack(frame);
	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("run4.png");
	frames.pushBack(frame);
	//Animation* animation = Animation::create();
	//animation->addSpriteFrameWithFileName("run3.png");
	//animation->addSpriteFrameWithFileName("run4.png");	
	
	Animation* animation = Animation::createWithSpriteFrames(frames);
	//animation->setLoops(-1);
	animation->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(animation, "run");
	Animate* animate = Animate::create(animation);
	//sp->runAction(animate);
	
	ui::Button* btn = ui::Button::create("CloseNormal.png");
	btn->setPosition(Vec2(200, 100));
	btn->addTouchEventListener(CC_CALLBACK_2(TestScene::run, this));
	addChild(btn);
	schedule(CC_SCHEDULE_SELECTOR(TestScene::boundingTest), 0.1f);
}

void TestScene::boundingTest(float dt)
{
	Sprite* node = (Sprite*)this->getChildByTag(10);
	auto act = node->getActionByTag(200);
	if (act)
	{
		Animate* animate = dynamic_cast<Animate*>(act);
		log("%d", animate->getCurrentFrameIndex());
	}
	//log("size:%f--%f", node->getSpriteFrame()->getOriginalSizeInPixels().width, node->getSpriteFrame()->getOriginalSizeInPixels().height);
}

void TestScene::run(cocos2d::Ref *, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		Sprite* node = (Sprite*)this->getChildByTag(10);
		node->stopAllActions();
		Animation* animation = AnimationCache::getInstance()->getAnimation("run");
		Animate* animate = Animate::create(animation);
		animate->setTag(200);
		//auto act = MoveBy::create(1.0, Vec2(200, 0));
		//act->setTag(200);
		node->runAction(animate);
	}
	
}

void TestScene::onEnter()
{
	Layer::onEnter();

	this->getScene()->getPhysicsWorld()->step(0.f);
}

void TestScene::AboutWidget()
{
	auto color = LayerColor::create(Color4B::BLUE, 100, 100);
	color->setPosition(Vec2(200, 200));
	addChild(color);

	ui::Widget* wid = ui::Widget::create();
	wid->setContentSize(Size(100, 100));
	wid->setPosition(Vec2(200, 200));
	wid->setTouchEnabled(true);
	wid->addTouchEventListener([](Ref*, ui::Widget::TouchEventType type) {log("haha"); });
	addChild(wid);
}

void TestScene::AboutSTLDeque()
{
	std::deque<int> deque{1, 2, 3, 4, 5};
	deque.pop_front();
	for (auto num : deque)
	{
		log("%d", num);
	}
}

void TestScene::AboutSTLMap()
{
	std::map<const char*, float > a;
	std::map<const char*, float>::iterator it;
	a["Num"] = 2.2f;
	a["go"] = 20.f;
	//上述会存在效率问题
	a.insert(std::pair<const char*, float>("No.", 10.f));
	//a.erase("go");
	it = a.find("go");
	if (it == a.end())
	{
		log("holly shit");
	}
	else
	{
		log("%f", (*it).second);
	}
}

struct Person
{
public:
	int a;
	int b;
	Person(int c, int d) :a(c), b(d) {}
	bool operator < (const Person& person) const
	{
		if (a == person.a)
			return b < person.b;
		else
			return a < person.a;
	}
};

struct PersonCmp
{
public:
	bool operator ()(const Person& a, const Person& b) const 
	{
		if (a.a == b.a)
			return a.b < b.b;
		else
			return a.a < b.a;
	}
};


bool cmp(Person a, Person b)
{
	if (a.a == b.a)
		return a.b < b.b;
	else
		return a.a < b.a;
}

void TestScene::AboutSTLSet()
{
	//-------------------------------Normal
	std::set<int> com;
	com.insert(18);
	com.insert(10);
	com.insert(5);
	for (auto iter = com.rbegin(); iter != com.rend(); iter++)
	{
		log("%d", *iter);
	}

	std::set<const char*> str;
	str.insert("abck");
	str.insert("abcd");
	str.insert("zskn");
	for (auto iter = str.rbegin(); iter != str.rend(); iter++)
	{
		log("%s", *iter);
	}

	//-------------------------------------custom1
	Person p1(1, 2), p2(3, 4), p3(1, 9);
	std::set<Person> per;
	per.insert(p1);
	per.insert(p2);
	per.insert(p3);

	for (auto iter = per.begin(); iter != per.end(); iter++)
	{
		log("%d", (*iter).b);
	}
	//-------------------------------------custom2
	std::set<Person, bool(*)(Person, Person)> pp(cmp);
	pp.insert(p1);
	pp.insert(p2);
	pp.insert(p3);

	for (auto iter = pp.begin(); iter != pp.end(); iter++)
	{
		log("-----%d", (*iter).b);
	}

	//-------------------------------------custom3
	std::set<Person, PersonCmp> pc;
	pc.insert(p1);
	pc.insert(p2);
	pc.insert(p3);

	for (auto iter = pc.begin(); iter != pc.end(); iter++)
	{
		log("&&&&%d", (*iter).b);
	}

}

struct Find
{
public:
	Find(const char* a, int b):b(a), a(b)  {}
	int a;
	const char* b;
	bool operator ==(const Find& find)
	{
		return a == find.a && strcmp(b, find.b) == 0;
	}
};

void TestScene::AboutSTLFind()
{
	int a[] = { 20, 30, 10, 200, 1 };
	int* iter = std::find(a, a + 5, 300);
	if (iter == a + 5)
	{
		log("bad!");
	}
	else
		log("%d", *iter);

	std::vector<int> b(a, a + 3);
	std::vector<int>::iterator it;
	it = std::find(b.begin(), b.end(), 20);
	if (it == b.end())
		log("holly");
	else
		log("%d", *it);

	//自定义
	std::vector<Find> fd;
	std::vector<Find>::iterator itr;
	fd.push_back(Find("baby", 1));
	fd.push_back(Find("std", 2));
	itr = std::find(fd.begin(), fd.end(), Find("baby", 1));
	if (itr == fd.end())
	{
		log("noob");
	}
	else
		log("%s--%d", (*itr).b, (*itr).a);

}

bool com(std::map<int ,  int>::value_type type)
{
	return type.second > 2;
}

struct Find_If
{
public:
	Find_If(int b) :b(b) {}
	int b;
	bool operator ()(std::vector<Find_If>::value_type type)
	{
		return type.b > b;
	}
};

struct Fif
{
public:
	bool operator() (std::map<int, int>::value_type type)
	{
		return type.second > 2;
	}
};

void TestScene::AboutSTLFind_If()
{
	//函数指针
	std::map<int, int> maps;
	std::map<int, int>::iterator it;
	std::map<int, int>::iterator iterat;
	maps[1] = 2;
	maps[2] = 3;
	it = std::find_if(maps.begin(), maps.end(), com);
	iterat = std::find_if(maps.begin(), maps.end(), Fif());
	log("%d", (*it).first);
	log("iterat:%d", (*iterat).first);
	//lamda
	std::vector<int> vec;
	std::vector<int>::iterator iter;
	vec.push_back(2);
	vec.push_back(10);
	int a[] = { 3, 4,5 ,6 };
	iter = std::find_if(vec.begin(), vec.end(), [](const int & a)->bool {return a > 5; });
	log("%d", *iter);
	//struct
	std::vector<Find_If> ff;
	std::vector<Find_If>::iterator itera;
	ff.push_back(Find_If(2));
	ff.push_back(Find_If(12));
	ff.push_back(Find_If(2));
	ff.push_back(Find_If(22));
	itera = std::find_if(ff.begin(), ff.end(), Find_If(5));
	log("%d", *itera);
}

struct For_Each
{
public:
	bool operator() (std::map<int, int>::value_type type)
	{
		if (type.first > 2)
		{
			log("%d--%d", type.first, type.second);
			return true;
		}
			
	}
};

void TestScene::AboutSTLFor_each()
{
	std::vector<int> a{1, 2,34, 5};
	std::for_each(a.begin(), a.end(), [](int i) {log("%d", i); });

	std::map<int, int> b;
	b.insert(std::make_pair(2, 3));
	b.insert(std::make_pair(1, 3));
	b.insert(std::pair<int, int>(3, 4));
	b.insert(std::pair<int, int>(5, 4));
	std::for_each(b.begin(), b.end(), For_Each());
}

//函数模板
template <typename Toss>
Toss func(Toss a, double b)
{
	log("%lf", b);
	return a;
}

template<class A, typename B>
B function(A a, B b)
{
	log("%d", a);
	return b;
}

void TestScene::AboutTemplate()
{
	func(2, 3.f);
	function(3, 'c');

}

void TestScene::AboutArmature()
{
	FileUtils::getInstance()->addSearchPath("123");
	FileUtils::getInstance()->addSearchPath("naruto");
	auto node = CSLoader::createNode("Enemy_3.csb");
	auto timeline = CSLoader::createTimeline("Enemy_3.csb");
	node->runAction(timeline);
	node->setPosition(Vec2(200, 0));
	addChild(node);


	//auto particle = ParticleSystemQuad::create("fire_effect.plist");
	//particle->setPosition(Vec2(200, 200));
	//addChild(particle);
}

class Aa
{
public:
	Aa() {}
	void num() { log("haha"); }
	virtual void nm() { log("virtual Aa"); }
};

class Bb :public Aa
{
public:
	Bb() {}
	void num() { Aa::num(); log("heyhey"); }
	virtual void nm() { Aa::nm(); log("virtual Bb"); }
	void nm(int) { log("override virtal Bb"); }
};


void TestScene::AboutUIButtonClick()
{
	//@override and overload
	Aa * p1 = new Aa();
	//p1->nm();
	Bb* p2 = new Bb();
	//p2->nm(1);
	Aa* p3 = new Bb();
	p3->nm();
	p3->num();

	ui::Button* btn = ui::Button::create("brokenBrick.png");
	btn->setPosition(Vec2(100, 200));
	addChild(btn);


	btn->addTouchEventListener(
		[](Ref* ref, ui::Widget::TouchEventType type) {
			ui::Button* btn = (ui::Button*)ref;
			log("begin:%f--%f", btn->getTouchBeganPosition().x, btn->getTouchBeganPosition().y);
			log("move:%f--%f", btn->getTouchMovePosition().x, btn->getTouchMovePosition().y);
			if(type == ui::Widget::TouchEventType::CANCELED)
				log("end:%f--%f", btn->getTouchEndPosition().x, btn->getTouchEndPosition().y);
		}
	);

}

void TestScene::AboutJson()
{
	std::string str = "{\"hello\" : \"word\"}";
	CCLOG("%s\n", str.c_str());
	rapidjson::Document d;
	d.Parse<0>(str.c_str());
	if (d.HasParseError())  //打印解析错误
	{
		CCLOG("GetParseError %s\n", d.GetParseError());
	}
	if (d.IsObject() && d.HasMember("hello")) {

		CCLOG("%s\n", d["hello"].GetString());//打印获取hello的值
	}

	rapidjson::Document document; 
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator(); 
	rapidjson::Value array(rapidjson::kArrayType); 
	rapidjson::Value object(rapidjson::kObjectType); 
	rapidjson::Value inta(rapidjson::kNumberType);
	inta.SetInt(1);
	object.AddMember("int", 1, allocator); 
	object.AddMember("double", 1.0, allocator); 
	object.AddMember("bool", true, allocator); 
	object.AddMember("hello", "你好", allocator); 
	array.PushBack(object, allocator);
	array.PushBack(inta, allocator);
	document.AddMember("json", "json string", allocator); 
	document.AddMember("array", array, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	CCLOG("%s", buffer.GetString());

	Data data = FileUtils::getInstance()->getDataFromFile("test.json");
	unsigned char* dataBuffer = (unsigned char*)malloc(sizeof(unsigned char*) * data.getSize() + 1);
	memcpy(dataBuffer, data.getBytes(), data.getSize());
	dataBuffer[data.getSize()] = '\0';

	std::string strrr = FileUtils::getInstance()->getStringFromFile("test.json");
	rapidjson::Document doc;
	doc.Parse<0>(strrr.c_str());
	if (doc.IsObject() && doc.HasMember("name")) {

		CCLOG("%s\n", doc["name"].GetString());//打印获取hello的值
	}
	for (auto begin = doc.MemberBegin(); begin != doc.MemberEnd(); begin++)
	{
		log("key:%s", begin->name.GetString());

		if (begin->value.IsArray())
		{
			for (int i = 0; i < begin->value.Capacity(); i++)
			{
				if ((begin->value)[0].IsInt())
				{
					log("array:%d", (begin->value)[i].GetInt());
				}
					
			}
		}
		else if(begin->value.IsString())
		{
			log("value:%s", (begin->value).GetString());
		}
	}

	free(dataBuffer);


	//读取数据
	//Data tryData = FileUtils::getInstance()->getDataFromFile("test.json");
	//unsigned char* c_str = (unsigned char*)malloc(sizeof(unsigned char*) * (tryData.getSize() + 1));
	//memcpy(c_str, tryData.getBytes(), tryData.getSize());
	//c_str[tryData.getSize()] = '\0';
	
	//方法二
	/*ssize_t size;
	unsigned char* data_2 = FileUtils::getInstance()->getFileData("test.json", "r", &size);
	std::string data_t = std::string((const char*)data_2, size);*/

	//rapidjson::Document dcm;
	//dcm.Parse<0>((const char*)c_str);
	//free(c_str);

	rapidjson::Document docu;
	docu.SetObject();
	rapidjson::Document::AllocatorType& allocatorType = docu.GetAllocator();
	rapidjson::Value array_1(rapidjson::kArrayType);
	rapidjson::Value obj_1(rapidjson::kObjectType);
	array_1.PushBack(1, allocatorType);
	array_1.PushBack(2, allocatorType);
	array_1.PushBack(3, allocatorType);
	array_1.PushBack(4, allocatorType);
	obj_1.AddMember("name", "json", allocatorType);
	obj_1.AddMember("name", "xml", allocatorType);
	obj_1.AddMember("name", "html", allocatorType);
	obj_1.AddMember("name", "js", allocatorType);
	docu.AddMember("array", array_1, allocatorType);
	docu.AddMember("obj", obj_1, allocatorType);

	rapidjson::StringBuffer buf;
	rapidjson::Writer<rapidjson::StringBuffer> writ(buf);
	docu.Accept(writ);
	CCLOG("%s", buf.GetString());

	//写入json
	std::string strr = FileUtils::getInstance()->getWritablePath();
	std::string direct = strr + "json/";
	bool isOk = FileUtils::getInstance()->createDirectory(direct);
	if (isOk)
	{
		std::string json_dire = direct + "test.json";
		bool isWriteOk = FileUtils::getInstance()->writeStringToFile(buf.GetString(), json_dire);
		if (isWriteOk)
			log("write ok");
	}
}

void TestScene::AboutXml()
{
	using namespace tinyxml2;
	
	//解析
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	std::string path = FileUtils::getInstance()->fullPathForFilename("test.xml");
	doc->LoadFile(path.c_str());
	XMLElement* rootEle = doc->RootElement();
	CCLOG("%s--%s--%s", rootEle->Name(), rootEle->Value(), rootEle->FirstAttribute()->Name());
	float version = 0.f;
	rootEle->QueryFloatAttribute("version", &version);
	CCLOG("%f", version);
	rootEle->SetAttribute("version", 2.0f);
	CCLOG("version:%f", rootEle->FirstAttribute()->FloatValue());
	auto nextEle = rootEle->FirstChildElement();
	auto nnextEle = nextEle->FirstChildElement();
	CCLOG("name: %s, value: %s, text:%s",nnextEle->Name(), nnextEle->Value(), nnextEle->GetText());
	log("");
	int isOk = doc->SaveFile(path.c_str());
	if (isOk)
		CCLOG("ok!");
}

void TestScene::AboutFilePointer()
{
	FILE* f = fopen("test.csv", "r+");
	if (f)
	{
		fseek(f, 0, SEEK_END);
		unsigned size = ftell(f);
		rewind(f);
		  
		rewind(f);
		std::string str_2;
		char *str_c = new char[size + 1];
		fread(str_c, sizeof(char), size, f);
		str_c[size] = '\0';
		str_2.assign(str_c, size);
		log("%s", str_c);


		delete[] str_c;
		fclose(f);
	}

	
}

void TestScene::AboutPraseCSV()
{
	std::vector<std::vector<std::string>> allData;
	//先获取
	FILE *f = fopen("prase.csv", "rb");
	if (f)
	{
		//转移
		fseek(f, 0, SEEK_END);
		unsigned long size = ftell(f);
		rewind(f);
		fseek(f, 0, SEEK_SET);

		char* buffer = new char[size + 1];
		fread(buffer, 1, size, f);
		buffer[size] = '\0';
		
		std::vector<std::string> vec;
		
		char* pBegin = buffer;
		char* pEnd = strchr(pBegin, '\n');
		
		int index = 0;
		while (pEnd)
		{

			char* pStart = pBegin;
			char* pLast = strchr(pStart, ',');
			while (pLast && pEnd - pLast > 0)
			{
				std::string str;
				str.insert(0, pStart, pLast - pStart);
				vec.push_back(str);

				pStart = pLast + 1;
				pLast = strchr(pStart, ',');
			}
			allData.push_back(vec);
			vec.clear();

			pBegin = pEnd + 1;
			pEnd = strchr(pBegin, '\n');
		}

		delete[] buffer;
	}
	fclose(f);

	for (auto iter = allData.begin(); iter != allData.end(); iter++)
	{
		for (auto it = iter->begin(); it != iter->end(); it++)
		{
			log("%s", (*it).c_str());
		}
		log("-------------------------");
	}

}

//对于vector和deque来说swap函数是交换了数据结构,即迭代器并不会失效
void TestScene::AboutSwap()
{
	std::deque<int> vec{ 1, 2, 3, 4 };
	std::deque<int> vec_2{ 5, 6, 7, 8 };
	std::deque<int>::iterator iter = vec.begin();
	for(; iter != vec.end();iter++)
	{
		if (*iter == 3)
		{
			vec.swap(vec_2);
			break;
		}
		log("%d", *iter);
	}

	for (; iter != vec_2.end(); iter++)
	{
		log("vec_2 : %d", *iter);
	}

	//log("swap : %d", *++iter);
	std::deque<int>::iterator begin = vec.begin();
	log("after : %d", *begin);
}

#include "AudioEngine.h"
void TestScene::AboutAudioEngine()
{
	using namespace experimental;
	
	//auto id_2 = experimental::AudioEngine::play2d("sound/attack.mp3");
	auto id = experimental::AudioEngine::play2d("sound/attack.mp3");
	AudioEngine::setFinishCallback(id, [](int id, const std::string str) {
		log("finish id:%d--%s", id, str.c_str());
	});
	log("%d", id);
	
	this->runAction(RepeatForever::create(
		Sequence::create(
			CallFunc::create([]() {
				for (int i = 0; i < 3; i++)
				{
					auto id = experimental::AudioEngine::play2d("sound/attack.mp3");
					AudioEngine::setFinishCallback(id, [](int id, const std::string str) {
						log("finish id:%d--%s", id, str.c_str());
					});
				}
			}),
			DelayTime::create(0.5f),
			nullptr
		)
	));


	ui::Button* btn = ui::Button::create("4000.png");
	btn->addTouchEventListener([&](Ref*, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				this->stopAllActions();
				AudioEngine::pauseAll();
				auto id = experimental::AudioEngine::play2d("sound/attack.mp3");
				AudioEngine::setFinishCallback(id, [](int id, const std::string str) 
				{
					log("click id:%d--%s", id, str.c_str());
					log("resume---------------------------");
					AudioEngine::resumeAll();
				});
			}
		});
	btn->setPosition(Vec2(400, 600));
	addChild(btn);

}

//缩放并不能改变子节点的属性：位置、大小
void TestScene::ScaleAndPos()
{
	Sprite* sp = Sprite::create("brokenBrick.png");
	sp->setAnchorPoint(Vec2::ZERO);
	addChild(sp);

	Sprite*sp2 = Sprite::create("brokenBrick.png");
	sp2->setPosition(Vec2(100, 100));
	sp->addChild(sp2);

	log("pos befor: %f--%f", sp2->getPositionX(), sp2->getPositionY());
	log("wid befor: %f", sp2->getContentSize().width);
	sp->setScale(0.5f);
	log("pos after: %f--%f", sp2->getPositionX(), sp2->getPositionY());
	log("wid after: %f", sp2->getContentSize().width);
}


class AA
{
public:
	AA& operator =(const AA& a) = delete;
	/*{
		this->a = 2; 
	}*/

	AA() {}
	AA(const AA& a) = delete;

	int a;
};

void TestScene::AboutClassAssignment()
{
	AA a;
	a.a = 10;
	//这个对应的是初始化构造函数
	//AA b = a;
	//这个对应的是赋值函数
	//b = a;
	log("");
}


void ParserJsonRecursive(rapidjson::Value & j_value, cocos2d::Value& value)
{
	if (j_value.IsDouble())
		value = cocos2d::Value(j_value.GetDouble());
	else if (j_value.IsInt())
		value = cocos2d::Value(j_value.GetInt());
	else if (j_value.IsString())
		value = cocos2d::Value(j_value.GetString());
	else if (j_value.IsBool())
		value = cocos2d::Value(j_value.GetBool());
	else if (j_value.IsArray())
	{
		value = cocos2d::Value(cocos2d::ValueVector());
		for (int i = 0; i < j_value.Capacity(); i++)
		{
			cocos2d::Value val;
			ParserJsonRecursive(j_value[i], val);
			value.asValueVector().push_back(val);
		}
	}
	else if (j_value.IsObject())
	{
		value = cocos2d::Value(cocos2d::ValueMap());
		for (auto begin = j_value.MemberBegin(); begin != j_value.MemberEnd(); begin++)
		{
			cocos2d::Value val;
			ParserJsonRecursive(begin->value, val);
			value.asValueMap()[begin->name.GetString()] = val;
		}
	}
	else
	{
		assert(false);
	}
}

void ParserJsonToValueVector(const std::string & path, cocos2d::ValueVector & valueVector)
{
	std::string text = cocos2d::FileUtils::getInstance()->getStringFromFile(path.c_str());
	rapidjson::Document doc;
	doc.Parse<0>(text.c_str());
	CCASSERT(doc.IsArray(), "doc is not a array");
	for (int i = 0; i < doc.Capacity(); i++)
	{
		cocos2d::Value val;
		ParserJsonRecursive(doc[i], val);
		valueVector.push_back(val);
	}
}

void ParserJsonToValueMap(const std::string & path, cocos2d::ValueMap & valueMap)
{
	std::string text = cocos2d::FileUtils::getInstance()->getStringFromFile(path.c_str());
	rapidjson::Document doc;
	doc.Parse<0>(text.c_str());
	CCASSERT(doc.IsObject(), "doc is not a object");
	for (auto begin = doc.MemberBegin(); begin != doc.MemberEnd(); begin++)
	{
		cocos2d::Value val;
		ParserJsonRecursive(begin->value, val);
		valueMap[begin->name.GetString()] = val;
	}
}

void TestScene::AboutRecursiveJson()
{
	ValueMap valuemap;
	ValueVector valueVector;
	//ParserJsonToValueMap("test.json", valuemap);
	ParserJsonToValueVector("mission_map.json", valueVector);
	log("");
}

void TestScene::testFormat()
{
	float value = 12.04f;
	char buf[32];
	snprintf(buf, sizeof buf, "%.10g", value);
	log("");

	int a;
	unsigned b;
	auto c = a + b;
}

void TestScene::testFilePointer()
{
	FILE* file = fopen("123.xml", "r");
	if (file)
	{
		//log("file open success");
		log("pos :%d", ftell(file));
		fseek(file, 0, SEEK_END);
	    ssize_t  size = ftell(file);
		rewind(file);
		char *word = new char[size + 1];
		fread(word, sizeof(char), size, file);
		word[size] = '\0';
		std::string str(word);

		log("%s", str.c_str());

		fclose(file);
	}

	//file = fopen("write.xo", "w");
	//if (file)
	//{
	//	
	//	std::string str = "wring book";
	//	log("length :%d, size:%d", str.length(), str.size());
	//	fwrite(str.c_str(), sizeof(char), str.length(), file);
	//	fclose(file);
	//}

	//file = fopen("write.xo", "a+");
	//if (file)
	//{
	//	log("file open success");
	//	log("pos :%d", ftell(file));
	//	std::string str = "\nread book";
	//	log("length :%d, size:%d", str.length(), str.size());
	//	fwrite(str.c_str(), sizeof(char), str.length(), file);
	//	fclose(file);
	//}

	//二进制和文本b和t的区别，百度
	file = fopen("write.xo", "rb");
	if (file)
	{
		log("file open success");
		fclose(file);
	}
}

#include <iostream>
#include <fstream>
#include <vector>

using inner = std::istream;
using std::cin;

inner& setNum(inner& in)
{
	
	char c;
	while (!in.eof() && in >> c)
	{
		log("%c", c);
	}

	in.clear();
	return in;
}

void readFile()
{
	std::ifstream file("write.xo");
	std::vector<std::string> vec_str;
	if (file)
	{

		std::string str;
		while (file >> str)
		{
			std::cout << str << std::endl;
			vec_str.push_back(str);
		}
		
		file.close();
	}

	std::ofstream note("write.xo", std::ofstream::app | std::ofstream::out);
	if (note)
	{
		log("file open success");

		note << "hello world" << std::flush;

		note.close();
	}
}

#include <sstream>
void readStringStream()
{
	std::ifstream file("write.xo");
	if (!file)
	{
		std::cerr << "ERROR::FILE CANNOT BE OPENED" << std::endl;
		return;
	}

	std::string str;
	std::istringstream word;
	while (std::getline(file, str))
	{
		word.clear();
		word.str(str);
		while (word >> str)
		{
			std::cout << str << std::endl;
		}
	}
}

void TestScene::testIOstream()
{
	//setNum(cin);
	//readFile();
	readStringStream();
}

#include <memory>
using std::shared_ptr;
using std::make_shared;

class StrBlob
{
	friend class StrBlobPtr;
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
	StrBlob(std::initializer_list<std::string> il) : data(make_shared<std::vector<std::string>>(il)) {}
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string & t) { data->push_back(t); }
	void pop_back()
	{
		check(0, "pop_back on empty StrBlob");
		data->pop_back();
	}
	//元素访问
	std::string& front()
	{
		check(0, "front on empty StrBlob");
		data->front();
	}
	std::string& back()
	{
		check(0, "back on empty StrBlob");
		data->back();
	}

	StrBlobPtr begin();
		
	StrBlobPtr end();


private:
	std::shared_ptr<std::vector<std::string>> data;
	//如果data[i]不合法，抛出一个异常
	void check(size_type i, const std::string &msg) const
	{
		if (i >= data->size())
			throw std::out_of_range(msg);
	}
};

class StrBlobPtr
{
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0) :wptr(a.data), curr(sz) {}
	std::string& deref() const
	{
		auto p = check(curr, "dereference past end");
		return p->at(curr);
	}

	//前缀递增
	StrBlobPtr& incr()
	{
		check(curr, "increment past end of StrBlobPtr");
		curr++;//推进当前位置
		return *this;
	}
private:
	//若检查成功，check返回一个指向vector的shared_ptr
	std::shared_ptr<std::vector<std::string>> check(std::size_t i, const std::string& str) const
	{
		auto ret = wptr.lock();
		if (!ret)
			throw std::runtime_error("unbound StrBlobPtr");
		if (i >= ret->size())
			throw std::out_of_range(str);
	}
	//保存一个weak_ptr,意味着底层vector可能会销毁
	std::weak_ptr<std::vector<std::string>> wptr;
	//在数组中的当前位置
	std::size_t curr;
};

std::vector<int>* createVector()
{
	std::vector<int>* ptr = new std::vector<int>();
	return ptr;
}

void inputVector(std::vector<int>* ptr)
{
	int a;
	while (cin >> a)
	{
		ptr->push_back(a);
	}
}

void outputVector(std::vector<int>* ptr)
{
	for (const auto& a : *ptr)
	{
		std::cout << a << std::endl;
	}
}


using shared_vec_int = shared_ptr<std::vector<int>>;

shared_ptr<std::vector<int>> createVec()
{
	shared_ptr<std::vector<int>> ptr = make_shared<std::vector<int>>();
	return ptr;
}

void inputVec(shared_ptr<std::vector<int>> ptr)
{
	int a;
	while (cin >> a)
	{
		ptr->push_back(a);
	}
}

void outputVector(shared_vec_int ptr)
{
	for (const auto& a : *ptr)
	{
		std::cout << a << std::endl;
	}
}

struct connection
{
	std::string ip;
	int port;
	connection(std::string ip_, int port_) :ip(ip_), port(port_) {}
};

struct destination
{
	std::string ip;
	int port;
	destination(std::string ip_, int port_) :ip(ip_), port(port_) {}
};

connection connect(destination* pDest)
{
	std::shared_ptr<connection> pConn(new connection(pDest->ip, pDest->port));
	std::cout << "creating connection (" << pConn.use_count() << ")" << std::endl;

	return *pConn;
}

void disconnect(connection pConn)
{
	std::cout << "connection close(" << pConn.ip << ":" << pConn.port << ")" << std::endl;
}

void end_connection(connection* pCon)
{ 
	disconnect(*pCon);
}

void f(destination &d)
{
	connection conn = connect(&d);
	std::shared_ptr<connection> p(&conn, 
		[](connection* pCon) { 
		std::cout << "connection close(" << pCon->ip << ":" << pCon->port << ")" << std::endl; });
	std::cout << "connecting now(" << p.use_count() << ")" << std::endl;
}

void TestScene::AboutSharedPtr()
{
	StrBlob b1 = { "apple", "banana" };
	{
		StrBlob b2;
		b2 = b1;
	}


	shared_ptr<int> ptr = make_shared<int>(43);
	{
		auto ptr_2 = ptr;
	}

	log("%d", ptr.use_count());


	//vector
	//auto vector = createVector();
	//inputVector(vector);
	//outputVector(vector);
	//delete vector;

	//shared_vec
	//auto ptrd = createVec();
	//inputVec(ptrd);
	//outputVector(ptrd);

	//stupid
	//auto a = new auto (2);
	//shared_ptr<int> a = shared_ptr<int>(a);

	//shared_ptr connection
	destination dest("202.118.176.67", 3316);
	f(dest);
}

void TestScene::AboutUniquePtr()
{
	int b = 20;
	int *a = new int(20);
	std::unique_ptr<int> ptr(a);
	std::unique_ptr<int> pt(new int(23));
	
}

void TestScene::AboutWeakPtr()
{
	
	std::weak_ptr<int> p;
	{
		auto ptr = make_shared<int>();
		p = ptr;
	}
	
	if (p.lock())
	{
		log("%d", p.use_count());
	}
}

#include	"tools\GetAssets.h"
void TestScene::AboutTools()
{
	GetAssets::getInstance()->init("resource");
}

#include <iostream>
struct List
{
	int data;
	List* next;
};

void deleteOne(int pos, List* ls)
{
	if (pos < 0)
		return;
	else if (pos == 0)
	{
		auto head = ls;
		ls = ls->next;
		delete head;
	}
	else
	{
		//找到删除的前一个
		for (int i = 1; i < pos - 1; i++)
		{
			CCASSERT(i + 1 < pos - 1 && !ls->next, "ERROR::POS IS LARGER THAN LIST'S SIZE");
			ls = ls->next;
		}
		auto next = ls->next;
		if (next)
		{
			ls->next = next->next;
			delete next;
		}
		
	}

}

void deleteAll(List*&ls)
{
	do
	{
		auto erase = ls;
		ls = ls->next;
		delete erase;
	} while(ls);
}

List* insert(int pos, List* &ls)
{
	if (pos < 0)
		return nullptr;
	if (pos == 0)
	{
		auto list = new List;
		list->data = rand() % 10;
		list->next = ls;
		return list;
	}

	for (int i = 1; i < pos; i++)
	{
		CCASSERT(i + 1 < pos && !ls->next, "ERROR::POS IS LARGER THAN LIST'S SIZE");
		ls = ls->next;
	}

	auto node = new List;
	node->data = random(0, 20);
	node->next = ls->next;
	ls->next = node;
	return node;
}

void printls(List* ls)
{
	do
	{
		std::cout << "ls:" << ls->data << std::endl;
		ls = ls->next;
	} while (ls);
}

void TestScene::AboutLinkList()
{
	auto head = new List;
	head->data = 0;
	head->next = nullptr;

	auto t = head;
	int n = 0;
	while (cin >> n)
	{
		auto temp = new List;
		temp->data = n;
		temp->next = nullptr;
		t->next = temp;
		t = temp;
	}
	cin.clear();
	printls(head);

	deleteOne(1, head);
	printls(head);

	deleteOne(10, head);
	printls(head);
}

void TestScene::testXml()
{
	auto xml = FileUtils::getInstance()->getValueMapFromFile("aksn.xml");
	log(""); 

}

//缩放会影响坐标
void TestScene::testForAdapt()
{
	auto node = Node::create();
	node->setScale(1.2);
	addChild(node);

	Sprite* sp = Sprite::create("brokenBrick.png");
	auto size = Director::getInstance()->getVisibleSize();
	sp->setPosition(100, 100);
	node->addChild(sp);

	auto pos = node->convertToWorldSpace(sp->getPosition());
	log("%f--%f", pos.x, pos.y);
}



void TestScene::testForContact()
{
	Sprite* sp = Sprite::create("brokenBrick.png");
	auto body = PhysicsBody::createBox(sp->getContentSize());
	//body->setCategoryBitmask(0x01);
	//body->setCollisionBitmask(0x02);
	body->setContactTestBitmask(0x01);
	sp->setPhysicsBody(body);
	sp->runAction(MoveBy::create(3.0f, Vec2(300, 0)));
	sp->setPosition(Vec2(100, 100));
	sp->setName("sp");
	addChild(sp);

	Sprite* sd = Sprite::create("brokenBrick.png");
	body = PhysicsBody::createBox(sd->getContentSize());
	body->setContactTestBitmask(0x01);
	//body->setCategoryBitmask(0x02);
	//body->setCollisionBitmask(0x01);
	sd->setPhysicsBody(body);
	//sd->runAction(MoveBy::create(3.0f, Vec2(-300, 0)));
	sd->setPosition(Vec2(500, 100));
	sd->runAction(MoveBy::create(3.0f, Vec2(-300, 0)));
	addChild(sd);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [](cocos2d::PhysicsContact& contact)->bool {
		log("collision");
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void TestScene::testForTC()
{
	FileUtils::getInstance()->addSearchPath("TC4");

	const char* str = "zombie_snowman.csb";
	const char* cp_1 = "snow_hand.csb";
	const char* cp_2 = "cap.csb";
	auto csb = CSLoader::createNode(str);
	//csb->getChildByName("main")->getChildByName("veil")->setVisible(false);
	csb->setPosition(Vec2(200, 200));
	addChild(csb);

	auto timeline = CSLoader::createTimeline(str);
	csb->runAction(timeline);
	timeline->gotoFrameAndPause(0);
	//timeline->play("move", true);

	csb = CSLoader::createNode(cp_1);
	timeline = CSLoader::createTimeline(cp_1);
	csb->runAction(timeline);
	timeline->gotoFrameAndPause(0);
	csb->setPosition(Vec2(200, 200));
	addChild(csb);
}

void TestScene::dumpPhysics()
{
	_left = false;
	_right = false;

	auto size = Director::getInstance()->getVisibleSize();
	this->setPhysicsBody(PhysicsBody::createEdgeBox(size));

	auto sp = Sprite::create("brokenBrick.png");
	auto body = PhysicsBody::createBox(sp->getContentSize());
	body->getFirstShape()->setRestitution(0.0f);
	body->getFirstShape()->setFriction(0.f);
	sp->setPhysicsBody(body);
	sp->setPosition(Vec2(100, 100));
	sp->setTag(100);
	addChild(sp);
	 

	auto kj = Sprite::create("brokenBrick.png");
	kj->setPosition(Vec2(500, 300));
	addChild(kj);
	auto node = Node::create();
	node->setAnchorPoint(Vec2::ZERO);
	node->setPosition(Vec2(300, 50));

	auto ssp = Sprite::create("one_arrow.png");
	ssp->setAnchorPoint(Vec2(0.5, 0));
	ssp->setRotation(180);
	//ssp->runAction(RotateBy::create(3.f, 100));
	//ssp->setAnchorPoint(Vec2(1, 1));
	//ssp->setScale(2.f);
	//ssp->setRotation(100.0f);
	auto boody = PhysicsBody::createBox(ssp->getContentSize());
	
	//boody->setRotationOffset(100);
	auto length = ssp->getContentSize().height / 2;
	auto rot = CC_DEGREES_TO_RADIANS(ssp->getRotation());
	boody->setPositionOffset(Vec2(length * sinf(rot), length * cosf(rot)));
	//boody->setRotationEnable(false);
	boody->setDynamic(false);
	node->setPhysicsBody(boody);
	boody->setRotationOffset(180.f);

	node->addChild(ssp);
	kj->addChild(node);

	//kj->setRotation(80.f);
	//kj->runAction(RotateBy::create(3.0f, 360.f));

	auto btn = ui::Button::create("brokenBrick.png");
	btn->setPosition(Vec2(500, 500));
	btn->addTouchEventListener([node, ssp, boody](Ref*, ui::Widget::TouchEventType type) 
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//auto pos = boody->getCPBody()->p;
			//node->setScale(node->getScale() * 2.0f);
			//ssp->setScale(2.f);
			//boody->setPositionOffset(Vec2(0, ssp->getContentSize().height / 2.f * node->getScale()));
		}
	});
	addChild(btn);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [sp, this](EventKeyboard::KeyCode code, Event* event) {
		if (code == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			_right = true;
		}
		else if(code == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			_left = true;
		}
	};

	listener->onKeyReleased = [sp, this](EventKeyboard::KeyCode code, Event* event) {
		if (code == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			_right = false;
		}
		else if (code == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			_left = false;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();

	auto li = EventListenerCustom::create("HaHa", [](cocos2d::EventCustom*) {
		log("haha");
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(li, this);


}

void TestScene::AboutCameraAndRender()
{
	auto size = Director::getInstance()->getVisibleSize();

	auto sp = Sprite::create("HelloWorld.png");
	//sp->setCameraMask(2);
	sp->setPosition(0, 0);
	addChild(sp);

	auto camera = Camera::createOrthographic(size.width, size.height, 0, 1024);
	camera->setCameraFlag(cocos2d::CameraFlag::USER1);
	camera->setPosition3D(Vec3(-100.f, -100.0f, 0.0f));
	camera->setRotation3D(Vec3(0.f, 0.f, 0.f));
	addChild(camera);	

	auto renderTexture = RenderTexture::create(size.width, size.height);
	renderTexture->setPosition(0, 0);
	addChild(renderTexture);
	//renderTexture->setCameraMask(2);
	renderTexture->begin();
	this->visit();
	renderTexture->end();
	//sp->setVisible(false);
	//addChild(renderTexture);
	sp = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());
	sp->setFlippedY(true);
	sp->setPosition(960, 640);
	addChild(sp);
}

void TestScene::AboutActionManager()
{
	auto actionManager = new ActionManager();
	Director::getInstance()->getScheduler()->scheduleUpdate(actionManager, 0, false);
	Director::getInstance()->getScheduler()->pauseTarget(actionManager);

	auto sp = Sprite::create("HelloWorld.png");
	sp->setActionManager(actionManager);
	sp->runAction(RotateBy::create(5.f, 360));
	addChild(sp);

}

void TestScene::dumpOrCamera()
{
	auto camera = Camera::createOrthographic(960, 640, -1024, 1024);
	camera->setCameraFlag(CameraFlag::USER1);
	addChild(camera);
	
	auto sp = Sprite::create("HelloWorld.png");
	sp->setCameraMask(2);
	addChild(sp);
}

void TestScene::update(float dt)
{
	
	//this->getScene()->getPhysicsWorld()->step(0);

	auto sp = (Sprite*)this->getChildByTag(100);
	auto body = sp->getPhysicsBody();
	auto origin = sp->getPosition();
	auto pos = Vec2::ZERO;
	
	auto velocity = body->getVelocity();
	body->setVelocity(Vec2(0, velocity.y));
	if (_left)
		body->applyImpulse(Vec2(-20000, 0));
	if (_right)
		body->applyImpulse(Vec2(20000, 0));

	for (int i = 0; i < 3; i++)
	{
		this->getScene()->getPhysicsWorld()->step(1 / 180.0f);
	}

	//if (pos.x)
	//	sp->setPosition(origin + pos);
}

StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end()
{
	return StrBlobPtr(*this, this->size());
}

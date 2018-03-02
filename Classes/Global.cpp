#include "Global.h"

//”Œœ∑≥°æ∞±≥æ∞Õº
const char* GAME_SCENE_BG_PATH[3] =
{
	"background_1.png",
	"background_2.png",
	"background_3.png"
};

int BG_SPEED = 1;

const char* CLOUD_PATH[3] = 
{
	"cloud_1.png",
	"cloud_2.png",
	"cloud_3.png"
};

extern const char* ITEM_TYPE[2] = 
{
	//∂‹
	"shield",
	//±‰¥Û
	"bigger"
};

const char* MAP_TYPE[3][MAP_SECTION_NUM] =
{
	{
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
	},
	{
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
	},
	{
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
		"mission1-1.tmx",
	}
};

//Õº≤„√˚◊÷
const char* TILEMAP_LAYER_NAME[5] =
{
	"root",
};

//√ø√Î
float MAP_SPEED = 600;
// «∑Ò…Û∫À
bool isCheck = false;
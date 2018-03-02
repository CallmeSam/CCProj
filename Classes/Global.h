#pragma once
#ifndef  __GLOBAL_H__
#define __GLOBAL_H__
#include <string>

#define MAP_SECTION_NUM 10

#define GRAVITY -3000
#define PROTECT_TIME 2
//根据csbNode做的 现在不可以改 
#define MAX_BLOOD 3
#define UPDATE 1/30.f
//从图框各个顶点偏离多少像素才是正常落地
#define OFF_PIXEL 20

extern const char* GAME_SCENE_BG_PATH[3];
//背景移动速度
extern const char* CLOUD_PATH[3];
extern int BG_SPEED;
extern float MAP_SPEED;
extern const char* ITEM_TYPE[2];
extern const char* MAP_TYPE[3][MAP_SECTION_NUM];
extern const char* TILEMAP_LAYER_NAME[5];
//是否检查
extern bool isCheck;


#endif // ! __GLOBAL_H__

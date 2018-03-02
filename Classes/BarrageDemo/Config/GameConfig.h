#pragma once
#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__

#include "cocos2d.h"

extern cocos2d::ValueVector SKILL_INFO;
extern cocos2d::ValueVector ENEMIES_INFO;
extern cocos2d::ValueVector BUFF_INFO;
extern const int ENEMY_CATEGORY_MASK;
extern const int ENEMY_CONTACT_MASK;
extern const int BULLET_CATEGORY_MASK;
extern const int BULLET_CONTACT_MASK;

extern const int PER_ROTATE;

extern cocos2d::ValueMap EMPTY_MAP;
#endif // !__GAME_CONFIG_H__
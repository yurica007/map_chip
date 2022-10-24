#include "DxLib.h"
#include "game.h"
#include "SceneTest.h"


namespace
{
}

void SceneTest::init()
{
	
}

void SceneTest::end()
{
}

SceneBase* SceneTest::update()
{
	
	return this;
}

void SceneTest::draw()
{
	DrawString(0, 0, "test", GetColor(255, 255, 255));
}


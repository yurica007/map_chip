#include "Map.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>
#include "Pad.h"

#include <iostream>
#include <fstream>

namespace
{
	// �}�b�v�`�b�v1�̃T�C�Y
	constexpr int kChipSize = 32;

	// �`�b�v�̐�
	constexpr int kBgNumX = Game::kScreenWidth / kChipSize;
	constexpr int kBgNumY = Game::kScreenHeight / kChipSize;

	// �o�̓t�@�C����
	const char* const kFileName = "map.bin";

	// �}�b�v�f�[�^
	constexpr int kMapData[kBgNumY][kBgNumX] =
	{
		{ 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};
}

Map::Map() :
	m_handle(-1),
	m_graphWidth(0),
	m_graphHeight(0),
	m_cursorNo(0),
	m_mapData(kBgNumX * kBgNumY, 0)
{
	
}

Map::~Map()
{

}

void Map::load()
{
	m_handle = LoadGraph("data/mapchip.png");
	GetGraphSize(m_handle, &m_graphWidth, &m_graphHeight);
}

void Map::unload()
{
	DeleteGraph(m_handle);
}

void Map::update()
{
	int indexX = m_cursorNo % kBgNumX;
	int indexY = m_cursorNo / kBgNumX;

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// �w�肵���}�b�v�`�b�v�̕ύX
		if (m_mapData[m_cursorNo] < (chipNum() - 1))
		{
			m_mapData[m_cursorNo]++;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		// �w�肵���}�b�v�`�b�v�̕ύX
		if (m_mapData[m_cursorNo] > 0)
		{
			m_mapData[m_cursorNo]--;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_3))
	{
		// �t�@�C���̏o��
//		outputData();
		readData();
	}

	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		if ((indexY) > 0)
		{
			m_cursorNo -= kBgNumX;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		if ((indexY) < (kBgNumY - 1))
		{
			m_cursorNo += kBgNumX;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{
		if (indexX > 0)
		{
			m_cursorNo--;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		if (indexX < (kBgNumX - 1))
		{
			m_cursorNo++;
		}
	}
}

void Map::draw()
{
	for (int x = 0; x < kBgNumX; x++)
	{
		for (int y = 0; y < kBgNumY; y++)
		{
			const int chipNo = m_mapData[y * kBgNumX + x];
			assert(chipNo >= 0);
			assert(chipNo < chipNum());

			int graphX = (chipNo % chipNumX()) * kChipSize;
			int graphY = (chipNo / chipNumX()) * kChipSize;
			DrawRectGraph(x * kChipSize, y * kChipSize, graphX, graphY, kChipSize, kChipSize, m_handle, true, false);
		}
	}
	drawCursor();
}

void Map::drawCursor()
{
	int indexX = m_cursorNo % kBgNumX;
	int indexY = m_cursorNo / kBgNumX;

	int graphX = indexX * kChipSize;
	int graphY = indexY * kChipSize;

	DrawBox(graphX, graphY, graphX + kChipSize, graphY + kChipSize, GetColor(255, 0, 0), false);
}

int Map::chipNumX()
{
	return (m_graphWidth / kChipSize);
}

int Map::chipNumY()
{
	return (m_graphHeight / kChipSize);
}

int Map::chipNum()
{
	return (chipNumX() * chipNumY());
}

void Map::outputData()
{
	std::ofstream ofs(kFileName, std::ios::binary);

	// �t�@�C���̃I�[�v���Ɏ��s
	if (!ofs) return;

	ofs.write(reinterpret_cast<char*>(m_mapData.data()), sizeof(int) * kBgNumX * kBgNumY);
	ofs.close();
}

void Map::readData()
{
	std::ifstream ifs(kFileName, std::ios::binary);

	// �t�@�C���̓ǂݍ��݂Ɏ��s
	if (!ifs) return;

	ifs.read(reinterpret_cast<char*>(m_mapData.data()), sizeof(int) * kBgNumX * kBgNumY);
	ifs.close();
}
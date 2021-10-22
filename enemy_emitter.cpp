//=============================================================================
//
// �G�l�~�[�����Ǘ� [enemy_emitter.cpp]
// Author : 
//
//=============================================================================
#include "enemy_emitter.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
struct ENEMY_EMIT_DATA
{
	float			frame;	//�����t���[��
	D3DXVECTOR2		pos;	//����������W
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int g_StageFrame = 0;		//���݂̃X�e�[�W���n�܂��Ă���̎���
static int g_EnemyEmitCount = 0;	//�����J�E���^�[
static int g_EmitTableSize = 0;		//�e�[�u���̃T�C�Y


ENEMY_EMIT_DATA g_EnemyEmitData[] =
{
	{120.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},
	{140.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},
	{160.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},
	{180.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},
	{200.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},

	{320.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},
	{340.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},
	{360.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},
	{380.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},
	{400.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},

	{520.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},
	{540.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},
	{560.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},
	{580.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},
	{600.0f, {SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 2}},

};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyEmitter(void)
{
	//������
	g_StageFrame = 0;
	g_EnemyEmitCount = 0;
	g_EmitTableSize = sizeof(g_EnemyEmitData) / sizeof(ENEMY_EMIT_DATA);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyEmitter(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyEmitter(void)
{
	//�����e�[�u���̏���`�F�b�N
	if (g_EnemyEmitCount >= g_EmitTableSize)
	{
		return;
	}

	//�G�̔����^�C�~���O�̐���
	if (g_StageFrame >= g_EnemyEmitData[g_EnemyEmitCount].frame)
	{
		SetEnemy(g_EnemyEmitData[g_EnemyEmitCount].pos);
		g_EnemyEmitCount++;
	}

	g_StageFrame++;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyEmitter(void)
{

}

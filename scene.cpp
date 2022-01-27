/*==============================================================================

   �V�[���Ǘ� [scene.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "stageselect.h"
#include "effect.h"
#include "logo.h"
#include "player.h"
#include "stagedata.h"
#include "FileDataManagement.h"
#include "worldselect.h"
#include "savedata.h"
#include "placement.h"
#include "mission.h"
#include "Prologue.h"
#include "pause.h"
#include "stageselect.h"

/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
static SCENE g_SceneIndex = SCENE_NONE;
static SCENE g_SceneNextIndex = g_SceneIndex;

bool	change_once = false;		// �V�[���ς��Ă��Ă��肢

int gas = 0;


/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitScene(SCENE index)
{
	g_SceneIndex = g_SceneNextIndex = index;

	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_LOGO:
		InitSavedata();
		InitMission();			// �X�e�[�W�Z���N�g�Ń~�b�V�����̏��g�������ɓǂ�ł���
		InitEffect();
		InitLogo();
		//InitStagedata();
		break;

	case SCENE_Prologue:
		InitEffect();
		InitPrologue();
		break;

	case SCENE_TITLE:
		InitEffect();
		InitTitle();
		break;

	case SCENE_WORLD_SELECT:
		InitEffect();
		InitWorldSelect();
		break;


	case SCENE_STAGE_SELECT:
		InitEffect(); 
		//InitStageSelect();
		InitStageSelect2();
		break;

	case SCENE_PLACEMENT:
		InitEffect();
		InitGameForPlacement();
		InitStagedata();
		SetStageData(GetNowChoiceStageNum());
		InitPlacement(); 
		break;

	case SCENE_GAME:
		InitEffect();
		InitGame();
		InitStagedata();
		SetStageData(GetNowChoiceStageNum());
		InitPause();
		break;

		//case SCENE_RESULT:
		//	InitEffect();
		//	InitResult();
		//	break;
	}
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitScene(void)
{

	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_LOGO:
		UninitEffect();
		UninitLogo();
		break;

	case SCENE_Prologue:
		UninitEffect();
		UninitPrologue();
		break;

	case SCENE_TITLE:
		UninitEffect();
		UninitTitle();
		break;

	case SCENE_WORLD_SELECT:
		UninitEffect();
		UninitWorldSelect();
		break;

	case SCENE_STAGE_SELECT:
		UninitEffect();
		UninitStageSelect();
		break;

	case SCENE_PLACEMENT:
		UninitEffect();
		UninitPlacement();
		break;

	case SCENE_GAME:
		UninitEffect();
		UninitGame();
		UninitPause();
		break;

		//case SCENE_RESULT:
		//	UninitEffect();
		//	UninitResult();
		//	break;
	}
}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateScene(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_LOGO:
		UpdateEffect();
		UpdateLogo();
		break;

	case SCENE_Prologue:
		UpdateEffect();
		UpdatePrologue();
		break;

	case SCENE_TITLE:
		UpdateEffect();
		UpdateTitle();
		break;

	case SCENE_WORLD_SELECT:
		UpdateEffect();
		UpdateWorldSelect();
		break;

	case SCENE_STAGE_SELECT:
		UpdateEffect();
		//UpdateStageSelect();
		UpdateStageSelect2();
		
		break;

	case SCENE_PLACEMENT:
		UpdateEffect();
		UpdatePlacement();
		break;

	case SCENE_GAME:
		UpdateEffect();
		UpdateGame();
		UpdatePause();
		break;

		//case SCENE_RESULT:
		//	UpdateSavedata();
		//	UpdateEffect();
		//	UpdateResult();
		//	UpdateStagedata();
		//	break;
	}

	UpdateFade();
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawScene(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_LOGO:
		DrawLogo();
		DrawEffect();
		break;

	case SCENE_Prologue:
		DrawEffect();
		DrawPrologue();
		break;

	case SCENE_TITLE:
		DrawTitle();
		DrawEffect();
		break;

	case SCENE_WORLD_SELECT:
		DrawWorldSelect();
		DrawEffect();
		break;

	case SCENE_STAGE_SELECT:
		DrawStageSelect();
		DrawEffect();
		break;

	case SCENE_PLACEMENT:
		DrawPlacement();
		DrawEffect();
		break;

	case SCENE_GAME:
		DrawGame();
		DrawEffect();
		DrawPause();
		break;

		//case SCENE_RESULT:
		//	DrawResult();
		//	DrawEffect();
		//	break;
	}

	DrawFade();
}

/*------------------------------------------------------------------------------
   �V�[���J�ڂ�v������֐�
------------------------------------------------------------------------------*/
void SetScene(SCENE index)
{
	change_once = true;

	//�J�ڐ�V�[����ݒ肷��
	g_SceneNextIndex = index;
}

/*------------------------------------------------------------------------------
   �J�ڂ�v��������ꍇ�ɃV�[����؂�ւ���֐�
------------------------------------------------------------------------------*/
void CheckScene(void)
{
	//////////���݂̃V�[���ƑJ�ڐ�V�[��������Ă�����
	////////if (g_SceneIndex != g_SceneNextIndex)
	////////{
	////////	//���݂̃V�[�����I��������
	////////	UninitScene();

	////////	//�J�ڐ�V�[���̏������������s��
	////////	InitScene(g_SceneNextIndex);
	////////}


	// �V�[���ς��Ă��Ă��肢�����Ă���1�񂾂��ύX����
	if (change_once == true)
	{
		change_once = false;

		//���݂̃V�[�����I��������
		UninitScene();

		//�J�ڐ�V�[���̏������������s��
		InitScene(g_SceneNextIndex);
	}

}


SCENE* GetScene(void)
{
	return &g_SceneIndex;
}
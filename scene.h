#pragma once

// �o�^�V�[���ꗗ
enum SCENE
{
	SCENE_NONE,			//�V�[�������Ȃ�
	SCENE_LOGO,		    //�`�[�����S
	SCENE_TITLE,		//�^�C�g��
	SCENE_GAME,			//�Q�[��
	SCENE_WORLD_SELECT,	//���[���h�I�����
	SCENE_STAGE_SELECT,	//�X�e�[�W�I�����
	//SCENE_RESULT,	    //���U���g
	SCENE_MAX		    //�Ōゾ�Ƃ킩��z�������
};

void InitScene(SCENE index);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);

void SetScene(SCENE index);
void CheckScene(void);

SCENE* GetScene(void);
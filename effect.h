//effect.h
#include "main.h"
#include "renderer.h"

#define MAX_EFFECT (150)

typedef struct 
{
	int				id;						//�G�t�F�N�g�ԍ�

	D3DXVECTOR2		pos;					// ���݂̈ʒu
	D3DXVECTOR2		pos1;					// �����ʒu
	D3DXVECTOR2		pos2;					// �I���ʒu
	int				pos_moving_pattern;		// �����ʒu����I���ʒu�Ɉړ�����Ƃ��̓����� 0:pos1���瓮���Ȃ�

	D3DXVECTOR2		size;					// ���݂̃T�C�Y
	D3DXVECTOR2		size1;					// �T�C�Y�̏����l
	D3DXVECTOR2		size2;					// �T�C�Y�̏I���l
	int				size_moving_pattern;	// �����T�C�Y����I���T�C�Y�ɕω�����Ƃ��̕ω��̎d�� 0:size1���瓮���Ȃ�

	D3DXVECTOR2				drawpos;				// �\������ۂ̍��W
	D3DXVECTOR2				drawsize;				// �\������ۂ̃T�C�Y

	int				fadeIn_count;			// 0�J�E���g����t�F�[�h�C�����n�܂�A�t�F�[�h�C������������܂ł̃J�E���g
	int				all_count;				// 999 �ɐݒ肷�邱�ƂŖ����ɃG�t�F�N�g��\������BfadeIn_count ���瓧���x��MAX�̏�ԂɂȂ�A����� fadeOut_count+fadeIn_count �܂ňێ�����
	int				fadeOut_count;			// fadeOut_count+fadeIn_count ����t�F�[�h�A�E�g���n�܂�A�t�F�[�h�A�E�g����������܂ł̃J�E���g
	int				now_count;				// ��������Ă���̃J�E���g

	int				moving_count;			// 1 ���� 2 �ɕω�����܂ł̃J�E���g�B��{�t�F�[�h�A�E�g���I���܂ł�3�̒l�𑫂����l��OK�B
											// �t�ɂ����3�𑫂����l��菬�����ƈړ��Ȃǂ̓r���ŃG�t�F�N�g�������Ă��܂��̂Œ��ӁB
	float			Clarity;				// ���݂̓����x
	float			Clarity_min;			// �����x�̍Œ�l
	float			Clarity_max;			// �����x�̍ő�l

	float			rot;					// ���݂̉�]�̃��W�A��
	float			rot_angle;				// ���݂̉�]�̊p�x
	float			rot_angle1;				// ��]�̊p�x�̏����l
	float			rot_angle2;				// ��]�̊p�x�̏I���l
	int				rot_moving_pattern;		// ��]�̃p�^�[���B
	int				rot_count;				// ��]���n�߂Ă���̃J�E���g�B������]�p�B

	int				use_array_num;			// �z��̉��Ԃ��g���Ă��邩

	D3DXCOLOR		color;					// ����Ɠ����x

	// UV�l
	float				tx;					// ����
	float				ty;					// �c��
	float				sx;					// �X�^�[�g�ʒux
	float				sy;					// �X�^�[�g�ʒuy

	bool			isUse;					// �g�p�t���O
}EFFECT;

void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

EFFECT* GetEffect(void);

int SetEffect(int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern, float tx = 1.0f, float ty = 1.0f, float sx = 0.0f, float sy = 0.0f);

int SetEffectInReverse(int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern, float tx = 1.0f, float ty = 1.0f, float sx = 0.0f, float sy = 0.0f);

int SetGameEffect(int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern);

void ChangeEffect(int use_array_num, int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern, int SerialNumber = 1);

float AngleToRadian(float angle);	// �p�x�����W�A����

void Fadeprocess(int i);
void PosMovingPattern(int i);
void SizeMovingPattern(int i);
void RotMovingPattern(int i);

int GetTextureData(int id);
void ChangeEffectCount(int use_array_num, int setcount, int SerialNumber = 1);
void ChangeEffectPos(int use_array_num, float setpos_x, float setpos_y, int SerialNumber = 1);
void ChangeEffectTexture(int use_array_num, int setTexid, int SerialNumber = 1);
void ChangeEffectColor(int use_array_num, float r, float g, float b, int SerialNumber = 1);
void ChangeEffectClarity(int use_array_num, float clarity, int SerialNumber = 1);
void EffectBreak(int use_array_num, int SerialNumber = 1);		// #include<iostream>��c++���g���Ă�B�f�t�H���g�����B�����Ȃ��Ă��悢�����ŁA�����Ȃ������炱����= 1 �Ƃ��Ă���悤��1������B�������珑�����������
// SerialNumber�͘A�ԂĈӖ�
// SerialNumber���ꂽ���R�́A�����Ƃ���2���ȏ�̏ꍇ�B�A�Ԃŉ��A�������w�肷��Ώ����₷������B

// �Z�b�g�G�t�F�N�g�̐����o�[�W�����B�����𓯎��ɐ������邩��int�^�̔z���Ԃ���B�X�^�[�g�ʒu�Ɖ��A�Ԃ��Ă邩�B
void SetEffectNumber(int num, int* back_array, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern);

D3DXVECTOR2 GetEffectPos(int use_array_num);
D3DXVECTOR2 GetEffectSize(int use_array_num);
float GetEffectClarity(int use_array_num);
int GetEffectnow_count(int use_array_num);
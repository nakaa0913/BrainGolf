//effect.h
#include "main.h"
#include "renderer.h"

#define MAX_EFFECT (100)

typedef struct 
{
	int		id;				//�G�t�F�N�g�ԍ�
	D3DXVECTOR2	pos;		// �ʒu
	D3DXVECTOR2	drawpos;	// �ʒu
	D3DXVECTOR2	vel;		// ���x
	D3DXVECTOR2	size;		// �T�C�Y
	int		fadeIn_count;	//�G�t�F�N�g�����p�J�E���g
	int		all_count;		//�G�t�F�N�g�����p�J�E���g
	int		fadeOut_count;	//�G�t�F�N�g�����p�J�E���g
	int		now_count;		//��������Ă���̃J�E���g
	int		direction;		//�G�t�F�N�g�̕���
	float	Clarity;		//�����x
	bool	isUse;			//�g�p�t���O
}EFFECT;

void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

EFFECT* GetEffect(void);

void SetEffect(int id, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 vel, int fadeIn_count, int all_count, int fadeOut_count, int direction);
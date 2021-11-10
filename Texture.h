#pragma once


#include "renderer.h"

int LoadTexture(char* fileName);
void UninitTexture(void);
void UnloadTexture(char* fileName);

ID3D11ShaderResourceView** GetTexture(int index);

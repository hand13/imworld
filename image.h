#ifndef IMAGE_H
#define IMAGE_H
#include <d3d11.h>
bool LoadTextureFromFile(const char * filename,ID3D11Device * g_pd3dDevice,ID3D11ShaderResourceView ** out_srv,int * out_width,int * out_height);
#endif

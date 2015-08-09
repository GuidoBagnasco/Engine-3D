#include "Texture.h"
#include "Renderer.h"
#include "VertexBuffer.h"
using namespace Engine;

Renderer::Renderer(HWND hWnd){
	m_hWnd = hWnd;
	p_D3D = NULL;
	m_pkDevice = NULL;
	m_pkVertexBuffer = NULL;
}



Renderer::~Renderer(void){
	if(m_pkVertexBuffer != NULL){
		m_pkVertexBuffer = NULL;
	}

	if(m_pkDevice != NULL)
		m_pkDevice->Release();

	if(p_D3D != NULL)
		p_D3D->Release();
}



void Renderer::StartFrame(){
	m_pkDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 30, 120), 1.0f, 0.0f);

	m_pkDevice->BeginScene();
}



bool Renderer::InitDX(HWND hWnd){
	HRESULT hr;
	m_hWnd = hWnd;
	p_D3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DDISPLAYMODE displayMode;
	hr = p_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

	if(hr != D3D_OK)
		return false;

	D3DPRESENT_PARAMETERS presentParameters;
	ZeroMemory(&presentParameters, sizeof(presentParameters));
	
	presentParameters.BackBufferCount = 1;
	presentParameters.BackBufferFormat = displayMode.Format;
	presentParameters.Windowed = TRUE;
	presentParameters.BackBufferHeight = WINDOW_HEIGHT;
	presentParameters.BackBufferWidth = WINDOW_WIDTH;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    presentParameters.EnableAutoDepthStencil = TRUE;
    presentParameters.AutoDepthStencilFormat = D3DFMT_D24S8; 	

	hr = p_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &presentParameters, &m_pkDevice);

	if(hr != D3D_OK)
		return false;
	
    m_pkDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    //m_pkDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    m_pkDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    m_pkDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    m_pkDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    m_pkDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    m_pkDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    m_pkDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	SetViewPosition(0, 0);
	D3DVIEWPORT9 kViewport;
	hr = m_pkDevice->GetViewport(&kViewport);

	if(hr != D3D_OK)
		return false;

	D3DXMatrixPerspectiveFovLH(&m_mProjectionMatrix, (float)kViewport.Width, (float)kViewport.Height, 0, 45);
	//D3DXMatrixOrthoLH(&m_mProjectionMatrix, (float)kViewport.Width, (float)kViewport.Height, -25, 25);		// W, H, Near plane, Far plane
	hr = m_pkDevice->SetTransform(D3DTS_PROJECTION, &m_mProjectionMatrix);
	
	if(hr != D3D_OK)
		return false;

	m_pkVertexBuffer = new VertexBuffer<D3DVERTEX, COLOR_VERTEX>();
	if(!m_pkVertexBuffer->Create(m_pkDevice, true)){
		return false;
	}

	m_pkVertexBufferS = new VertexBuffer<D3DTVERTEX, TEXTURE_VERTEX>();
	if(!m_pkVertexBufferS->Create(m_pkDevice, true)){
		return false;
	}

	return true;
}



void Renderer::EndFrame(){
	m_pkDevice->EndScene();
	m_pkDevice->Present(NULL, NULL, NULL, NULL);
}



void Renderer::Draw(D3DVERTEX* vertexCollection, D3DPRIMITIVETYPE ePrim, unsigned int uiVertexCount){
	// Draws shapes
	m_pkVertexBuffer->Bind();
	m_pkVertexBuffer->Draw(vertexCollection, ePrim, uiVertexCount);
}


void Renderer::DrawSP(D3DTVERTEX* vertexCollection, unsigned int uiVertexCount){
	// Draws sprites
	m_pkVertexBufferS->Bind();
	m_pkVertexBufferS->Draw(vertexCollection, D3DPT_TRIANGLESTRIP, uiVertexCount);
}


Texture* Renderer::LoadTexture(std::string fileName, int keycode){
	D3DXIMAGE_INFO imgInfo;
	IDirect3DTexture9* p_Texture = NULL;

	HRESULT hr = D3DXCreateTextureFromFileEx(m_pkDevice, fileName.c_str(), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
												D3DX_FILTER_NONE, D3DX_FILTER_NONE, keycode, &imgInfo, NULL, &p_Texture);

	if(hr != D3D_OK){
		return NULL;
	}
	else{
		Texture* texture = new Texture();
		texture->SetTexture(p_Texture);
		texture->SetName(fileName);
		texture->SetDimension(imgInfo.Width, imgInfo.Height);
		texture->SetKeycode(keycode);
		//texture->SetFileName(fileName);
		return texture;
	}
}



void Renderer::SetTexture(Texture* texture){
	if(texture == NULL)
		m_pkDevice->SetTexture(0, NULL);
	else
		m_pkDevice->SetTexture(0, texture->GetTexture());
}



void Renderer::SetMatrixMode(MATRIX_MODE mode){
	m_eCurrentMatMode = mode;
}



void Renderer::SetViewPosition(float posX, float posY){
	D3DXMATRIX kMatrix;
	D3DXVECTOR3 kLookPos;
	D3DXVECTOR3 kViewPos;

	kLookPos.x = posX;	// (1, 0, 0)
	kLookPos.y = posY;
	kLookPos.z = 0.0f;

	kViewPos.x = 0.0f;	
	kViewPos.y = 0.0f;
	kViewPos.z = 0.0f;

	kViewUp.x = 0.0f;	// (0, 1, 0)
	kViewUp.y = 1.0f;
	kViewUp.z = 0.0f;

	D3DXMatrixLookAtLH(&kMatrix, &kViewPos, &kLookPos, &kViewUp);		// Matriz que guarda el resultado, Eye, Look at, Up
	m_pkDevice->SetTransform(D3DTS_VIEW, &kMatrix);
}


void Renderer::LoadIdentity(){
	D3DXMATRIX kTempMatrix;

	//Sets identity matrix.
	D3DXMatrixIdentity(&kTempMatrix);

	//If it is a view matrix, uses default values.
	if(m_eCurrentMatMode == View){
		D3DXVECTOR3 kEyePos(0, 0, -1);
		D3DXVECTOR3 kLookPos(0, 0, 0);
		D3DXVECTOR3 kUpVector(0, 1, 0);

		//Generates the view matrix.
		D3DXMatrixLookAtLH(&kTempMatrix, &kEyePos, &kLookPos, &kUpVector);
	}

	//Converts from MatrixMode to D3DTRANSFORMSTATETYPE
	D3DTRANSFORMSTATETYPE eMatMode = static_cast<D3DTRANSFORMSTATETYPE> (m_eCurrentMatMode);

	//Sets the matrix.
	m_pkDevice->SetTransform(eMatMode, &kTempMatrix);
}



void Renderer::Translate(float fx, float fy){
	D3DXMATRIX kTempMatrix;

	//Generate translation matrix.
	D3DXMatrixTranslation(&kTempMatrix, fx, fy, 1);

	//Converts from MatrixMode to D3DTRANSFORMSTATETYPE
	D3DTRANSFORMSTATETYPE eMatMode = static_cast<D3DTRANSFORMSTATETYPE>(m_eCurrentMatMode);

	//Sets the matrix.
	m_pkDevice->MultiplyTransform(eMatMode, &kTempMatrix);
}



void Renderer::Scale(float h, float w){
	D3DXMATRIX kTempMatrix;

	//Generate translation matrix.
	D3DXMatrixScaling(&kTempMatrix, w, h, 1.0f);

	//Converts from MatrixMode to D3DTRANSFORMSTATETYPE
	D3DTRANSFORMSTATETYPE eMatMode = static_cast<D3DTRANSFORMSTATETYPE> (m_eCurrentMatMode);

	//Sets the matrix.
	m_pkDevice->MultiplyTransform(eMatMode, &kTempMatrix);
}
#pragma once

#define MODEL_CUBE ("asset\\model\\DrawOBB1.obj")

// �}�e���A���\����
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;

};


// �`��T�u�Z�b�g�\����
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


// ���f���\����
struct MODEL
{
	VERTEX_3D		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};





class Model
{
private:

	MODEL model;
	ID3D11Buffer*	m_VertexBuffer;
	ID3D11Buffer*	m_IndexBuffer;

	SUBSET*	m_SubsetArray;
	unsigned int	m_SubsetNum;

	void LoadObj( const char *FileName, MODEL *Model );
	void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum );

public:

	void Draw();

	void Load( const char *FileName );
	void Unload();

	VERTEX_3D* GetVertexArray()
	{
		return model.VertexArray;
	}
	unsigned int* GetIndexArray()
	{
		return model.IndexArray;
	}

	unsigned int GetVertexNum()
	{
		return model.VertexNum;
	}

	unsigned int GetIndexNum()
	{
		return model.IndexNum;
	}
};
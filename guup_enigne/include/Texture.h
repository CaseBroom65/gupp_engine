#pragma once
#include "PreRequisitos.h"

class Device;
class DeviceContext;

class Texture
{
public:
	Texture() = default;
	~Texture() = default;
	/// <summary>
	/// Brief:Crea la tectura a partir de una imagen (.dds) desde nuestro ordenador
	/// </summary>
	/// <param name="device">Llamamos al device para poder generar los recursos en memoria. </param>
	/// <param name="TextureName"> Almacenaremos el nombre de la textura, para cargarla desde memoria.</param>
	HRESULT init(Device device, std::string TextureName);
	/// <summary>
	/// Brief: The method is responsable for creating a 2D Texture from the data provided
	/// </summary>
	/// <param name="device"> It is in change of providing the resourses to create the 2D texture.</param>
	/// <param name="width"> It will take the witdh of our window.</param>
	/// <param name="height"> It will take the hightof our window</param>
	/// <param name="Format"> It is a classifier that will allow bit spaces to be created correctly in memory.</param>
	/// <param name="Blindflags"> It is a characteristic to classify the type of texture that is being created.</param>
	void init(Device device, unsigned int width, unsigned int height, DXGI_FORMAT Format, unsigned int Bindflags);
	/// <summary>
	/// Brief: This method is in charge of updating the logic of the texture.
	/// </summary>
	void update();
	/// <summary>
	/// Brief: This method is in change of drawing the resources on the screen. (only if necessary)
	/// </summary>
	/// <param name="deviceContext"> It is in change of assigning resources to be used.</param>
	/// <param name="StartSlot"> It is in change of assigning the starting point in memory. </param>
	/// We reccomended checking it is not spliced?? in memory with other resources.</param>
	void render(DeviceContext& deviceContext, unsigned int StartSlot,unsigned int NumViews);
	/// <summary>
	/// Brief: This method is in change of releasing the resources stored in the class's memory.
	/// </summary>
	void destroy();

public:
	//this variable is in change of handle a texture resource as data
	ID3D11Texture2D* m_texture = nullptr;
	//this variable is in change of handle  texture recource as image data
	ID3D11ShaderResourceView* m_textureFromImg;
};

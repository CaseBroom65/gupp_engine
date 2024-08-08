#pragma once
#include "PreRequisitos.h"
#include "Component.h"
#include "DeviceContext.h"

/*
* Clase MeshComponent 
*  componente que representa una malla de juego.
* 
* La clase Mesh Component hereda de Component y representa una malla con vertices e indices.
* permite actualización y renderización
*/


class MeshComponent : public Component {
public:
	/*Constructor por defecto
	*
	* Inicializar el componente de malla con tipo 'ComponentType:MESH' y valores por defecto.
	*/
	MeshComponent() : m_numVertex(0), m_numIndex(0), Component(ComponentType::MESH) {}

	/*Descturctor virtual*/
	virtual ~MeshComponent() = default;

	/*actualizar el componente de malla
	*param deltaTime El tiempo trancurrido desde la ultima actualización.
	*/

	void
		update(float deltaTime) override {}

	/*Renderizar el componente de la malla
	param deviceContext Contexto del dispositivo para operaciones graficas*/

	void 
		render(DeviceContext deviceContext) override {}

public:

	std::string m_name;	//Nombre de la malla
	std::vector<SimpleVertex> m_vertex; //Vertices en la malla.
	std::vector<unsigned int>m_index;	//Indices en la malla.
	int m_numVertex;  //numero de vertices.
	int m_numIndex;	 //numero de indices.
};

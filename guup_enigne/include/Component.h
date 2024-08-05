#pragma once
class DeviceContext;

/*
* enum ComponentType
* Tipos de componentes disponibles en el juego.
*/

enum ComponentType
{
	NONE = 0,		///Tipo de componente no especificado
	TRANSFORM= 1,	///Componente de transformación
	MESH =2,		///componente de la malla.
	MATERIAL =3		///Componente de material.
};

/*
* class component
*  clase base abstracta para todos los componentes del juego.
* 
* La clase component define la interfaz basica que todos los componentes deben implementar,
* permitiendo actualizar y renderizar el componente , asi como obtener su tipo.
*/

class Component
{
public:
	/*Constructor por defecto*/
	Component() = default;

	/*
	* Constructor cdon tipo de componente.
	* param Type Tipo de componente.
	*/
	Component(const ComponentType type) : m_type(type) {}

	/*Destructor Virtual*/
	virtual ~Component() = default;

	/*Metodo virtual puro para actualizar el componente.
	* Param deltaTime El tiempo transcurrido desde la ultima actualización.
	*/

	virtual void update(float deltaTime) = 0;

	/*
	* metodo virutal para renderizar el componente
	* param DeviceContext Contexto  del dispositivo para operaciones graficas.
	*/

	virtual void render(DeviceContext deviceContext) = 0;

	/*
	*Obtiene el tipo del componente
	* return el tipo de componente
	*/
	ComponentType getType() const { return m_type; }

protected:
	ComponentType m_type; ///Tipo de Componente.
};
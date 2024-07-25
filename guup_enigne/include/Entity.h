#pragma once
#include "PreRequisitos.h"
#include "Component.h"
//#include "Transform.h"


class DeviceContext;

/*
*Class Enitity
*Clase basica para todas la enitdades en el juego.
*
*La clase Entity representa culaquier objeto que pueda tener componentes 
*y que se puedan actualizar y renderizar
*/

class Entity
{
public:
	//destructor virtual
	virtual ~Entity() = default;

	/*
	Metodo virtual puro para actualizar la entidad
	param deltatime el tiempo trancurrido desde la ultima actualizacion
	param DevicxeContext Contexto del dispositivo para operaciones graficas 
	*/

	virtual void update(float DeltaTime, DeviceContext deviceContext) = 0;

	/*
	* metodo virtual puro para renderizar la entidad
	* deviceContext contexto del dispositivo para operaciones graficos.
	*/
	virtual void render(DeviceContext deviceContext) = 0;

	/*
	*Agrega un componente a la entidad
	* tparam T Tipo del componente, debe derivar del component.
	* param component Puntero compartido al componente que va a agregar.
	*/

	template <typename T>
	void addComponent(std::shared_ptr<T> component)
	{
		static assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
		components.push_back(component);
	}

	/*
	* Obtiene un componente de la entidad.
	* tparam T tipo del componente que va a obtener.
	* return Puntero Compartido al componente, o nullptr si no se encuentra 
	*/
	template <typename T>
	std::shared_ptr<T>getComponent() 
	{
		for (auto& component : components)
		{
			std::shared_ptr<T> specificComponent = std::dynamic_pointer_cast<T>(component);
			if (specificComponent)
			{
				return specificComponent;
			}
		}
		return nullptr;
	}

protected:
	bool IsActive; ///Indica si la entidad esta activa.
	std::string id; ///Identificador unico de la entidad.

	std::vector<std::shared_ptr<Component>> Components; /// Lista de componentes de la entidad.

};

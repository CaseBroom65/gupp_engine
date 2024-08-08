#pragma once
#include "PreRequisitos.h"
#include "Entity.h"
#include "Buffer.h"
#include "Texture.h"
#include "SampleState.h"
#include "Transform.h"

class Device;
class MeshComponent;
/*Class Actor
 *clase que representa un actor en el juego
 *
 * La clase Actor hereda de Entity y representa un objeto en el juego que puede tener mallas,
 * texturas y varios componentes. Proporciona metodos para actualizar , renderizar, y destruir un actor.
*/
class Actor : public Entity{
public:
	/*Constructor por defecto*/
	Actor() = default;
	/*Constructor que inicializa el actor con el dispositivo.
	* param device El dispositivo con el cual se inicializa el actor.
	*/
	Actor(Device device);

	/*destructor virtual*/
	virtual ~Actor() = default;

	/*Actualizar al actor.
	 *deltaTime El tiempo transcurrido desde la ultima actualización.
	 *deviceContext Contexto del dispositivo para operaciones graficas.
	 */
	void 
	update(float deltaTime, DeviceContext deviceContext) override;

	void 
	render(DeviceContext deviceContext)override;
	/*Destruye el actor y libera los recursos asociados*/

	void 
	destroy();
	/*obtiene un componente especifico del actor.
	param T Tipo del componente que se va a obtener
	return puntero compartido al componente, o nullptr si no se encuentra*/
	template <typename T>
	std::shared_ptr<T> getComponent();
	/*Establece mallas en el actor
	param device El dispositivo con el cual se inicializan las mallas
	param meshes Vector de componentes de mallas que se van a establecer*/

	void 
	SetMesh(Device device, std::vector<MeshComponent> meshes);
	/*Establece las texturas del actor
	param textures Vector de trexturas  que se van a establecer*/

	void 
	SetTextures(std::vector<Texture> textures);
	/*Obtiene el nombre del actor
	return el nombre del actor.
	*/

	std::string getName() { return m_name; }

private:
	std::vector<MeshComponent> m_meshes; //vector de componentes de malla
	std::vector<Texture> m_textures; //vector de texturas
	SamplerState m_sampler;   //Estado de muestreo.
	std::vector<Buffer> m_vertexBuffers; //Buffer de los vertices
	std::vector<Buffer> m_indexBuffers; //Buffer de los indices
	Buffer m_modelBuffer;
	CBChangesEveryFrame model;
	std::string m_name = "Actor";
};
template <typename T>
inline std::shared_ptr<T> Actor::getComponent()
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

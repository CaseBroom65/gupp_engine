#pragma once
#include "PreRequisitos.h"
#include "Component.h"
#include "UserInterface.h"




class Transform : public Component
{
public:
	Transform()=default;
	~Transform()=default;

	void init();
	void update(float deltaTime);
	void render(DeviceContext deviceContext);
	void destroy();


public:
	XMMATRIX matrix;
};


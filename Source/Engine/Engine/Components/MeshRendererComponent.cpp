#include "MeshRendererComponent.h"
#include "Engine/Graphics/GPUContext.h"
#include "Engine/Graphics/Models/Model.h"


using namespace DawnEngine;


void MeshRendererComponent::Start()
{
	ComponentBase::Start();
	m_Model->InitGPUResource();
}


void MeshRendererComponent::Render(GPUContext* context)
{
	m_Model->Draw(context);
}
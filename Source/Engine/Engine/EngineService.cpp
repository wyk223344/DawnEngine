
#include "Engine/Core/Log.h"
#include "Engine/Engine/EngineService.h"
#include <algorithm>

using namespace DawnEngine;

static bool CompareEngineServices(EngineService* const& a, EngineService* const& b)
{
	return a->Order < b->Order;
}

#define DEFINE_ENGINE_SERVICE_EVENT(name) \
	void EngineService::name() { } \
	void EngineService::On##name() \
	{ \
		auto& services = GetServices(); \
		for (int32 i = 0; i < services.size(); i++) \
			services[i]->name(); \
	}

#define DEFINE_ENGINE_SERVICE_EVENT_INVERTED(name) \
	void EngineService::name() { } \
	void EngineService::On##name() \
	{ \
		auto& services = GetServices(); \
		for (int32 i = services.size() - 1; i >= 0; i--) \
			services[i]->name(); \
	}

DEFINE_ENGINE_SERVICE_EVENT(Update);
DEFINE_ENGINE_SERVICE_EVENT(LateUpdate);
DEFINE_ENGINE_SERVICE_EVENT(FixedUpdate);
DEFINE_ENGINE_SERVICE_EVENT(Draw);
DEFINE_ENGINE_SERVICE_EVENT_INVERTED(BeforeExit);


EngineService::EngineServicesArray& EngineService::GetServices()
{
	static EngineServicesArray Services;
	return Services;
}

void EngineService::Sort()
{
	auto& services = GetServices();
	std::sort(services.begin(), services.end(), CompareEngineServices);
}

EngineService::EngineService(const Char* name, int32 order)
{
	Name = name;
	Order = order;

	auto& services = GetServices();
	services.push_back(this);
	if (services[0]->IsInitialized)
	{
		Sort();
	}
}

bool EngineService::Init()
{
	return false;
}

void EngineService::OnInit()
{
	Sort();

	auto& services = GetServices();
	for (int32 i = 0; i < services.size(); i++)
	{
		const auto service = services[i];
		LOG_INFO("Initialize %s...", service->Name);
		service->IsInitialized = true;
		service->Init();
	}
	LOG_INFO("Engine services are ready!");
}

void EngineService::Dispose()
{
}

void EngineService::OnDispose()
{
	auto& services = GetServices();
	for (int32 i = services.size() - 1; i >= 0; i--)
	{
		const auto service = services[i];
		if (service->IsInitialized)
		{
			service->IsInitialized = false;
			service->Dispose();
		}
	}
}
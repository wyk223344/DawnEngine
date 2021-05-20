#pragma once


#include "Engine/Core/Types/BaseTypes.h"
#include <vector>


class EngineService
{
public:
	typedef std::vector<EngineService*> EngineServicesArray;

public:

	/// <summary>
	/// 获取注册的Services
	/// </summary>
	/// <returns></returns>
	static EngineServicesArray& GetServices();

	/// <summary>
	/// 排序注册的Services
	/// </summary>
	static void Sort();

private:
	
	bool IsInitialized = false;

protected:
	
	EngineService(const Char* name, int32 order = 0);

public:

	virtual ~EngineService() = default;

	const Char* Name;
	int32 Order;

#define DECLARE_ENGINE_SERVICE_EVENT(result, name) virtual result name(); static void On##name();
	DECLARE_ENGINE_SERVICE_EVENT(bool, Init);
	DECLARE_ENGINE_SERVICE_EVENT(void, FixedUpdate);
	DECLARE_ENGINE_SERVICE_EVENT(void, Update);
	DECLARE_ENGINE_SERVICE_EVENT(void, LateUpdate);
	DECLARE_ENGINE_SERVICE_EVENT(void, Draw);
	DECLARE_ENGINE_SERVICE_EVENT(void, BeforeExit);
	DECLARE_ENGINE_SERVICE_EVENT(void, Dispose);
#undef DECLARE_ENGINE_SERVICE_EVENT
};
#include "Reflection.h"
#include <cstring>
#include <map>

using namespace DawnEngine;
using namespace DawnEngine::Reflection;

namespace ReflectionImpl
{
	const char* k_UnknownType = "UnknownType";
	const char* k_Unknown = "Unknown";

	static std::map<std::string, ClassFunctionTuple*>      s_ClassMap;
	static std::multimap<std::string, FieldFunctionTuple*> s_FieldMap;
	static std::map<std::string, ArrayFunctionTuple*>      s_ArrayMap;
}

#pragma region TypeMetaRegisterInterface

void TypeMetaRegisterInterface::RegisterToFieldMap(const char* name, FieldFunctionTuple* value)
{
	ReflectionImpl::s_FieldMap.insert(std::make_pair(name, value));
}

void TypeMetaRegisterInterface::RegisterToArrayMap(const char* name, ArrayFunctionTuple* value)
{
	if (ReflectionImpl::s_ArrayMap.find(name) == ReflectionImpl::s_ArrayMap.end())
	{
		ReflectionImpl::s_ArrayMap.insert(std::make_pair(name, value));
	}
	else
	{
		delete value;
	}
}

void TypeMetaRegisterInterface::RegisterToClassMap(const char* name, ClassFunctionTuple* value)
{
	if (ReflectionImpl::s_ClassMap.find(name) == ReflectionImpl::s_ClassMap.end())
	{
		ReflectionImpl::s_ClassMap.insert(std::make_pair(name, value));
	}
	else
	{
		delete value;
	}
}

void TypeMetaRegisterInterface::UnregisterAll()
{
	for (const auto& itr : ReflectionImpl::s_FieldMap)
	{
		delete itr.second;
	}
	ReflectionImpl::s_FieldMap.clear();
	for (const auto& itr : ReflectionImpl::s_ArrayMap)
	{
		delete itr.second;
	}
	ReflectionImpl::s_ArrayMap.clear();
	for (const auto& itr : ReflectionImpl::s_ClassMap)
	{
		delete itr.second;
	}
	ReflectionImpl::s_ClassMap.clear();
}

#pragma endregion


#pragma region TypeMeta

TypeMeta::TypeMeta() : m_TypeName(ReflectionImpl::k_UnknownType), m_IsValid(false) { m_Fields.clear(); }

TypeMeta::TypeMeta(std::string typeName) : m_TypeName(typeName)
{
	m_IsValid = false;
	m_Fields.clear();

	auto filedIter = ReflectionImpl::s_FieldMap.equal_range(typeName);
	while (filedIter.first != filedIter.second)
	{
		FieldAccessor fieldAccessor(filedIter.first->second);
		m_Fields.emplace_back(fieldAccessor);
		m_IsValid = true;

		++filedIter.first;
	}
}

TypeMeta TypeMeta::NewMetaFromName(std::string typeName)
{
	TypeMeta typeMeta(typeName);
	return typeMeta;
}

bool TypeMeta::NewArrayAccessorFromName(std::string arrayTypeName, ArrayAccessor& accessor)
{
	auto iter = ReflectionImpl::s_ArrayMap.find(arrayTypeName);

	if (iter != ReflectionImpl::s_ArrayMap.end())
	{
		ArrayAccessor newAccessor(iter->second);
		accessor = newAccessor;
		return true;
	}
	return false;
}

ReflectionInstance TypeMeta::NewFromNameAndJson(std::string typeName, const Json& jsonContext)
{
	auto iter = ReflectionImpl::s_ClassMap.find(typeName);

	if (iter != ReflectionImpl::s_ClassMap.end())
	{
		return ReflectionInstance(TypeMeta(typeName), (std::get<1>(*iter->second)(jsonContext)));
	}
	return ReflectionInstance();
}

Json TypeMeta::WriteByName(std::string typeName, void* instance)
{
	auto iter = ReflectionImpl::s_ClassMap.find(typeName);

	if (iter != ReflectionImpl::s_ClassMap.end())
	{
		return std::get<2>(*iter->second)(instance);
	}
	return Json();
}

int TypeMeta::GetFieldsList(FieldAccessor*& outList)
{
	int count = m_Fields.size();
	outList = new FieldAccessor[count];
	for (int i = 0; i < count; ++i)
	{
		outList[i] = m_Fields[i];
	}
	return count;
}

int TypeMeta::GetBaseClassReflectionInstanceList(ReflectionInstance*& out_list, void* instance)
{
	auto iter = ReflectionImpl::s_ClassMap.find(m_TypeName);

	if (iter != ReflectionImpl::s_ClassMap.end())
	{
		return (std::get<0>(*iter->second))(out_list, instance);
	}

	return 0;
}

FieldAccessor TypeMeta::GetFieldByName(const char* name)
{
	const auto it = std::find_if(
		m_Fields.begin(), 
		m_Fields.end(), 
		[&](const auto& i) { return std::strcmp(i.GetFieldName(), name) == 0; }
	);
	if (it != m_Fields.end())
		return *it;
	return FieldAccessor(nullptr);
}

TypeMeta& TypeMeta::operator=(const TypeMeta& dest)
{
	if (this == &dest)
	{
		return *this;
	}
	m_Fields.clear();
	m_Fields = dest.m_Fields;
	m_TypeName = dest.m_TypeName;
	m_IsValid = dest.m_IsValid;

	return *this;
}


#pragma endregion

#pragma region FieldAccessor

FieldAccessor::FieldAccessor()
{
	m_FieldName = ReflectionImpl::k_Unknown;
	m_FieldTypeName = ReflectionImpl::k_UnknownType;
	m_FunctionTuple = nullptr;
}

FieldAccessor::FieldAccessor(FieldFunctionTuple* functionTuple) : m_FunctionTuple(functionTuple)
{
	m_FieldName = ReflectionImpl::k_Unknown;
	m_FieldTypeName = ReflectionImpl::k_UnknownType;

	if (m_FunctionTuple == nullptr) return;

	m_FieldName = std::get<3>(*m_FunctionTuple)();
	m_FieldTypeName = std::get<4>(*m_FunctionTuple)();
}

void FieldAccessor::Set(void* instance, void* value)
{
	(std::get<0>(*m_FunctionTuple))(instance, value);
}

void* FieldAccessor::Get(void* instance)
{
	return static_cast<void*>((std::get<1>(*m_FunctionTuple))(instance));
}

TypeMeta FieldAccessor::GetOwnerTypeMeta()
{
	TypeMeta typeMeta((std::get<2>(*m_FunctionTuple))());
	return typeMeta;
}

bool FieldAccessor::GetTypeMeta(TypeMeta& fieldType)
{
	TypeMeta typeMeta(m_FieldTypeName);
	fieldType = typeMeta;
	return typeMeta.m_IsValid;
}

const char* FieldAccessor::GetFieldName() const { return m_FieldName; }

const char* FieldAccessor::GetFieldTypeName() { return m_FieldTypeName; }

bool FieldAccessor::IsArrayType()
{
	return (std::get<5>(*m_FunctionTuple))();
}

FieldAccessor& FieldAccessor::operator=(const FieldAccessor& dest)
{
	if (this == &dest)
	{
		return *this;
	}
	m_FunctionTuple = dest.m_FunctionTuple;
	m_FieldName = dest.m_FieldName;
	m_FieldTypeName = dest.m_FieldTypeName;
	return *this;
}

#pragma endregion

#pragma region ArrayAccessor

ArrayAccessor::ArrayAccessor() 
{
	m_ArrayTypeName = ReflectionImpl::k_UnknownType;
	m_ElementTypeName = ReflectionImpl::k_UnknownType;
	m_FunctionTuple = nullptr;
}

ArrayAccessor::ArrayAccessor(ArrayFunctionTuple* functionTuple) : m_FunctionTuple(functionTuple)
{
	m_ArrayTypeName = ReflectionImpl::k_UnknownType;
	m_ElementTypeName = ReflectionImpl::k_UnknownType;
	
	if (m_FunctionTuple == nullptr) return;

	m_ArrayTypeName = std::get<3>(*m_FunctionTuple)();
	m_ElementTypeName = std::get<4>(*m_FunctionTuple)();
}

void ArrayAccessor::Set(int index, void* instance, void* elementValue)
{
	std::get<0>(*m_FunctionTuple)(index, instance, elementValue);
}

void* ArrayAccessor::Get(int index, void* instance)
{
	return std::get<1>(*m_FunctionTuple)(index, instance);
}

int ArrayAccessor::GetSize(void* instance)
{
	return std::get<2>(*m_FunctionTuple)(instance);
}

const char* ArrayAccessor::GetArrayTypeName() { return m_ArrayTypeName; }

const char* ArrayAccessor::GetElementTypeName() { return m_ElementTypeName; }

ArrayAccessor& ArrayAccessor::operator=(ArrayAccessor& dest)
{
	if (this == &dest)
	{
		return *this;
	}
	m_FunctionTuple = dest.m_FunctionTuple;
	m_ArrayTypeName = dest.m_ArrayTypeName;
	m_ElementTypeName = dest.m_ElementTypeName;
	return *this;
}
			
#pragma endregion


#pragma region ReflectionInstance

ReflectionInstance& ReflectionInstance::operator=(ReflectionInstance& dest)
{
	if (this == &dest)
	{
		return *this;
	}
	m_Instance = dest.m_Instance;
	m_Meta = dest.m_Meta;
	return *this;
}

ReflectionInstance& ReflectionInstance::operator=(ReflectionInstance&& dest)
{
	if (this == &dest)
	{
		return *this;
	}
	m_Instance = dest.m_Instance;
	m_Meta = dest.m_Meta;
	return *this;
}

#pragma endregion

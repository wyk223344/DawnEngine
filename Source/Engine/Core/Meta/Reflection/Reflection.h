#pragma once

#include "Engine/Core/Meta/Json.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


namespace DawnEngine
{

    namespace Reflection
    {
        class TypeMeta;
        class FieldAccessor;
        class ArrayAccessor;
        class ReflectionInstance;
    }

    typedef std::function<void(void*, void*)>      SetFunction;
    typedef std::function<void* (void*)>           GetFunction;
    typedef std::function<const char* ()>          GetNameFunction;
    typedef std::function<void(int, void*, void*)> SetArrayFunc;
    typedef std::function<void* (int, void*)>      GetArrayFunc;
    typedef std::function<int(void*)>              GetSizeFunc;
    typedef std::function<bool()>                  GetBoolFunc;

    typedef std::function<void* (const Json&)>                          ConstructorWithPJson;
    typedef std::function<Json(void*)>                                  WritePJsonByName;
    typedef std::function<int(Reflection::ReflectionInstance*&, void*)> GetBaseClassReflectionInstanceListFunc;

    typedef std::tuple<SetFunction, GetFunction, GetNameFunction, GetNameFunction, GetNameFunction, GetBoolFunc> FieldFunctionTuple;
    typedef std::tuple<SetArrayFunc, GetArrayFunc, GetSizeFunc, GetNameFunction, GetNameFunction> ArrayFunctionTuple;
    typedef std::tuple<GetBaseClassReflectionInstanceListFunc, ConstructorWithPJson, WritePJsonByName> ClassFunctionTuple;

    namespace Reflection
    {
        class TypeMetaRegisterInterface
        {
        public:
            static void RegisterToClassMap(const char* name, ClassFunctionTuple* value);
            static void RegisterToFieldMap(const char* name, FieldFunctionTuple* value);
            static void RegisterToArrayMap(const char* name, ArrayFunctionTuple* value);

            static void UnregisterAll();
        };

        class TypeMeta
        {
            friend class FieldAccessor;
            friend class ArrayAccessor;
            friend class TypeMetaRegisterInterface;

        public:

            static TypeMeta NewMetaFromName(std::string typeName);

            static bool NewArrayAccessorFromName(std::string arrayTypeName, ArrayAccessor& accessor);

            static ReflectionInstance NewFromNameAndJson(std::string typeName, const Json& jsonContext);
            
            static Json WriteByName(std::string typeName, void* instance);

        public:

            TypeMeta();

            int GetFieldsList(FieldAccessor*& outList);

            int GetBaseClassReflectionInstanceList(ReflectionInstance*& out_list, void* instance);

            FieldAccessor GetFieldByName(const char* name);

            TypeMeta& operator=(const TypeMeta& dest);

            std::string GetTypeName() { return m_TypeName; }

            bool IsValid() { return m_IsValid; }

        private:

            TypeMeta(std::string typeName);

        private:
            std::vector<FieldAccessor, std::allocator<FieldAccessor>> m_Fields;
            std::string m_TypeName;
            bool m_IsValid;
        };

        class FieldAccessor
        {
            friend class TypeMeta;

        public:
            FieldAccessor();

            void  Set(void* instance, void* value);
            void* Get(void* instance);

            TypeMeta GetOwnerTypeMeta();

            bool        GetTypeMeta(TypeMeta& fieldType);
            const char* GetFieldName() const;
            const char* GetFieldTypeName();
            bool        IsArrayType();

            FieldAccessor& operator=(const FieldAccessor& dest);

        private:
            FieldAccessor(FieldFunctionTuple* functionTuple);

        private:
            FieldFunctionTuple* m_FunctionTuple;
            const char* m_FieldName;
            const char* m_FieldTypeName;
        };

        class ArrayAccessor
        {
            friend class TypeMeta;

        public:
            ArrayAccessor();

            void  Set(int index, void* instance, void* elementValue);
            void* Get(int index, void* instance);

            const char* GetArrayTypeName();
            const char* GetElementTypeName();
            
            int GetSize(void* instance);

            ArrayAccessor& operator=(ArrayAccessor& dest);

        private:
            ArrayAccessor(ArrayFunctionTuple* functionTuple);

        private:
            ArrayFunctionTuple* m_FunctionTuple;
            const char* m_ArrayTypeName;
            const char* m_ElementTypeName;
        };

        class ReflectionInstance
        {
        public:
            ReflectionInstance(TypeMeta meta, void* instance) : m_Meta(meta), m_Instance(instance) {}
            ReflectionInstance() : m_Meta(), m_Instance(nullptr) {}

            ReflectionInstance& operator=(ReflectionInstance& dest);

            ReflectionInstance& operator=(ReflectionInstance&& dest);

        public:
            TypeMeta m_Meta;
            void* m_Instance;
        };

        template<typename T>
        class ReflectionPtr
        {
        public:
            ReflectionPtr() : m_TypeName(), m_Instance(nullptr) {}
            ReflectionPtr(std::string typeName, T* instance) : m_TypeName(typeName), m_Instance(instance) {}
            ReflectionPtr(const ReflectionPtr& dest) : m_TypeName(dest.m_TypeName), m_Instance(dest.m_Instance) {}



        private:
            std::string m_TypeName;
            typedef T m_Type;
            T* m_Instance;
        };
    }
}
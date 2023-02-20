#pragma once

#include "Engine/Core/Meta/Json.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


namespace DawnEngine
{

#if defined(__REFLECTION_PARSER__)
#define META(...) __attribute__((annotate(#__VA_ARGS__)))
#define CLASS(class_name, ...) class __attribute__((annotate(#__VA_ARGS__))) class_name
#define STRUCT(struct_name, ...) struct __attribute__((annotate(#__VA_ARGS__))) struct_name
    //#define CLASS(class_name,...) class __attribute__((annotate(#__VA_ARGS__))) class_name:public Reflection::object
#else
#define META(...)
#define CLASS(class_name, ...) class class_name
#define STRUCT(struct_name, ...) struct struct_name
    //#define CLASS(class_name,...) class class_name:public Reflection::object
#endif // __REFLECTION_PARSER__

#define REFLECTION_BODY(class_name) \
    friend class Reflection::TypeFieldReflectionOparator::Type##class_name##Operator; \
    friend class Serializer;
    // public: virtual std::string getTypeName() override {return #class_name;}

#define REFLECTION_TYPE(class_name) \
    namespace Reflection \
    { \
        namespace TypeFieldReflectionOparator \
        { \
            class Type##class_name##Operator; \
        } \
    };

#define REGISTER_FIELD_TO_MAP(name, value) TypeMetaRegisterInterface::RegisterToFieldMap(name, value);
#define REGISTER_BASE_CLASS_TO_MAP(name, value) TypeMetaRegisterInterface::RegisterToClassMap(name, value);
#define REGISTER_ARRAY_TO_MAP(name, value) TypeMetaRegisterInterface::RegisterToArrayMap(name, value);
#define UNREGISTER_ALL TypeMetaRegisterInterface::UnregisterAll();

#define DAWN_REFLECTION_NEW(name, ...) Reflection::ReflectionPtr(#name, new name(__VA_ARGS__));
#define DAWN_REFLECTION_DELETE(value) \
    if (value) \
    { \
        delete value.operator->(); \
        value.getPtrReference() = nullptr; \
    }
#define DAWN_REFLECTION_DEEP_COPY(type, dst_ptr, src_ptr) \
    *static_cast<type*>(dst_ptr) = *static_cast<type*>(src_ptr.getPtr());

// #define TypeMetaDef(class_name, ptr) \
//     Piccolo::Reflection::ReflectionInstance(Piccolo::Reflection::TypeMeta::newMetaFromName(#class_name), (class_name*)ptr)

// #define TypeMetaDefPtr(class_name, ptr) \
//     new Piccolo::Reflection::ReflectionInstance(Piccolo::Reflection::TypeMeta::newMetaFromName(#class_name), \
//                                               (class_name*)ptr)

//     template<typename T, typename U, typename = void>
//     struct is_safely_castable : std::false_type
//     {};

//     template<typename T, typename U>
//     struct is_safely_castable<T, U, std::void_t<decltype(static_cast<U>(std::declval<T>()))>> : std::true_type
//     {};

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

            template<typename U /*, typename = typename std::enable_if<std::is_safely_castable<T*, U*>::value>::type */>
            ReflectionPtr<T>& operator=(const ReflectionPtr<U>& dest)
            {
                if (this == static_cast<void*>(&dest))
                {
                    return *this;
                }
                m_TypeName = dest.m_TypeName;
                m_Instance = static_cast<T*>(dest.m_Instance);
                return *this;
            }

            template<typename U /*, typename = typename std::enable_if<std::is_safely_castable<T*, U*>::value>::type*/>
            ReflectionPtr<T>& operator=(ReflectionPtr<U>&& dest)
            {
                if (this == static_cast<void*>(&dest))
                {
                    return *this;
                }
                m_TypeName = dest.m_TypeName;
                m_Instance = static_cast<T*>(dest.m_Instance);
                return *this;
            }

            ReflectionPtr<T>& operator=(const ReflectionPtr<T>& dest)
            {
                if (this == &dest)
                {
                    return *this;
                }
                m_TypeName = dest.m_TypeName;
                m_Instance = dest.m_Instance;
                return *this;
            }

            ReflectionPtr<T>& operator=(ReflectionPtr<T>&& dest)
            {
                if (this == &dest)
                {
                    return *this;
                }
                m_TypeName = dest.m_TypeName;
                m_Instance = dest.m_Instance;
                return *this;
            }

            std::string GetTypeName() const { return m_TypeName; }

            void SetTypeName(std::string name) { m_TypeName = name; }

            bool operator==(const T* ptr) const { return (m_Instance == ptr); }

            bool operator!=(const T* ptr) const { return (m_Instance != ptr); }

            bool operator==(const ReflectionPtr<T>& rhsPtr) const { return (m_Instance == rhsPtr.m_Instance); }

            bool operator!=(const ReflectionPtr<T>& rhsPtr) const { return (m_Instance != rhsPtr.m_Instance); }



        private:
            std::string m_TypeName;
            typedef T m_Type;
            T* m_Instance;
        };
    }
}
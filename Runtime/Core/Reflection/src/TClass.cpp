#include "TClass.h"
#include "VarRange.h"

std::unordered_map<Type,TypeInfo> TClass::typeinfos;
TypeIDRegistry TClass::tregistry;
NameIDRegistry TClass::nregistry;
std::shared_ptr<std::pmr::memory_resource>TClass::object_resource=std::make_shared<std::pmr::synchronized_pool_resource>();

ObjectView TClass::MakeShared(Type type, ArgsView args ){
	return MMakeShared(type, object_resource.get(), args);
}

ObjectView TClass::MMakeShared(Type type, std::pmr::memory_resource* rsrc, ArgsView args){
	ObjectView obj = MNew(type, rsrc, args);
	return obj;
}

ObjectView TClass::MNew(Type type, std::pmr::memory_resource* rsrc, ArgsView args){
	auto target = typeinfos.find(type);
	if (target==typeinfos.end())
	{
		return {};
	}
	auto& typeinfo = target->second;
	void* buffer = rsrc->allocate(std::max<std::size_t>(1, typeinfo.size), typeinfo.alignment);
	if (!buffer) {
		return{};
	}
	ObjectView obj(type, buffer);
	bool sucess = Construct(obj, args);
	assert(sucess);
	return obj;
}

Type TClass::Invoke(ObjectView obj, Name method_name, void* result_buffer, ArgsView args, MethodFlag flag)
{
	auto typeInfo = GetTypeInfo(obj.GetType());
	auto methodInfo = typeInfo->methodInfos.find(method_name);
	if (methodInfo == typeInfo->methodInfos.end()) {
		return obj.GetType();
	}
	auto func = methodInfo->second.methodptr;
	func.Invoke(&obj, result_buffer, args);
	return obj.GetType();
}

ObjectView TClass::Var(ObjectView obj, Name field_name, FieldFlag flag)
{
	//for (const auto& [name, var] : VarRange{ obj,flag }) {
	//	if (name == field_name) {
	//		return var;
	//	}
	//}
	//return {};
	auto typeInfo = GetTypeInfo(obj.GetType());
	if (typeInfo == nullptr) {
		return {};
	}
	auto target = typeInfo->fieldInfos.find(field_name);
	if (target == typeInfo->fieldInfos.end()) {
		return {};
	}
	char* p = (char*)obj.GetPtr();
	p += target->second.fieldPtr.offset();
	return { type_of<float>,p };
}


Type TClass::RegisterType(Type type, size_t size, size_t alignment, bool is_polymorphic, bool is_tarivil)
{
	assert(alignment > 0 &&(alignment & (alignment - 1)) == 0);
	auto target = typeinfos.find(type);
	if (target != typeinfos.end()) {
		return {};
	}
	Type new_type = { tregistry.Register(type.GetID(),type.GetName()),type.GetID() };
	typeinfos.emplace_hint(target, new_type, TypeInfo{ size,alignment,is_polymorphic, is_tarivil });
	if (is_tarivil) {
		AddTrivialCopyConstructor(new_type);
	}
	return new_type;
}

bool TClass::Construct(ObjectView obj, ArgsView args){
	auto target = typeinfos.find(obj.GetType());
	if (target == typeinfos.end()) {
		return false;
	}
	const auto& typeinfo = target->second;
	if (args.Types().empty() && typeinfo.is_trivial) {
		return true;
	}
	auto [begin_iter, end_iter] = typeinfo.methodInfos.equal_range(NameIDRegistry::Meta::ctor);
	for (auto iter = begin_iter; iter != end_iter; ++iter) {
		if (iter->second.methodptr.GetMethodFlag() == MethodFlag::Variable) {
			if (iter->second.methodptr.IsMatch(&args)) {
				iter->second.methodptr.Invoke(obj.GetPtr(), nullptr, args);
				return true;
			}
		}
	}
	return false;
}

bool TClass::AddField(Type type,Name field_name,FieldInfo fieldInfo)
{
    auto typeinfo= GetTypeInfo(type);
    if(!typeinfo){
        assert(false);
    }
    auto ftarget=typeinfo->fieldInfos.find(field_name);
    if(ftarget!=typeinfo->fieldInfos.end()){
        return false;
    }
    Name new_field_name={nregistry.Register(field_name.GetID(),field_name.GetName()),field_name.GetID()};
    typeinfo->fieldInfos.emplace_hint(ftarget,new_field_name,std::move(fieldInfo));
}

bool TClass::AddBase(Type  derived, Type base, BaseInfo baseInfo)
{
	auto typeinfo = GetTypeInfo(derived);
	if (!typeinfo) {
		return {};
	}
	auto baseTarget =typeinfo->baseInfos.find(base);
	if (baseTarget != typeinfo->baseInfos.end()) {
		return {};
	}
	typeinfo->baseInfos.emplace_hint(baseTarget, base, std::move(baseInfo));
}


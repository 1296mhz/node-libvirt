// Copyright 2010, Camilo Aguilar. Cloudescape, LLC.
#ifndef SRC_INTERFACE_H_
#define SRC_INTERFACE_H_

#include "node_libvirt.h"

#include "nlv_async_worker.h"
#include "worker_macros.h"

namespace NodeLibvirt {

class Interface : public ObjectWrap
{
public:
  static void Initialize(Handle<Object> exports);
  static Local<Object> NewInstance2(virInterfacePtr handle);
  virtual ~Interface();

  virInterfacePtr GetInterface() const;

private:
  static Persistent<Function> constructor;
  virInterfacePtr handle_;

  friend class Hypervisor;

private:
  explicit Interface(virInterfacePtr handle) : handle_(handle) {}

  // HYPERVISOR METHODS
  static NAN_METHOD(LookupByName);
  static NAN_METHOD(LookupByMacAddress);
  static NAN_METHOD(Define);

  // METHODS
  static NAN_METHOD(Start);
  static NAN_METHOD(Stop);
  static NAN_METHOD(Undefine);
  static NAN_METHOD(IsActive);
  static NAN_METHOD(GetName);
  static NAN_METHOD(GetMacAddress);
  static NAN_METHOD(ToXml);

private:
  // HYPERVISOR METHOD WORKERS
  NLV_LOOKUP_BY_VALUE_WORKER2(LookupByName, Interface, virConnectPtr, virInterfacePtr);
  NLV_LOOKUP_BY_VALUE_WORKER2(LookupByMacAddress, Interface, virConnectPtr, virInterfacePtr);
  NLV_LOOKUP_BY_VALUE_WORKER2(Define, Interface, virConnectPtr, virInterfacePtr);

  // WORKERS
  NLV_PRIMITIVE_RETURN_WORKER2(Start, virInterfacePtr, bool);
  NLV_PRIMITIVE_RETURN_WORKER2(Stop, virInterfacePtr, bool);
  NLV_PRIMITIVE_RETURN_WORKER2(Undefine, virInterfacePtr, bool);
  NLV_PRIMITIVE_RETURN_WORKER2(IsActive, virInterfacePtr, bool);
  NLV_PRIMITIVE_RETURN_WORKER2(GetName, virInterfacePtr, std::string);
  NLV_PRIMITIVE_RETURN_WORKER2(GetMacAddress, virInterfacePtr, std::string);
  NLV_PRIMITIVE_RETURN_WORKER2(ToXml, virInterfacePtr, std::string);


};

}  // namespace NodeLibvirt

#endif  // SRC_INTERFACE_H_

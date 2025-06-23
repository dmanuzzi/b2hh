// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME sel_RooJohnsonFunc_dict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "sel_RooJohnsonFunc.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_sel_RooJohnsonFunc(void *p = nullptr);
   static void *newArray_sel_RooJohnsonFunc(Long_t size, void *p);
   static void delete_sel_RooJohnsonFunc(void *p);
   static void deleteArray_sel_RooJohnsonFunc(void *p);
   static void destruct_sel_RooJohnsonFunc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::sel_RooJohnsonFunc*)
   {
      ::sel_RooJohnsonFunc *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::sel_RooJohnsonFunc >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("sel_RooJohnsonFunc", ::sel_RooJohnsonFunc::Class_Version(), "sel_RooJohnsonFunc.h", 16,
                  typeid(::sel_RooJohnsonFunc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::sel_RooJohnsonFunc::Dictionary, isa_proxy, 4,
                  sizeof(::sel_RooJohnsonFunc) );
      instance.SetNew(&new_sel_RooJohnsonFunc);
      instance.SetNewArray(&newArray_sel_RooJohnsonFunc);
      instance.SetDelete(&delete_sel_RooJohnsonFunc);
      instance.SetDeleteArray(&deleteArray_sel_RooJohnsonFunc);
      instance.SetDestructor(&destruct_sel_RooJohnsonFunc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::sel_RooJohnsonFunc*)
   {
      return GenerateInitInstanceLocal(static_cast<::sel_RooJohnsonFunc*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::sel_RooJohnsonFunc*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr sel_RooJohnsonFunc::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *sel_RooJohnsonFunc::Class_Name()
{
   return "sel_RooJohnsonFunc";
}

//______________________________________________________________________________
const char *sel_RooJohnsonFunc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::sel_RooJohnsonFunc*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int sel_RooJohnsonFunc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::sel_RooJohnsonFunc*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *sel_RooJohnsonFunc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::sel_RooJohnsonFunc*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *sel_RooJohnsonFunc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::sel_RooJohnsonFunc*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void sel_RooJohnsonFunc::Streamer(TBuffer &R__b)
{
   // Stream an object of class sel_RooJohnsonFunc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(sel_RooJohnsonFunc::Class(),this);
   } else {
      R__b.WriteClassBuffer(sel_RooJohnsonFunc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_sel_RooJohnsonFunc(void *p) {
      return  p ? new(p) ::sel_RooJohnsonFunc : new ::sel_RooJohnsonFunc;
   }
   static void *newArray_sel_RooJohnsonFunc(Long_t nElements, void *p) {
      return p ? new(p) ::sel_RooJohnsonFunc[nElements] : new ::sel_RooJohnsonFunc[nElements];
   }
   // Wrapper around operator delete
   static void delete_sel_RooJohnsonFunc(void *p) {
      delete (static_cast<::sel_RooJohnsonFunc*>(p));
   }
   static void deleteArray_sel_RooJohnsonFunc(void *p) {
      delete [] (static_cast<::sel_RooJohnsonFunc*>(p));
   }
   static void destruct_sel_RooJohnsonFunc(void *p) {
      typedef ::sel_RooJohnsonFunc current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::sel_RooJohnsonFunc

namespace {
  void TriggerDictionaryInitialization_sel_RooJohnsonFunc_dict_Impl() {
    static const char* headers[] = {
"sel_RooJohnsonFunc.h",
nullptr
    };
    static const char* includePaths[] = {
"/cvmfs/sft.cern.ch/lcg/releases/ROOT/6.30.02-fb5be/x86_64-el9-gcc13-opt/include/",
"/home/ceph/mcaporal/bspipi/src/newBDTtrain/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "sel_RooJohnsonFunc_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$sel_RooJohnsonFunc.h")))  sel_RooJohnsonFunc;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "sel_RooJohnsonFunc_dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "sel_RooJohnsonFunc.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"sel_RooJohnsonFunc", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("sel_RooJohnsonFunc_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_sel_RooJohnsonFunc_dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_sel_RooJohnsonFunc_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_sel_RooJohnsonFunc_dict() {
  TriggerDictionaryInitialization_sel_RooJohnsonFunc_dict_Impl();
}

// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME FitToolsDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
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

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "FitTools.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *FitTools_Dictionary();
   static void FitTools_TClassManip(TClass*);
   static void delete_FitTools(void *p);
   static void deleteArray_FitTools(void *p);
   static void destruct_FitTools(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FitTools*)
   {
      ::FitTools *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FitTools));
      static ::ROOT::TGenericClassInfo 
         instance("FitTools", "FitTools.h", 19,
                  typeid(::FitTools), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &FitTools_Dictionary, isa_proxy, 0,
                  sizeof(::FitTools) );
      instance.SetDelete(&delete_FitTools);
      instance.SetDeleteArray(&deleteArray_FitTools);
      instance.SetDestructor(&destruct_FitTools);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FitTools*)
   {
      return GenerateInitInstanceLocal((::FitTools*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FitTools*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FitTools_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FitTools*)0x0)->GetClass();
      FitTools_TClassManip(theClass);
   return theClass;
   }

   static void FitTools_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FitTools(void *p) {
      delete ((::FitTools*)p);
   }
   static void deleteArray_FitTools(void *p) {
      delete [] ((::FitTools*)p);
   }
   static void destruct_FitTools(void *p) {
      typedef ::FitTools current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FitTools

namespace {
  void TriggerDictionaryInitialization_FitToolsDict_Impl() {
    static const char* headers[] = {
"FitTools.h",
0
    };
    static const char* includePaths[] = {
"/afs/cern.ch/sw/lcg/releases/ROOT/6.06.02-6cc9c/x86_64-slc6-gcc49-opt/include",
"/afs/cern.ch/user/r/rvazquez/RDS/DaVinciDev_v41r3/Phys/BsDsMuNuForRDS/Templates/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "FitToolsDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$FitTools.h")))  FitTools;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "FitToolsDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "FitTools.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FitTools", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("FitToolsDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_FitToolsDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_FitToolsDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_FitToolsDict() {
  TriggerDictionaryInitialization_FitToolsDict_Impl();
}

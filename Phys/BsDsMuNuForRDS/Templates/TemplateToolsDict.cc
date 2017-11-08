// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TemplateToolsDict

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
#include "TemplateTools.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *TemplateTools_Dictionary();
   static void TemplateTools_TClassManip(TClass*);
   static void delete_TemplateTools(void *p);
   static void deleteArray_TemplateTools(void *p);
   static void destruct_TemplateTools(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TemplateTools*)
   {
      ::TemplateTools *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TemplateTools));
      static ::ROOT::TGenericClassInfo 
         instance("TemplateTools", "TemplateTools.h", 17,
                  typeid(::TemplateTools), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TemplateTools_Dictionary, isa_proxy, 0,
                  sizeof(::TemplateTools) );
      instance.SetDelete(&delete_TemplateTools);
      instance.SetDeleteArray(&deleteArray_TemplateTools);
      instance.SetDestructor(&destruct_TemplateTools);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TemplateTools*)
   {
      return GenerateInitInstanceLocal((::TemplateTools*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TemplateTools*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TemplateTools_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TemplateTools*)0x0)->GetClass();
      TemplateTools_TClassManip(theClass);
   return theClass;
   }

   static void TemplateTools_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TemplateTools(void *p) {
      delete ((::TemplateTools*)p);
   }
   static void deleteArray_TemplateTools(void *p) {
      delete [] ((::TemplateTools*)p);
   }
   static void destruct_TemplateTools(void *p) {
      typedef ::TemplateTools current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TemplateTools

namespace {
  void TriggerDictionaryInitialization_TemplateToolsDict_Impl() {
    static const char* headers[] = {
"TemplateTools.h",
0
    };
    static const char* includePaths[] = {
"/afs/cern.ch/sw/lcg/releases/ROOT/6.06.02-6cc9c/x86_64-slc6-gcc49-opt/include",
"/afs/cern.ch/user/r/rvazquez/RDS/DaVinciDev_v41r3/Phys/BsDsMuNuForRDS/Templates/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TemplateToolsDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TemplateTools.h")))  TemplateTools;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TemplateToolsDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TemplateTools.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TemplateTools", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TemplateToolsDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TemplateToolsDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TemplateToolsDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TemplateToolsDict() {
  TriggerDictionaryInitialization_TemplateToolsDict_Impl();
}

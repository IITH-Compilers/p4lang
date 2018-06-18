/*
Copyright 2013-present Barefoot Networks, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef _BACKENDS_LLBMV2_HELPERS_H_
#define _BACKENDS_LLBMV2_HELPERS_H_

// #include "ir/ir.h"
#include "lib/cstring.h"
#include "lib/json.h"
#include "lib/ordered_map.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Support/raw_ostream.h"
#include "../JsonObjects.h"
#include <iomanip>

// #include "../analyzer.h"
// #include "frontends/common/model.h"

namespace LLVMJsonBackend {

/// constant used in LLBMV2 backend code generation
// class TableImplementation {
//  public:
//     static const cstring actionProfileName;
//     static const cstring actionSelectorName;
//     static const cstring directCounterName;
//     static const cstring directMeterName;
//     static const cstring counterName;
// };

// class MatchImplementation {
//  public:
//     static const cstring selectorMatchTypeName;
//     static const cstring rangeMatchTypeName;
// };

// class TableAttributes {
//  public:
//     static const cstring implementationName;
//     static const cstring sizeName;
//     static const cstring supportTimeoutName;
//     static const unsigned defaultTableSize;
//     static const cstring countersName;
//     static const cstring metersName;
// };

// class V1ModelProperties {
//  public:
//     static const cstring jsonMetadataParameterName;

//     /// The name of BMV2's valid field. This is a hidden bit<1> field
//     /// automatically added by BMV2 to all header types; reading from it tells
//     /// you whether the header is valid, just as if you had called isValid().
//     static const cstring validField;
// };

// using ErrorValue = unsigned int;
// using ErrorCodesMap = ordered_map<const IR::IDeclaration *, ErrorValue>;
// using BlockTypeMap = std::map<const IR::Block*, const IR::Type*>;
static std::map<llvm::Instruction *, std::string> allocaMap;
static std::map<cstring ,cstring> headerMap[3];
static std::map<cstring, cstring> metaMap;
enum header_type
{
    Scalar,
    Header,
    Union,
    Unknown
};
static std::map<cstring, unsigned> genNameMap;
static std::map<cstring, unsigned> actionIDMap;

void setActionID(cstring action, unsigned id);
unsigned getActionID(cstring action);
cstring genName(cstring name);
Util::JsonArray* mkArrayField(Util::JsonObject* parent, cstring name);
Util::JsonArray* mkParameters(Util::JsonObject* object);
Util::JsonArray* pushNewArray(Util::JsonArray* parent);
Util::JsonObject* mkPrimitive(cstring name, Util::JsonArray* appendTo);
std::string getAllocaName(llvm::Instruction *I);
bool setAllocaName(llvm::Instruction *I, std::string name);
static bool isIndex1D(llvm::GetElementPtrInst *gep);
static unsigned get1DIndex(llvm::GetElementPtrInst *gep);
static std::string getMultiDimFieldName(llvm::GetElementPtrInst *gep, Util::JsonArray* f = nullptr);
cstring getFieldName(llvm::Value *arg, Util::JsonArray *f = nullptr);
cstring getHeaderType(cstring, header_type ht);
bool setHeaderType(cstring name, cstring type, header_type ht);
header_type getBasicHeaderType(cstring);
void insertInMetaMap();
bool isSMeta(cstring);
cstring getFromMetaMap(cstring);
void emitErrors(LLBMV2::JsonObjects*);
void emitFieldAliases(LLBMV2::JsonObjects*);
cstring getOpcodeSym(cstring op);
Util::IJson *getJsonExp(llvm::Value *inst);


// cstring stringRepr(mpz_class value, unsigned bytes = 0);
unsigned nextId(cstring group);

}  // namespace LLBMV2

#endif /* _BACKENDS_LLBMV2_HELPERS_H_ */

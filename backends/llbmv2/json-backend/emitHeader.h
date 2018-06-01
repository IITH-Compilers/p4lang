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

#ifndef _BACKENDS_BMV2_HEADER_H_
#define _BACKENDS_BMV2_HEADER_H_

#include <list>
// #include "ir/ir.h"
#include "lib/json.h"
// #include "frontends/p4/typeMap.h"
// #include "frontends/common/resolveReferences/referenceMap.h"
// #include "helpers.h"
// #include "JsonObjects.h"
#include "llvm/IR/DerivedTypes.h"
#include "lib/cstring.h"
#include "../JsonObjects.h"
#include "llvm/IR/Instructions.h"
#include <set>

namespace LLBMV2 {

// class Backend;

class ConvertHeaders {
    // Backend*             backend;
    cstring              scalarsName;
    cstring              scalarsTypeName;
    // P4::ReferenceMap*    refMap;
    // P4::TypeMap*         typeMap;
    // JsonObjects*         json;
    std::vector<cstring>    visitedHeaders;

    const unsigned       boolWidth = 1;    // convert booleans to 1-bit integers
    const unsigned       errorWidth = 32;  // convert errors to 32-bit integers
    unsigned             scalars_width = 0;

 protected:
    Util::JsonArray* pushNewArray(Util::JsonArray* parent);
    void addHeaderField(JsonObjects *json, const cstring& header, const cstring& name, int size, bool is_signed);

 public:
    void addHeaderType(llvm::StructType *st,
                std::map<llvm::StructType *, std::string> *struct2Type,
                JsonObjects *json);
    void processHeaders(llvm::SmallVector<llvm::AllocaInst *, 8> *allocaList,
                std::map<llvm::StructType *, std::string> *struct2Type,
                JsonObjects *json);
    void addTypesAndInstances(llvm::StructType *type,
                std::map<llvm::StructType *, std::string> *struct2Type,
                JsonObjects *json, bool meta);
    void addHeaderStacks(llvm::StructType *headersStruct,
                std::map<llvm::StructType *, std::string> *struct2Type,
                JsonObjects *json);
    bool processParams(llvm::StructType *st,
                std::map<llvm::StructType *, std::string> *struct2Type,
                JsonObjects *json);
        // void addTypesAndInstances(const IR::Type_StructLike* type, bool meta);
    bool isHeaders(llvm::StructType *st,
                std::map<llvm::StructType *, std::string> *struct2Type);

    // Visitor::profile_t init_apply(const IR::Node* node) override;
    // void end_apply(const IR::Node* node) override;

    // bool preorder(const IR::PackageBlock* b) override;
    // bool preorder(const IR::Parameter* param) override;

    ConvertHeaders();
    // ConvertHeaders(Backend* backend, cstring scalarsName);
};

}  // namespace LLBMV2

#endif /* _BACKENDS_BMV2_HEADER_H_ */

/*
//@HEADER
// *****************************************************************************
//
//                                  derived.h
//                           DARMA Toolkit v. 1.0.0
//                 DARMA/checkpoint => Serialization Library
//
// Copyright 2019 National Technology & Engineering Solutions of Sandia, LLC
// (NTESS). Under the terms of Contract DE-NA0003525 with NTESS, the U.S.
// Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from this
//   software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact darma@sandia.gov
//
// *****************************************************************************
//@HEADER
*/

#if !defined INCLUDED_CHECKPOINT_DISPATCH_VRT_DERIVED_H
#define INCLUDED_CHECKPOINT_DISPATCH_VRT_DERIVED_H

#include "checkpoint/dispatch/vrt/registry_common.h"
#include "checkpoint/dispatch/vrt/static_dispatch_typeidx.h"
#include "checkpoint/dispatch/vrt/object_registry.h"
#include "checkpoint/dispatch/vrt/serializer_registry.h"
#include "checkpoint/dispatch/vrt/inheritance_assert_helpers.h"
#include "checkpoint/dispatch/vrt/serialize_instantiator.h"

#define checkpoint_virtual_serialize_derived(DERIVED, BASE)                          \
  void _checkpointDynamicSerialize(                                                  \
    void* s,                                                                         \
    ::checkpoint::dispatch::vrt::TypeIdx base_ser_idx,                               \
    ::checkpoint::dispatch::vrt::TypeIdx expected_idx                                \
  ) override {                                                                       \
    ::checkpoint::instantiateObjSerializer<                                          \
      DERIVED,                                                                       \
      checkpoint_serializer_variatic_args()                                          \
    >();                                                                             \
    debug_checkpoint(                                                                \
      "%s: BEGIN: _checkpointDynamicSerialize: serializer_idx=%d {\n",               \
      typeid(DERIVED).name(), base_ser_idx                                           \
    );                                                                               \
    ::checkpoint::dispatch::vrt::assertTypeIdxMatch<DERIVED>(expected_idx);          \
    auto base_idx = ::checkpoint::dispatch::vrt::objregistry::makeObjIdx<BASE>();    \
    BASE::_checkpointDynamicSerialize(s, base_ser_idx, base_idx);                    \
    auto dispatcher =                                                                \
      ::checkpoint::dispatch::vrt::serializer_registry::getBaseIdx<DERIVED>(         \
        base_ser_idx                                                                 \
      );                                                                             \
    dispatcher(s, *static_cast<DERIVED*>(this));                                     \
    debug_checkpoint(                                                                \
      "%s: END: _checkpointDynamicSerialize: serializer_idx=%d }\n",                 \
      typeid(DERIVED).name(), base_ser_idx                                           \
    );                                                                               \
  }                                                                                  \
  ::checkpoint::dispatch::vrt::TypeIdx _checkpointDynamicTypeIndex() override {      \
    return ::checkpoint::dispatch::vrt::DispatchTypeIdx<DERIVED>::get();             \
  }                                                                                  \

namespace checkpoint { namespace dispatch { namespace vrt {

/**
 * \brief A derived class of an inheritance hierarchy should inherit from this
 *
 * \param DerivedT the derived class, following CRTP
 * \param BaseT the base class to inherit from and identify the relevant hierarchy
 *
 * The serialize() method of such derived classes need not call any
 * base class serialize() explicitly
 */
template <typename DerivedT, typename BaseT>
struct SerializableDerived : BaseT {
  template <typename... Args>
  explicit SerializableDerived(Args&&... args)
    : BaseT(std::forward<Args>(args)...)
  { }

  SerializableDerived() = default;

  template <typename SerializerT>
  void serialize(SerializerT& s) {
    debug_checkpoint("SerializableDerived:: serialize\n");
    BaseT::serialize(s);
  }

  checkpoint_virtual_serialize_derived(DerivedT, BaseT)
};

}}} /* end namespace checkpoint::dispatch::vrt */

namespace checkpoint {

template <typename DerivedT, typename BaseT>
using SerializableDerived = dispatch::vrt::SerializableDerived<DerivedT, BaseT>;

} /* end namespace checkpoint */

#endif /*INCLUDED_CHECKPOINT_DISPATCH_VRT_DERIVED_H*/

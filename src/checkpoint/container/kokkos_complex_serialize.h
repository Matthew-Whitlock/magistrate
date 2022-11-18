/*
//@HEADER
// *****************************************************************************
//
//                      kokkos_complex_serialize.h
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

#if !defined INCLUDED_CHECKPOINT_CONTAINER_KOKKOS_COMPLEX_SERIALIZE_H
#define INCLUDED_CHECKPOINT_CONTAINER_KOKKOS_COMPLEX_SERIALIZE_H

#include "checkpoint/common.h"
#include "checkpoint/serializers/serializers_headers.h"
#include "checkpoint/dispatch/allocator.h"
#include "checkpoint/dispatch/dispatch.h"
#include "checkpoint/dispatch/reconstructor.h"

#if KOKKOS_ENABLED_CHECKPOINT

#include <Kokkos_Complex.hpp>

namespace checkpoint {

template <typename SerializerT, typename T1>
void serialize(SerializerT& s, Kokkos::complex<T1>& complex)
{
  s | complex.real();
  s | complex.imag();
}

} // namespace checkpoint

#endif /*KOKKOS_ENABLED_CHECKPOINT*/

#endif /*INCLUDED_CHECKPOINT_CONTAINER_KOKKOS_COMPLEX_SERIALIZE_H*/
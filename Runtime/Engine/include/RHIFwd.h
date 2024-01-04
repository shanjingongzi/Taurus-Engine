#pragma once

#include "RefCounting.h"
class RHIShaderResourceView;
class RHIBuffer;
using ShaderResourceViewRHIRef=TRefCountPtr<RHIShaderResourceView>;
using BufferRHIRef = TRefCountPtr<RHIBuffer>;

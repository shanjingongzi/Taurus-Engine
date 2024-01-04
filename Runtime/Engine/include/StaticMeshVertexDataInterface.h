 #pragma once

enum class EResizeBufferFlags
{
	None = 0,
	AllowSlackOnGrow = 1 << 0,
	AllowSlackOnReduce = 1 << 1
};

class StaticMeshVertexDataInterface
{
public:
	virtual ~StaticMeshVertexDataInterface();
	virtual void ResizeBuffer(unsigned int  numVertices,EResizeBufferFlags flag=EResizeBufferFlags::None);
	virtual void Empty(int numVertices)=0;
	virtual bool IsValidIndex( unsigned int index)=0;
	virtual unsigned int Num()const =0;
	virtual unsigned char *GetDataPointer()=0;
	virtual class ResourceArrayInterfafce*GetResourceArray()=0;
	virtual void OverrideFreezeSizeAndAlignment(size_t &size,int &Alignment)const =0;
	virtual size_t GetResourceSize()const=0;
	virtual bool GetAllowCPUAccess()const=0;
};


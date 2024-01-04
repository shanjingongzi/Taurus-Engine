#pragma once 
/*完成地描述了一个Pass Draw Call的所有状态和数据，如shader绑定，顶点数据，索引数据，PSO缓存等
 *所属线程：渲染
 */

class ParallelMeshDrawCommandPass
{
public:
	enum class EWaitThread
	{
		Render,
		Task,
		TaskAlreadyWaited
	};

};

class MeshDrawCommand
{
	public:
	private:
};


#ifndef NAVIGATION_SCENE_H
#define NAVIGATION_SCENE_H
#include "Octree.hpp"
#include "NavigationOctree.h"
#include "TObject.h"
#include "CameraComponent.h"
#include "Ray.hpp"
#include "IRenderObject.h"
class NavigationScene
{
public:
	NavigationScene();
	~NavigationScene();
	Octree<NavigationOctreeElement, NavigationOctreeSemantics>* tree() { return octree; }

	Octree<NavigationOctreeElement, NavigationOctreeSemantics>*octree;
    //Camera *rootCamera;
	void IntersectRayAABB(const TE::Math::TRay<double>& ray)
	{
		auto predicateFunc = [ray](NodeIndex parentIndex, NodeIndex currentIndex, const BoxCenterAndExtent& bound) {
			return IntersectRayAABB(ray, bound);
		};
		selected.clear();
		auto IteratorFunc = [=](int parentIndex, int currentIndex, const Node& node)
		{
			if (node.IsLeaf()) {
				auto childSet = octree->Elements()[currentIndex];
				for (auto iter : childSet) {
					auto center = iter.bounds.origin;
					auto extend = iter.bounds.boxExtent;
					auto aabb=BoxCenterAndExtent(center, extend);
					if (IntersectRayAABB(ray, aabb)) {
						selected.push_back(iter);
					}
				}
			}
		};
		tree()->FindNodesWithPredicate(predicateFunc, IteratorFunc);
	}
	std::vector<NavigationOctreeElement> Selected() {
		return selected;
	}
private:
	inline static int IntersectRayAABB(const TE::Math::TRay<double>&ray,const BoxCenterAndExtent& b)
	{
		auto box = b.GetBox();
		double tmin = -INFINITY, tmax = INFINITY;
		for (int i = 0; i < 3; ++i) {
			double t1 = (box.min[i] - ray.origin[i]) / ray.direction[i];
			double t2 = (box.max[i] - ray.origin[i]) / ray.direction[i];
			tmin = std::max(tmin, std::min(t1, t2));
			tmax = std::min(tmax, std::max(t1, t2));
		}
		return tmax > std::max(tmin, 0.0);
	}
	std::vector<NavigationOctreeElement>selected;
};

static int IntersectRayAABB(const TE::Math::TRay<double>&ray,const BoxCenterAndExtent& b)
{
}

#endif

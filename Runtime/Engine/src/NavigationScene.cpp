#include "NavigationScene.h"
NavigationScene::NavigationScene()
{
	octree = new Octree<NavigationOctreeElement, NavigationOctreeSemantics>(Vector(0.0,0.0,0.0),64.0);
}
NavigationScene::~NavigationScene()
{

}

/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2006 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef COLLISION__DISPATCHER_H
#define COLLISION__DISPATCHER_H

#include "BulletCollision/BroadphaseCollision/btDispatcher.h"
#include "BulletCollision/NarrowPhaseCollision/btPersistentManifold.h"

#include "BulletCollision/CollisionDispatch/btManifoldResult.h"

#include "BulletCollision/BroadphaseCollision/btBroadphaseProxy.h"


class btIDebugDraw;
class btOverlappingPairCache;


#include "btCollisionCreateFunc.h"




///btCollisionDispatcher supports algorithms that handle ConvexConvex and ConvexConcave collision pairs.
///Time of Impact, Closest Points and Penetration Depth.
class btCollisionDispatcher : public btDispatcher
{
	
	std::vector<btPersistentManifold*>	m_manifoldsPtr;

	bool m_useIslands;
	
	btManifoldResult	m_defaultManifoldResult;
	
	btCollisionAlgorithmCreateFunc* m_doubleDispatch[MAX_BROADPHASE_COLLISION_TYPES][MAX_BROADPHASE_COLLISION_TYPES];
	
	btCollisionAlgorithmCreateFunc* internalFindCreateFunc(int proxyType0,int proxyType1);

	//default CreationFunctions, filling the m_doubleDispatch table
	btCollisionAlgorithmCreateFunc*	m_convexConvexCreateFunc;
	btCollisionAlgorithmCreateFunc*	m_convexConcaveCreateFunc;
	btCollisionAlgorithmCreateFunc*	m_swappedConvexConcaveCreateFunc;
	btCollisionAlgorithmCreateFunc*	m_compoundCreateFunc;
	btCollisionAlgorithmCreateFunc*	m_swappedCompoundCreateFunc;
	btCollisionAlgorithmCreateFunc*   m_emptyCreateFunc;

public:

	///registerCollisionCreateFunc allows registration of custom/alternative collision create functions
	void	registerCollisionCreateFunc(int proxyType0,int proxyType1, btCollisionAlgorithmCreateFunc* createFunc);

	int	getNumManifolds() const
	{ 
		return m_manifoldsPtr.size();
	}

	btPersistentManifold**	getInternalManifoldPointer()
	{
		return &m_manifoldsPtr[0];
	}

	 btPersistentManifold* getManifoldByIndexInternal(int index)
	{
		return m_manifoldsPtr[index];
	}

	 const btPersistentManifold* getManifoldByIndexInternal(int index) const
	{
		return m_manifoldsPtr[index];
	}

	int m_count;
	
	btCollisionDispatcher ();
	virtual ~btCollisionDispatcher();

	virtual btPersistentManifold*	getNewManifold(void* b0,void* b1);
	
	virtual void releaseManifold(btPersistentManifold* manifold);

	
	///allows the user to get contact point callbacks 
	virtual	btManifoldResult*	getNewManifoldResult(btCollisionObject* obj0,btCollisionObject* obj1,btPersistentManifold* manifold);

	///allows the user to get contact point callbacks 
	virtual	void	releaseManifoldResult(btManifoldResult*);

	virtual void clearManifold(btPersistentManifold* manifold);

			
	btCollisionAlgorithm* findAlgorithm(btBroadphaseProxy& proxy0,btBroadphaseProxy& proxy1);
	
	btCollisionAlgorithm* internalFindAlgorithm(btBroadphaseProxy& proxy0,btBroadphaseProxy& proxy1);
	
	virtual bool	needsCollision(btBroadphaseProxy& proxy0,btBroadphaseProxy& proxy1);
	
	virtual bool	needsResponse(const btCollisionObject& colObj0,const btCollisionObject& colObj1);

	virtual int getUniqueId() { return RIGIDBODY_DISPATCHER;}
	
	virtual void	dispatchAllCollisionPairs(btOverlappingPairCache* pairCache,btDispatcherInfo& dispatchInfo);

	

};

#endif //COLLISION__DISPATCHER_H

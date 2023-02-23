#include "PxPhysicsAPI.h"
#include <iostream>

static physx::PxDefaultErrorCallback gDefaultErrorCallback;
static physx::PxDefaultAllocator gDefaultAllocatorCallback;

int main()
{
	physx::PxFoundation* mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);

	bool recordMemoryAllocations = true;

	physx::PxPvd* mPvd = physx::PxCreatePvd(*mFoundation);
	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("localhost", 5425, 10);
	mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

	physx::PxPhysics* physics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, physx::PxTolerancesScale(), recordMemoryAllocations, mPvd);

	if (physics)
	{
		std::cout << "Physics booted up." << std::endl;
	}
	else
	{
		std::cout << "Physics failed to start." << std::endl;
	}

	physics->release();
	mFoundation->release();

	std::cin.get();

	return 0;
}
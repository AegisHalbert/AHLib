#include "PxPhysicsAPI.h"
#include <iostream>

static physx::PxDefaultErrorCallback gDefaultErrorCallback;
static physx::PxDefaultAllocator gDefaultAllocatorCallback;

int main()
{
	physx::PxFoundation* mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
	if (!mFoundation)
	{
		std::cout << "Error while initializing" << std::endl;
	}
	else
	{
		std::cout << "Correct initialization" << std::endl;
	}

	return 0;
}
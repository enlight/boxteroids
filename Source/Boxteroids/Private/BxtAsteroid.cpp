//-------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015 Vadim Macagon
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//-------------------------------------------------------------------------------

#include "Boxteroids.h"
#include "BxtAsteroid.h"

ABxtAsteroid::ABxtAsteroid(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	AsteroidMeshComponent =
		objectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("AsteroidMesh0"));
	AsteroidMeshComponent->SetMobility(EComponentMobility::Movable);
	RootComponent = AsteroidMeshComponent;
	
	ProjectileMovementComponent =
		objectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileMovement0"));
	ProjectileMovementComponent->UpdatedComponent = AsteroidMeshComponent;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f; // not affected by gravity
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
}

void ABxtAsteroid::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}
/*
void ABxtAsteroid::ReceiveHit(
	UPrimitiveComponent* myComp, AActor* otherActor, UPrimitiveComponent* otherComp, 
	bool bSelfMoved, FVector hitLocation, FVector hitNormal, FVector normalImpulse, 
	const FHitResult& hit)
{
	
}
*/

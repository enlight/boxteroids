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
#include "BxtProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABxtProjectile::ABxtProjectile(const FObjectInitializer& objectInitializer) 
	: Super(objectInitializer)
{
	// the actual mesh used by this component will be set in BP
	MeshComponent = objectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("ProjectileMesh0"));
	MeshComponent->AttachTo(RootComponent);
	MeshComponent->SetCollisionProfileName("Projectile");
	MeshComponent->OnComponentHit.AddDynamic(this, &ABxtProjectile::OnHit);
	RootComponent = MeshComponent;

	MovementComponent = objectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileMovement0"));
	MovementComponent->UpdatedComponent = MeshComponent;
	MovementComponent->InitialSpeed = 3000.f;
	MovementComponent->MaxSpeed = 3000.f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bShouldBounce = false;
	MovementComponent->ProjectileGravityScale = 0.0f; // disable gravity for projectile
	// the projectile is only allowed to move along the x & y axes
	MovementComponent->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);
	MovementComponent->bConstrainToPlane = true;
	MovementComponent->bSnapToPlaneAtStart = true;

	// projectile should self-destruct after 3 seconds
	InitialLifeSpan = 3.0f;
}

void ABxtProjectile::OnHit(
	AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit
)
{
	if (otherActor && (otherActor != this) && otherComp && otherComp->IsSimulatingPhysics())
	{
		otherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	Destroy();
}
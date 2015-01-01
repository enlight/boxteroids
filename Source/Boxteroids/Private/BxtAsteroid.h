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
#pragma once

#include "BxtAsteroid.generated.h"

/**
 * @brief An asteroid that bounces off the screen edges and other asteroids.
 */
UCLASS(Blueprintable)
class ABxtAsteroid : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly)
	class UStaticMeshComponent* AsteroidMeshComponent;

public:
	/** Projectile movement component */
	UPROPERTY(Category = Movement, VisibleAnywhere, BlueprintReadOnly)
	class UProjectileMovementComponent* ProjectileMovementComponent;

public:
	ABxtAsteroid(const FObjectInitializer& objectInitializer);

public: // AActor interface
	virtual void Tick(float deltaSeconds) override;
	/*
	virtual void ReceiveHit(
		class UPrimitiveComponent* myComp, AActor* otherActor, class UPrimitiveComponent* otherComp,
		bool bSelfMoved, FVector hitLocation, FVector hitNormal, FVector normalImpulse, 
		const FHitResult& hit
	) override;
	*/
};

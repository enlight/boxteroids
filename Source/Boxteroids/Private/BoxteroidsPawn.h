//-------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2014 Vadim Macagon
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

#include "GameFramework/Character.h"
#include "BoxteroidsPawn.generated.h"

UCLASS(Blueprintable)
class ABoxteroidsPawn : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly)
	class UStaticMeshComponent* ShipMeshComponent;

	UPROPERTY(VisibleDefaultsOnly)
	class UFloatingPawnMovement* MovementComponent;

public:
	/** Offset from the ships location to spawn projectiles. */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	FVector GunOffset;
	
	/* How fast the ship can fire. */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float FireRate;

	/* How fast the ship can turn. */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float TurnSpeed;

	/** Sound to play each time the ship fires. */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;

public:
	ABoxteroidsPawn(const FObjectInitializer& objectInitializer);

	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;
	// End Actor Interface

	/* Fire a shot in the specified direction */
	void FireShot(FVector FireDirection);

	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

private:
	// names for axis bindings
	static const FName HeadingAxisName;
	static const FName SideAxisName;

private:
	/* Flag to control firing */
	uint32 bCanFire : 1;
};


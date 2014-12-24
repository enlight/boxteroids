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

#include "Boxteroids.h"
#include "BoxteroidsPawn.h"
//#include "BoxteroidsProjectile.h"
#include "TimerManager.h"

const FName ABoxteroidsPawn::HeadingAxisName("MoveForward");
const FName ABoxteroidsPawn::SideAxisName("MoveRight");

ABoxteroidsPawn::ABoxteroidsPawn(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{	
	bUseControllerRotationYaw = true;

	// Create the mesh component
	ShipMeshComponent = 
		objectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(TEXT("Pawn"));

	MovementComponent = 
		objectInitializer.CreateDefaultSubobject<UFloatingPawnMovement>(this, TEXT("Movement"));
	// the ship is only allowed to move along the x & y axes
	MovementComponent->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);
	MovementComponent->bConstrainToPlane = true;
	MovementComponent->bSnapToPlaneAtStart = true;
	
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;
}

void ABoxteroidsPawn::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	check(InputComponent);

	// set up gameplay key bindings
	InputComponent->BindAxis(HeadingAxisName);
	InputComponent->BindAxis(SideAxisName);
}

void ABoxteroidsPawn::Tick(float DeltaSeconds)
{
	const float headingValue = GetInputAxisValue(HeadingAxisName);
	const float sideValue = GetInputAxisValue(SideAxisName);

	if (Controller)
	{
		float deltaYaw = TurnSpeed * sideValue * DeltaSeconds;
		if (!FMath::IsNearlyZero(deltaYaw))
		{
			Controller->SetControlRotation(
				FRotator(0.0f, Controller->GetControlRotation().Yaw + deltaYaw, 0.0f)
			);
		}

		if (!FMath::IsNearlyZero(headingValue))
		{
			AddMovementInput(
				FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X), 
				headingValue
			);
		}
	}
}

void ABoxteroidsPawn::FireShot(FVector FireDirection)
{
	/*
	// If we it's ok to fire again
	if (bCanFire == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				// spawn the projectile
				World->SpawnActor<ABoxteroidsProjectile>(SpawnLocation, FireRotation);
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(this, &ABoxteroidsPawn::ShotTimerExpired, FireRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
		}
	}
	*/
}

void ABoxteroidsPawn::ShotTimerExpired()
{
	bCanFire = true;
}


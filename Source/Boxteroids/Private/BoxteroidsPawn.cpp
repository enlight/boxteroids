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
#include "BxtProjectile.h"
#include "TimerManager.h"

const FName ABoxteroidsPawn::HeadingAxisName("MoveForward");
const FName ABoxteroidsPawn::SideAxisName("MoveRight");
const FName ABoxteroidsPawn::FireActionName("Fire");

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
	FiringDelay = 0.5f;
	_bShouldFire = false;
	_lastShotTime = 0.0f;
}

void ABoxteroidsPawn::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	check(InputComponent);

	// set up gameplay key bindings
	InputComponent->BindAxis(HeadingAxisName);
	InputComponent->BindAxis(SideAxisName);
	InputComponent->BindAction(FireActionName, IE_Pressed, this, &ABoxteroidsPawn::StartFiring);
	InputComponent->BindAction(FireActionName, IE_Released, this, &ABoxteroidsPawn::StopFiring);
}

void ABoxteroidsPawn::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	const float headingValue = GetInputAxisValue(HeadingAxisName);
	const float sideValue = GetInputAxisValue(SideAxisName);

	if (Controller)
	{
		float deltaYaw = TurnSpeed * sideValue * deltaSeconds;
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

	UWorld* world = GetWorld();
	if (_bShouldFire && world)
	{
		float currentTime = world->GetTimeSeconds();
		if ((currentTime - _lastShotTime) >= FiringDelay)
		{
			const FRotator shipRotation = GetActorRotation();
			const FVector projectilePos = GetActorLocation() + shipRotation.RotateVector(GunOffset);
			auto projectile = world->SpawnActor<ABxtProjectile>(ProjectileType, projectilePos, shipRotation);
			// UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			_lastShotTime = currentTime;
		}
	}
}

void ABoxteroidsPawn::StartFiring()
{
	_bShouldFire = true;
}

void ABoxteroidsPawn::StopFiring()
{
	_bShouldFire = false;
}

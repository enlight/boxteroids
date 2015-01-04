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
#include "BxtAsteroidSpawner.h"
#include "BxtAsteroid.h"

ABxtAsteroidSpawner::ABxtAsteroidSpawner(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{	
	PrimaryActorTick.bCanEverTick = true;

	UBrushComponent* volume = GetBrushComponent();
	if (volume)
	{
		volume->bGenerateOverlapEvents = false;
	}
}

void ABxtAsteroidSpawner::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	if (_numAsteroidsSpawned >= TotalAsteroidsToSpawn)
	{
		// already spawned all the asteroids we'll ever need
		return;
	}

	float curTime = GetWorld()->GetTimeSeconds();
	if ((-1.0f == _lastSpawnTime) || ((curTime - _lastSpawnTime) > AsteroidSpawnDelay))
	{
		SpawnAsteroid();

		_lastSpawnTime = curTime;
		++_numAsteroidsSpawned;
	}
}

FVector ABxtAsteroidSpawner::GetRandomSpawnLocation()
{
	FBox spawnerBounds = GetComponentsBoundingBox(true);
	float y = FMath::FRandRange(spawnerBounds.Min.Y, spawnerBounds.Max.Y);
	return FVector(spawnerBounds.GetCenter().X - 500.0f, y, 0.0f);
}

void ABxtAsteroidSpawner::SpawnAsteroid()
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	auto asteroid = GetWorld()->SpawnActor<ABxtAsteroid>(
		AsteroidClass, GetRandomSpawnLocation(), FRotator::ZeroRotator, spawnParams
	);

	if (asteroid)
	{
		asteroid->SetInitialSpeed(AsteroidSpeed);
		asteroid->SetDirection(FVector(-1.0f, 0.0f, 0.0f));
	}
}

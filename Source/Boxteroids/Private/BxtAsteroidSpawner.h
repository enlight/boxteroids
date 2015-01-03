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

#include "BxtAsteroidSpawner.generated.h"

/**
 * Spawns asteroids in the map it is placed in.
 */
UCLASS(Blueprintable)
class ABxtAsteroidSpawner : public AVolume
{
	GENERATED_BODY()

public:
	/** Total number of asteroids that should be spawned in the map. */
	UPROPERTY(Category = Spawner, EditAnywhere, BlueprintReadOnly)
	int32 TotalAsteroidsToSpawn;

	/** Number of seconds the spawner should wait before spawning each asteroid. */
	UPROPERTY(Category = Spawner, EditAnywhere, BlueprintReadOnly)
	float AsteroidSpawnDelay;

	/** How fast asteroids should be moving when spawned. */
	UPROPERTY(Category = Spawner, EditAnywhere, BlueprintReadOnly)
	float AsteroidSpeed;

public:
	ABxtAsteroidSpawner(const FObjectInitializer& objectInitializer);

public: // AActor interface
	virtual void Tick(float deltaSeconds) override;

private:
	FVector GetRandomSpawnLocation();
	void SpawnAsteroid();

private:
	int32 _numAsteroidsSpawned = 0;
	float _lastSpawnTime = -1.0f;
};

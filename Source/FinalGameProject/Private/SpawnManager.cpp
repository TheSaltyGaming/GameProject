// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"
#include "Enemy/Enemy.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WaveSize.Add(10);
	WaveSize.Add(15);
	WaveSize.Add(20);

	WaveDifficulty.Add(0.5);
	WaveDifficulty.Add(1);
	WaveDifficulty.Add(2);

	WaveSpawnFrequency.Add(2);
	WaveSpawnFrequency.Add(1);
	WaveSpawnFrequency.Add(0.5f);

	MinX = 2000;
	MaxX = 2200;

	MinY = -400;
	MaxY = 400;
	GameWon = false;
}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	CurrentWave = 1;
	LeftToSpawn = WaveSize[CurrentWave - 1];
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += DeltaTime;
	if (Timer > WaveSpawnFrequency[CurrentWave - 1] && !GameWon)
	{
		Timer = 0.f;
		FVector Location = FVector(FMath::RandRange(MinX, MaxX), FMath::RandRange(MinY, MaxY), 80);

		// Spawning
		AActor* Actor = GetWorld()->SpawnActor<AActor>(Target_BP, Location, FRotator::ZeroRotator);
		AEnemy* Enemy = Cast<AEnemy>(Actor);

		// Changing Target Values
		if (Enemy)
		{
			Enemy->MovementSpeed *= WaveDifficulty[CurrentWave - 1];
		}
		
		LeftToSpawn--;
		if (LeftToSpawn <= 0)
		{
			ChangeWave(CurrentWave + 1);
		}
	}
}

void ASpawnManager::ChangeWave(int wave)
{
	if (WaveSize.Num() < wave)
	{
		// Game Won
		GameWon = true;
		return;
	}

	CurrentWave = wave;
	LeftToSpawn = WaveSize[CurrentWave - 1];
}


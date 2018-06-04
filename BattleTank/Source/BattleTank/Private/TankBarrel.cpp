    
#include "TankBarrel.h"                                   
#include "BattleTank.h"
#include "Engine/World.h" //for getWorld
#



void UTankBarrel::Elevate(float RelativeSpeed)
{
	//move the barrel the right amount this frame
	//Given a max elevation speed and a frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));

	

}                                  


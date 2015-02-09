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

#include "Blueprint/UserWidget.h"
#include "BxtPlayerLifeCounter.generated.h"

/**
 * Base class for a UMG widget that displays the number of lives the player has remaining.
 * 
 * This class provides native event handlers that must be bound in a derived Widget Blueprint via
 * the UMG designer. In UE 4.6 one must create a wrapper function in the Widget Blueprint that
 * calls the native function, hopefully this will be simplified one day.
 */
UCLASS(Abstract)
class UBxtPlayerLifeCounter : public UUserWidget
{
	GENERATED_BODY()

public:
	/* Get a string that indicates the number of lives a player has remaining. */
	UFUNCTION(BlueprintPure, Category = Default)
	FText GetLivesLeft() const;
};

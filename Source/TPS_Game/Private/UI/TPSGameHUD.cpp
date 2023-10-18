// Third Person Shooter. All Rights Reserved.

#include "UI/TPSGameHUD.h"
#include "Engine/Canvas.h"

void ATPSGameHUD::DrawHUD()
{
    Super::DrawHUD();
    DrawCrossHair();
}


void ATPSGameHUD::DrawCrossHair()
{
    const TInterval<float> Center(Canvas->SizeX * .5f, Canvas->SizeY * .5f);

    const float HalfLineSize = 10.f;
    const float LineThickness = 2.f;
    const FLinearColor LineColor = FLinearColor::Blue;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}
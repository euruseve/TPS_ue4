#pragma once

class TPSUtils
{
public:
	template<typename T> 
	static T* GetTPSPlayerComponent(AActor* PlayerPawn)
	{
        if (!PlayerPawn)
            return nullptr;

        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());

        return Cast<T>(Component);
	}
};
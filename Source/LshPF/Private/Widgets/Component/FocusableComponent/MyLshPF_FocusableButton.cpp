// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/MyLshPF_FocusableButton.h"

#include "Components/TextBlock.h"
#include "Controllers/LshPF_PlayerControllerBase.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "Widgets/Component/LshPF_Button.h"


void UMyLshPF_FocusableButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonWidget)
	{
		ButtonWidget->OnClicked.AddDynamic(this, &ThisClass::UMyLshPF_FocusableButton::OnButtonClicked);
	}
}

void UMyLshPF_FocusableButton::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);
	
	ALshPF_PlayerControllerBase* LshPF_PlayerController = Cast<ALshPF_PlayerControllerBase>(ButtonText->GetOwningPlayer());
	LshPF_PlayerController->SetFocusedButton(ButtonWidget);
}

void UMyLshPF_FocusableButton::SetButtonText(FText& Text)
{
	ButtonText->SetText(Text);
}

void UMyLshPF_FocusableButton::OnButtonClicked()
{
	
	FHardwareDeviceIdentifier HardwareDeviceIdentifier = UInputDeviceSubsystem::Get()->GetMostRecentlyUsedHardwareDevice(GetOwningPlayer()->GetPlatformUserId());
	
	//UE_LOG(LogTemp, Warning, TEXT("Clicked by %d"), HardwareDeviceIdentifier.PrimaryDeviceType);
	//1 -> 키보드 2-> 패드
	/*
	 * 버튼으로 입력 컨슘 > 버튼에서 직접 디바이스 전송
	 * 아닐경우 PC 에서 아무키 바인딩한 IA 를 통해 디바이스 전송
	 * SButton 쪽에서 Virtual Accept 로 키를 Handle 해버림.이 방식이 아니면  Sbutton을 커스텀해서 사용필요
	 */
}

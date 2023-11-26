// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameGroupSelectWidget.h"

void UGameGroupSelectWidget::NativeConstruct()
{
	// TODO: Prepare widget in C++.
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	this->VerticalBox = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());
	RootWidget->AddChild(this->VerticalBox);
}

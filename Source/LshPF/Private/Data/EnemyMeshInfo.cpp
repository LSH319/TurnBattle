// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/EnemyMeshInfo.h"

FEnemyMeshData UEnemyMeshInfo::GetEnemyMeshInfoByKeyName(FName EnemyKeyName)
{
	return EnemyMeshInfoMap.FindChecked(EnemyKeyName);
}

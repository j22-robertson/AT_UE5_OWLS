// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


UENUM(BlueprintType)
enum class EDirection : uint8
{
	Forward, Right, Back, Left, Up, Down,
};

UENUM(BlueprintType)
enum class EBlockType : uint8
{
	Null,
	Air,
	Stone,
	Dirt
	, Grass
};

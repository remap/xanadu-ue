// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

typedef unsigned char TypeTok;
static const TypeTok TYPE_TOK_VOID = 0;
static const TypeTok TYPE_TOK_HANDLE = 1;
static const TypeTok TYPE_TOK_STRING = 2;
static const TypeTok TYPE_TOK_BOOL = 3;
static const TypeTok TYPE_TOK_INT = 4;
static const TypeTok TYPE_TOK_DOUBLE = 5;
static const TypeTok TYPE_TOK_FLOAT = 6;
static const TypeTok TYPE_TOK_UCHAR = 7;
static const TypeTok TYPE_TOK_UINT = 8;
static const TypeTok TYPE_TOK_HANDLE_ARRAY = 64;
static const TypeTok TYPE_TOK_STRING_ARRAY = 65;
static const TypeTok TYPE_TOK_BOOL_ARRAY = 66;
static const TypeTok TYPE_TOK_INT_ARRAY = 67;
static const TypeTok TYPE_TOK_DOUBLE_ARRAY = 68;
static const TypeTok TYPE_TOK_FLOAT_ARRAY = 69;
static const TypeTok TYPE_TOK_UCHAR_ARRAY = 70;
static const TypeTok TYPE_TOK_UINT_ARRAY = 71;

typedef unsigned int StackId;
static const StackId STACK_ID_VOID = 0;
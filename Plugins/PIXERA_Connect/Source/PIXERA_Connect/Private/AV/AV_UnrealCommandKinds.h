#pragma once

namespace AV
{
typedef unsigned int UECommandKinds;
static constexpr UECommandKinds eUECommandKindNone = 0;
static constexpr UECommandKinds eUECommandKindRequestWorldRefreshUe = 1;
static constexpr UECommandKinds eUECommandKindCreateNewLight = 2;
static constexpr UECommandKinds eUECommandKindRequestWorldIdentification = 3;
static constexpr UECommandKinds eUECommandKindRegisterUnrealInstance = 4;
static constexpr UECommandKinds eUECommandKindConnectionClosed = 5;
static constexpr UECommandKinds eUECommandKindLoadStreamingLevel = 6;
static constexpr UECommandKinds eUECommandKindTriggerEvent = 7;
static constexpr UECommandKinds eUECommandKindDataFromUnreal = 8;
static constexpr UECommandKinds eUECommandKindApplyBlacklistedInfo = 9;
static constexpr UECommandKinds eUECommandKindApplyVisibilityInfo = 10;
static constexpr UECommandKinds eUECommandKindApplyInterpolationTime = 11;
static constexpr UECommandKinds eUECommandKindDataFromPixera = 12;
}
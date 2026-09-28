#pragma once

// Native reVC counterpart of the distance preset in the desktop re3 project.
// These are project-selected MixSets-style values, not MixSets VC stock defaults.
namespace VisualTuning {
constexpr float VehicleHighDetail = 200.0f;
constexpr float VehicleLowDetail = 250.0f;
constexpr float VehicleFade = 260.0f;
// Keep traffic beyond its spawn range without moving the spawn ring outward.
constexpr float VehicleDespawnOnScreen = 180.0f;
constexpr float VehicleDespawnOffScreen = 90.0f;
constexpr float VehicleShadow = 300.0f;
constexpr float PedShadow = 300.0f;
constexpr float TrafficLight = 300.0f;
}

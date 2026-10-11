#pragma once

// Native reVC counterpart of the distance preset in the desktop re3 project.
// These are project-selected MixSets-style values, not MixSets VC stock defaults.
namespace VisualTuning {
const float VehicleHighDetail = 200.0f;
const float VehicleLowDetail = 250.0f;
const float VehicleFade = 260.0f;
// Keep traffic beyond its spawn range without moving the spawn ring outward.
const float VehicleDespawnOnScreen = 180.0f;
const float VehicleDespawnOffScreen = 90.0f;
const float VehicleShadow = 300.0f;
const float PedShadow = 300.0f;
const float TrafficLight = 300.0f;
}

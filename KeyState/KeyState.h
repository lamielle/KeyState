#pragma once

#include "resource.h"

#define IsKeyDown(key) ((GetAsyncKeyState(key) & 0x8000) != 0)
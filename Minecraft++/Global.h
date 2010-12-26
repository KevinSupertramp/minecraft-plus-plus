#pragma once

//SFML
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

//Boost
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

//And other stuff too
#include <noise/noise.h>

//STL
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include <cstdint>
#define UINT64_HALF 0x8000000000000000ULL
#include <random>
#include <functional>
#include <queue>
using namespace std;

//Our own headers
#include "Utilities.h"
#include "Position.h"
#include "Rotation.h"
#include "Graphics.h"
#include "Clouds.h"
#include "Models.h"
#include "Blocks.h"
#include "Chunks.h"
#include "Player.h"
#include "Game.h"
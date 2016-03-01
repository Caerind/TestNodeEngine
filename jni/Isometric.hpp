#ifndef NISOMETRIC_HPP
#define NISOMETRIC_HPP

#include <cmath>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include "Utils/Vector.hpp"

namespace NIsometric
{

std::vector<sf::Vector2i> getNeighboors(sf::Vector2i const& coords);
sf::Vector2i worldToCoords(NVector const& pos);
NVector coordsToWorld(sf::Vector2i const& coords); // center of the tile

} // namespace NIsometric

#endif // NISOMETRIC_HPP

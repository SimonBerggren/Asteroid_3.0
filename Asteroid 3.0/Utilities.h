#pragma once
#include "SFML/System.hpp"
#include <iostream>
#include <sstream>
#include <stdarg.h>
#include <random>
#include <ctime>

typedef unsigned int uint;

// some useful utilities
namespace utils
{
	template<class Owner>
	static std::string ToString(Owner i)
	{
		std::ostringstream stream;
		stream << i;
		return stream.str();
	}

	static double Round(double value, int precision)
	{
		return int(value * std::pow(10.0f, precision) + 0.5f) / std::pow(10.0f, precision);
	}

	static float Clamp(float value, float min, float max)
	{
		return (value < min) ? min : (value > max) ? max : value;
	}

	static float ToDegrees(float radians)
	{
		return radians * (180.0f / std::_Pi);
	}

	static float ToRadians(float degrees)
	{
		return degrees * (std::_Pi / 180);
	}

	static float Abs(float value)
	{
		return (value < 0.0f) ? -value : value;
	}

	static void Print(float value)
	{
		std::cout << value << std::endl;
	}

	static void Print(char* value)
	{
		std::cout << value << std::endl;
	}

	static void Print(char* text, float value)
	{
		std::cout << text << value << std::endl;
	}

	// Vector
	namespace vec
	{
		static float Distance(const sf::Vector2f& v1, const sf::Vector2f& v2)
		{
			return sqrt(pow((v2.x - v1.x), 2.0f) + pow((v2.y - v1.y), 2.0f));
		}

		static float Length(const sf::Vector2f& v)
		{
			return sqrt((v.x * v.x) + (v.y * v.y));
		}

		static sf::Vector2f Normalized(const sf::Vector2f& v)
		{
			float length = Length(v);
			return sf::Vector2f(v.x / length, v.y / length);
		}

		static sf::Vector2f Direction(const sf::Vector2f& v1, const sf::Vector2f& v2)
		{
			return sf::Vector2f(v2.x - v1.x, v2.y - v1.y);
		}

		static sf::Vector2f FromRadians(float radians)
		{
			return sf::Vector2f(std::cos(radians), std::sin(radians));
		}

		static sf::Vector2f FromDegrees(float degree)
		{
			return FromRadians(utils::ToRadians(degree));
		}

		static float ToDegrees(const sf::Vector2f& v)
		{
			return std::atan2(v.y, v.x) * (180.0f / std::_Pi);
		}

		static float ToRadians(const sf::Vector2f& v)
		{
			return utils::ToRadians(ToDegrees(v));
		}
	}

	// Random
	namespace rnd
	{
		static float Float(float min, float max)
		{
			static std::mt19937 randomGenerator(time(0));
			std::uniform_real_distribution<float> random(min, max);
			return random(randomGenerator);
		}

		static int Int(int min, int max)
		{
			static std::mt19937 randomGenerator(time(0));
			std::uniform_int_distribution<int> random(min, max);
			return random(randomGenerator);
		}
	}
}
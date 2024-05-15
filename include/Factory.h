#pragma once

#include "MovingObject.h"
#include "StaticObject.h"

template <class T>
class Factory
{
public:
	using pFnc = std::shared_ptr<T>(*)(float height, float width, b2World* world);
	using pFncWall = std::shared_ptr<T>(*)(float height, float width, b2World* world, char type);

	static std::shared_ptr<T> create(const std::string& name, float height, float width, b2World* world);
	static std::shared_ptr<T> create(const std::string& name, float height, float width, b2World* world, char type);

	static bool registerit(const std::string& name, pFnc);
	static bool registerit(const std::string& name, pFncWall);

private:
	static auto& getMap() {
		static std::map<std::string, pFnc> map;
		return map;
	}
	static auto& getMapWall() {
		static std::map<std::string, pFncWall> mapWall;
		return mapWall;
	}
};

template <class T>
std::shared_ptr<T> Factory<T>::create(const std::string& name, float height, float width, b2World* world) {
	auto it = Factory::getMap().find(name);
	if (it == Factory::getMap().end())
		return nullptr;
	return it->second(height, width, world);
}

template <class T>
bool Factory<T>::registerit(const std::string& name, pFnc f) {
	Factory::getMap().emplace(name, f);
	return true;
}

//------------
template <class T>
std::shared_ptr<T> Factory<T>::create(const std::string& name, float height, float width, b2World* world, char type) {
	auto it = Factory::getMapWall().find(name);
	if (it == Factory::getMapWall().end())
		return nullptr;
	return it->second(height, width, world, type);
}

template <class T>
bool Factory<T>::registerit(const std::string& name, pFncWall f) {
	Factory::getMapWall().emplace(name, f);
	return true;
}
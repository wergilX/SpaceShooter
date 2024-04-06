#pragma once

#include<map>
#include<memory>
#include<string>
#include<stdexcept>
#include<cassert>
#include<SFML/Graphics.hpp>

namespace Textures
{
	enum ID 
	{ 
		Landscape, 
		Airplane, 
		Missle,
		Projectile,
		Background,
		SpaceShip,
		Support,
		Insect,
		Obstacle,
		None
	};
}

template<typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void load(Identifier id, const std::string fileName);
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;

	// can load area from image with secondParam
	template<typename Parameter>
	void load(Identifier id, const std::string& fileName, const Parameter& secondParam);

private:
	std::map<Identifier, std::unique_ptr<Resource>> m_textureMap;
};

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

template<typename Resource, typename Identifier>
inline void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string fileName)
{
	//std::unique_ptr<sf::Texture> texture(new sf::Texture()); //example
	auto resource = std::make_unique<Resource>(Resource());
	if (!resource->loadFromFile(fileName))
	{
		throw std::runtime_error("TextureHolder::load - Failed to load " + fileName);
	}

	auto inserted = m_textureMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}


template<typename Resource, typename Identifier>
template<typename Parameter>
inline void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& fileName, const Parameter& secondParam)
{
	auto resource = std::make_unique<Resource>(Resource());
	if (!resource.loadFromFile(fileName, secondParam))
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load " + fileName);
	}
	auto inserted = m_textureMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template<typename Resource, typename Identifier>
inline Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = m_textureMap.find(id);
	assert(found != m_textureMap.end());
	return *found->second;
}

template<typename Resource, typename Identifier>
inline const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = m_textureMap.find(id);
	assert(found != m_textureMap.end());
	return *found->second;
}


#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template<typename Resource, typename Identifier>
class ResourceHolder
{
public:
	// Load files
	void					load(Identifier id, const std::string& filename);

	// Overloaded load for loading shaders
	template<typename Parameter>
	void					load(Identifier id, const std::string& filename, const Parameter& secondParam);

	// Get resource from its container
	Resource& get(Identifier id);

	// if the instance calling is const, then this will be called
	const Resource&			get(Identifier id) const;

private:
	void					insertResource(Identifier id, std::unique_ptr<Resource> resource);

	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include <ResourceHolder.inl>
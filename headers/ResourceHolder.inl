/*
 * @brief Loads a resource from a file.
 * @param id The identifier for the resource (enum).
 * @param filename The path to the resource file.
 * @throws std::runtime_error if the resource cannot be loaded.
 */
template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	insertResource(id, std::move(resource));
}

/*
* @brief Overloaded load for loading shaders
* @param id The identifier for the resource (enum)
* @param filename The path to the resource file
* @param secondParam The
* @throws std::runtime_error if the resource cannot be loaded
*/
template<typename Resource, typename Identifier>
template<typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
	// Create a new resource object
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	insertResource(id, std::move(resource));
}

/*
* @brief Search the resource tree for resource
* @param id The identifier we are looking for
* @return reference to the object we are searching for
* @asserts Assert if the object is not found
*/
template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

/*
* @brief Will be called if the object calling get is a const object
* @param id The identifier we are looking for
* @return reference to the object we are searching for
* @assert Assert if the object is not found
*/
template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}


/*
* @brief Inserting the resource object by using move semantics on the resource itself
* @param id The identifier of the resource we are inserting into the tree
* @param resource The pointer to the address of the resource object we created to be inserted into the tree
* @assert Assert to check the success of the insert
*/
template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
	// Insert and check success
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}
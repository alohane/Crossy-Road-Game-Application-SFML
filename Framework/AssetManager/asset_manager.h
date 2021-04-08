#ifndef _asset_manager
#define _asset_manager
#include<string>
#include<unordered_map>
constexpr auto DEFAULT_FOLDER_DIR = "Assets/";
constexpr auto FAILED_FILE_NAME = "FAILED";
template<typename Resource_t>
class asset_manager
{
private:
	const std::string							_folder_dir;
	std::unordered_map<std::string, Resource_t> _container;
	std::string	file_dir	(const std::string& full_name);
	std::string full_name	(const std::string& name, const std::string& ext);
	void load_file			(const std::string& name, const std::string& ext);
public:
	asset_manager			(const std::string& folder_name);
	Resource_t& get			(const std::string& name, const std::string& ext);
};

template<typename Resource_t>
std::string asset_manager<Resource_t>::file_dir(const std::string& full_name) {
	return _folder_dir + full_name;
}
template<typename Resource_t>
std::string asset_manager<Resource_t>::full_name(const std::string& name, const std::string& ext) {
	return name + "." + ext;
}
template<typename Resource_t>
void asset_manager<Resource_t>::load_file(const std::string& name, const std::string& ext) {
	Resource_t res;
	const std::string name_with_ext = full_name(name, ext);
	if (res.loadFromFile(file_dir(name_with_ext)) == 0) {
		//load placeholder if file not found
		res.loadFromFile(file_dir(full_name(FAILED_FILE_NAME, ext)));
	}
	_container.emplace(name_with_ext, res);
}

template<typename Resource_t>
asset_manager<Resource_t>::asset_manager(const std::string& folder_name)
	: _folder_dir(DEFAULT_FOLDER_DIR + folder_name + "/")
{}
template<typename Resource_t>
Resource_t& asset_manager<Resource_t>::get(const std::string& name, const std::string& ext) {
	std::string fullName = full_name(name, ext);
	//find resource
	auto found = _container.find(fullName);
	if (found != _container.end())
		return found->second;
	//not found, load from file
	else {
		load_file(name, ext);
		return _container.at(fullName);
	}
}
#endif // !_asset_manager
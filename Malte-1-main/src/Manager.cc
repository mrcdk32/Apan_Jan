
#include <string>
#include <vector>
#include <map>
template <typename T>
auto load_from_file(std::string filename)
{
    T result;
    if(!result.loadFromFile(filename))
    {
        throw std::runtime_error("Missing game map file");
    }
    return result;
}
template<typename T>
class Manager
{  
    public:
    static T& load(std::string const& name)
    {
        auto it = resources.find(name);
    if (it == end(resources))
    {
        T res {load_from_file<T>(name)};
        it = resources.emplace(make_pair(name, res)).first;
    }
    return it->second;
    }
    private:
    static std::map<std::string, T> resources;

};

template<typename T>
std::map<std::string, T> Manager<T>::resources;

#include <unordered_map>
#include <string>
#include <iostream>

const int num_buckets = 4;

struct KeyHash {
 std::size_t operator()(std::string k) const {
    return k.length()%num_buckets; 
 }
};

int main() {
    std::unordered_map<std::string, std::string, KeyHash> m = {{
            { "Homer", "Simpson"},
            { "Marge", "Simpson"}
    }, 5};
    // insert con []
    m["Ned"] = "Flanders";
   // insert function
   m.insert ({"Montgomery","Burns"});
   m.insert({{"Apu","Nahasapeemapetilon"},{"Milhouse","Van Houten"}});
   // insert two pairs
   std::pair<std::string,std::string> my_bart ("Bart","Simpson");
   std::pair<std::string,std::string> my_lisa ("Lisa","Simpson");
   m.insert(my_bart);
   m.insert(my_lisa);
   // Check size and num of buckets
   std::cout << "size: " << m.size() << std::endl;
   std::cout << "buckets: " << m.bucket_count() << std::endl;
   // Map traversal
   for ( auto& x: m )
    std::cout << x.first << ": " << x.second << std::endl;
   // remove an entry
   m.erase("Apu");
   // Check size and num of buckets
   std::cout << "size: " << m.size() << std::endl;
   std::cout << "buckets: " << m.bucket_count() << std::endl;
   // Map traversal by key iterator
   for ( auto& x: m )
    std::cout << x.first << ": " << x.second << std::endl;
   // Buckets traversal by key iterator
   for ( auto& x: m )
    std::cout << x.first << " esta en el bucket " << m.bucket(x.first) << std::endl;
}

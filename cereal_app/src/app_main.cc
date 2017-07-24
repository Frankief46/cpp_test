#define CATCH_CONFIG_MAIN

#include <iostream>
#include <string>
#include "catch.hpp"

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

using namespace std;

struct PayLoad {
    string x = "xDefault";
    string y = "yDefault";
    string z = "zDefault";
    
    void save(cereal::JSONOutputArchive &archive) const{
         archive(
            ::cereal::make_nvp("x", x),
            ::cereal::make_nvp("y", y),
            ::cereal::make_nvp("z", z)
        );
    }
    
    void load(cereal::JSONInputArchive &archive) {
        //x is required
        bool isXLoaded = false;
        while (true)
        {
            const auto namePtr = archive.getNodeName();
            if (!namePtr)
                break;
            const auto name = std::string(namePtr);
            
            if(name == "x"){
                archive(this->x);
                isXLoaded = true;
            }else if(name == "y"){
                archive(this->y);
            }else if(name == "z"){
                archive(this->z);
            }else{
                throw cereal::Exception("undefined field " + name);
            }
        }
        
        if(!isXLoaded){
            throw cereal::Exception("Missing required field x in PayLoad");
        }
    }
};


struct Wrapper{
    int a = 123;
    PayLoad p;
    
    void save(cereal::JSONOutputArchive &archive) const{
         archive(
            ::cereal::make_nvp("a", a),
            ::cereal::make_nvp("p", p)
        );
    }

    void load(cereal::JSONInputArchive &archive) {
        while (true)
        {
            const auto namePtr = archive.getNodeName();
            if (!namePtr)
                break;
            const auto name = std::string(namePtr);
            
            if(name == "a"){
                archive(this->a);
            }else if(name == "p"){
                archive(this->p);
            }else{
                throw cereal::Exception("undefined field " + name);
            }
        }
    }
};

TEST_CASE("Handle optional fields", "[json][optional]"){
    
    // Wrapper e;
    // ostringstream ostream;
    // {
    //     cereal::JSONOutputArchive archive(ostream);
    //     e.save(archive);
    // }
    // cout << ostream.str() << endl;
    
    string wapper_json_no_missing = "{\"a\": 345,\"p\": {\"x\": \"xfull\",\"y\": \"yfull\",\"z\": \"zfull\"}}";
    string wapper_json_missing_z_unorder = "{\"p\": {\"y\": \"y_missing_z\",\"x\": \"x_missing_z\"},\"a\": 345}";
    
    std::string fullJson = "{\n    \"x\": \"xfull\",\n    \"y\": \"yfull\",\n    \"z\": \"zfull\"\n}";
    std::string missing_y_out_of_order_json = "{\"z\": \"z_missing_y\",\"x\":\"x_missing_y\"\n}";
    std::string missing_x_json = "{\"y\": \"yfull\",\n    \"z\": \"zfull\"\n}";
    
    PayLoad presult;
    Wrapper wresult;
    
    SECTION("no missing fields wrapper"){
        istringstream istream(wapper_json_no_missing);
        cereal::JSONInputArchive archive(istream);
        wresult.load(archive);
        
        CHECK(wresult.a == 345);
        CHECK(wresult.p.x == "xfull");
        CHECK(wresult.p.y == "yfull");
        CHECK(wresult.p.z == "zfull");
    }
    
    SECTION("wrapper missing z field in payload, random order"){
        istringstream istream(wapper_json_missing_z_unorder);
        cereal::JSONInputArchive archive(istream);
        wresult.load(archive);
        
        CHECK(wresult.a == 345);
        CHECK(wresult.p.x == "x_missing_z");
        CHECK(wresult.p.y == "y_missing_z");
        CHECK(wresult.p.z == "zDefault");
    }
    
    SECTION("no missing fields"){
        istringstream istream(fullJson);
        cereal::JSONInputArchive archive(istream);
        presult.load(archive);
        
        CHECK(presult.x == "xfull");
        CHECK(presult.y == "yfull");
        CHECK(presult.z == "zfull");
    }
    
    SECTION("missing y field && out of order"){
        istringstream istream(missing_y_out_of_order_json);
        cereal::JSONInputArchive archive(istream);
        presult.load(archive);
        
        CHECK(presult.x == "x_missing_y");
        INFO("y filed is set to default");
        CHECK(presult.y == "yDefault");
        CHECK(presult.z == "z_missing_y");
    }
    
    SECTION("missing required field x, should throw exception"){
        istringstream istream(missing_x_json);
        cereal::JSONInputArchive archive(istream);
        
        INFO("A cereal exception should throw");
        CHECK_THROWS_AS(presult.load(archive), cereal::Exception);
    }
}
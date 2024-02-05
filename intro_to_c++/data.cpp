#include <iostream>
#include <string>
#include <map>
#include <vector>

float bmi(float weight, float height)
{
    float bmi = weight / (height * height);
    return bmi;
}

int main()
{
    // declare the map that uses a person's name as a key, and looks
    // up a map that stores the person's weight and height
    std::map< std::string, std::map<std::string, float> > database;

    // let's first put the data in three vectors
    std::vector<std::string> names = { "James", "Jane", "Janet", "John" };
    std::vector<float> heights = { 1.7, 1.8, 1.5, 1.4 };
    std::vector<float> weights = { 75.4, 76.5, 56.8, 52.0 };

    // now put all of the data into the database
    for (int i=0; i<names.size(); ++i)
    {
        std::map<std::string,float> data;

        data["height"] = heights[i];
        data["weight"] = weights[i];

        database[names[i]] = data;
    }

    // Calculate bmi for every person and save it in the database
    for (int j = 0; j < names.size(); j++)
    {
        float bmi_j = bmi(weights[j], heights[j]);
        database[names[j]]["bmi"] = bmi_j;
    }
    

    // now print out the entire database
    for ( auto item : database )
    {
        // print out the name
        std::cout << item.first << " : ";

        // now print out all of the data about the person
        for ( auto data : item.second )
        {
            std::cout << data.first << "=" << data.second << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}
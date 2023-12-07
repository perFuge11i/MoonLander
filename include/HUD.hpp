#ifndef MOONLANDER_HUD_HPP
#define MOONLANDER_HUD_HPP

#include "threepp/geometries/TextGeometry.hpp"
#include "threepp/loaders/FontLoader.hpp"
#include <string>
#include <cstring>

class HUD {
private:
    std::shared_ptr<threepp::Object3D> HUDmesh = std::make_shared<threepp::Object3D>();
    std::vector<std::vector<std::shared_ptr<threepp::Mesh>>> elements;

    std::vector<std::string> headers;
    std::vector<int> rows;
    std::vector<int> columns;
    std::optional<threepp::Font> font;

    std::vector<std::string> lastString;
public:
    HUD() {
        threepp::FontLoader loader;
        font = loader.load("../data/fonts/optimer_bold.typeface.json");
        threepp::TextGeometry::Options options(*font, 3);

        auto material = threepp::MeshBasicMaterial::create();
        material->color.setHex(0xffffff);

        headers = {"Score", "Time", "Fuel", "Altitude", "Horizontal Speed", "Vertical Speed"};
        lastString = {"","","","","",""};

        rows = {-72, 32, -60, 66};
        columns = {66, 60, 54};

        for (int i = 0; i < headers.size(); i++) {
            auto headerGeometry = threepp::TextGeometry::create(headers[i],options);
            auto valueGeometry = threepp::TextGeometry::create("NaN",options);

            auto headerMesh = threepp::Mesh::create(headerGeometry, material);
            auto valueMesh = threepp::Mesh::create(valueGeometry, material);

            headerMesh->position.set(static_cast<float>(rows[((i)/3)%2]), static_cast<float>(columns[i%3]), 0);
            valueMesh->position.set(static_cast<float>(rows[((i)/3)%2+2]), static_cast<float>(columns[i%3]), 0);

            HUDmesh->add(headerMesh);
            HUDmesh->add(valueMesh);
            elements.push_back(std::vector<std::shared_ptr<threepp::Mesh>> {headerMesh,valueMesh});
        }
    }

    std::shared_ptr<threepp::Object3D> getHUD() {
        return HUDmesh;
    }
    void setPosition(std::vector<float> position) {
        HUDmesh->position.set(static_cast<float>(position[0]), static_cast<float>(position[1]),0);
    }
    void setScale(float scale) {
        HUDmesh->scale.set(scale, scale, scale);
    }
    void setElement(auto header, float number) {
        if (header != "Time") {
            char string[50];
            std::snprintf(string, sizeof(string), "%04d", static_cast<int>(number));

            auto index = std::distance(headers.begin(), std::find(headers.begin(), headers.end(), header));
            threepp::TextGeometry::Options options(*font, 3);
            if (lastString[index] != string) {
                auto geometry = threepp::TextGeometry::create(string, options);

                elements[index][1]->setGeometry(geometry);
            }
            lastString[index] = string;
        }
    }
    void setTime(float time) {
        int minutes = static_cast<int>(time)/60;
        int seconds = static_cast<int>(time)%60;
        char timeString[50];
        char minutesString[50];
        char secondsString[50];
        std::snprintf(minutesString, sizeof(minutesString), "%d", minutes);
        std::snprintf(secondsString, sizeof(secondsString), "%02d", seconds);
        strcat(timeString, minutesString);
        strcat(timeString, ":");
        strcat(timeString, secondsString);

        auto index = std::distance(headers.begin(), std::find(headers.begin(),headers.end(),"Time"));
        if (lastString[index] != timeString) {
            threepp::TextGeometry::Options options(*font, 3);
            auto geometry = threepp::TextGeometry::create(timeString, options);
            elements[index][1]->setGeometry(geometry);
        }
        lastString[index] = timeString;
    }

};

#endif //MOONLANDER_HUD_HPP
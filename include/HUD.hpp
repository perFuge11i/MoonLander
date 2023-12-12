#ifndef MOONLANDER_HUD_HPP
#define MOONLANDER_HUD_HPP

//Line 27: Font from threepp library

#include "threepp/geometries/TextGeometry.hpp"
#include "threepp/loaders/FontLoader.hpp"
#include <string>
#include <cstring>

class HUD {
private:
    std::shared_ptr<threepp::Object3D> HUDmesh = std::make_shared<threepp::Object3D>();
    std::vector<std::vector<std::shared_ptr<threepp::Mesh>>> elements;

    std::vector<std::string> instructions;
    std::vector<std::string> headers;
    std::vector<int> columns;
    std::vector<int> rows;
    std::optional<threepp::Font> font;

    std::vector<std::string> lastString;
    std::shared_ptr<threepp::Mesh> centerTextMesh;

public:
    HUD() {
        threepp::FontLoader loader;
        font = loader.load("../data/fonts/optimer_bold.typeface.json");
        threepp::TextGeometry::Options options(*font, 3);

        auto material = threepp::MeshBasicMaterial::create();
        material->color.setHex(0xffffff);

        instructions = {"< - Rotate left","> - Rotate right","^ - Forward", "x2", "x4", "x5"};
        headers = {"Score", "Time", "Fuel", "Altitude",};
        lastString = {"","","",""};

        columns = {-72, 44, -60, 62};
        rows = {66, 60, 54, 48, 42, 36};

        //Adding isntructions to 'HUDmesh'
        for (int i = 0; i < instructions.size(); i++) {
            auto color = 0xffffff;
            auto instructionGeometry = threepp::TextGeometry::create(instructions[i],options);
            auto instructionMaterial = threepp::MeshBasicMaterial::create();
            if (instructions[i] == "x2") {
                color = 0x00FFFF;
            } else if (instructions[i] == "x4") {
                color = 0x00FF00;
            } else if (instructions[i] == "x5") {
                color = 0xFFFF00;
            }
            instructionMaterial->color.setHex(color);

            auto instructionMesh = threepp::Mesh::create(instructionGeometry, instructionMaterial);
            instructionMesh->position.set(columns[1], rows[i+2], 0);
            if (instructions[i] == "x2") {
                instructionMesh->position.set(columns[1], rows[5], 0);
            } else if (instructions[i] == "x4") {
                instructionMesh->position.set(columns[1] + 10, rows[5], 0);
            } else if (instructions[i] == "x5") {
                instructionMesh->position.set(columns[1] + 20, rows[5], 0);
            }

            HUDmesh->add(instructionMesh);
        }

        //Adding headers and placeholder for values
        for (int i = 0; i < headers.size(); i++) {
            auto headerGeometry = threepp::TextGeometry::create(headers[i],options);
            auto valueGeometry = threepp::TextGeometry::create("",options);

            auto headerMesh = threepp::Mesh::create(headerGeometry, material);
            auto valueMesh = threepp::Mesh::create(valueGeometry, material);

            headerMesh->position.set(static_cast<float>(columns[((i)/3)%2]), static_cast<float>(rows[i%3]), 0);
            valueMesh->position.set(static_cast<float>(columns[((i)/3)%2+2]), static_cast<float>(rows[i%3]), 0);


            HUDmesh->add(headerMesh);
            HUDmesh->add(valueMesh);
            elements.push_back(std::vector<std::shared_ptr<threepp::Mesh>> {headerMesh,valueMesh});
        }

        auto centerTextGeometry = threepp::TextGeometry::create("",options);
        centerTextMesh = threepp::Mesh::create(centerTextGeometry, material);
    }
    void setPosition(std::vector<float> position) {
        HUDmesh->position.set(static_cast<float>(position[0]), static_cast<float>(position[1]),0);
        centerTextMesh->position.set(static_cast<float>(position[0]), static_cast<float>(position[1])+5,0);
    }
    void setScale(float scale) {
        HUDmesh->scale.set(scale, scale, scale);
    }
    void setElement(auto header, float number) {
        if (header != "Time") {
            char string[50];
            std::snprintf(string, sizeof(string), "%04d", static_cast<int>(number));
            //finding the index of the given header
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
   void setCenterText(std::string text, int size) {
        threepp::TextGeometry::Options options(*font, size);
        auto geometry = threepp::TextGeometry::create(text, options);
        geometry->center();
        centerTextMesh->setGeometry(geometry);
    }
    std::shared_ptr<threepp::Mesh> getCenterText() {
        return centerTextMesh;
    }
    std::shared_ptr<threepp::Object3D> getHUD() {
        return HUDmesh;
    }
};

#endif //MOONLANDER_HUD_HPP
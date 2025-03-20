#pragma once

#include "toml.h"
#include "util.h"
#include <filesystem>

namespace sfml {
    inline bool validateProjectInfo(const toml::table &content) {
        std::vector<std::string> missingFields = {};
        std::vector<std::string> expectedFields = {
            "author", "dependencies", "description", "factorio_version", "name", "title", "version"
        };

        bool valid = true;

        if (!content["info"]) {
            valid = false;
        }

        for (const auto &field: expectedFields) {
            if (!content["info"][field]) {
                util::log("Missing field \"" + field + "\" in project.toml!", BgYellow);
                missingFields.push_back(field);
                valid = false;
            }
        }

        return valid;
    }

    inline bool validateProjectCompiler(const toml::table &content) {
        std::vector<std::string> missingFields = {};
        std::vector<std::string> expectedFields = {
            "out_dir"
        };

        bool valid = true;

        if (!content["compile"]) {
            valid = false;
        }

        for (const auto &field: expectedFields) {
            if (!content["compile"][field]) {
                util::log("Missing field \"" + field + "\" in project.toml!", BgYellow);
                missingFields.push_back(field);
                valid = false;
            }
        }

        return valid;
    }

    inline toml::table loadProjectFile(const std::filesystem::path &currentExecutingPath) {
        const std::filesystem::path filePath = currentExecutingPath / "project.toml";

        if (!util::fileExists(filePath)) {
            util::log("Failed to locate project.toml in " + currentExecutingPath.string() + "!", BgRed);
        }

        const auto fileContent = util::loadFile(filePath);

        const auto table = toml::parse(fileContent);

        return table;
    }
}

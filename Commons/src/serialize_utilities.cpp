#include "serialize_utilities.h"

#include <optional>
#include <sstream>

namespace commons {
	json_schema_validator validator;

	bool _validateFileExistence(const std::string& path)
	{
		if (path.empty()) { return false; }
		std::filesystem::path _filepath = { path };
		return std::filesystem::exists(_filepath);
	}

	bool _validateFileExistence(const std::filesystem::path& path)
	{
		return !path.empty() && std::filesystem::exists(path);
	}

	bool is_project_file(const std::filesystem::path& path)
	{
		return path.extension() == ".pproject";
	}

	std::optional<std::filesystem::path> to_project_relative(
	const std::filesystem::path& absPath,
	const std::filesystem::path& projectRoot)
	{
		if (absPath.empty() || projectRoot.empty()) {
			return std::nullopt;
		}

		auto rel = std::filesystem::relative(absPath, projectRoot);
		if (rel.empty()) {
			return std::nullopt;
		}

		return rel.lexically_normal();
	}

	std::optional<std::filesystem::path> to_project_relative(
	const std::string& absPath,
	const std::string& projectRoot){
		return to_project_relative(
			std::filesystem::path(absPath),
			std::filesystem::path(projectRoot));
	}

	bool _validateSchemaAdherence(const std::string& path, const json& schema) {
		std::ifstream data(path);
		if (!data.is_open()) {
			return false;
		}

		json data_json;
		try {
			// data >> data_json;
			data_json = json::parse(data);
		} catch (const json::parse_error& e) {
			std::cerr << "JSON parse failed: " << e.what() << "\n";
			return false;
		}

		validator.set_root_schema(schema);
		try {
			auto json_content = validator.validate(data_json);
			std::cout << "Validation of file " << path << " succeeded\n";
			return true;
		}
		catch (const std::exception& e) {
			std::cerr << "Validation failed, here is why: " << e.what() << "\n";
			return false;
		}
		// Further schema validation logic can go here
		return true;
	}

	namespace fileIO
	{
		/// @brief Extract Source code from file.
		/// @param path - The relative path to the file.
		/// @return A std::string contained in the file.
		/// @note Works with Absolute paths too.
		std::string extractSourceFromFile(const char *path) {
			// Open file with RAII; automatically closes when out of scope.
			const std::ifstream file(path, std::ios::in);
			if (!file) {
				throw std::runtime_error("File Read Error.");
			}

			// Read the entire file into a string using a stringstream.
			std::ostringstream sourceStream;
			sourceStream << file.rdbuf();
			std::string source = sourceStream.str();

			// Log the content and return the string.
			std::cout << source.c_str() << std::endl;
			return source;
		}

		/// @brief Extract Accets, Scene, and Prefab raw source data from JSON
		/// @param path - The Absolute path to the json file
		/// @return A json object from the nlohmann library representing the unparsed schema-aligned contents of the file
		std::optional<json> extractSourceFromJSON(const char* path)
		{
			if (path == nullptr || *path == '\0') { return std::nullopt; }
			const auto real_path = std::filesystem::path(path);

			if (!_validateFileExistence(real_path)){ return std::nullopt; }
			std::ifstream data(real_path.c_str());
			if (!data) { return std::nullopt; }
			// data >> data_json;

			try {
				json data_json = json::parse(data);
				return data_json;
			}
			catch (const json::parse_error& e) {
				std::cerr << "JSON parse failed: " << e.what() << "\n";
				return std::nullopt;
			}
		}
	}
}
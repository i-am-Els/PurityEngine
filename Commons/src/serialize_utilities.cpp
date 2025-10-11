#include "serialize_utilities.h"

namespace commons {
	json_schema_validator validator;

	bool _validateFileExistence(const std::string& path)
	{
		std::filesystem::path _filepath = { path };
		return std::filesystem::exists(_filepath);
	}

	bool _validateFileExistence(const std::filesystem::path& path)
	{
		return std::filesystem::exists(path);
	}

	bool _validateSchemaAdherence(const std::string& path, const json& schema) {

		std::ifstream data(path);
		const json data_json = json::parse(data);
		if (!data && !data_json) { return false; }

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
}
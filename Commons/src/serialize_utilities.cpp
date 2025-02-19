#include "serialize_utilities.h"

namespace commons {
	bool _validateFileExistence(std::string path)
	{
		std::filesystem::path _filepath = { path };
		return std::filesystem::exists(_filepath);
	}

	bool _validateFileExistence(std::filesystem::path path)
	{
		return std::filesystem::exists(path);
	}

	bool _validateSchemaAdherence(std::string path, json schema) {

		std::ifstream data(path);
		json data_json = json::parse(data);
		if (!data && !data_json) { return false; }

		json_schema_validator validator;
		validator.set_root_schema(schema);
		try {
			validator.validate(data_json);
			std::cout << "Validation of file " << path << " succeeded\n";
		}
		catch (const std::exception& e) {
			std::cerr << "Validation failed, here is why: " << e.what() << "\n";
			return false;
		}
		// Further schema validation logic can go here
		return true;
	}
}
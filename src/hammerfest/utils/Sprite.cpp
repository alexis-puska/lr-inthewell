#include "Sprite.h"

#include "resources/image_parser.h"
#include "resources/light.h"

#include <vector>

Sprite Sprite::m_instance = Sprite();

Sprite::Sprite() {

	TTF_Init();
	IMG_Init (IMG_INIT_PNG);
	fprintf(stderr, "Init sprite system\n");

	fprintf(stderr, "%s", image_parser_json);

	Json::Reader reader;
	Json::Value root;

	std::string jsonString(image_parser_json, image_parser_json + sizeof image_parser_json / sizeof image_parser_json[0]);
	reader.parse(jsonString, root);
	for (int i = 0; i < root.size(); i++) {
		fprintf(stderr, "test json : %i %i %s\n", root.size(), i, root[i]["file"].asCString());
		for (int j = 0; j < root[i]["area"].size(); j++) {
		fprintf(stderr, "nb area : %i\n", root[i]["area"].size());
		fprintf(stderr, "area : %i %i %i %i %i %i\n", root[i]["area"][j]["x"].asUInt(),
				root[i]["area"][j]["y"].asUInt(),
				root[i]["area"][j]["nx"].asUInt(),
				root[i]["area"][j]["ny"].asUInt(),
				root[i]["area"][j]["sx"].asUInt(),
				root[i]["area"][j]["sy"].asUInt()
		);
	}
}

fprintf(stderr, "\n\n\n\nEnd init sprite system\n");

}

Sprite::~Sprite() {
fprintf(stderr, "close sprite system\n");

fprintf(stderr, "close font text system\n");
//TTF_CloseFont(font);
IMG_Quit();
TTF_Quit();
}

Sprite& Sprite::Instance() {
return m_instance;
}


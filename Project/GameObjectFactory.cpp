#include "GameObject.h"
#include "GameObjectFactory.h"

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include <fstream>

extern ResourceManager* gpResourceManager;
extern GameObjectManager* gpGameObjectManager;

GameObjectFactory::GameObjectFactory()
{
	mComponentCreators["Transform"] = (void*)(new TransformCreator());
	mComponentCreators["Sprite"] = (void*)(new SpriteCreator());
	mComponentCreators["Controller"] = (void*)(new ControllerCreator());
	mComponentCreators["Health"] = (void*)(new HealthCreator());
	mComponentCreators["Beam Ammo"] = (void*)(new BeamAmmoCreator());
	mComponentCreators["Big Enemy Powers"] = (void*)(new BigEnemyPowersCreator());
	mComponentCreators["Stat Display Manager"] = (void*)(new StatDisplayManagerCreator());
}

GameObject* GameObjectFactory::BuildObject(std::string dataFilePath)
{
	GameObject* pGameObject = new GameObject();

	std::ifstream ifs(dataFilePath);
	rapidjson::IStreamWrapper isw(ifs);

	rapidjson::Document document;
	document.ParseStream(isw);  

	if (document.HasMember("Transform")) {
		pGameObject->AddComponent<Transform>(((TransformCreator*)mComponentCreators["Transform"])->Create() );
		pGameObject->GetComponent<Transform>()->Deserialize(document["Transform"].GetObject());
	}

	if (document.HasMember("Sprite")) {
		pGameObject->AddComponent<Sprite>(((SpriteCreator*)mComponentCreators["Sprite"])->Create());
		pGameObject->GetComponent<Sprite>()->Deserialize(document["Sprite"].GetObject());
	}

	if (document.HasMember("Controller")) {
		pGameObject->AddComponent<Controller>(((ControllerCreator*)mComponentCreators["Controller"])->Create());
	}

	if (document.HasMember("Health")) {
		pGameObject->AddComponent<Health>(((HealthCreator*)mComponentCreators["Health"])->Create());
		pGameObject->GetComponent<Health>()->mHealth = document["Health"].GetInt();
	}

	if (document.HasMember("Beam Ammo")) {
		pGameObject->AddComponent<BeamAmmo>(((BeamAmmoCreator*)mComponentCreators["Beam Ammo"])->Create());
		pGameObject->GetComponent<BeamAmmo>()->mAmmo = document["Beam Ammo"].GetInt();
	}

	if (document.HasMember("Big Enemy Powers")) {
		pGameObject->AddComponent<BigEnemyPowers>(((BigEnemyPowersCreator*)mComponentCreators["Big Enemy Powers"])->Create());
	}

	if (document.HasMember("Stat Display Manager")) {
		pGameObject->AddComponent<StatDisplayManager>(((StatDisplayManagerCreator*)mComponentCreators["Stat Display Manager"])->Create());
	}

	if (document.HasMember("Color")) {
		pGameObject->mColor = document["Color"].GetString();
	}

	pGameObject->mType = document.FindMember("Type")->value.GetString();
	pGameObject->mName = document.FindMember("Name")->value.GetString();

	gpGameObjectManager->AddGameObject(pGameObject);

	return pGameObject;
}

void GameObjectFactory::LevelLoad(std::string dataFilePath)
{
	std::ifstream ifs(dataFilePath);
	rapidjson::IStreamWrapper isw(ifs);

	rapidjson::Document document;
	document.ParseStream(isw);

	const rapidjson::Value& gameObjects = document["Game Objects"];

	for (rapidjson::Value::ConstValueIterator itr = gameObjects.Begin(); itr != gameObjects.End(); ++itr) {
	
		if (itr->HasMember("Archetype")) {
			GameObject* tempPtoGameObj = BuildObject(((itr->GetObject()).FindMember("Archetype"))->value.GetString());		

			//tempPtoGameObj->mName = itr->FindMember("Name")->value.GetString();

			if (itr->HasMember("Transform")) {
				rapidjson::GenericObject<true, rapidjson::Value::ValueType> transformItems = (itr->FindMember("Transform"))->value.GetObject();
				tempPtoGameObj->GetComponent<Transform>()->mPos.x = transformItems.FindMember("posX")->value.GetFloat();
				tempPtoGameObj->GetComponent<Transform>()->mPos.y = transformItems.FindMember("posY")->value.GetFloat();
			}
		}
	}
}

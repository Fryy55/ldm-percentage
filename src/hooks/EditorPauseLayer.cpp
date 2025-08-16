#include <Geode/modify/EditorPauseLayer.hpp>

using namespace geode::prelude;


class $modify(EditorPauseLayer) {
	$override
	bool init(LevelEditorLayer* p0) {
		if (!EditorPauseLayer::init(p0))
			return false;

		auto label = static_cast<CCLabelBMFont*>(this->querySelector("object-count-label"));
		bool ldm = Mod::get()->getSettingValue<bool>("general-ldm");

		std::uint64_t foundObjectsCount = 0u;
		for (auto obj : CCArrayExt<GameObject*>(m_editorLayer->m_objects)) {
			foundObjectsCount += ldm ? !obj->m_isHighDetail : obj->m_isHighDetail;
		}

		auto precision = Mod::get()->getSettingValue<int>("general-precision");
		auto percentage = static_cast<double>(foundObjectsCount) / m_editorLayer->m_objectCount * 100.;

		label->setString(
			std::string(label->getString()).append(
				fmt::format(
					" | {}: {} ({}%)",
					ldm ?
						"LDM"
						:
						"High Detail",
					foundObjectsCount,
					precision ?
						numToString(percentage, precision)
						:
						numToString(std::round(percentage))
				)
			).c_str()
		);

		return true;
	}
};
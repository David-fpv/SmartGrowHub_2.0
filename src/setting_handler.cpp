#include "setting_handler.h"

void SettingHandler::AddSetting(Setting setting)
{
    settings_.push_back(setting);
};

void SettingHandler::SetStringJson(std::string string_json)
{
    JsonDocument json;
    deserializeJson(json, string_json);
    JsonArray json_array = json.as<JsonArray>();

    for (JsonVariant array_value: json_array) // iterate through all the settings of the json file
    {
        std::string component_type = array_value["Type"].as<std::string>();
        for (int i = 0; i < settings_.size(); i++) // we are looking for a setting with this type
        {
            if (settings_[i].GetType() == component_type)
            {
                JsonArray components_array = array_value["Components"].as<JsonArray>();
                
                for (JsonObject component_value : components_array) // iterating over the components of the json file
                {
                    std::string type = component_value["Type"].as<std::string>();
                    double value = component_value["Value"].as<double>();
                    std::string unit;
                    if (component_type != "Mode")
                    {
                        std::string unit = component_value["Unit"].as<std::string>();
                    }
                    settings_[i].UpdateComponent(Component (type, value, unit));
                }
            } 
        }
    }
};

Setting SettingHandler::GetSetting(std::string type)
{
    for (int i = 0; i < settings_.size(); i++)
    {
        if (settings_[i].GetType() == type)
        {
            return settings_[i];
        }
    }
}

void SettingHandler::CurateAllSetting()
{
    for (int i = 0; i < settings_.size(); i++)
    {
        settings_[i].Adjust();
    }
}
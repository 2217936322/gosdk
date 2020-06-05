#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <memory>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <variant>

#include "../dependencies/global.hpp"
#include "../utilities/global.hpp"

namespace Variables {
  class CConfig {
  private:
    // clang-format off
  #define add_setting(setting, default_value) \
  mSettings[setting] = default_value;
    // clang-format on

    class SSettings {
    private:
      using Setting_t = std::variant<int, bool, float, std::string, Utils::Color>;
      std::unordered_map<std::string, Setting_t> mSettings;

      /// <summary>
      /// Create config functions there
      /// </summary>
    public:
      SSettings( ) { add_setting( "test_boolean", false ); }

      /// <summary>
      /// Getter from the config map
      /// </summary>
      /// <param name="setting">Function name to scan for</param>
      /// <returns>Return value(s) for types supposed by the variant</returns>
      template <typename Type> Type & get( const std::string & setting ) { return std::get<Type>( mSettings[ setting ] ); }

      /// <summary>
      /// Function that will handle creating a config file and storing values from SSettings to it
      /// </summary>
      /// <param name="config_file_name">Name you want to give the config file</param>
      bool m_bSave( const std::string & config_file_name );

      /// <summary>
      /// Function that will handle loading a config file and assign values according to the SSettings
      /// </summary>
      /// <param name="config_file_name">Name you want to get the config from</param>
      bool m_bLoad( const std::string & config_file_name );
    };

  public:
    /// <summary>
    /// Pointer that will handle scope and lifetime of config object
    /// </summary>
    std::unique_ptr<CConfig::SSettings> g_pSettings{ nullptr };

    /// <summary>
    /// Not very cash money
    /// </summary>
    void RunConfig( ) { g_pSettings = std::make_unique<CConfig::SSettings>( ); }

    void ReleaseConfig( ) { g_pSettings.reset( ); }
  };

  inline CConfig g_Config{ };
} // namespace Variables
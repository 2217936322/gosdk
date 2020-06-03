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

namespace Config {
  // clang-format off
  #define add_setting(setting, default_value) \
  mSettings[STR(setting)] = default_value;
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

  /// <summary>
  /// Pointer that will handle scope and lifetime of config object
  /// </summary>
  inline std::unique_ptr<Config::SSettings> g_pConfig{ nullptr };

  /// <summary>
  /// Not very cash money
  /// </summary>
  inline void RunConfig( ) { g_pConfig = std::make_unique<Config::SSettings>( ); }

  inline void ReleaseConfig( ) { g_pConfig.reset( ); }
} // namespace Config
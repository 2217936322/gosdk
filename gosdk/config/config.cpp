#include "config.hpp"
#include <Windows.h>
#include <sstream>

#pragma warning( disable : 4244 )

namespace Variables {
  bool CConfig::SSettings::m_bSave( const std::string & config_file_name ) {
    nlohmann::json config;
    for ( const auto & [ setting, value ] : mSettings ) {
      if ( std::holds_alternative<int>( value ) )
        config[ setting ] = { { "identifier", value.index( ) }, { "value", this->get<int>( setting ) } };
      else if ( std::holds_alternative<bool>( value ) )
        config[ setting ] = { { "identifier", value.index( ) }, { "value", this->get<bool>( setting ) } };
      else if ( std::holds_alternative<float>( value ) )
        config[ setting ] = { { "identifier", value.index( ) }, { "value", this->get<float>( setting ) } };
      else if ( std::holds_alternative<std::string>( value ) )
        config[ setting ] = { { "identifier", value.index( ) }, { "value", this->get<std::string>( setting ) } };
      else if ( std::holds_alternative<Utils::Color>( value ) )
        config[ setting ] = { { "identifier", value.index( ) },
                              { "value_r", this->get<Utils::Color>( setting ).m_uRed },
                              { "value_g", this->get<Utils::Color>( setting ).m_uGreen },
                              { "value_b", this->get<Utils::Color>( setting ).m_uBlue }

        };
    }
    std::ofstream ofConfig( config_file_name );
#ifdef _DEBUG
    ofConfig << std::setw( 2 ) << config << std::endl;
#else
    // Reduce configs file size in release mode.
    ofConfig << config << std::endl;
#endif
    ofConfig.close( );
    return true;
  }

  bool CConfig::SSettings::m_bLoad( const std::string & config_file_name ) {
    if ( !std::filesystem::exists( std::filesystem::current_path( ) / config_file_name ) )
      return false;

    std::ifstream ifConfig( config_file_name );
    nlohmann::json config = nlohmann::json::parse( ifConfig );
    for ( const auto & [ setting, value ] : config.items( ) ) {
      switch ( value[ "identifier" ].get<int>( ) ) {
        case 0:
          mSettings[ setting ] = value[ "value" ].get<int>( );
          break;
        case 1:
          mSettings[ setting ] = value[ "value" ].get<bool>( );
          break;
        case 2:
          mSettings[ setting ] = value[ "value" ].get<float>( );
          break;
        case 3:
          mSettings[ setting ] = value[ "value" ].get<std::string>( );
          break;
        case 4:
          this->get<Utils::Color>( setting ).m_uRed = value[ "value_r" ].get<float>( );
          this->get<Utils::Color>( setting ).m_uGreen = value[ "value_g" ].get<float>( );
          this->get<Utils::Color>( setting ).m_uBlue = value[ "value_b" ].get<float>( );
          break;
      }
    }
    ifConfig.close( );
    return true;
  }
} // namespace Variables
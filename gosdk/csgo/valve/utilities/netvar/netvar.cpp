#include "netvar.hpp"
#include "../../interfaces.hpp"
#include <fstream>

std::ofstream ofStream( "netvar_dump.dmp" );

void DumpRecursive( CS::Classes::CRecvTable * table ) {
  for ( auto i = 0; i < table->m_iPropsCount; ++i ) {
    const auto Prop = &table->m_Props[ i ];

    if ( !Prop || std::isdigit( Prop->m_cPropName[ 0 ] ) || !std::strcmp( Prop->m_cPropName, ( "baseclass" ) ) )
      continue;

    if ( Prop->m_PropType == 6 && Prop->m_DataTable && Prop->m_DataTable->m_cTableName[ 0 ] == 'D' )
      DumpRecursive( Prop->m_DataTable );

    ofStream << table->m_cTableName + std::string( "->" ) + Prop->m_cPropName << "=" << Prop->m_iOffset << '\n';

    CS::g_Netvar.Offsets[ table->m_cTableName + std::string( "->" ) + Prop->m_cPropName ] = Prop->m_iOffset;
  }
}

void CS::CNetvar::RunNetvar( ) noexcept {
  for ( auto pClass = CS::g_Interfaces.g_pClient->GetAllClasses( ); pClass; pClass = pClass->m_NextPtr ) {
    const auto Table = pClass->m_RecvTablePtr;

    if ( !Table )
      continue;

    DumpRecursive( Table );
  }
}

void CS::CNetvar::ReleaseNetvars( ) noexcept { Offsets.clear( ); }
#pragma once

namespace CS::Classes {
  class CDVariant;
  class CRecvTable;
  class CRecvProp;
  class CRecvProxyData;

  using RecvVarProxy_t = void ( * )( const CRecvProxyData * pData, void * pStruct, void * pOut );
  using ArrayLengthRecvProxy_t = void ( * )( void * pStruct, int iObjectId, int iCurrentArrayLength );
  using DataTableRecvVarProxy_t = void ( * )( const CRecvProp * pProp, void ** pOut, void * pData, int iObjectId );

  enum ESendPropType : short {
    _int = 0,
    _float,
    _vec,
    _vec_xy,
    _string,
    _array,
    _data_table,
    _int_64,
  };

  class CDVariant {
  public:
    union {
      float m_fFloat;
      long m_iInt;
      char * m_cString;
      void * m_Data;
      float m_fVector[ 3 ];
      __int64 m_iInt64;
    };
    ESendPropType m_Type;
  };
  class CRecvProxyData {
  public:
    const CRecvProp * m_RecvProp;
    CDVariant m_Value;
    int m_iElementIndex;
    int m_iObjectID;
  };

  class CRecvProp {
  public:
    char * m_cPropName;
    ESendPropType m_PropType;
    int m_iPropFlags;
    int m_iBufferSize;
    int m_iIsInsideOfArray;
    const void * m_ExtraDataPtr;
    CRecvProp * m_ArrayProp;
    ArrayLengthRecvProxy_t m_ArrLengthProxy;
    RecvVarProxy_t m_Proxy_t;
    DataTableRecvVarProxy_t m_DataTableProxy_t;
    CRecvTable * m_DataTable;
    int m_iOffset;
    int m_iElementsStride;
    int m_ElementsCount;
    const char * m_cParrentArrayPropName;
  };

  class CRecvTable {
  public:
    CRecvProp * m_Props;
    int m_iPropsCount;
    void * m_DecoderPtr;
    char * m_cTableName;
    bool m_bIsInitialized;
    bool m_bIsInMainList;
  };
} // namespace CS::Classes
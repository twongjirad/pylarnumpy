#include <iostream>
#include <vector>
#include <string>

// #ifndef H5_NO_NAMESPACE
// #ifndef H5_NO_STD
// using std::cout;
// using std::endl;
// #endif  // H5_NO_STD
// #endif

#include "H5Cpp.h"

int main( int nargs, char** agv ) {

  const H5std_string FILE_NAME( "test.hd5" );

  H5::H5File file( FILE_NAME, H5F_ACC_TRUNC );

  // ----------------------------------------------------------------
  // '/' Group
  // Add attributes
  // CLASS: "Group"
  std::string str_CLASS = "CLASS";
  const H5std_string ATTR_CLASS_VALUE( "GROUP" );
  H5::StrType strdatatype_class( H5::PredType::C_S1, str_CLASS.length() );
  H5::DataSpace attr_dataspace_class = H5::DataSpace(H5S_SCALAR);
  H5::Attribute* att_class = new H5::Attribute( file.createAttribute( str_CLASS.c_str(), strdatatype_class, attr_dataspace_class ) );
  att_class->write( strdatatype_class, ATTR_CLASS_VALUE );
  // PYTABLES_FORMAT_VERSION: "2.1"
  std::string str_pytformat = "PYTABLES_FORMAT_VERSION";
  const H5std_string ATTR_PYTFORMAT_VALUE( "2.1" );
  H5::StrType strdatatype_pytformat( H5::PredType::C_S1, 3 );
  H5::DataSpace attr_dataspace_pytformat = H5::DataSpace(H5S_SCALAR);
  H5::Attribute* att_pytformat = new H5::Attribute( file.createAttribute( str_pytformat.c_str(), strdatatype_pytformat, attr_dataspace_pytformat ) );
  att_pytformat->write( strdatatype_pytformat, ATTR_PYTFORMAT_VALUE );
  // TITLE: "root"
  std::string str_title = "TITLE";
  const H5std_string ATTR_TITLE_VALUE( "ROOT" );
  H5::StrType strdatatype_title( H5::PredType::C_S1, 1 );
  H5::DataSpace attr_dataspace_title = H5::DataSpace(H5S_SCALAR);
  H5::Attribute* att_title = new H5::Attribute( file.createAttribute( str_title.c_str(), strdatatype_title, attr_dataspace_title ) );
  att_title->write( strdatatype_title, ATTR_TITLE_VALUE );
  // VERSION: "1.0"
  std::string str_version = "VERSION";
  const H5std_string ATTR_VERSION_VALUE( "1.0" );
  H5::StrType strdatatype_version( H5::PredType::C_S1, 3 );
  H5::DataSpace attr_dataspace_version = H5::DataSpace(H5S_SCALAR);
  H5::Attribute* att_version = new H5::Attribute( file.createAttribute( str_version.c_str(), strdatatype_version, attr_dataspace_version ) );
  att_version->write( strdatatype_version, ATTR_VERSION_VALUE );

  // ----------------------------------------------------------------
  // Store RawDigits Table
  // Represented as a Compound data type with certain attributes
  const int LENGTH = 5;
  hsize_t dim[] = { LENGTH };
  H5::DataSpace rawdigits_dataspace( 1, dim );
  const int NADCS = 10;
  hsize_t adc_dim[] = { NADCS };
  typedef struct rawdigits_t {
    unsigned int eventid;
    unsigned short crate;
    unsigned short slot;
    unsigned short channel;
    unsigned short wireid;
    unsigned short adcs[ NADCS ];
  } rawdigits_t;
  rawdigits_t raw[LENGTH];

  // name columns
  const H5std_string RAW_DIGITS_ATT_EVENTID_VALUE( "eventid" );
  const H5std_string RAW_DIGITS_ATT_CRATE_VALUE( "crate" );
  const H5std_string RAW_DIGITS_ATT_SLOT_VALUE( "slot" );
  const H5std_string RAW_DIGITS_ATT_CHANNEL_VALUE( "channel" );
  const H5std_string RAW_DIGITS_ATT_WIREID_VALUE( "wireid" );
  const H5std_string RAW_DIGITS_ATT_ADCS_VALUE( "adcs" );

  // fill data
  for (int i=0; i<LENGTH; i++) {
    raw[i].eventid = i+1;
    raw[i].crate = 9;
    raw[i].slot  = 7;
    raw[i].channel = 16;
    raw[i].wireid = 1000;
    std::vector<unsigned short> wfm( NADCS, (unsigned short)i );
    //raw[i].adcs = wfm;
    memcpy( raw[i].adcs, wfm.data(), sizeof(unsigned short)*NADCS );
  }
  H5::CompType rawdigits_comptype( sizeof( rawdigits_t ) );
  rawdigits_comptype.insertMember( RAW_DIGITS_ATT_EVENTID_VALUE, HOFFSET(rawdigits_t, eventid), H5::PredType::NATIVE_UINT );
  rawdigits_comptype.insertMember( RAW_DIGITS_ATT_CRATE_VALUE, HOFFSET(rawdigits_t, crate), H5::PredType::NATIVE_UINT16 );
  rawdigits_comptype.insertMember( RAW_DIGITS_ATT_SLOT_VALUE, HOFFSET(rawdigits_t, slot), H5::PredType::NATIVE_UINT16 );
  rawdigits_comptype.insertMember( RAW_DIGITS_ATT_CHANNEL_VALUE, HOFFSET(rawdigits_t, channel), H5::PredType::NATIVE_UINT16 );
  rawdigits_comptype.insertMember( RAW_DIGITS_ATT_WIREID_VALUE, HOFFSET(rawdigits_t, wireid), H5::PredType::NATIVE_UINT16 );
  rawdigits_comptype.insertMember( RAW_DIGITS_ATT_ADCS_VALUE, HOFFSET(rawdigits_t, adcs), H5::ArrayType( H5::PredType::NATIVE_UINT16, 1, adc_dim ) );
  

  H5::DataSet* dataset_rawdigits = new H5::DataSet( file.createDataSet( "/RawDigit", rawdigits_comptype, rawdigits_dataspace ) );
  dataset_rawdigits->write( raw, rawdigits_comptype );

  // add attributes
  // CLASS: "Group"
  const H5std_string RAW_DIGITS_ATTR_CLASS_VALUE( "TABLE" );
  H5::StrType rawdigits_strdatatype_class( H5::PredType::C_S1, 5+1 );
  H5::Attribute* raw_digits_att_class = new H5::Attribute( dataset_rawdigits->createAttribute( str_CLASS.c_str(), strdatatype_class, attr_dataspace_class ) );
  raw_digits_att_class->write( rawdigits_strdatatype_class, RAW_DIGITS_ATTR_CLASS_VALUE );
  // TITLE
  const H5std_string RAW_DIGITS_ATTR_TITLE_VALUE( "RawDigits" );
  H5::StrType rawdigits_strdatatype_title( H5::PredType::C_S1, 9+1 );
  H5::Attribute* raw_digits_att_title = new H5::Attribute( dataset_rawdigits->createAttribute( str_title.c_str(), rawdigits_strdatatype_title, attr_dataspace_title ) );
  raw_digits_att_title->write( rawdigits_strdatatype_title, RAW_DIGITS_ATTR_TITLE_VALUE );
  // VERSION
  const H5std_string ATTR_TABLE_VERSION_VALUE( "2.7" );
  H5::StrType rawdigits_strdatatype_version( H5::PredType::C_S1, 3+1 );
  H5::Attribute* raw_digits_att_version = new H5::Attribute( dataset_rawdigits->createAttribute( str_version.c_str(), rawdigits_strdatatype_version, attr_dataspace_version ) );
  raw_digits_att_version->write( rawdigits_strdatatype_version, ATTR_TABLE_VERSION_VALUE );
  // COLUMNS
  std::string str_rawdigits_eventid = "FIELD_0_NAME";
  H5::StrType rawdigits_strdatatype_eventid( H5::PredType::C_S1, 7+1 );
  H5::Attribute* raw_digits_att_eventid = new H5::Attribute( dataset_rawdigits->createAttribute( str_rawdigits_eventid.c_str(), rawdigits_strdatatype_eventid, H5::DataSpace(H5S_SCALAR) ) );
  raw_digits_att_eventid->write( rawdigits_strdatatype_eventid, RAW_DIGITS_ATT_EVENTID_VALUE );
  std::string str_rawdigits_eventid_fill = "FIELD_0_FILL";
  unsigned int rawdigits_eventid_fill = 0;
  H5::Attribute* raw_digits_att_eventid_fill = new H5::Attribute( dataset_rawdigits->createAttribute( str_rawdigits_eventid_fill.c_str(), H5::IntType(H5::PredType::NATIVE_UINT16), H5::DataSpace(H5S_SCALAR) ) );
  raw_digits_att_eventid_fill->write( H5::IntType(H5::PredType::NATIVE_UINT16), &rawdigits_eventid_fill );
  // ---
  std::string str_rawdigits_crate = "FIELD_1_NAME";
  H5::StrType rawdigits_strdatatype_crate( H5::PredType::C_S1, 5+1 );
  H5::DataSpace rawdigits_att_dataspace_crate = H5::DataSpace(H5S_SCALAR);
  H5::Attribute* raw_digits_att_crate = new H5::Attribute( dataset_rawdigits->createAttribute( str_rawdigits_crate.c_str(), rawdigits_strdatatype_crate, rawdigits_att_dataspace_crate ) );
  raw_digits_att_crate->write( rawdigits_strdatatype_crate, RAW_DIGITS_ATT_CRATE_VALUE );
  std::string str_rawdigits_crate_fill = "FIELD_1_FILL";
  unsigned short rawdigits_crate_fill = 0;
  H5::IntType rawdigits_datatype_crate_fill( H5::PredType::NATIVE_UINT16 );
  H5::Attribute* raw_digits_att_crate_fill = new H5::Attribute( dataset_rawdigits->createAttribute( str_rawdigits_crate_fill.c_str(), rawdigits_datatype_crate_fill, rawdigits_att_dataspace_crate ) );
  raw_digits_att_crate_fill->write( rawdigits_datatype_crate_fill, &rawdigits_crate_fill );
  // ---
  std::string str_rawdigits_slot = "FIELD_2_NAME";
  H5::StrType rawdigits_strdatatype_slot( H5::PredType::C_S1, 4+1 );
  H5::DataSpace rawdigits_att_dataspace_slot = H5::DataSpace(H5S_SCALAR);
  H5::Attribute* raw_digits_att_slot = new H5::Attribute( dataset_rawdigits->createAttribute( str_rawdigits_slot.c_str(), rawdigits_strdatatype_slot, rawdigits_att_dataspace_slot ) );
  raw_digits_att_slot->write( rawdigits_strdatatype_slot, RAW_DIGITS_ATT_SLOT_VALUE );
  std::string str_rawdigits_slot_fill = "FIELD_2_FILL";
  unsigned short rawdigits_slot_fill = 0;
  H5::Attribute* raw_digits_att_slot_fill = new H5::Attribute( dataset_rawdigits->createAttribute( str_rawdigits_slot_fill.c_str(), H5::IntType(H5::PredType::NATIVE_UINT16), H5::DataSpace(H5S_SCALAR) ) );
  raw_digits_att_slot_fill->write( H5::IntType(H5::PredType::NATIVE_UINT16), &rawdigits_slot_fill );
  // ---
  std::string str_rawdigits_channel = "FIELD_3_NAME";
  H5::StrType rawdigits_strdatatype_channel( H5::PredType::C_S1, 7+1 );
  H5::DataSpace rawdigits_att_dataspace_channel = H5::DataSpace(H5S_SCALAR);
  H5::Attribute* raw_digits_att_channel = new H5::Attribute( dataset_rawdigits->createAttribute( str_rawdigits_channel.c_str(), rawdigits_strdatatype_channel, rawdigits_att_dataspace_channel ) );
  raw_digits_att_channel->write( rawdigits_strdatatype_channel, RAW_DIGITS_ATT_CHANNEL_VALUE );
  std::string str_rawdigits_channel_fill = "FIELD_3_FILL";
  unsigned short rawdigits_channel_fill = 0;
  H5::Attribute* raw_digits_att_channel_fill = new H5::Attribute( dataset_rawdigits->createAttribute( str_rawdigits_channel_fill.c_str(), H5::IntType(H5::PredType::NATIVE_UINT16), H5::DataSpace(H5S_SCALAR) ) );
  raw_digits_att_channel_fill->write( H5::IntType(H5::PredType::NATIVE_UINT16), &rawdigits_channel_fill );
  // ---
  std::string str_rawdigits_wireid = "FIELD_4_NAME";
  H5::StrType rawdigits_strdatatype_wireid( H5::PredType::C_S1, 6+1 );
  H5::DataSpace rawdigits_att_dataspace_wireid = H5::DataSpace(H5S_SCALAR);
  H5::Attribute* raw_digits_att_wireid = new H5::Attribute( dataset_rawdigits->createAttribute( str_rawdigits_wireid.c_str(), rawdigits_strdatatype_wireid, rawdigits_att_dataspace_wireid ) );
  raw_digits_att_wireid->write( rawdigits_strdatatype_wireid, RAW_DIGITS_ATT_WIREID_VALUE );
  std::string str_rawdigits_wireid_fill = "FIELD_4_FILL";
  unsigned short rawdigits_wireid_fill = 0;
  H5::Attribute* raw_digits_att_wireid_fill = new H5::Attribute( dataset_rawdigits->createAttribute( str_rawdigits_wireid_fill.c_str(), H5::IntType(H5::PredType::NATIVE_UINT16), H5::DataSpace(H5S_SCALAR) ) );
  raw_digits_att_wireid_fill->write( H5::IntType(H5::PredType::NATIVE_UINT16), &rawdigits_wireid_fill );
  // ---
  std::string str_rawdigits_ADCS = "FIELD_5_NAME";
  H5::StrType rawdigits_strdatatype_ADCS( H5::PredType::C_S1, 4+1 );
  H5::DataSpace rawdigits_att_dataspace_ADCS = H5::DataSpace(H5S_SCALAR);
  H5::Attribute* raw_digits_att_ADCS = new H5::Attribute( dataset_rawdigits->createAttribute( str_rawdigits_ADCS.c_str(), rawdigits_strdatatype_ADCS, rawdigits_att_dataspace_ADCS ) );
  raw_digits_att_ADCS->write( rawdigits_strdatatype_ADCS, RAW_DIGITS_ATT_ADCS_VALUE );
  std::string str_rawdigits_adcs_fill = "FIELD_5_FILL";
  unsigned short rawdigits_adcs_fill = 0;
  H5::Attribute* raw_digits_att_adcs_fill = new H5::Attribute( dataset_rawdigits->createAttribute( str_rawdigits_adcs_fill.c_str(), H5::IntType(H5::PredType::NATIVE_UINT16), H5::DataSpace(H5S_SCALAR) ) );
  raw_digits_att_adcs_fill->write( H5::IntType(H5::PredType::NATIVE_UINT16), &rawdigits_adcs_fill );
  // ---
  std::string str_rawdigits_nrows = "NROWS";
  int nrows = LENGTH;
  H5::Attribute* raw_digits_att_nrows = new H5::Attribute( dataset_rawdigits->createAttribute( str_rawdigits_nrows.c_str(), H5::IntType(H5::PredType::NATIVE_INT16), H5::DataSpace(H5S_SCALAR) ) );
  raw_digits_att_nrows->write( H5::IntType(H5::PredType::NATIVE_INT16), &nrows );

}

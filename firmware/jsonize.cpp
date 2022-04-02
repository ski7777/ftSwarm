/*
 * jsonize.cpp
 *
 *  Created on: 14.11.2021
 *      Author: Stefan
 */

#include "jsonize.h"

JSONize::JSONize( httpd_req_t *req ) {
  _req = req;
}

void JSONize::newObject( JSONObject_t object ) {

  char line[50];

  if ( (lastObject == object) ||
     ( ( lastObject == JSONVariable) && (object = JSONArray) )
     ) {
    httpd_resp_sendstr_chunk( _req, "," );
  }

  lastObject = object;
}

void JSONize::closeObject() {

  uint8_t len = strlen(tabs) ;
  if (len>0) { tabs[len-1] = '\0'; }
}

void JSONize::startArray( const char *identifier) {

  newObject(JSONArray);

  if (identifier) {
    text2string( strdup(identifier) );
    assign();
  }
  httpd_resp_sendstr_chunk( _req, "[" );
}

void JSONize::endArray( ) {

  httpd_resp_sendstr_chunk( _req, "]" );
  closeObject();

}

void JSONize::startObject( ) {

  newObject(JSONObject);

  httpd_resp_sendstr_chunk( _req, "{" );
}

void JSONize::endObject( ) {

  httpd_resp_sendstr_chunk( _req, "}" );
  lastObject=JSONObject;
  closeObject();

}

void JSONize::assign( ) {
  httpd_resp_sendstr_chunk( _req, ":" );
}

void JSONize::text2string( char *t ) {
  httpd_resp_sendstr_chunk( _req, "\"" );
  httpd_resp_sendstr_chunk( _req, t );
  httpd_resp_sendstr_chunk( _req, "\"" );
}

void JSONize::variable( const char *identifier, char *value) {

  newObject(JSONVariable);

  text2string( strdup(identifier) );
  assign();
  text2string(value);

}

void JSONize::variable( const char *identifier, const char *value) {
  variable(identifier, strdup(value));
}

void JSONize::variable( const char *identifier, uint32_t i ) {

  char value[10];

  newObject(JSONVariable);

  text2string( strdup(identifier) );
  assign();

  sprintf(value, "%lu", (unsigned long) i );
  httpd_resp_sendstr_chunk( _req, value );

}

void JSONize::variableX( const char *identifier, uint32_t i ) {

  char value[10];

  newObject(JSONVariable);

  text2string( strdup(identifier) );
  assign();

  sprintf(value, "\"%06lx\"", (long) i );
  httpd_resp_sendstr_chunk( _req, value );

}

void JSONize::variableVolt( const char *identifier, float f ) {

  char value[20];

  newObject(JSONVariable);

  text2string( strdup(identifier) );
  assign();

  sprintf(value, "%0.3f V", f );
  text2string( value );

}

void JSONize::variableOhm( const char *identifier, float f ) {

  char value[20];

  newObject(JSONVariable);

  text2string( strdup(identifier) );
  assign();

  uint x = f;

  sprintf(value, "%u Ohm", x );
  text2string( value );

}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
void JSONize::variableCelcius( const char *identifier, float f ) {

  char value[20];

  newObject(JSONVariable);

  text2string( strdup(identifier) );
  assign();

  sprintf(value, "%0.1f °C", f );
  text2string( value );

}

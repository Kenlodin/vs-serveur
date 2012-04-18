/*
 * Chuck.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "Chuck.hh"

Chuck::Chuck()
{
  // TODO Auto-generated constructor stub
  length_ = 0;
  data_ = nullptr;
}

Chuck::Chuck(int length, sf::Int8* data)
{
  length_ = length;
  data_ = data;
}

Chuck::~Chuck()
{
  // TODO Auto-generated destructor stub
  delete data_;
}

sf::Int8* Chuck::getData() const
{
  return data_;
}

void Chuck::setData(sf::Int8* data)
{
  this->data_ = data;
}

int Chuck::getLength() const
{
  return length_;
}

void Chuck::setLength(int length)
{
  this->length_ = length;
}



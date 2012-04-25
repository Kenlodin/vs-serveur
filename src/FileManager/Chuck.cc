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
  subChunk_ = nullptr;
}

Chuck::~Chuck()
{
  // TODO Auto-generated destructor stub
  if (subChunk_)
  {
    if (subChunk_->data)
      free(subChunk_->data);
    free(subChunk_);
  }
}

void Chuck::clear()
{
  if (subChunk_)
    {
      if (subChunk_->data)
        free(subChunk_->data);
      subChunk_->data = nullptr;
      free(subChunk_);
      subChunk_ = nullptr;
    }
}




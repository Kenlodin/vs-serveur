/*
 * Chuck.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "Chuck.hh"

Chunk::Chunk()
{
  subChunk_ = nullptr;
}

Chunk::~Chunk()
{
  if (subChunk_)
  {
    if (subChunk_->data)
      free(subChunk_->data);
    free(subChunk_);
  }
}

void Chunk::clear()
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




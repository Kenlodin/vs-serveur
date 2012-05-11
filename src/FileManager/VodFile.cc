/*
 * File.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "VodFile.hh"

VodFile::VodFile(int videoId)
{
  COUTDEBUG("Init Vod n° :" << videoId);
  name_ = "movie/" + tools::toString(videoId) + ".avi"; // TODO Filetype
  currentPacket_ = new Chunk();
  currentPacket_->subChunk_ = nullptr;
  nbpacket_ = 0;
  maxnbpacket_ = 0;
  offset_ = 0;
  fd_ = open(name_.c_str(), O_RDONLY);
  if (fd_ == -1)
  {
    isValid_ = 0;
    COUTDEBUG("Unable to open : " << name_);
  }
  else
  {
    isValid_ = 1;
    loadChunk(avifile::e_opcode::AVI_RIFF_AVI);
    loadChunk(avifile::e_opcode::AVI_LIST_HDRL);
    loadChunk(avifile::e_opcode::AVI_LIST_INFO);
    loadChunk(avifile::e_opcode::AVI_JUNK);
    loadChunk(avifile::e_opcode::AVI_LIST_MOVI);
    loadSubChunk();
  }
  COUTDEBUG("Init Vod done n° :" << videoId);
}

VodFile::~VodFile()
{
  if (fd_ > 0)
    close(fd_);
  for (int i = 0; i < 5; i++)
  {
    if (fileHeader_[i])
    {
      if (fileHeader_[i]->data)
        free(fileHeader_[i]->data);
      free(fileHeader_[i]);
    }
  }
  delete currentPacket_;
}

void VodFile::loadSubChunk()
{
  COUTDEBUG("LoadSubChuck : no:" << nbpacket_ << " offset:" << offset_);
  if (isValid_ == 0)
  {
    COUTDEBUG("LoadSubChunk : BadFile");
    return;
  }
  seekPos_[nbpacket_] = offset_;
  nbpacket_++;
  maxnbpacket_ = MAX(nbpacket_, maxnbpacket_);
  currentPacket_->clear();
  currentPacket_->subChunk_ = reinterpret_cast<avifile::s_sub_chunk*>(malloc(
      sizeof(avifile::s_sub_chunk)));
  read(fd_, currentPacket_->subChunk_, SIZE_SUBCHUNK_HEADER);
  //printf("type:%.4s name:%.4s size:%u\n", chunk->fcc, chunk->name, chunk->size);
  COUTDEBUG("Read:" << currentPacket_->subChunk_->size);
  currentPacket_->subChunk_->data = malloc(
      MOD2(currentPacket_->subChunk_->size));
  read(fd_, currentPacket_->subChunk_->data,
      MOD2(currentPacket_->subChunk_->size));
  offset_ += SIZE_SUBCHUNK_HEADER + currentPacket_->subChunk_->size;
  //+= MOD2(currentPacket_->subChunk->size) + 2 * sizeof(u32);
}

void VodFile::loadChunk(avifile::e_opcode type)
{
  COUTDEBUG("LoadChuck : no:" << type << " offset:" << offset_);
  if (isValid_ == 0)
  {
    COUTDEBUG("LoadChunk : BadFile");
    return;
  }
  fileHeader_[type] = reinterpret_cast<avifile::s_chunk*>(malloc(
      sizeof(avifile::s_chunk)));
  read(fd_, fileHeader_[type], SIZE_CHUNK_HEADER);
  fileHeader_[type]->data = NULL;

  if (fileHeader_[type]->fcc[0] == 'm' && fileHeader_[type]->fcc[1] == 'o'
      && fileHeader_[type]->fcc[1] == 'v' && fileHeader_[type]->fcc[1] == 'i')
  {
    videoLength_ = fileHeader_[type]->size;
  }
  if (type != avifile::e_opcode::AVI_RIFF_AVI
      && type != avifile::e_opcode::AVI_LIST_MOVI)
  {
    fileHeader_[type]->data = malloc(
        fileHeader_[type]->size - sizeof(avifile::u32));
    read(fd_, fileHeader_[type]->data,
        fileHeader_[type]->size - sizeof(avifile::u32));
    offset_ += fileHeader_[type]->size;
  }
  offset_ += SIZE_CHUNK_HEADER;
}

Chunk* VodFile::getPacket(int number)
{
  COUTDEBUG("GetPacket : no:" << videoId_ << " : no:" << nbpacket_);
  if (isValid_ == 0)
  {
    COUTDEBUG("getPacket : BadFile");
    return nullptr;
  }
  actionMutex_.lock();
  if (number > nbpacket_)
    moveUp(number);
  else if (number < nbpacket_)
    moveDown(number);
  actionMutex_.unlock();
  return currentPacket_; // TODO GPb
}

void VodFile::moveUp(int number)
{
  if (isValid_ == 0)
    {
      COUTDEBUG("moveUp : BadFile");
      return;
    }
  offset_ = seekPos_[maxnbpacket_];
  nbpacket_ = maxnbpacket_;
  int nbToLoad = number - maxnbpacket_;
  lseek(fd_, offset_, SEEK_SET);
  for (int i = 0; i < nbToLoad; i++)
  {
    loadSubChunk();
  }
}

void VodFile::moveDown(int number)
{
  if (isValid_ == 0)
    {
      COUTDEBUG("moveDown : BadFile");
      return;
    }
  offset_ = seekPos_[number];
  lseek(fd_, offset_, SEEK_SET);
  nbpacket_ = number;
  loadSubChunk();
}




/*
 * File.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include <core/fileManager/VodFile.hh>

VodFile::VodFile(int videoId)
{
  COUTDEBUG("Init Vod n° :" << videoId);
  name_ = "movie/" + tools::toString(videoId) + ".avi"; // TODO Filetype
  currentPacket_ = new Chunk();
  currentPacket_->subChunk_ = nullptr;
  videoId_ = videoId;
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
  //COUTDEBUG("Init Vod done n° :" << videoId);
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
  //COUTDEBUG("LoadSubChuck : no:" << nbpacket_ << " offset:" << offset_);
  if (isValid_ == 0)
  {
    COUTDEBUG("LoadSubChunk : BadFile");
    return;
  }
  nbpacket_++;
  currentPacket_->clear();
  currentPacket_->subChunk_ = reinterpret_cast<avifile::s_sub_chunk*>(malloc(
      sizeof(avifile::s_sub_chunk)));
  read(fd_, currentPacket_->subChunk_, SIZE_SUBCHUNK_HEADER);
  //printf("type:%.4s size:%u\n", currentPacket_->subChunk_->fcc
  //    , MOD2(currentPacket_->subChunk_->size));
  //COUTDEBUG("Read:" << currentPacket_->subChunk_->size);
  currentPacket_->subChunk_->data = malloc(
      MOD2(currentPacket_->subChunk_->size));
  read(fd_, currentPacket_->subChunk_->data,
      MOD2(currentPacket_->subChunk_->size));
  offset_ += SIZE_SUBCHUNK_HEADER + MOD2(currentPacket_->subChunk_->size);
  //+= MOD2(currentPacket_->subChunk->size) + 2 * sizeof(u32);
  if (nbpacket_ > maxnbpacket_)
  {
    maxnbpacket_ = nbpacket_;
    seekPos_[nbpacket_] = offset_;
  }
}

void VodFile::loadChunk(avifile::e_opcode type)
{
  //COUTDEBUG("LoadChuck : no:" << type << " offset:" << offset_);
  if (isValid_ == 0)
  {
    COUTDEBUG("LoadChunk : BadFile");
    return;
  }
  fileHeader_[type] = reinterpret_cast<avifile::s_chunk*>(malloc(
      sizeof(avifile::s_chunk)));
  read(fd_, fileHeader_[type], SIZE_CHUNK_HEADER);
  //printf("type:%.4s name:%.4s size:%u\n", fileHeader_[type]->fcc
  //    , fileHeader_[type]->name, fileHeader_[type]->size);
  fileHeader_[type]->data = NULL;

  if (fileHeader_[type]->fcc[0] == 'm' && fileHeader_[type]->fcc[1] == 'o'
      && fileHeader_[type]->fcc[1] == 'v' && fileHeader_[type]->fcc[1] == 'i')
  {
    videoLength_ = fileHeader_[type]->size;
    //printf("Set movi size at %d\n", videoLength_);
  }
  if (type != avifile::e_opcode::AVI_RIFF_AVI
      && type != avifile::e_opcode::AVI_LIST_MOVI)
  {
    fileHeader_[type]->data = malloc(
        fileHeader_[type]->size - sizeof(avifile::u32));
    read(fd_, fileHeader_[type]->data,
        fileHeader_[type]->size - sizeof(avifile::u32));
    offset_ += fileHeader_[type]->size - sizeof(avifile::u32);
  }
  offset_ += SIZE_CHUNK_HEADER;
  seekPos_[nbpacket_] = offset_;
}

Chunk* VodFile::getElement(int number)
{
  //COUTDEBUG("GetPacket : no:" << videoId_ << " : no:" << number);
  if (isValid_ == 0)
  {
    COUTDEBUG("getPacket : BadFile");
    return nullptr;
  }
  Chunk *result;
  actionMutex_.lock();
  if (number > maxnbpacket_ - 1)// Current_load = nbpacket_ - 1
    moveUp(number);
  else // Already parse
    moveDown(number);
  actionMutex_.unlock();
  result = new Chunk(*currentPacket_);
  return result;
}

void VodFile::moveUp(int number)
{
  if (isValid_ == 0)
    {
      COUTDEBUG("moveUp : BadFile");
      return;
    }
  //COUTDEBUG("MoveUp : from : " << nbpacket_ - 1 << "to : " << number);
  offset_ = seekPos_[maxnbpacket_];
  nbpacket_ = maxnbpacket_;
  int nbToLoad = number - maxnbpacket_;
  lseek(fd_, offset_, SEEK_SET);
  for (int i = 0; i <= nbToLoad; i++)
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
  //COUTDEBUG("MoveUp : from : " << nbpacket_ - 1 << "to : " << number);
  offset_ = seekPos_[number];
  lseek(fd_, offset_, SEEK_SET);
  nbpacket_ = number;
  loadSubChunk();
}


void VodFile::setElement(int number, Chunk* element)
{
  return; // TODO
}

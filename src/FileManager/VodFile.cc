/*
 * File.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "VodFile.hh"

VodFile::VodFile()
{
  // TODO Auto-generated constructor stub
  fd_ = -1;
  name_ = "";
  nbpacket_ = 0;
  fd_ = open("toto.avi", O_RDONLY); //TODO Name
  if (fd_ == -1) //TODO Error
    exit(1);
  loadChunk(OPCODE_RIFF_AVI);
  loadChunk(OPCODE_LIST_HDRL);
  loadChunk(OPCODE_LIST_INFO);
  loadChunk(OPCODE_JUNK);
  loadChunk(OPCODE_LIST_MOVI);
}

VodFile::VodFile(int videoId)
{
  videoId_ = videoId;
  fd_ = -1;
  name_ = "";
  nbpacket_ = 0;
}

VodFile::~VodFile()
{
  // TODO Auto-generated destructor stub
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
}

void VodFile::loadSubChunk()
{
  seekPos_[nbpacket_] = offset_;
  nbpacket_++;
  maxnbpacket_ = MAX(nbpacket_, maxnbpacket_);
  currentPacket_->clear();
  currentPacket_->subChunk_ = reinterpret_cast<Chuck::s_sub_chunk*>(malloc(sizeof(Chuck::s_sub_chunk)));
  read(fd_, currentPacket_->subChunk_, SIZE_SUBCHUNK_HEADER);
  currentPacket_->subChunk_->data = malloc(MOD2(currentPacket_->subChunk_->size));
  read(fd_, currentPacket_->subChunk_->data,
      MOD2(currentPacket_->subChunk_->size));
  offset_ += SIZE_SUBCHUNK_HEADER + currentPacket_->subChunk_->size;
  //+= MOD2(currentPacket_->subChunk->size) + 2 * sizeof(u32);
}


void VodFile::loadChunk(e_opcode type)
{
  fileHeader_[type] = reinterpret_cast<s_chunk*>(malloc(sizeof(s_chunk)));
  read(fd_, fileHeader_[type], SIZE_CHUNK_HEADER);
  fileHeader_[type]->data = NULL;

  if (fileHeader_[type]->fcc[0] == 'm' && fileHeader_[type]->fcc[1] == 'o'
      && fileHeader_[type]->fcc[1] == 'v' && fileHeader_[type]->fcc[1] == 'i')
  {
    videoLength_ = fileHeader_[type]->size;
  }
  if (type == OPCODE_RIFF_AVI || type == OPCODE_LIST_MOVI)
  {
    fileHeader_[type]->data = malloc(fileHeader_[type]->size - sizeof(u32));
    read(fd_, fileHeader_[type]->data, fileHeader_[type]->size - sizeof(u32));
    offset_ += fileHeader_[type]->size;
  }
  offset_ += SIZE_CHUNK_HEADER;
}

std::string VodFile::getName() const
{
  return name_;
}

VodFile::s_chunk* const* VodFile::getFileHeader() const
{
  return fileHeader_;
}

Chuck* VodFile::getPacket(int number)
{
  if (number > nbpacket_)
    moveUp(number);
  else if (number < nbpacket_)
    moveDown(number);
  return currentPacket_;
}

void VodFile::moveUp(int number)
{
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
  offset_ = seekPos_[number];
  lseek(fd_, offset_, SEEK_SET);
  nbpacket_ = number;
  loadSubChunk();
}


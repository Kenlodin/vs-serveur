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
}

std::string VodFile::getName() const
{
  return name_;
}

void VodFile::setName(std::string name)
{
  this->name_ = name;
}

int VodFile::getNbpacket() const
{
  return nbpacket_;
}

void VodFile::setNbpacket(int nbpacket)
{
  this->nbpacket_ = nbpacket;
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
  //TODO
}

void VodFile::moveDown(int number)
{
  //TODO
}

